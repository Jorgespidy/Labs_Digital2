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
#include "SPI.h"
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
uint8_t lol;

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
    ANSELH = 0b00010000; //RB0
    TRISA = 0b00100000;
    TRISB = 0b00000001; // entrada analogica
    TRISC = 0b00011000;
    TRISD = 0;
    ADCON0bits.CHS = 0b1100; // para habilitar AN8 
    ADCON0bits.ADON = 1; //y ADC enable bit
    ADCON1 = 0b00000000; // justificado a la izquiera (MSB) y sin referencias en pines (ADRESH)
    INTCON = 0b11000000; // GIE, PEIE enable
    PIE1 = 0b01100000; // ADIE enable y enable del TMR2IE
    PR2 = 255; // tasa de polleo del timer 2
    T2CON = 0b00000100; // enciende el tmr2

    PIR1bits.SSPIF = 0; // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1; // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1; // Slave Select

    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}

void __interrupt() ISR(void) {
    if (PIR1bits.ADIF == 1) {//A/D converter interrupt flag
        ADC = ADRESH; // se envia ADRESH por la configuracion del ADCON1
        PIR1bits.ADIF = 0;
    }
    // ADC = carry(); //obtiene los valores del ADC
    if (PIR1bits.SSPIF == 1) {
        lol = spiRead();
        spiWrite(ADC);
        PIR1bits.SSPIF = 0;
    }
}

//******************************************************************************
// Ciclo principal
//******************************************************************************

void main(void) {
    setup();
    while (1) {
        if (ADCON0bits.GO == 0) {//Activa la bandera de conversiones ADC cada 5ms
            __delay_ms(5);
            (ADCON0bits.GO = 1);
        }
        //spiWrite(ADC);
        PORTD = ADC;
    }

}
