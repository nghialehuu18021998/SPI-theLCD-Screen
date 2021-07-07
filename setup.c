#include "setup.h"

void setup_gpio(void)
{
	PD->PMD &= ~(0x03UL << 28);
	PD->PMD |= (0x02UL << 28);			// Set GPD14 to open-drain output
	PD->DOUT &= ~(0x01UL << 14);		// LCD Backlight on
}

void setup_clock(void)
{
	SYS_UnlockReg();								// Lift write protiection
	CLK->PWRCON |= (0x01UL << 0);		// Set to external clock 
	while (!(CLK->CLKSTATUS & (0x01UL << 0)));	// Wait until external clock is on and stabilized
	SYS_LockReg();									// Reinstate write protection

	CLK->CLKSEL1 &= ~(0x07UL << 8);		// Select external clock source for Timer 0
	while (!(CLK->CLKSTATUS & (0x01UL << 0)));
	CLK->CLKSEL0 &= ~(0x07UL << 0);		// Enable external high speed clock on AHB
	while (!(CLK->CLKSTATUS & (0x01UL << 0)));	// Wait until external clock is stabilized
	CLK->APBCLK |= (0x01UL << 15);		// Enable SPI 3
	while (!(CLK->CLKSTATUS & (0x01UL << 0)));	// Wait until external clock is stabilized	
}

void setup_spi(void)
{
	// SPI is setup for 3 wire mode - LCD onyl supports write mode in this configuration
	// Setup up SPI for high clock polarity, 9 bits per word, divide clock by 12.
    SPI3 -> CNTRL = 0 | (9 << 3) | (1ul << 2);
	// Enable special function use on pins GPD 8, 9 & 11.
	SYS->GPD_MFP |= 0xF00; 
	// Write your definition here to setup the SPI module
	SPI3 -> CNTRL2 |= (1ul << 31);
    SPI3 -> DIVIDER &= (0xB); //(11+ 1) * 2 
	SPI3 -> DIVIDER |= (0xB); //Divide clock by 24
	//Disale auto SS
    SPI3 -> SSR &= ~((1ul << 3) | (3ul << 0));
}
