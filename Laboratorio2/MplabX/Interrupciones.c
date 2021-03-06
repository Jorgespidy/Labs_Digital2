/*
 * File:   Interripciones.c
 * Author: Jorge Castillo Palomo - 18209
 * Lab 02 - Interrupciones y uso de librerias (Temario A) 
 * Created on February 7, 2021, 12:03 PM
 */


//******************************************************************************
// Importación de librerías
//******************************************************************************

#include <xc.h>
#include <stdint.h>
#include "Display.h"

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

#define up PORTBbits.RB0
#define down PORTBbits.RB1
#define disp1 PORTDbits.RD0
#define disp2 PORTDbits.RD1

//******************************************************************************
// Variables
//******************************************************************************
uint8_t ADC;
uint8_t MSB;
uint8_t LSB;
uint8_t num;

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    //Se limpian los tris a usar, los puertos y se setea el anselh
    PORTA = 0;
    PORTC = 0;
    PORTD = 0;
    ANSEL = 0;
    ANSELH = 0b00000001;
    TRISA = 0;
    TRISB = 0b00000111; // para botones up & down, y entrada analogica
    TRISC = 0;
    TRISD = 0;
    ADCON0 = 0b00100001; // para habilitar AN8 y ADC enable bit
    ADCON1 = 0b00000000; // justificado a la izquiera (MSB) y sin referencias en pines
    INTCON = 0b11001000; // GIE, PEIE & RBIE enable
    PIE1 = 0b01000010; // ADIE enable y enable del timer 2
    PR2 = 255; // tasa de polleo del timer 2
    IOCB = 0b00000011; // solo activan interrupciones RB0 y RB1

    return;
}

//******************************************************************************
// Ciclo principal
//******************************************************************************

void main(void) {
    setup();
    while (1) {
        __delay_ms(20);
        if (ADCON0bits.GO == 0) {//Activa la bandera de conversion de conversiones ADC cada 10ms
            (ADCON0bits.GO = 1);
        }
        if (disp2 == 1){
            LSB = ADC & 0b00001111;
            Display (LSB);
        }
        else{
            MSB = ADC >> 4;
            Display (MSB);
        }
    }

    return;
}

//******************************************************************************
// Interrupciones
//******************************************************************************

void __interrupt() ISR(void) {
    if (INTCONbits.RBIF == 1) {//interrupaciones del contador binario
        if (up == 1) {//verifica si esta presionado el boton de aumentar contador
            PORTA++;
            INTCONbits.RBIF = 0;
        }
        if (down == 1) {
            PORTA--;
            INTCONbits.RBIF = 0;
        }
    }
    if (PIR1bits.ADIF == 1) {// interrupciones del ADC
        ADC = ADRESH;
        PIR1bits.ADIF = 0;
    }
    if (PIR1bits.TMR2IF == 1){// interrupciones del multiplexado de displays
        if (disp2 == 1){// verifica si esta encendido el display 2
            disp2 = 0;
            disp1 = 1;
            PIR1bits.TMR2IF = 0;
        }
        else{
            disp2 = 1;
            disp1 = 0;
            PIR1bits.TMR2IF = 0;
        }
    }
}




//******************************************************************************
// Funciones
//******************************************************************************

