# 1 "led.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.45/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "led.c" 2
# 1 "./led.h" 1



void ConfiguraLed(void);
void LigarLed(char num);
void DesligarLed(char num);
# 1 "led.c" 2




unsigned char led[8] = {
    0b000000001, 0b000000010, 0b000000100, 0b000001000,
    0b000100000, 0b000010000, 0b001000000, 0b010000000
};

void ConfiguraLed(void) {
    (*(volatile __near unsigned char*) 0xF95) = 0x00;
    (*(volatile __near unsigned char*) 0xF83) = 0x00;
}

void LigarLed(char num) {
    (*(volatile __near unsigned char*) 0xF83) |= led[num];
}

void DesligarLed(char num) {
    (*(volatile __near unsigned char*) 0xF83) &= ~led[num];
}
