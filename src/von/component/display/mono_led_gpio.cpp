#include "mono_led_gpio.h"
#include "von/utility/logger.h"
// Led::Led(uint8_t id, uint8_t pin, uint8_t turn_on_level):BinaryOutput_GPIO(id, pin, turn_on_level){
    
// }


void Mono_Led_GPIO::SetState(EnumState new_state){
    switch (__state){
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
