/*
 * File:   Juego_carreras.c
 * Author: Jorge Castillo Palomo - 18209
 * Lab 01 - Juego de Carreras (Temario A) 
 * Created on January 31, 2021, 6:36 PM
 */


//******************************************************************************
// Importación de librerías
//******************************************************************************

#include <xc.h>

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

#define Rojo PORTDbits.RD0
#define Amarillo PORTDbits.RD1
#define Verde PORTDbits.RD2

#define Start PORTAbits.RA0
#define User1 PORTAbits.RA1
#define User2 PORTAbits.RA2

#define winner1 PORTDbits.RD3
#define winner2 PORTDbits.RD4

//******************************************************************************
// Variables
//******************************************************************************

int cont = 0;
int flag;

//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);
void semaforo(void);

//******************************************************************************
// Ciclo principal
//******************************************************************************

void main(void) {
    setup();
    while (1){
     if (Start){
         semaforo();
         while (winner1 == 0){
             while (winner2 == 0){
                 if (User1){
                     if (PORTB == 0){
                       
                         PORTB = 1;
                         __delay_ms(300);
                     }
                     else {
                         PORTB = 2*PORTB;
                         __delay_ms(300);
                     }
                 }
                 if (User2){
                     if (PORTC == 0){
                         PORTC = 1;
                         __delay_ms(300);
                     }
                     else {
                         PORTC = 2*PORTC;
                         __delay_ms(300);
                     }
                 }
             }
         }
     }
         
    }
    return;
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
    TRISA = 0b00000111;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    flag = 0;
    return;
}
//******************************************************************************
// Funciones
//******************************************************************************

void semaforo(void) {
    Rojo = 1;
    __delay_ms(1000);
    Rojo = 0;
    Amarillo = 1;
    __delay_ms(500);
    Amarillo = 0;
    Verde = 1;
    __delay_ms(500);
    Verde = 0;
}