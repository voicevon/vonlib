#include <WiFi.h>
#include "task_wifi.h"

#include "esp_wifi.h"
// #include "von/c/utility/logger/logger.hpp"
#include "von/utility/logger.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"


// extern TaskHandle_t task_Mqtt;
// static bool __control_mqtt_task;
static bool __IsConnected = false;

int state = 0;   // 0=idle, 1= connecting 2= connected, 3 = failed 

void wifi_scan_ap(){
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    if (n == 0) {
        Logger::Info("wifi_scan_ap()  no networks found");
    } else {
        Logger::Info("wifi_scan_ap()   networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(":\tSSID ");
            Serial.print(WiFi.SSID(i));
            Serial.print("\t RSSI(");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
        delay(10);
    }
    }
    Serial.println("");
}

static void onWiFiEvent(WiFiEvent_t event) {
    switch(event) {
    case SYSTEM_EVENT_WIFI_READY:
        Logger::Info("onWiFiEvent::SYSTEM_EVENT_WIFI_READY");
        break;
    case SYSTEM_EVENT_SCAN_DONE:
        Logger::Info("onWiFiEvent::SYSTEM_EVENT_SCAN_DONE");
        break;
    case SYSTEM_EVENT_STA_START:
        Logger::Info("onWiFiEvent::SYSTEM_EVENT_STA_START");
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        Logger::Info("onWiFiEvent::SYSTEM_EVENT_STA_CONNECTED");
        break;

    case SYSTEM_EVENT_STA_GOT_IP:
        Logger::Info("onWiFiEvent::SYSTEM_EVENT_STA_GOT_IP");
        // logPrint("Local IP address: ", WiFi.localIP());
        Serial.print("Local ip address is: \t");
        Serial.println(WiFi.localIP());
        // xTimerStart(mqttReconnectTimer,0);
        // if (__control_mqtt_task){
        //     vTaskResume(task_Mqtt);
        // }
        __IsConnected = true;
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        // if(__control_mqtt_task){
        //     vTaskSuspend(task_Mqtt);
        // }
        Logger::Warn("onWiFiEvent:: WifiEvent== SYSTEM_EVENT_STA_DISCONNECTED reconnecting");
        __IsConnected = false;
        WiFi.reconnect();   // simpler than statemachine?
        break;

    default:
        Logger::Warn(("onWiFiEvent:: Unknown event ID     --->" + String(event)).c_str());
      break;
    }
}

/// @brief Will auto reconnect if lost connnection.
void ConnectToWifi_FakeTask(void* parameters) {
    WiFiTask_config * task_config = (WiFiTask_config*)(parameters);
    // __control_mqtt_task = task_config->ControlMqttTask;
    WiFi.onEvent(onWiFiEvent);
    Logger::Info("ConnectToWifi_FakeTask Connecting to WiFi..");
    Logger::Print("wifi_ssid", task_config->ssid);
    // Logger::Print("wifi_password", wifi_credential->password);
    WiFi.mode(WIFI_STA);   // cause brown-out, why?
    WiFi.disconnect();       //disconnect from an AP if it was previously connected     
    ESP_ERROR_CHECK(esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_11B |WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N));
	WiFi.begin(task_config->ssid, task_config->password);
    if (task_config->Asyncconnection) return;
    while (!__IsConnected){
        vTaskDelay(1);
    }

}




// void TaskWiFi(void* parameter){
//     WiFi.onEvent(onWiFiEvent);
//     while (true){
//         // WiFi.status()
//         if(state==0){
//             connectToWifi();
//             state = 1;
//         }else if(state ==1){
//             bool timeout = false;
//             if (timeout){
//                 state = 3;
//             }
//         }
//         vTaskDelay(1000);
//     }

// }