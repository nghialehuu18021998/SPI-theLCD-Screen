#ifndef __LCDFUNCTIONS__
#define __LCDFUNCTIONS__
#include "NUC100Series.h"
#define LCD_Xmax 128
#define LCD_Ymax 64
void lcd_command(unsigned char txdata);
void lcd_data(unsigned char txdata);
void initialize_lcd(void);
void clear_lcd(void);
void set_address(short int page, short int column);
void display_image(short int x_loc, short int y_loc, short int x_dim, short int y_dim, unsigned char *image);

#endif
