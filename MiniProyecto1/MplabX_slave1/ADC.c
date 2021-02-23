#include <xc.h>
#include <stdint.h>
#include "ADC.h"


uint8_t ADC;

uint8_t carry(void) {
    if (PIR1bits.ADIF == 1) {//A/D converter interrupt flag
        ADC = ADRESH; // se envia ADRESH por la configuracion del ADCON1
        PIR1bits.ADIF = 0;
    }
}
