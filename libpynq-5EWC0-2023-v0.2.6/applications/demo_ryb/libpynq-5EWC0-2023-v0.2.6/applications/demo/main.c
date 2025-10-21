#include <libpynq.h>
#include <stdio.h>
#include <uart.h>
#include "functions.h"
#define 	DISPLAY_HEIGHT   240
#define 	DISPLAY_WIDTH   240

int main(void)
{
    pynq_init();

    display_t display;
    display_init(&display);
    display_set_flip(&display, true, true);
    displayFillScreen(&display, RGB_WHITE);

    switchbox_set_pin(IO_RBPI27, SWB_UART1_RX);
//pmoda 3
    switchbox_set_pin(IO_RBPI28, SWB_UART1_TX);
//pmoda 4
    
    uart_init(UART0);
    uart_init(UART1);
    uart_reset_fifos(UART0);
    uart_reset_fifos(UART1);

uint8_t counter = 2;
uint8_t value1 = 0;
uint8_t value2 = 0;
uint8_t value3 = 0;


while(1){
    if( counter % 2 == 0)
    {
        switchbox_set_pin(IO_RBPI07, SWB_UART0_RX);
        //pmoda 1
        switchbox_set_pin(IO_RBPI29, SWB_UART0_TX);
        //pmoda 2
        sleep_msec(2);
        uart_send(UART0, 1);
        while(!uart_has_data(UART0)); 
        value1 = uart_recv(UART0);
        uart_reset_fifos(UART0);  
    }

    if( counter % 2 == 5)
    {
        switchbox_set_pin(IO_RBPI31, SWB_UART0_RX);
        //pmoda 7 
        switchbox_set_pin(IO_RBPI26, SWB_UART0_TX);
        //pmoda 8
        sleep_msec(2);
        uart_send(UART0, 1);

        while(!uart_has_data(UART0));
        value2 = uart_recv(UART0);
        uart_reset_fifos(UART0);  
    }

    value3 = value1 + value2;
    uart_send(UART1, value3);


    displaying(value1, value2, value3, display);
    switchbox_set_pin(IO_RBPI07, SWB_GPIO);
    switchbox_set_pin(IO_RBPI29, SWB_GPIO);
    switchbox_set_pin(IO_RBPI31, SWB_GPIO);
    switchbox_set_pin(IO_RBPI26, SWB_GPIO);
        
    sleep_msec(500);
}

    display_destroy(&display);
    pynq_destroy();
    return 0;
}
  