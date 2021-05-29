// Universidad del Valle de Guatemala
// Electronica digital 2 - seccion 20
// Jorge Castillo - 18209
// Proyecto 4

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

//***************************************************************
//VARIABLES
//***************************************************************

uint8_t display = 0;
bool p1;
bool p2;
bool p3;
bool p4;
int d1;
int d2;
int d3;
int d4;
uint32_t enviar;

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
    SysCtlClockSet(SYSCTL_SYSDIV_6|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Habilitar periféricos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);// puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);// puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);// puerto B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);// puerto C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);// puerto A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);// puerto D

    //Habilitar UART1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);// enable clock port C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);// enable clock UART1
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); // config
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

    while (1)
    {
        display = 0;
        if (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0) == 0) //verifica si el primer push button esta presionado
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
            p1 = 1; // para saber que el led se encienda
            d1 = 0b00000001;// dato a mandar en la uart
        }
        else if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0) == 1)
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
            p1 = 0;
            d1 = 0x00;
        }
        if (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) == 0)// push 2
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);
            p2 = 1;
            d2 = 0b00000010;
        }
        else
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
            p2 = 0;
            d2 = 0x00;
        }
        if (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2) == 0)// push 3
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
            p3 = 1;
            d3 = 0b00000100;
        }
        else
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
            p3 = 0;
            d3 = 0x00;
        }
        if (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3) == 0)// push 4
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
            p4 = 1;
            d4 = 0b00001000;
        }
        else
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
            p4 = 0;
            d4 = 0x00;
        }
        disp(); // manda a llamar la funcion para mostrar los parqueos disponibles
        enviar = d1 + d2 + d3 + d4; // se envian los binarios de los 4 parqueos
        UARTCharPut(UART1_BASE, enviar); // funcion para enviar los datos por uart1



    }

}



void disp (void){
    display = p1+p2+p3+p4;
    if(display == 0) {//4 parqueos disponibles
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_5);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_6);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4, GPIO_PIN_0 | GPIO_PIN_1) ;

    }
    else if(display == 1) {//3 parqueos disponibles
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_4 | GPIO_PIN_5);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4, GPIO_PIN_0) ;
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_5 | GPIO_PIN_6);
    }
    else if(display == 2){// 2 parqueos disponibles
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5,  GPIO_PIN_4 | GPIO_PIN_5);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4, GPIO_PIN_0 | GPIO_PIN_4) ;
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_5) ;
    }
    else if (display == 3){// 1 parqueo disponible
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_5);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_6);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4, 0) ;
    }
    else if (display == 4){// 0 parqueos disponibles
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_4 | GPIO_PIN_5);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1 | GPIO_PIN_4, GPIO_PIN_1 | GPIO_PIN_4) ;
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_5 | GPIO_PIN_6);
    }
    else{// reset de leds
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5, 0);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4, 0) ;
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6, 0);
    }
}

