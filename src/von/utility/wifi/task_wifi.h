struct WiFiTask_config {
    char* ssid;
    char* password;
    // bool ControlMqttTask;
    bool Asyncconnection;
};

extern void ConnectToWifi_FakeTask(void* parameter);
