

// #include "task_mqtt.h"
#include "von/cpp/utility/logger.h"
#include "freertos/FreeRTOS.h"
// #include <AsyncMqttClient.h>
#include "von/cpp/mqtt/task_helper.h"

TaskHandle_t task_Mqtt;


void TaskMqtt(void* parameter){
    MqttTaskHelper::Instance().Init();
    vTaskSuspend(NULL);
    Logger::Info("TaskMqtt is go on from init to loop");
    while(true){
        // int xx = MqttTaskHelper::Instance().Get_Payload_bits();
        // if (xx>0)        
        //     xEventGroupSetBits(my_EventGroup,  EVENT_BIT_MQTT_RX_0);  // set eventbit	
        // // vTaskSuspend(NULL);                                            // suspend myself

        if(MqttTaskHelper::Instance().GetState() == MqttTaskHelper::EnumState::DISCONNECTED){
            MqttTaskHelper::Instance().ConnectToBroker();
        }
        else if(MqttTaskHelper::Instance().GetState() == MqttTaskHelper::EnumState::CONNECTING){
            if (MqttTaskHelper::Instance().passed_ms() > 10000){
                MqttTaskHelper::Instance().DisconnectFromBroker();
                MqttTaskHelper::Instance().ConnectToBroker();
            }
        }
        vTaskDelay(1);
    }
}
