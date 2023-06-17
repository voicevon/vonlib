#pragma once
#include "von/basic/c_string/c_string_base.h"

#define MAX_LENGTH_OF_MQTT_TOPIC_CHARS_LENGTH 40

class MqttTopic: public C_String_Base{
    public:
        // MqttTopic(): C_String_Base(__bytes, 40) {};
        MqttTopic(): C_String_Base(__bytes, MAX_LENGTH_OF_MQTT_TOPIC_CHARS_LENGTH) {};
    private:
        char __bytes[MAX_LENGTH_OF_MQTT_TOPIC_CHARS_LENGTH];
};