#include "mqtt_subscriber_base.h"
#include "von/utility/logger.h"


void MqttSubscriberBase::Init(const char* mqtt_topic, int id){
    _mqtt_topic.CopyFrom(mqtt_topic);
    __my_id = id;
}

void MqttSubscriberBase::onGot_MqttMessage_piece(char* topic, char* payload,  size_t len, size_t index, size_t total){

	if (index == 0) {
        __mqttPayloadBuffer.clear();
    }
    for (int i=0; i<len; i++){
        __mqttPayloadBuffer.push_back(*(payload+i));
    }

	if (index + len != total) return;  // return if payload buffer is not complete
    
	// here, our mqttPayloadBuffer is compplete
    __mqttPayloadBuffer.push_back(char(0x00));
    // Logger::Info("MqttSubscriberBase::onGot_MqttMessage_piece() --> got whole content");
    // Logger::Print("", &__mqttPayloadBuffer[0]);
    _onGot_MqttMessage_whole(&__mqttPayloadBuffer[0], __mqttPayloadBuffer.size());
    if (__got_mqttmessage_service_function == nullptr){
        Logger::Warn("MqttSubscriberBase::  __got_mqttmessage_service_function  is nullptr");
    }else{
        __got_mqttmessage_service_function(this);
    }

}

const char* MqttSubscriberBase::ReadPayload_as_string(){
    // Logger::Debug("MqttSubscriberBase::ReadPayload_as_string()");
    // Logger::Print(this->_mqtt_topic.c_str(), this->GetId());
    // Logger::Print("payload_length", this->GetPayloadLength());
    // Logger::Print("payload ", &__mqttPayloadBuffer[0]);
    return &__mqttPayloadBuffer[0];
}

