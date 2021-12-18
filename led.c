#include "led.h"
#define PORTD (*(volatile __near unsigned char*) 0xF83)
#define TRISD (*(volatile __near unsigned char*) 0xF95)

unsigned char led[8] = {
    0b000000001, 0b000000010, 0b000000100, 0b000001000,
    0b000100000, 0b000010000, 0b001000000, 0b010000000
};

void ConfiguraLed(void) {
    TRISD = 0x00;
    PORTD = 0x00;
}

void LigarLed(char num) {
    PORTD |= led[num];
}

void DesligarLed(char num) {
    PORTD &= ~led[num];
}
