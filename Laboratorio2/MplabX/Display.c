#include "Display.h"
void Display(int num) {
    switch (num) {
        case 0:
            PORTC = 0X3F;
            break;
        case 1:
            PORTC = 0X06;
            break;
        case 2:
            PORTC = 0X5B;
            break;
        case 3:
            PORTC = 0X4F;
            break;
        case 4:
            PORTC = 0X66;
            break;
        case 5:
            PORTC = 0X6D;
            break;
        case 6:
            PORTC = 0X7D;
            break;
        case 7:
            PORTC = 0X07;
            break;
        case 8:
            PORTC = 0X7F;
            break;
        case 9:
            PORTC = 0X6F;
            break;
        default:
            //do nothing
            break;

    }
}
