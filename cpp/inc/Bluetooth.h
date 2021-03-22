#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "AT.h"
#ifdef __cplusplus
}
#endif

#ifndef __BLUETOOTH_H_
#define __BLUETOOTH_H_

class Bluetooth
{
private: // Vars.
    //TODO: Add private rars.
    uint8_t deviceAddress[6] = {0x11,0x11,0x11,0x11,0x11,0x11};
    uint8_t deviceName[23]  = {0};

    uint16_t gapServiceHandle;
    uint16_t gapCharHandle;
    uint16_t gapCharAppearanceHandle;

    AT serial;

    uint16_t serviceHandle;
    uint16_t charHandle;
    uint16_t descHandle;

    uint8_t serviceID[2] = {0xe0, 0xaa};
    uint8_t charID[2] = {0xe1, 0xaa};

    


public: // Vars.
    //TODO: Add public vars.
private: // Funcs.
    //TODO: Add private funcs.
public: /// Funcs.
    //TODO: Add public funcs.

    void InitDevice();
    void AddService();
    void Tick();

public:
    Bluetooth(  char *name );
    ~Bluetooth();
};




#endif
