#include "lcdfunctions.h"
#define BIT_PER_PAGE 8
void lcd_command(unsigned char txdata)
{
	SPI3->SSR |= (0x01UL << 0);				// Enable Slave Select Bit
	SPI3->TX[0] |= txdata;					// lcd command to transmit
	SPI3->CNTRL |= (0x01UL << 0);			// Start SPI Transfer
	while(SPI3->CNTRL & 0x01UL);			// Wait until SPI TX finishes
	SPI3->SSR &= ~(0x01UL << 0);			// Disable Slave Select Bit
}

void lcd_data(unsigned char txdata)
{
	SPI3->SSR |= (0x01UL << 0);				// Enable Slave Select Bit
	SPI3->TX[0] |= 0x100 + txdata;		    // lcd data to transmit
	SPI3->CNTRL |= (0x01UL << 0);			// Start SPI Transfer
	while(SPI3->CNTRL & 0x01UL);			// Wait until SPI TX finishes
	SPI3->SSR &= ~(0x01UL << 0);			// Disable Slave Select Bit
}

void initialize_lcd(void)
{
	// System Reset
	// Set Frame Rate
	// Set LCD Bias Ratio
	// Set Vbias Potentiometer
	// Set Vbias Pot Value
	// Set LCD Mapping Control - MX enabled, MY disabled
	// Set Display Enable
    
	unsigned char setup_commands[] = {0xE2, 0xA1, 0xEB, 0x81, 0xA0, 0xC2, 0xAF, '\0'};
	for (int i = 0; setup_commands[i] != '\0'; i++)
		lcd_command(setup_commands[i]);
}

void set_address(short int page, short int column)
{
	lcd_command(0x00 | (column & 0x0F) >> 0);	// LSB of column address
	lcd_command(0x10 | (column & 0xF0) >> 4);	// MSB of column address
	lcd_command(0xB0 | page);									// Page address - one page is equal to 8 sequential pixels in a row
}

void clear_lcd(void)
{
	// LCD has 128 columns and 8x8 rows - 8 pages with 8 rows per page
	// Write your definition here to clear the LCD screen
	int16_t i, j;
	set_address(0x0, 0x0);	
    for (j = 0; j < 8; j++)    
        for (i = 0; i < 132; i++)
            lcd_data(0x00);
	lcd_data(0x0f);
}

void display_image(short int x_loc, short int y_loc, short int x_dim, short int y_dim, unsigned char* image)
{
	// x_loc and y_loc denote the x, y origin (top left starting point)
	// x_dim & y_dim denote the columns and page width of the image
	// A pointer to image is passed into this function
	// Write your definition to display an image here
    
    uint8_t t, i, jx, jy, k, kx, ky, no_page_per_row, no_page_per_column;
    no_page_per_row = y_dim / 8;
    no_page_per_column = (LCD_Xmax / 8);

    for (jy = 0; jy < no_page_per_row; jy++) { // Loop through number of page per row
        for (jx = 0; jx < (x_dim / no_page_per_column); jx++) {
            k = x_loc;
            for (i = 0; i < no_page_per_column; i++) {
                kx = x_loc + jx * no_page_per_column + i;
                t = image[i + jx * no_page_per_column + jy * x_dim];
                set_address(y_loc / BIT_PER_PAGE + jy, jx * no_page_per_column + k);
                lcd_data(image[i + jx * no_page_per_column + jy * x_dim]);
                k++;
            }
        }
    }
	      
}
