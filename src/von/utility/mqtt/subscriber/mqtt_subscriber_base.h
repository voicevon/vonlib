#pragma once
#include "stdint.h"
#include "von/utility/mqtt/mqtt_topic.h"
#include "stddef.h"  // size_t
#include "vector"
#include "stdlib.h"  // atoi(), atof(), atoff()

class MqttSubscriberBase{
    public:
        void Init(const char* mqtt_topic, int id);
        MqttTopic* GetMqttTopic(){return &_mqtt_topic;};
        int GetId(){return __my_id;};

        //TODO:  friend class
        void onGot_MqttMessage_piece(char* topic, char* payload,  size_t len, size_t index, size_t total); 

        // The payload is variable data. type, I can not dertermin.
        void SetCallback_onGot_MqttMessage(void (*service_function)(MqttSubscriberBase*)){__got_mqttmessage_service_function=service_function;};
        const int GetPayloadLength(){return __mqttPayloadBuffer.size();};
        const char* ReadPayload_as_string(); //  {return &__mqttPayloadBuffer[0];};
        const int ReadPayload_as_int(){return atoi(&__mqttPayloadBuffer[0]);};
        const double ReadPayload_as_double(){return atof(&__mqttPayloadBuffer[0]);};
        const float ReadPayload_as_float(){return atoff(&__mqttPayloadBuffer[0]);};
        
    protected:
        virtual void _onGot_MqttMessage_whole(const char* payload, size_t total_len){}; 
        MqttTopic _mqtt_topic;
		std::vector<char> __mqttPayloadBuffer = {};
        int __my_id = 0;
        void (*__got_mqttmessage_service_function)(MqttSubscriberBase*) = nullptr;
};

