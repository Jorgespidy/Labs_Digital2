// Universidad del Valle de Guatemala
// Electronica digital 2 - seccion 20
// Jorge Castillo - 18209


#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"



//***************************************************************
//VARIABLES
//***************************************************************
char estado = 0;
int led;
char dato = 0;
//***************************************************************
//FUNCIONES PROTOTIPO
//***************************************************************
 extern void Timer0IntHandler(void);
 extern void UARTIntHandler(void);

 //***************************************************************
 //MAIN
 //***************************************************************
int main(void)
{
    //Reloj a 40MHz
    SysCtlClockSet(SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_5);

    //Habilitar periférico GPIO F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //Pines de salida

    //Enable del timer 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/2 - 1); //Cargar el valor que contará el temporizador para 0.5 Hz
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler); //Establecer la ISR
    IntEnable(INT_TIMER0A);
    IntMasterEnable();
    TimerEnable(TIMER0_BASE, TIMER_A); //Enable del timer 0

    //Habilitar UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntRegister(UART0_BASE, UARTIntHandler);




}

void Timer0IntHandler(void) {
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    switch(estado){
    case 0:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, led);
        estado++;
        break;
    case 1:
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
        estado = 0;
        break;
    }
}

void UARTIntHandler(){
    UARTIntClear (UART0_BASE, UART_INT_RX);
    dato = UARTCharGet(UART0_BASE);

}


