#include "task_helper.h"
#include "von/utility/logger.h"
#include "g_var.h"

#define MQTT_HOST "voicevon.vicp.io"
#define MQTT_PORT 1883
#define MQTT_UID "von"
#define MQTT_PASSWORD "von1970"


static TimerHandle_t mqttReconnectTimer;
static  MqttTaskHelper::EnumState __ConnectionState = MqttTaskHelper::EnumState::DISCONNECTED;

MqttTaskHelper::EnumState MqttTaskHelper::GetState(){
    return __ConnectionState;
}

void MqttTaskHelper::ConnectToBroker() {
	Logger::Info ("Connecting to MQTT...");
    __ConnectionState = EnumState::CONNECTING;
    __started_at = millis();

	g_mqttClient.connect();
}

void MqttTaskHelper::DisconnectFromBroker(){
    g_mqttClient.disconnect();
}

void MqttTaskHelper::Init(){
    __ConnectionState = EnumState::DISCONNECTED;
    g_mqttClient.onConnect(this->onMqttConnected);
    g_mqttClient.onDisconnect(this->onMqttDisconnect);

    g_mqttClient.onPublish(this->onMqttPublish);

    g_mqttClient.setServer(MQTT_HOST, MQTT_PORT);
	g_mqttClient.setCredentials(MQTT_UID, MQTT_PASSWORD);

}    

//TODO:  subsribe topics after:  disconnected --> connected.
void MqttTaskHelper::onMqttConnected(bool sessionPresent) {
    __ConnectionState = EnumState::CONNECTED;
    Logger::Info("MQTT event:  onMqttConnected()");
    Serial.print("Session present: ");
    Serial.print(sessionPresent);
    Serial.print("\tmqtt client id:   ");
    Serial.print(g_mqttClient.getClientId());
    Serial.println();

    bool test_publish = false;
    if (test_publish){
        uint16_t packetIdSub = g_mqttClient.subscribe("test/lol", 2);
        Serial.print("Subscribing at QoS 2, packetId: ");
        Serial.println(packetIdSub);
        g_mqttClient.publish("test/lol", 0, true, "test 1");
        Serial.println("Publishing at QoS 0");
        uint16_t packetIdPub1 = g_mqttClient.publish("test/lol", 1, true, "test 2");
        Serial.print("Publishing at QoS 1, packetId: ");
        Serial.println(packetIdPub1);
        uint16_t packetIdPub2 = g_mqttClient.publish("test/lol", 2, true, "test 3");
        Serial.print("Publishing at QoS 2, packetId: ");
        Serial.println(packetIdPub2);
    }
    // If you want , add app's callback to subscribe.
    // app_mqtt_subscribe();
    // MqttTaskHelper::mqtt_is_connected = true;
}

void MqttTaskHelper::onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
    __ConnectionState = EnumState::DISCONNECTED;
    Logger::Warn("MQTT event: onMqttDisconnect()");
    String reason_str = "   reason = ";
    if (reason == AsyncMqttClientDisconnectReason::TCP_DISCONNECTED) reason_str.concat("TCP_DISCONNECTED"); 
    if (reason == AsyncMqttClientDisconnectReason::MQTT_UNACCEPTABLE_PROTOCOL_VERSION) reason_str.concat("MQTT_UNACCEPTABLE_PROTOCOL_VERSION"); 
    if (reason == AsyncMqttClientDisconnectReason::MQTT_IDENTIFIER_REJECTED) reason_str.concat("MQTT_IDENTIFIER_REJECTED"); 
    if (reason == AsyncMqttClientDisconnectReason::MQTT_SERVER_UNAVAILABLE) reason_str.concat("MQTT_SERVER_UNAVAILABLE"); 
    if (reason == AsyncMqttClientDisconnectReason::MQTT_MALFORMED_CREDENTIALS) reason_str.concat("MQTT_MALFORMED_CREDENTIALS"); 
    if (reason == AsyncMqttClientDisconnectReason::MQTT_NOT_AUTHORIZED) reason_str.concat("MQTT_NOT_AUTHORIZED"); 
    if (reason == AsyncMqttClientDisconnectReason::ESP8266_NOT_ENOUGH_SPACE) reason_str.concat("ESP8266_NOT_ENOUGH_SPACE"); 
    if (reason == AsyncMqttClientDisconnectReason::TLS_BAD_FINGERPRINT) reason_str.concat("TLS_BAD_FINGERPRINT"); 
    Logger::Print("reason code",(uint8_t)reason);
    Logger::Print("reason", reason_str.c_str());

	// if (WiFi.isConnected()) {
	// 	xTimerStart(mqttReconnectTimer, 0);
	// }
}


void MqttTaskHelper::onMqttPublish(uint16_t packetId) {
	bool debug=false;
	if (debug){
		Serial.print("Publish acknowledged.");
		Serial.print("  packetId: ");
		Serial.println(packetId);
	}
}

// void MqttTaskHelper::mqtt_publish(const char* topic, const char* payload){
//     g_mqttClient.publish(topic, 2,true, payload);
// }
