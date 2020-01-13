/******************************************************************************************************************
*	@file			-	TM4C123xx.h																																													*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
* This file contains base addresses of core components, base addresses of peripherals, core components' register	*
*	definitions, peripheral register definitions, pointers to peripheral registers, and clock enable/disable macros.*
* This file also contains some shorthands and peripheral name definitions which are used in the other files.			*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
******************************************************************************************************************/

/******************************************************************************************************************
*		Things that need to be changed/improved																																				*
*			<>	Change the data type of all reserved registers to uint8_t and update the array size accordingly, so			*
*					that it is easier to assign the size of reserved array. Also it would help in debugging.								*
*			<>	Change GPIO register pointer names from GPIO_X(H/P) to GPIOX_(H/P) to increase readability.							*
*					Make sure to update every header and source files to match the new naming convention.										*
*			<>	Add bus selection feature in every function.																														*
******************************************************************************************************************/



#ifndef TM4C123XX_H
#define TM4C123XX_H

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>



/******************************************************************************************************************
*																									Peripheral Names																								*
******************************************************************************************************************/
// 1 - GPIO ports
#define GPIO_PORT_A 0
#define GPIO_PORT_B 1
#define GPIO_PORT_C 2
#define GPIO_PORT_D 3
#define GPIO_PORT_E 4
#define GPIO_PORT_F 5

// 2 - Synchronous Serial Interface (SSI)
#define SSI0 6
#define SSI1 7
#define SSI2 8
#define SSI3 9

// 3 - Inter Integrated Circuit (I2C) Interface
#define I2C0 10
#define I2C1 11
#define I2C2 12
#define I2C3 13

// 4 - UART
#define UART0 14
#define UART1 15
#define UART2 16
#define UART3 17
#define UART4 18
#define UART5 19
#define UART6 20
#define UART7 21

// 5 - Controller Area Network (CAN) Module
#define CAN0 22
#define CAN1 23

// 6 - Peripheral_6



/******************************************************************************************************************
*																				 CORE COMPONENTS' BASE ADDRESSES																					*
******************************************************************************************************************/
#define FLASH_BASE_ADDRESS						0X00000000U							// Base Addr of Flash Memory
#define SRAM_BASE_ADDRESS							0x20000000U							// Base Addr of SRAM1
#define SRAM													SRAM_BASE_ADDRESS				// Shorthand for SRAM Base Addr

#define CORE_PERIPH_BASE 							0xE000E000U							// Base Addr of Core Peripherals
#define SYSTEM_CONTROL_BASE_ADDRESS		0x400FE000U							// Base Addr of System Control Block Register
#define NVIC_BASE_ADDRESS							0xE000E100U							// Base Addr of NVIC registers
#define VECTOR_TABLE_BASE_ADDR				0x00000000U							// Base Addr of Vector Table



/******************************************************************************************************************
*																							 GPIO BASE ADDRESSES																								*
*		These use the format GPIOX(H/P) = GPIO_BASE_ADDRESS + Port_Offset																							*
*		Note: All GPIO  ports are connected to both AHB and APB Bus ( GPIOxP => APB bus GPIOxH => AHB bus )						*
******************************************************************************************************************/
#define GPIO_BASE																		 0x40004000U
#define GPIOAP_BASE_ADDRESS							(GPIO_BASE + 0x00000000U)
#define GPIOBP_BASE_ADDRESS							(GPIO_BASE + 0x00001000U)
#define GPIOCP_BASE_ADDRESS							(GPIO_BASE + 0x00002000U)
#define GPIODP_BASE_ADDRESS							(GPIO_BASE + 0x00003000U)
#define GPIOEP_BASE_ADDRESS							(GPIO_BASE + 0x00020000U)
#define GPIOFP_BASE_ADDRESS							(GPIO_BASE + 0x00021000U)

#define GPIOAH_BASE_ADDRESS							(GPIO_BASE + 0x00054000U)
#define GPIOBH_BASE_ADDRESS							(GPIO_BASE + 0x00055000U)
#define GPIOCH_BASE_ADDRESS							(GPIO_BASE + 0x00056000U)
#define GPIODH_BASE_ADDRESS							(GPIO_BASE + 0x00057000U)
#define GPIOEH_BASE_ADDRESS							(GPIO_BASE + 0x00058000U)
#define GPIOFH_BASE_ADDRESS							(GPIO_BASE + 0x00059000U)



/******************************************************************************************************************
*																						SSI MODULE BASE ADDRESSES																							*
*		SSI interface is connected to APB bus.																																				*
******************************************************************************************************************/
#define SSI0_BASE 0x40008000
#define SSI1_BASE 0x40009000
#define SSI2_BASE 0x4000A000
#define SSI3_BASE 0x4000B000



/******************************************************************************************************************
*																						I2C MODULE BASE ADDRESSES																							*
*		I2C interface is connected to APB bus.																																				*
******************************************************************************************************************/
#define I2C0_BASE 0x40020000U
#define I2C1_BASE 0x40021000U
#define I2C2_BASE 0x40022000U
#define I2C3_BASE 0x40023000U



/***************************** REGISTER DEFINITIONS FOR MICROCONTROLLER'S PERIPHERALS *****************************/
#define __vo volatile



/******************************************************************************************************************
*																			System Control Register Definition																					*
*		Base address for system control peripherals is defined as SYSTEM_CONTROL_BASE_ADDRESS in CORE COMPONENTS'			*
*		BASE ADDRESS Section																																													*
******************************************************************************************************************/
typedef struct
{
	__vo uint32_t  DID0;                              // Device Identification 0
  __vo uint32_t  DID1;                              // Device Identification 1
  __vo uint32_t  DC0;                               // Device Capabilities 0
	__vo uint32_t  RESERVED;
  __vo uint32_t  DC1;                               // Device Capabilities 1
  __vo uint32_t  DC2;                               // Device Capabilities 2
  __vo uint32_t  DC3;                               // Device Capabilities 3
  __vo uint32_t  DC4;                               // Device Capabilities 4
  __vo uint32_t  DC5;                               // Device Capabilities 5
  __vo uint32_t  DC6;                               // Device Capabilities 6
  __vo uint32_t  DC7;                               // Device Capabilities 7
  __vo uint32_t  DC8;                               // Device Capabilities 8
  __vo uint32_t  PBORCTL;                           // Brown-Out Reset Control
	__vo uint32_t  RESERVED1[3];
  __vo uint32_t  SRCR0;                             // Software Reset Control 0
  __vo uint32_t  SRCR1;                             // Software Reset Control 1
  __vo uint32_t  SRCR2;                             // Software Reset Control 2
	__vo uint32_t  RESERVED2;
  __vo uint32_t  RIS;                               // Raw Interrupt Status
  __vo uint32_t  IMC;                               // Interrupt Mask Control
  __vo uint32_t  MISC;                              // Masked Interrupt Status and Clear
  __vo uint32_t  RESC;                              // Reset Cause
  __vo uint32_t  RCC;                               // Run-Mode Clock Configuration
	__vo uint32_t  RESERVED3[2];
  __vo uint32_t  GPIOHBCTL;                         // GPIO High-Performance Bus Control
  __vo uint32_t  RCC2;                              // Run-Mode Clock Configuration 2
	__vo uint32_t  RESERVED4[2];
  __vo uint32_t  MOSCCTL;                           // Main Oscillator Control
	__vo uint32_t  RESERVED5[32];
  __vo uint32_t  RCGC0;                             // Run Mode Clock Gating Control Register 0
  __vo uint32_t  RCGC1;                             // Run Mode Clock Gating Control Register 1
  __vo uint32_t  RCGC2;                             // Run Mode Clock Gating Control Register 2
	__vo uint32_t  RESERVED6;
  __vo uint32_t  SCGC0;                             // Sleep Mode Clock Gating Control Register 0
  __vo uint32_t  SCGC1;                             // Sleep Mode Clock Gating Control Register 1
  __vo uint32_t  SCGC2;                             // Sleep Mode Clock Gating Control Register 2
	__vo uint32_t  RESERVED7;
  __vo uint32_t  DCGC0;                             // Deep Sleep Mode Clock Gating Control Register 0
  __vo uint32_t  DCGC1;                             // Deep-Sleep Mode Clock Gating Control Register 1
  __vo uint32_t  DCGC2;                             // Deep Sleep Mode Clock Gating Control Register 2
	__vo uint32_t  RESERVED8[6];
  __vo uint32_t  DSLPCLKCFG;                        // Deep Sleep Clock Configuration
	__vo uint32_t  RESERVED9;
  __vo uint32_t  SYSPROP;                           // System Properties
  __vo uint32_t  PIOSCCAL;                          // Precision Internal Oscillator Calibration
  __vo uint32_t  PIOSCSTAT;                         // Precision Internal Oscillator Statistics
	__vo uint32_t  RESERVED10[2];
  __vo uint32_t  PLLFREQ0;                          // PLL Frequency 0
  __vo uint32_t  PLLFREQ1;                          // PLL Frequency 1
  __vo uint32_t  PLLSTAT;                           // PLL Status
	__vo uint32_t  RESERVED11[7];
  __vo uint32_t  SLPPWRCFG;                         // Sleep Power Configuration
  __vo uint32_t  DSLPPWRCFG;                        // Deep-Sleep Power Configuration
  __vo uint32_t  DC9;                               // Device Capabilities 9
	__vo uint32_t  RESERVED12[3];
  __vo uint32_t  NVMSTAT;                           // Non-Volatile Memory Information
	__vo uint32_t  RESERVED13[4];
  __vo uint32_t  LDOSPCTL;                          // LDO Sleep Power Control
	__vo uint32_t  RESERVED14;
  __vo uint32_t  LDODPCTL;                          // LDO Deep-Sleep Power Control
	__vo uint32_t  RESERVED15[80];
  __vo uint32_t  PPWD;                              // Watchdog Timer Peripheral Present
  __vo uint32_t  PPTIMER;                           // 16/32-Bit General-Purpose Timer Peripheral Present
  __vo uint32_t  PPGPIO;                            // General-Purpose Input/Output Peripheral Present
  __vo uint32_t  PPDMA;                             // Micro Direct Memory Access Peripheral Present
	__vo uint32_t  RESERVED16;
  __vo uint32_t  PPHIB;                             // Hibernation Peripheral Present
  __vo uint32_t  PPUART;                            // Universal Asynchronous Receiver/Transmitter Peripheral Present
  __vo uint32_t  PPSSI;                             // Synchronous Serial Interface Peripheral Present
  __vo uint32_t  PPI2C;                             // Inter-Integrated Circuit Peripheral Present
	__vo uint32_t  RESERVED17;
  __vo uint32_t  PPUSB;                             // Universal Serial Bus Peripheral Present
	__vo uint32_t  RESERVED18[2];
  __vo uint32_t  PPCAN;                             // Controller Area Network Peripheral Present
  __vo uint32_t  PPADC;                             // Analog-to-Digital Converter Peripheral Present
  __vo uint32_t  PPACMP;                            // Analog Comparator Peripheral Present
  __vo uint32_t  PPPWM;                             // Pulse Width Modulator Peripheral Present
  __vo uint32_t  PPQEI;                             // Quadrature Encoder Interface Peripheral Present
	__vo uint32_t  RESERVED19[4];
  __vo uint32_t  PPEEPROM;                          // EEPROM Peripheral Present
  __vo uint32_t  PPWTIMER;                          // 32/64-Bit Wide General-Purpose Timer Peripheral Present
	__vo uint32_t  RESERVED20[104];
  __vo uint32_t  SRWD;                              // Watchdog Timer Software Reset/
  __vo uint32_t  SRTIMER;                           // 16/32-Bit General-Purpose Timer Software Reset
  __vo uint32_t  SRGPIO;                            // General-Purpose Input/Output Software Reset
  __vo uint32_t  SRDMA;                             // Micro Direct Memory Access Software Reset
	__vo uint32_t  RESERVED21;
  __vo uint32_t  SRHIB;                             // Hibernation Software Reset
  __vo uint32_t  SRUART;                            // Universal Asynchronous Receiver/Transmitter Software Reset
  __vo uint32_t  SRSSI;                             // Synchronous Serial Interface Software Reset
  __vo uint32_t  SRI2C;                             // Inter-Integrated Circuit Software Reset
	__vo uint32_t  RESERVED22;
  __vo uint32_t  SRUSB;                             // Universal Serial Bus Software Reset
	__vo uint32_t  RESERVED23[2];
  __vo uint32_t  SRCAN;                             // Controller Area Network Software Reset
  __vo uint32_t  SRADC;                             // Analog-to-Digital Converter Software Reset
  __vo uint32_t  SRACMP;                            // Analog Comparator Software Reset
  __vo uint32_t  SRPWM;                             // Pulse Width Modulator Software Reset
  __vo uint32_t  SRQEI;                             // Quadrature Encoder Interface Software Reset
	__vo uint32_t  RESERVED24[4];
  __vo uint32_t  SREEPROM;                          // EEPROM Software Reset
  __vo uint32_t  SRWTIMER;                          // 32/64-Bit Wide General-Purpose Timer Software Reset
	__vo uint32_t  RESERVED25[40];
  __vo uint32_t  RCGCWD;                            // Watchdog Timer Run Mode Clock Gating Control
  __vo uint32_t  RCGCTIMER;                         // 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control
  __vo uint32_t  RCGCGPIO;                          // General-Purpose Input/Output Run Mode Clock Gating Control
  __vo uint32_t  RCGCDMA;                           // Micro Direct Memory Access Run Mode Clock Gating Control
	__vo uint32_t  RESERVED26;
  __vo uint32_t  RCGCHIB;                           // Hibernation Run Mode Clock Gating Control
  __vo uint32_t  RCGCUART;                          // Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control
  __vo uint32_t  RCGCSSI;                           // Synchronous Serial Interface Run Mode Clock Gating Control
  __vo uint32_t  RCGCI2C;                           // Inter-Integrated Circuit Run Mode Clock Gating Control
	__vo uint32_t  RESERVED27;
  __vo uint32_t  RCGCUSB;                           // Universal Serial Bus Run Mode Clock Gating Control
	__vo uint32_t  RESERVED28[2];
  __vo uint32_t  RCGCCAN;                           // Controller Area Network Run Mode Clock Gating Control
  __vo uint32_t  RCGCADC;                           // Analog-to-Digital Converter Run Mode Clock Gating Control
  __vo uint32_t  RCGCACMP;                          // Analog Comparator Run Mode Clock Gating Control
  __vo uint32_t  RCGCPWM;                           // Pulse Width Modulator Run Mode Clock Gating Control
  __vo uint32_t  RCGCQEI;                           // Quadrature Encoder Interface Run Mode Clock Gating Control
	__vo uint32_t  RESERVED29[4];
  __vo uint32_t  RCGCEEPROM;                        // EEPROM Run Mode Clock Gating Control
  __vo uint32_t  RCGCWTIMER;                        // 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control
	__vo uint32_t  RESERVED30[40];
  __vo uint32_t  SCGCWD;                            // Watchdog Timer Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCTIMER;                         // 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCGPIO;                          // General-Purpose Input/Output Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCDMA;                           // Micro Direct Memory Access Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED31;
  __vo uint32_t  SCGCHIB;                           // Hibernation Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCUART;                          // Universal Asynchronous Receiver/Transmitter Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCSSI;                           // Synchronous Serial Interface Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCI2C;                           // Inter-Integrated Circuit Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED32;
  __vo uint32_t  SCGCUSB;                           // Universal Serial Bus Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED33[2];
  __vo uint32_t  SCGCCAN;                           // Controller Area Network Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCADC;                           // Analog-to-Digital Converter Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCACMP;                          // Analog Comparator Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCPWM;                           // Pulse Width Modulator Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCQEI;                           // Quadrature Encoder Interface Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED34[4];
  __vo uint32_t  SCGCEEPROM;                        // EEPROM Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCWTIMER;                        // 32/64-Bit Wide General-Purpose Timer Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED35[40];
  __vo uint32_t  DCGCWD;                            // Watchdog Timer Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCTIMER;                         // 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCGPIO;                          // General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCDMA;                           // Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED36;
  __vo uint32_t  DCGCHIB;                           // Hibernation Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCUART;                          // Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCSSI;                           // Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCI2C;                           // Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED37;
  __vo uint32_t  DCGCUSB;                           // Universal Serial Bus Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED38[2];
  __vo uint32_t  DCGCCAN;                           // Controller Area Network Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCADC;                           // Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCACMP;                          // Analog Comparator Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCPWM;                           // Pulse Width Modulator Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCQEI;                           // Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED39[4];
  __vo uint32_t  DCGCEEPROM;                        // EEPROM Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCWTIMER;                        // 32/64-Bit Wide General-Purpose Timer Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED40[104];
  __vo uint32_t  PRWD;                              // Watchdog Timer Peripheral Ready
  __vo uint32_t  PRTIMER;                           // 16/32-Bit General-Purpose Timer Peripheral Ready
  __vo uint32_t  PRGPIO;                            // General-Purpose Input/Output Peripheral Ready
  __vo uint32_t  PRDMA;                             // Micro Direct Memory Access Peripheral Ready
	__vo uint32_t  RESERVED41;
  __vo uint32_t  PRHIB;                             // Hibernation Peripheral Ready
  __vo uint32_t  PRUART;                            // Universal Asynchronous Receiver/Transmitter Peripheral Ready
  __vo uint32_t  PRSSI;                             // Synchronous Serial Interface Peripheral Ready
  __vo uint32_t  PRI2C;                             // Inter-Integrated Circuit Peripheral Ready
	__vo uint32_t  RESERVED42;
  __vo uint32_t  PRUSB;                             // Universal Serial Bus Peripheral Ready
	__vo uint32_t  RESERVED43[2];
  __vo uint32_t  PRCAN;                             // Controller Area Network Peripheral Ready
  __vo uint32_t  PRADC;                             // Analog-to-Digital Converter Peripheral Ready
  __vo uint32_t  PRACMP;                            // Analog Comparator Peripheral Ready
  __vo uint32_t  PRPWM;                             // Pulse Width Modulator Peripheral Ready
  __vo uint32_t  PRQEI;                             // Quadrature Encoder Interface Peripheral Ready
	__vo uint32_t  RESERVED44[4];
  __vo uint32_t  PREEPROM;                          // EEPROM Peripheral Ready
  __vo uint32_t  PRWTIMER; 
}SYSCTL_reg;

#define SYSCTL ( (SYSCTL_reg*)SYSTEM_CONTROL_BASE_ADDRESS )



/******************************************************************************************************************
*																		Register Definition for GPIO PORTS																						*
*		Base address for these is defined in the GPIO BASE ADDRESSES section																					*
******************************************************************************************************************/
typedef struct
{
	//__vo uint32_t GPIO_DATA[256];
	__vo uint32_t RESERVED0[255];
	__vo uint32_t GPIO_DATA;
	__vo uint32_t GPIO_DIR;
	__vo uint32_t GPIO_IS;
	__vo uint32_t GPIO_IBE;
	__vo uint32_t GPIO_IEV;
	__vo uint32_t GPIO_IM;
	__vo uint32_t GPIO_RIS;
	__vo uint32_t GPIO_MIS;
	__vo uint32_t GPIO_ICR;
	__vo uint32_t GPIO_AFSEL;
	__vo uint32_t RESERVED1[55];
	__vo uint32_t GPIO_DR2R;
	__vo uint32_t GPIO_DR4R;
	__vo uint32_t GPIO_DR8R;
	__vo uint32_t GPIO_ODR;
	__vo uint32_t GPIO_PUR;
	__vo uint32_t GPIO_PDR;
	__vo uint32_t GPIO_SLR;
	__vo uint32_t GPIO_DEN;
	__vo uint32_t GPIO_LOCK;
	__vo uint32_t GPIO_CR;
	__vo uint32_t GPIO_AMSEL;
	__vo uint32_t GPIO_PCTL;
	__vo uint32_t GPIO_ADCCTL;
	__vo uint32_t GPIO_DMACTL;
	__vo uint32_t RESERVED2[678];
	/*	Registers defined below are READ_ONLY.*/
//	__vo uint32_t GPIOPeriphlD4;
//	__vo uint32_t GPIOPeriphlD5;
//	__vo uint32_t GPIOPeriphlD6;
//	__vo uint32_t GPIOPeriphlD7;
//	__vo uint32_t GPIOPeriphlD0;
//	__vo uint32_t GPIOPeriphlD1;
//	__vo uint32_t GPIOPeriphlD2;
//	__vo uint32_t GPIOPeriphlD3;
//	__vo uint32_t GPIOPCellID0;
//	__vo uint32_t GPIOPCellID1;
//	__vo uint32_t GPIOPCellID2;
//	__vo uint32_t GPIOPCellID3;
}GPIO_reg;

#define GPIO_A_H (GPIO_reg*) GPIOAH_BASE_ADDRESS
#define GPIO_A_P (GPIO_reg*) GPIOAP_BASE_ADDRESS
#define GPIO_B_H (GPIO_reg*) GPIOBH_BASE_ADDRESS
#define GPIO_B_P (GPIO_reg*) GPIOBP_BASE_ADDRESS
#define GPIO_C_H (GPIO_reg*) GPIOCH_BASE_ADDRESS
#define GPIO_C_P (GPIO_reg*) GPIOCP_BASE_ADDRESS
#define GPIO_D_H (GPIO_reg*) GPIODH_BASE_ADDRESS
#define GPIO_D_P (GPIO_reg*) GPIODP_BASE_ADDRESS
#define GPIO_E_H (GPIO_reg*) GPIOEH_BASE_ADDRESS
#define GPIO_E_P (GPIO_reg*) GPIOEP_BASE_ADDRESS
#define GPIO_F_H (GPIO_reg*) GPIOFH_BASE_ADDRESS
#define GPIO_F_P (GPIO_reg*) GPIOFP_BASE_ADDRESS



/******************************************************************************************************************
*																	Clock Enable & Disable Macros for GPIO Ports																		*
*																																																									*
*		Clock to a GPIO port is enabled or disabled by setting or clearing the appropriate bits in the RCGCGPIO				*
*		register.																																																			*
*		RCCGPIO Register:																																															*
*		Bit 0:	1 => Port A is enabled when 1, 0 => disabled.																													*
*		Bit 1:	1 => Port B is enabled when 1, 0 => disabled.																													*
*		.						.																		.																															*
*		.						.																		.																															*
*		Bit 5:	1 => Port F is enabled when 1, 0 => disabled.																													*
*		Bit 6-31:	Reserved																																														*
******************************************************************************************************************/
#define GPIOA_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<0) )
#define GPIOB_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<1) )
#define GPIOC_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<2) )
#define GPIOD_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<3) )
#define GPIOE_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<4) )
#define GPIOF_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<5) )

#define GPIOA_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<0) )
#define GPIOB_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<1) )
#define GPIOC_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<2) )
#define GPIOD_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<3) )
#define GPIOE_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<4) )
#define GPIOF_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<5) )



/******************************************************************************************************************
*											 Register Definition for NVIC: Nested Vector Interrupt Controller														*
*		Base address of NVIC is defined in the CORE COMPONENT BASE ADDRESSES section																	*
******************************************************************************************************************/
typedef struct
{
	__vo uint32_t EN[5];
	__vo uint32_t RESERVED0[27];
	__vo uint32_t DIS[5];
	__vo uint32_t RESERVED1[27];
	__vo uint32_t PEND[5];
	__vo uint32_t RESERVED2[27];
	__vo uint32_t UNPEND[5];
	__vo uint32_t RESERVED3[27];
	__vo uint32_t ACTIVE[5];
	__vo uint32_t RESERVED4[59];
	__vo uint32_t PRI[35];
	__vo uint32_t RESERVED5[669];
	__vo uint32_t SWTRIG;
}NVIC_reg;

#define Nvic ( (NVIC_reg*)NVIC_BASE_ADDRESS )
/******************************************************************************************************************
*		NVIC Enable Registers Bit definitions																																					*
*		NVIC_ENABLE_0																																																	*
*		Bit:	0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27		*
*		Int#: 0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27		*
*																																																									*
*		Bit:	28  29  30  31																																													*
*		Int#: 28  29  30  31																																													*
*	--------------------------------------------------------------------------------------------------------------- *
*		NVIC_ENABLE_1																																																	*
*		Bit:	0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  *
*		Int#: 32  33  34  35  36  37  38	39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55  56  57	*
*																																																									*
*		Bit:	26  27  28  29  30  31																																									*
*		Int#: 58  59  60  61  62  63																																									*
*	--------------------------------------------------------------------------------------------------------------- *
*		NVIC_ENABLE_2																																																	*
*		Bit:	0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  *
*		Int#: 64  65  66  67  68  69  70  71  72  73  74  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89	*
*																																																									*
*		Bit:	26  27  28  29  30  31																																									*
*		Int#: 90  91  92  93  94  95																																									*
*	--------------------------------------------------------------------------------------------------------------- *
*		NVIC_ENABLE_3																																																	*
*		Bit:	0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20  *
*		Int#: 96   97   98   99   100  101  102  103  104  105  106  107  108  109  110  111  112  113  114  115  116	*
*																																																									*
*		Bit:	21   22   23   24   25   26   27   28   29   30   31																										*
*		Int#: 117  118  119  120  121  122  123  124  125  126  127																										*
*	--------------------------------------------------------------------------------------------------------------- *
*		NVIC_ENABLE_4																																																	*
*		Bit:	0    1    2    3    4    5    6    7    8    9    10		( Bits 11:31 are not used )											*
*		Int#: 128  129  130  131  132  133  134  135  136  137  138																										*
******************************************************************************************************************/



/******************************************************************************************************************
*																	Register Definition for Exception Handlers																			*
*		Base address of these is defined in the CORE COMPONENT BASE ADDRESSES section as VECTOR_TABLE_BASE_ADDR				*
******************************************************************************************************************/
typedef struct
{
	__vo uint8_t	Offset0_40h[64];						// Offset(0x40) for System exceptions
	__vo uint32_t	GPIOA;
	__vo uint32_t	GPIOB;
	__vo uint32_t	GPIOC;
	__vo uint32_t	GPIOD;
	__vo uint32_t	GPIOE;
	__vo uint8_t	Offset1_64h[100];						// Refer to comment 1 for details
	__vo uint32_t	GPIOF;
}Vector_Table_reg;
#define ExceptionHandlers ( (Vector_Table_reg*)VECTOR_TABLE_BASE_ADDR )
/******************************************************************************************************************
*		Comments for the above section																																								*
*		1.	There are few addresses of ISRs of different peripherals which should lie between GPIO E and F.	These			*
*				will be defined later.																																										*
******************************************************************************************************************/



/******************************************************************************************************************
*													Register Definition for Synchronous Serial Interface (SSI)															*
*		Base address of these is defined in the SSI MODULE BASE ADDRESSES section.																		*
******************************************************************************************************************/
typedef struct
{
	__vo uint32_t	SSI_CR[2];
	__vo uint32_t	SSI_DR;
	__vo uint32_t	SSI_SR;
	__vo uint32_t	SSI_CPSR;
	__vo uint32_t	SSI_IM;
	__vo uint32_t	SSI_RIS;
	__vo uint32_t	SSI_MIS;
	__vo uint32_t	SSI_ICR;
	__vo uint32_t	SSI_DMACTL;
	__vo uint8_t	Reserved[4000];							//OFFSET
	__vo uint32_t	SSI_CC;
	__vo uint32_t	SSI_PeriphID4;
	__vo uint32_t	SSI_PeriphID5;
	__vo uint32_t	SSI_PeriphID6;
	__vo uint32_t	SSI_PeriphID7;
	__vo uint32_t	SSI_PeriphID0;
	__vo uint32_t	SSI_PeriphID1;
	__vo uint32_t	SSI_PeriphID2;
	__vo uint32_t	SSI_PeriphID3;
	__vo uint32_t	SSI_CellID[4];
}ssi_reg;

#define pSSI0 ( (ssi_reg*)SSI0_BASE )
#define pSSI1 ( (ssi_reg*)SSI1_BASE )
#define pSSI2 ( (ssi_reg*)SSI2_BASE )
#define pSSI3 ( (ssi_reg*)SSI3_BASE )

/******************************************************************************************************************
*																	Clock Enable & Disable Macros for SSI Modules																		*
*		Clock to the SSI modules can be enabled or diabled by setting or clearing the appropriate bit in the RCGCSSI	*
*		register.																																																			*
*		Bit 0:	1 => SSI Module 0 is Enabled, 0 => Disabled																														*
*		Bit 1:	1 => SSI Module 1 is Enabled, 0 => Disabled																														*
*		Bit 2:	1 => SSI Module 2 is Enabled, 0 => Disabled																														*
*		Bit 3:	1 => SSI Module 3 is Enabled, 0 => Disabled																														*
*		Bit 4-31:	Reserved																																														*
******************************************************************************************************************/
#define SSI0_PCLK_EN() (SYSCTL->RCGCSSI |= (1<<0))
#define SSI1_PCLK_EN() (SYSCTL->RCGCSSI |= (1<<1))
#define SSI2_PCLK_EN() (SYSCTL->RCGCSSI |= (1<<2))
#define SSI3_PCLK_EN() (SYSCTL->RCGCSSI |= (1<<3))

#define SSI0_PCLK_DIS() (SYSCTL->RCGCSSI &= ~(1<<0))
#define SSI1_PCLK_DIS() (SYSCTL->RCGCSSI &= ~(1<<1))
#define SSI2_PCLK_DIS() (SYSCTL->RCGCSSI &= ~(1<<2))
#define SSI3_PCLK_DIS() (SYSCTL->RCGCSSI &= ~(1<<3))



/******************************************************************************************************************
*															Clock Enable & Disable Macros for I2C Modules																				*
*		I2C modules' clock can be enabled by setting the appropriate bit in the RCGCI2C register											*
*		RCGCI2C Register Definition:																																									*
*		Bit 0:	1 => I2C Module 0 is Enabled, 0 => Disabled																														*
*		Bit 1:	1 => I2C Module 1 is Enabled, 0 => Disabled																														*
*		Bit 2:	1 => I2C Module 2 is Enabled, 0 => Disabled																														*
*		Bit 3:	1 => I2C Module 3 is Enabled, 0 => Disabled																														*
*		Bit 4-31:	Reserved																																														*
******************************************************************************************************************/
#define I2C0_PCLK_EN()	( SYSCTL->RCGCI2C |= (1<<0) )
#define I2C1_PCLK_EN()	( SYSCTL->RCGCI2C |= (1<<1) )
#define I2C2_PCLK_EN()	( SYSCTL->RCGCI2C |= (1<<2) )
#define I2C3_PCLK_EN()	( SYSCTL->RCGCI2C |= (1<<3) )

#define I2C0_PCLK_DIS()	( SYSCTL->RCGCI2C &= ~(1<<0) )
#define I2C1_PCLK_DIS()	( SYSCTL->RCGCI2C &= ~(1<<1) )
#define I2C2_PCLK_DIS()	( SYSCTL->RCGCI2C &= ~(1<<2) )
#define I2C3_PCLK_DIS()	( SYSCTL->RCGCI2C &= ~(1<<3) )



/******************************************************************************************************************
*																				Miscellaneous macros and shorthands																				*
******************************************************************************************************************/
#define ENABLE			1
#define DISABLE			0
#define SET					ENABLE
#define RESET				DISABLE
#define PIN_SET			SET
#define PIN_RESET		RESET
#define YES					1
#define NO					0
#define IN					0
#define OUT					1

#define APB_BUS	0
#define AHB_BUS	1



/******************************************************************************************************************
*																					Driver and other Header Files																						*
*																																																									*
******************************************************************************************************************/
#include "TM4C123xxGPIO_DRIVER.h"
#include "TM4C123xxSSI_DRIVER.h"

#include "GPIO_PIN_NAMES.h"


#endif
