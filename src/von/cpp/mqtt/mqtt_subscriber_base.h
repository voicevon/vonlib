#pragma once
#include "stdint.h"
#include "von/cpp/basic/text/mqtt_topic.h"

class MqttSubscriberBase{
    public:
        void SubscribeMqtt(const char* mqtt_topic);
        MqttTopic* GetMqttTopic(){return &_mqtt_topic;};
        virtual void onGot_MqttMessage(const char* payload, uint16_t payload_len){};
        
    protected:
        MqttTopic _mqtt_topic;
};

