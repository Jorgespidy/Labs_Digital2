/*
 * File:   master.c
 * Author: Jorge Castillo Palomo - 18209
 * Miniproyecto 1 "Comunicacion SPI, main del master" 
 */


//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI.h"

//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = XT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000

uint8_t slave1;
//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);

//******************************************************************************
// Configuración
//******************************************************************************

void main(void) {
    setup();
    while (1){
        PORTBbits.RB0 = 0;
        __delay_ms(1);
        spiWrite(1);
        slave1 = spiRead();
        PORTD = slave1;
        __delay_ms(1);
        PORTBbits.RB0 = 1;
        
    }
}

void setup(void) {
    //Se limpian los tris a usar, los puertos y se setea el anselh
    ANSEL = 0;
    ANSELH = 0;
    TRISC = 0b00010000;
    TRISB = 0;
    TRISA = 0;
    TRISD = 0;
    PORTB = 0b00000111; //slave select 1, 2 & 3
    PORTA = 0;
    PORTC = 0;
    PORTD = 0b10101010;
    
   
    
     spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
}
