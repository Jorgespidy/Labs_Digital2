/*
 * File:   Slave2.c
 * Author: Jorge Castillo Palomo - 18209
 * Miniproyecto 1 "Comunicacion SPI, main del slave 2" 
 */

//******************************************************************************
// Importación de librerías
//******************************************************************************

#include <xc.h>
#include <stdint.h>
//******************************************************************************
// Palabra de configuración
//******************************************************************************

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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


#define _XTAL_FREQ 8000000
#define Up PORTBbits.RB0
#define Down PORTBbits.RB1

//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);


//******************************************************************************
// Ciclo principal
//******************************************************************************

void main(void) {
    setup();
    while (1) {
        
    }
}

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    //Se limpian los puertos, ansel y triestados a utilizar
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0b00000011;
    TRISC = 0;
    TRISD = 0;
    INTCON = 0b10001000; // GIE & RBIE enable
    IOCB = 0b00000011; // solo activan interrupciones RB0 y RB1
    return;
}
//******************************************************************************
// Interrupciones
//******************************************************************************
void __interrupt() ISR(void) {
    if (INTCONbits.RBIF == 1) {//interrupaciones del contador binario
        if (Up == 1) {//verifica si esta presionado el boton de aumentar contador
            PORTD++;
            INTCONbits.RBIF = 0;
        }
        else{
            INTCONbits.RBIF = 0;
        }
      
        if (Down == 1) {
            PORTD--;
            INTCONbits.RBIF = 0;
        } 
        else{
            INTCONbits.RBIF = 0;
        }
    }
}