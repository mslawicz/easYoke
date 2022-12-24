/*
 * main_app.cpp
 *
 *  Created on: Dec 23, 2022
 *      Author: marci
 */

#include "main_app_api.h"
#include "main.h"
#include "custom_stm.h"
#include "custom_app.h"

void mainApp()
{
    static uint32_t cnt = 0;
    static uint8_t batteryLevel = 99;
    static bool notify = false;
    if(cnt++ > 300000)
    {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        if(notify)
        {
            notifyBatteryLevel(batteryLevel);
        }
        else
        {
            updateBatteryLevel(batteryLevel);
        }
        notify = !notify;
        if(batteryLevel-- == 0)
        {
            batteryLevel = 99;
        }
        cnt = 0;
    }
}

