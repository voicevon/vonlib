#pragma once
#include "stdint.h"

#include "von/utility/mqtt/mqtt_topic.h"
#include "von/utility/mqtt/g_var.h"

class MqttTaskHelper{
    public:
        enum EnumState{
            // IDLE = 0,
            CONNECTING,
            CONNECTED,
            DISCONNECTED,
        };
        static MqttTaskHelper& Instance(){
            static MqttTaskHelper __instance;
            return __instance;
        }
        // static void mqtt_publish(const char* topic, const char* payload);

        EnumState GetState();
        // int Get_Payload_bits(){return 1;};
        void ConnectToBroker();
        void DisconnectFromBroker();
        void Init();
        uint32_t passed_ms(){return millis() - __started_at;};

    private:
        MqttTaskHelper(){};
        static bool mqtt_is_connected;
        // static MqttTopic mqtt_topics[20];

        uint32_t __started_at = 0;

        static void onMqttConnected(bool sessionPresent);
        static void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) ;
        static void onMqttPublish(uint16_t packetId) ;
};

