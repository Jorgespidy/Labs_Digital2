/*
 * File:   Slave1.c
 * Author: Jorge Castillo Palomo - 18209
 * Miniproyecto 1 "Comunicacion SPI, main del slave 1" 
 */

//******************************************************************************
// Importación de librerías
//******************************************************************************

#include <xc.h>
#include <stdint.h>
#include "ADC.h"

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

//******************************************************************************
// Variables
//******************************************************************************
uint8_t ADC;

//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    //Se limpian los tris a usar, los puertos y se setea el anselh
    PORTA = 0;
    PORTC = 0;
    PORTD = 0;
    ANSEL = 0;
    ANSELH = 0b00000001; //RB2
    TRISA = 0;
    TRISB = 0b00000100; // para botones up & down, y entrada analogica
    TRISC = 0;
    TRISD = 0;
    ADCON0 = 0b00100001; // para habilitar AN8 y ADC enable bit
    ADCON1 = 0b00000000; // justificado a la izquiera (MSB) y sin referencias en pines (ADRESH)
    INTCON = 0b11000000; // GIE, PEIE enable
    PIE1 = 0b01100000; // ADIE enable y enable del TMR2IE
    PR2 = 255; // tasa de polleo del timer 2
    T2CON = 0b00000100; // enciende el tmr2
}

void __interrupt() ISR(void) {
    ADC = carry(); //obtiene los valores del ADC
}

void main(void) {
    setup();
    if (ADCON0bits.GO == 0) {//Activa la bandera de conversiones ADC cada 5ms
        __delay_ms(5);
        (ADCON0bits.GO = 1);
    }
}
