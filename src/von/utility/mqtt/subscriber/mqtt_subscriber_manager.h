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
        static void mqtt_subscribe(const char* topic);
        static void mqtt_subscribe_with_topicIndex(const char* topic, int subsciber_id);
        static int mqtt_get_payload_length( int subsciber_id);
        static const char* mqtt_read_payload( int subsciber_id);
        static void mqtt_release_buffer( int subsciber_id);

    private:
        static MqttSubscriberBase* __find_subscriber(const char* topic);
        static void onMqttSubscribe(uint16_t packetId, uint8_t qos) ;
        static void onMqttUnsubscribe(uint16_t packetId) ;
        static void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) ;

};