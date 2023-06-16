#pragma once
#include "mqtt_subscriber_base.h"
#include "AsyncMqttClient.h"


class gs_MqttSubscriberManager{
    public:
        static gs_MqttSubscriberManager& Instance(){
            static gs_MqttSubscriberManager __instance;
            return __instance;
        };
        void Init(bool debug_mode);
        void AddSubscriber(const char* mqtt_topic, MqttSubscriberBase* subscriber);
        // void on_mqtt_client_received_message(char* topic, char* payload,  size_t payload_len);
        // void on_mqtt_client_received_message(char* topic, char* payload,  size_t len, size_t index, size_t total);
        
        static void mqtt_subscribe(const char* topic);
        static void mqtt_subscribe_with_topicIndex(const char* topic, int topic_id);
        static int mqtt_read_payload(const int topic_id, char* payload);
        static void mqtt_release_buffer(const int topic_id);

    private:
        static MqttSubscriberBase* __find_subscriber(const char* topic);
        static void onMqttSubscribe(uint16_t packetId, uint8_t qos) ;
        static void onMqttUnsubscribe(uint16_t packetId) ;
        static void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) ;

};