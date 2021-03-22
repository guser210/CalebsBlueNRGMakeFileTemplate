
#include <stdio.h>
#ifndef __AT_H_
#define __AT_H_

class AT
{
private: // Vars.
    //TODO: Add private rars.
    const static uint8_t maxSize = 100;
    int bufferCounter = 0;
    uint8_t buffer[maxSize] = {0};
public: // Vars.
    //TODO: Add public vars.
    uint8_t message[maxSize] = {0};
    bool newMessage = false;
private: // Funcs.
    //TODO: Add private funcs.
public: /// Funcs.
    //TODO: Add public funcs.
    void InitUart(uint32_t speed);
    void AddChar(char c);
    void SendMessage(char *msg, ...);
public:
    AT(    /* args */    );
    ~AT();
};




#endif
