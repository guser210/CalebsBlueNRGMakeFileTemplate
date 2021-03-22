#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "maincpp.h"
#include "AT.h"
#include "bluenrg1_api.h"
#include "clock.h"

#include "ble_config.h"
#include "bluenrg1_stack.h"

#include "Bluetooth.h"
#ifdef __cplusplus
}
#endif


void maincpp(){
    SystemInit();

    Clock_Init();

    BlueNRG_Stack_Initialization(&BlueNRG_Stack_Init_params);

    AT pico;
    pico.InitUart(115200);
    pico.SendMessage("main loop\r");

    Bluetooth ble("guser210 BlueNRG Device");
    ble.InitDevice();
    ble.AddService();
    while(1){

        Clock_Wait(50);

        BTLE_StackTick();

        ble.Tick();

    }
}