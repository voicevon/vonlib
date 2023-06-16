#pragma once
#include "stdint.h"
#include "von/cpp/mqtt/mqtt_topic.h"
#include "stddef.h"  // size_t
#include "vector"

class MqttSubscriberBase{
    public:
        void SubscribeMqtt(const char* mqtt_topic);
        MqttTopic* GetMqttTopic(){return &_mqtt_topic;};

        void onGot_MqttMessage_piece(char* topic, char* payload,  size_t len, size_t index, size_t total); 
        // The payload is variable data. type, I can not dertermin.
        virtual void onGot_MqttMessage_whole(const char* payload, size_t total_len){}; 
        
    protected:
        MqttTopic _mqtt_topic;
		std::vector<char> __mqttPayloadBuffer = {};
};

