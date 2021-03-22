#ifdef __cplusplus
extern "C" {
#endif
#include "AT.h"
#include "BlueNRG1_gpio.h"
#include "BlueNRG1_uart.h"
#include <string.h>
#include <stdarg.h>
#include "BlueNRG1_sysCtrl.h"
#include "clock.h"
#ifdef __cplusplus
}
#endif



AT::AT(    /* args */    )
{
}

AT::~AT()
{
}


void AT::InitUart(uint32_t speed){
    SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO | CLOCK_PERIPH_UART, ENABLE);

    GPIO_InitType ig;
    ig.GPIO_HighPwr = DISABLE;
    ig.GPIO_Mode = Serial1_Mode;
    ig.GPIO_Pull = DISABLE;
    ig.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(&ig);
    ig.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(&ig);

    UART_InitType iu;
    iu.UART_BaudRate = speed;
    iu.UART_FifoEnable = ENABLE;
    iu.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
    iu.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
    iu.UART_Parity = UART_Parity_No;
    iu.UART_StopBits = UART_StopBits_1;
    iu.UART_WordLengthReceive = UART_WordLength_8b;
    iu.UART_WordLengthTransmit = UART_WordLength_8b;

    UART_Init(&iu);
    UART_Cmd(ENABLE);
    UART_RxFifoIrqLevelConfig(FIFO_LEV_1_64);

}

void AT::AddChar(char c){
    if ( c == '\r' || c == '\n' || bufferCounter >= maxSize){
        memcpy( message, buffer, maxSize);
        memset(buffer, 0, maxSize);

        newMessage = true;
        bufferCounter = 0;
    }else{
        buffer[bufferCounter++] = c;
    }
}

void AT::SendMessage(char *msg, ...){
    char localBuffer[100];
    
    va_list args;
    va_start(args, msg);

    vsprintf(localBuffer, msg, args);

    va_end(args);

    tClockTime time;
    for( int index = 0; index < strlen(localBuffer); index++){
        time = Clock_Time();
        if( UART_GetFlagStatus(UART_FLAG_TXFF) == SET){
            if( Clock_Time() > time + 500) return;
        }
        UART_SendData(localBuffer[index]);
    }



}