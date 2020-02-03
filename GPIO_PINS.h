#ifndef GPIO_PINS_H
#define GPIO_PINS_H

#include "TM4C123xx.h"

#define PA0 10
#define PA1 11
#define PA2 12
#define PA3 13
#define PA4 14
#define PA5 15
#define PA6 16
#define PA7 17

#define PB0 20
#define PB1 21
#define PB2 22
#define PB3 23
#define PB4 24
#define PB5 25
#define PB6 26
#define PB7 27

#define PC0 30
#define PC1 31
#define PC2 32
#define PC3 33
#define PC4 34
#define PC5 35
#define PC6 36
#define PC7 37

#define PD0 40
#define PD1 41
#define PD2 42
#define PD3 43
#define PD4 44
#define PD5 45
#define PD6 46
#define PD7 47

#define PE0 50
#define PE1 51
#define PE2 52
#define PE3 53
#define PE4 54
#define PE5 55
#define PE6 56
#define PE7 57

#define PF0 60
#define PF1 61
#define PF2 62
#define PF3 63
#define PF4 64
#define PF5 65
#define PF6 66
#define PF7 67

#define LED_RED			PF1
#define LED_BLUE		PF2
#define LED_GREEN		PF3

#define USER_SW1		PF4
#define USER_SW2		PF0

GPIO_reg* getPortAddr(uint8_t pin, uint8_t bus);
GPIO_reg* getPortAddrFromPortName(uint8_t GPIO_PORT, uint8_t bus);
uint8_t getPortName(uint8_t pin);
uint8_t getPinNumber(uint8_t pin);

void UseLEDs(void);
void TurnOn(uint8_t pin);
void TurnOff(uint8_t pin);
void blink(uint8_t pin);

void UseButtons(void);
uint8_t ReadButtons(void);

#endif
