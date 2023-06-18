#include "mono_led_gpio.h"
#include "von/utility/logger.h"



void Mono_Led_GPIO::SetState(EnumState new_state){
    switch (new_state){
        case TURN_ON:
            this->TurnOn();
            break;
        case TURN_OFF:
            this->TurnOff();
            break;
        case FLASH_1Hz:
            break;
        case FLASH_2Hz:
            break;
        default:
            Logger::Error("Mono_Led_GPIO::SetState()  Unknown new_state");
            Logger::Print("new_state", new_state);
            Logger::Halt("");
            break;
    }
}

void Mono_Led_GPIO::SpinOnce(){
    switch (__state){
        case FLASH_1Hz:
            break;
        default:
            break;
    }
}
