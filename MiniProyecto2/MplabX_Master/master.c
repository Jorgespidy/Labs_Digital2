/*
 * File:   master.c
 * Author: Jorge Castillo Palomo - 18209
 * Miniproyecto 2 "Comunicacion I2C, main del master" 
 *
 * Created on March 7, 2021, 5:54 PM
 */
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>

#include <xc.h>
#include "I2C.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000

uint8_t sec;
uint8_t min;
uint8_t hr;
uint8_t hr_temp;
uint8_t sec_u;
uint8_t sec_d;
uint8_t min_u;
uint8_t min_d;
uint8_t hr_u;
uint8_t hr_d;
uint8_t variable;
uint8_t aski;


//*****************************************************************************
// Prototipo de funciones
//*****************************************************************************
void setup(void);
void RTC_time(void);
uint8_t conv(uint8_t bcd);
void ready(char val);
void SendString(char* val);



//*****************************************************************************
// Main
//*****************************************************************************

void main(void) {
    setup();

    while (1) {

        RTC_time();

        hr_d = hr/10;
        hr_u = hr - (hr_d*10);
        
        min_d = min/10;
        min_u = min - (min_d*10);
        
        sec_d = sec/10;
        sec_u = sec - (sec_d*10);
        //Comunicacion UART
        if (TXSTAbits.TRMT == 1) {
           
            SendString("hora :");
            __delay_ms(4);
            TXREG = 0X20; //espacio
            aski = ascii(hr_d);
            TXREG = aski;
            __delay_ms(4);
            aski = ascii(hr_u);
            TXREG = aski;
            __delay_ms(4);
            TXREG = 0X20; //espacio
            
            SendString("min :");
            __delay_ms(4);
            TXREG = 0X20; //espacio
            aski = ascii(min_d);
            TXREG = aski;
            __delay_ms(4);
            aski = ascii(min_u);
            TXREG = aski;
            __delay_ms(4);
            TXREG = 0X20; //espacio
            
            SendString("seg :");
            __delay_ms(4);
            TXREG = 0X20; //espacio
            aski = ascii(sec_d);
            TXREG = aski;
            __delay_ms(4);
            aski = ascii(sec_u);
            TXREG = aski;
            __delay_ms(4);
            TXREG = 0X0D; //Enter
            __delay_ms(300);
            
           
        }
    }
}

    //******************************************************************************
    // Configuración
    //******************************************************************************

    void setup(void) {
        //Se limpian los tris a usar, los puertos y se setea el anselh
        ANSEL = 0;
        ANSELH = 0;
        TRISC = 0b00010000;
        TRISB = 0;

        I2C_Master_Init(100000);

        // config de la UART
        INTCON = 0b11000000; // GIE, PEIE enable
        SPBRGH = 0;
        SPBRG = 51; //para 8MHz
        BAUDCTL = 0x00; //config del baudrate 9615
        TXSTA = 0b00100100;
        RCSTA = 0b10010000;
    }


    //*****************************************************************************
    // Funciones
    //*****************************************************************************

    // Función para obtener tiempo del RTC

    void RTC_time(void) {
        I2C_Master_Start(); //Escritura
        I2C_Master_Write(0xD0); //Codigo de escritura
        I2C_Master_Write(0x00); // primera dirección
        I2C_Master_Stop();
        __delay_ms(4);

        I2C_Master_Start();
        I2C_Master_Write(0xD1); //Codigo de lectura
        sec = conv(I2C_Master_Read(1) & 0x7F); // lee los 7 bits de segundos. El master read esta en 1 porque es el primer acknowledge bit
   
        min = conv(I2C_Master_Read(1) & 0x7F); // lee los 7 bits de los minutos
        
        hr = conv(I2C_Master_Read(0) & 0b00111111); // lee nibble menos significativo de la hora. Master read en 0 porque es el  ultimo acknowledge bit
        
        I2C_Master_Stop();
        __delay_ms(4);
    }

    uint8_t conv(uint8_t bcd) { //  convierte de BCD a binario
        variable = bcd;
        variable = variable >> 1;
        variable &= 0x78;
        return (variable + (variable >> 2)+ (bcd & 0x0F));
    }
     

    void ready(char val) {
        while (!TXIF);
        TXREG = val;
    }

    void SendString(char* val) {
        while (*val)
            ready(*val++);
    }
