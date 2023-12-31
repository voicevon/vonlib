#include "mqtt_subscriber_manager.h"
#include "von/utility/logger.h"
#include "../g_var.h"


static bool __debug_mode = false;
static MqttSubscriberBase* __all_subscribers[20];
static int __subscriber_id = 0;

void gs_MqttSubscriberManager::Init(bool debug_mode){
    __subscriber_id = 0;  // For the case: reconnecting, resubscribe,
    __debug_mode = debug_mode;
    g_mqttClient.onSubscribe(this->onMqttSubscribe);
    g_mqttClient.onUnsubscribe(this->onMqttUnsubscribe);
    g_mqttClient.onMessage(this->onMqttMessage);
}

void gs_MqttSubscriberManager::ReSubscribeAll(){
    const char* mqtt_topic;
    for (int i=0; i<__subscriber_id; i++){
        mqtt_topic = __all_subscribers[i]->GetMqttTopic()->c_str();
        g_mqttClient.subscribe(mqtt_topic, 2);
    }

}

void gs_MqttSubscriberManager::onMqttSubscribe(uint16_t packetId, uint8_t qos) {
    if (__debug_mode){
        Serial.println("[Info] wifi_mqtt_client.cpp   onMqttSubscribe()   Subscribe acknowledged.");
        Serial.print("  packetId: ");
        Serial.println(packetId);
        Serial.print("  qos: ");
        Serial.println(qos);
    }
}

void gs_MqttSubscriberManager::onMqttUnsubscribe(uint16_t packetId) {
	Serial.println("Unsubscribe acknowledged.");
	Serial.print("  packetId: ");
	Serial.println(packetId);
}

void gs_MqttSubscriberManager::onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
    if (__debug_mode){
        Serial.println("onMqttMessage().");
        Serial.print("  topic: ");
        Serial.println(topic);
        Serial.print("  paylod: ");
        Serial.println(payload);
        Serial.print("  qos: ");
        Serial.println(properties.qos);
        Serial.print("  dup: ");
        Serial.println(properties.dup);
        Serial.print("  retain: ");
        Serial.println(properties.retain);
        Serial.print("  len: ");
        Serial.println(len);
        Serial.print("  index: ");
        Serial.println(index);
        Serial.print("  total: ");
        Serial.println(total);
    }
    MqttSubscriberBase* subscriber =  gs_MqttSubscriberManager::__find_subscriber(topic);
    subscriber->onGot_MqttMessage_piece(topic, payload,len,index,total);
}


MqttSubscriberBase* gs_MqttSubscriberManager::__find_subscriber(const char* topic){

    MqttSubscriberBase* subscriber;
    // Logger::Debug("gs_MqttSubscriberManager::on_mqtt_client_received_message()");
    for (int i=0; i<__subscriber_id; i++){
        // try to find who is subscribing this topic
        subscriber = __all_subscribers[i];
        // if (subscriber->IsTopicEqualTo(topic)){
        if (subscriber->GetMqttTopic()->IsEqualTo(topic)){
            return subscriber;
        }
    }
    Logger::Error("gs_MqttSubscriberManager::on_mqtt_client_received_message().  Out of my managerment");
    Logger::Print("mqtt topic", topic);
    return nullptr;
}

void gs_MqttSubscriberManager::AddSubscriber(const char* mqtt_topic, MqttSubscriberBase* subscriber){
    __all_subscribers[__subscriber_id] = subscriber;
    subscriber->Init(mqtt_topic, __subscriber_id);
    g_mqttClient.subscribe(mqtt_topic, 2);

    __subscriber_id++;
    if (__subscriber_id >=20){
        Logger::Warn(" gs_MqttSubscriberManager::AddSubscriber   will overflow if put another subscriber");
    }
}



void gs_MqttSubscriberManager::mqtt_subscribe(const char* topic){
    g_mqttClient.subscribe(topic, 2);
}

void gs_MqttSubscriberManager::mqtt_subscribe_with_topicIndex(const char* topic, int subsciber_id){
    g_mqttClient.subscribe(topic, 2);
}

// const char* mqtt_read_first_topic(){

// }

int gs_MqttSubscriberManager::mqtt_get_payload_length(int subsciber_id){
    return __all_subscribers[subsciber_id]->GetPayloadLength();
}

const char* gs_MqttSubscriberManager::mqtt_read_payload(int subsciber_id){
    return  __all_subscribers[subsciber_id]->ReadPayload_as_string();
}

void gs_MqttSubscriberManager::mqtt_release_buffer(int subsciber_id){

}
