/*
 * main.c
 *
 *  Created on: 27 Tem 2026
 *      Author: Stajyer1
 */
#include "xparameters.h"
#include "xil_io.h"		/* veri okuma ve yazma islemleri icin */

#define UART_IP_BASEADDR XPAR_UART_IP_ELA_0_S00_AXI_BASEADDR

#define reg_tx 0x00
#define reg_status 0x08

#define reg_rx 0x04
void uart_send (u8 byte) {			/* u8 8 bitlik data byte degiskeni adinda*/
	Xil_Out32(UART_IP_BASEADDR + reg_tx, byte);			/*ciktiyi hangi registere yazacagimizi secmek icin */
}

u8 uart_receive (void) {
    u32 status;
    do {
        status = Xil_In32(UART_IP_BASEADDR + reg_status);
    } while (status & 0x1);   // K
    return (u8)(Xil_In32(UART_IP_BASEADDR + reg_rx) & 0xFF);
}

int main(void)
{
    u8 data;

    xil_printf("uart echo modunda\r\n");
    while (1)
    {
        data = uart_receive();
        xil_printf("alinan: %c ", data);
        uart_send(data);
    }
}
