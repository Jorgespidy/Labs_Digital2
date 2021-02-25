#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000
#define RS RC0
#define EN RC1
uint8_t ret;

void Lcd_Port(char a) {
    PORTD = a;
}

void Lcd_Cmd(char a)//para enviar comandos
{
    RS = 0; // => RS = 0, comandos
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear() {
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    char temp;
    if (a == 1) {
        temp = 0x80 + b - 1;
        Lcd_Cmd(temp);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        Lcd_Cmd(temp);
    }
}

void Lcd_Init() {
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(11);
    Lcd_Cmd(0x03);
    /////////////////////////////////////////////////////
    //Inicializacion 8 bits
    Lcd_Cmd(0b00111000);
    Lcd_Cmd(0b00001100);
    Lcd_Cmd(0b00000001);
    Lcd_Cmd(0b00000110);

}

void Lcd_Write_Char(char a)//se quiere enviar todo el bit, no los 2 nibbles
{
    RS = 1; // => RS = 1
    Lcd_Port(a); //Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right() {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left() {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}

uint8_t ascii(uint8_t num) {
    switch (num) {
        case 0:
            ret = 0X30;
            break;
        case 1:
            ret = 0X31;
            break;
        case 2:
            ret = 0X32;
            break;
        case 3:
            ret = 0X33;
            break;
        case 4:
            ret = 0X34;
            break;
        case 5:
            ret = 0X35;
            break;
        case 6:
            ret = 0X36;
            break;
        case 7:
            ret = 0X37;
            break;
        case 8:
            ret = 0X38;
            break;
        case 9:
            ret = 0X39;
            break;
        default:
            ret = 0X40;
            break;

    }
}
