#include "mqtt_subscriber_base.h"

class MqttSubscriber_String: public MqttSubscriberBase{
    public:

    private:
        void onGot_MqttMessage_whole(const char* payload, size_t total_len) override;  

};