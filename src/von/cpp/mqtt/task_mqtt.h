#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern void TaskMqtt(void* parameter);
extern TaskHandle_t task_Mqtt;

