#pragma once
#include "stdint.h"

#include "von/utility/mqtt/mqtt_topic.h"
#include "von/utility/mqtt/g_var.h"

class MqttTaskHelper{
    public:
        enum EnumState{
            // IDLE = 0,
            SUSPENDED,
            DISCONNECTED,
            CONNECTING,
            CONNECTED,
            SUBSCRIBED,
        };
        static MqttTaskHelper& Instance(){
            static MqttTaskHelper __instance;
            return __instance;
        }
        static void StatemachineSpinOnce();
        EnumState GetState();
        void DisconnectFromBroker();
        void Init();
        void SetStateToSubscribed();

    private:
        MqttTaskHelper(){};
        static bool mqtt_is_connected;

        static void onMqttConnected(bool sessionPresent);
        static void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) ;
        static void onMqttPublish(uint16_t packetId) ;
};

