#ifndef GPIO_PIN_NAMES_H
#define GPIO_PIN_NAMES_H

#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"

#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7

#define PB0 10
#define PB1 11
#define PB2 12
#define PB3 13
#define PB4 14
#define PB5 15
#define PB6 16
#define PB7 17

#define PC0 20
#define PC1 21
#define PC2 22
#define PC3 23
#define PC4 24
#define PC5 25
#define PC6 26
#define PC7 27

#define PD0 30
#define PD1 31
#define PD2 32
#define PD3 33
#define PD4 34
#define PD5 35
#define PD6 36
#define PD7 37

#define PE0 40
#define PE1 41
#define PE2 42
#define PE3 43
#define PE4 44
#define PE5 45
#define PE6 46
#define PE7 47

#define PF0 50
#define PF1 51
#define PF2 52
#define PF3 53
#define PF4 54
#define PF5 55
#define PF6 56
#define PF7 57

GPIO_reg* getPortAddr(uint8_t pin, uint8_t bus);
GPIO_reg* getPortAddrFromPortName(uint8_t GPIO_PORT, uint8_t bus);
uint8_t getPortName(uint8_t pin);
uint8_t getPinNumber(uint8_t pin);

#endif
