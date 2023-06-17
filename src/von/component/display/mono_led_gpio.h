#pragma once

#include "../binary_output_gpio.h"



class Mono_Led_GPIO: public BinaryOutput_GPIO
{
    public:
        enum EnumState{
            TURN_ON = 1,
            TURN_OFF = 2 ,
            FLASH_1Hz = 101,
            FLASH_2Hz = 102,
        };
        Mono_Led_GPIO():BinaryOutput_GPIO(){};   // Is this necessary?
        Mono_Led_GPIO(uint8_t id, uint8_t pin, uint8_t turn_on_level):BinaryOutput_GPIO(id, pin, turn_on_level){};
        // void Flash();
        void SpinOnce();
        void SetState(EnumState new_state);

    protected:

    private:
        EnumState __state;
};

