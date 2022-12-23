/*
 * main_app.cpp
 *
 *  Created on: Dec 23, 2022
 *      Author: marci
 */

#include "main_app_api.h"
#include "main.h"
#include "custom_app.h"

void mainApp()
{
    static uint32_t cnt = 0;
    static uint8_t batteryLevel = 99;
    if(cnt++ > 100000)
    {
        HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
        setBatteryLevel(batteryLevel);
        if(batteryLevel-- == 0)
        {
            batteryLevel = 99;
        }
        cnt = 0;
    }
}

