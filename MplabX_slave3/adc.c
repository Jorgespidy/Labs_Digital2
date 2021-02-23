#include <xc.h>
#include <stdint.h>
#include "adc.h"


uint8_t value;

uint8_t carry(void) {
    if (PIR1bits.ADIF == 1) {//A/D converter interrupt flag
        value = ADRESH; // se envia ADRESH por la configuracion del ADCON1
        PIR1bits.ADIF = 0;
    }
    return(value);
}
