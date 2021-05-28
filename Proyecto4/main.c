// Universidad del Valle de Guatemala
// Electronica digital 2 - seccion 20
// Jorge Castillo - 18209
// Proyecto 4

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"inc/tm4c123gh6pm.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/timer.h"
#include"driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"

//***************************************************************
//VARIABLES
//***************************************************************

char display = 0;

//***************************************************************
//FUNCIONES PROTOTIPO
//***************************************************************
void disp (void);

 //***************************************************************
 //MAIN
 //***************************************************************
int main(void)
{
    //Reloj a 40MHz
    SysCtlClockSet(SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_5);

    //Habilitar periféricos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);// puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);// puerto B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);// puerto C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);// puerto D


    //Habilitar UART1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);// enable clock port C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);// enable clock UART1
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE); // config
    UARTEnable(UART1_BASE);


    //Salida de LEDs
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4);

    //Salida de Display
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_5);

    //Entrada de Push buttons
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    //Pullup de los push buttons
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


    while(1){
        display = 0;
        if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0) == 0){
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 8);
            display ++;
            UARTCharPut(UART1_BASE, '1');
        }
        else if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0) == 1){
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
            UARTCharPut(UART1_BASE, '2');
            }
        if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) == 0){
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 10);
            display ++;
            UARTCharPut(UART1_BASE, '3');
        }
        else if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) == 1){
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
            UARTCharPut(UART1_BASE, '4');
            }
        if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2) == 0){
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 80);
            display ++;
            UARTCharPut(UART1_BASE, '5');
        }
        else if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2) == 1){
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
            UARTCharPut(UART1_BASE, '6');
            }
        if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3) == 0){
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 40);
            display ++;
            UARTCharPut(UART1_BASE, '7');
        }
        else if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3) == 1){
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
            UARTCharPut(UART1_BASE, '8');
            }

        }

}



void disp (void){
    if(display == '1') {
        //poner numero 3
    }
    else if(display == '2'){
        //poner numero 2
    }
}

