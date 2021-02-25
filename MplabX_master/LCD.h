
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_h
#define	LCD_h

#include <xc.h> // include processor files - each processor file is guarded.  

//******************************************************************************
// Prototipo de funciones
//******************************************************************************
void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear();
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init();
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right();
void Lcd_Shift_Left();
uint8_t ascii(uint8_t num);
#endif	/* XC_HEADER_TEMPLATE_H */
