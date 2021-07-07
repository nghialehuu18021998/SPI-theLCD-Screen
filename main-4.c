#define ACTIVITY 1

#if ACTIVITY == 1
#include "setup.h"
#include "lcdfunctions.h"
#include "images.h"

int main(void)
{
    setup_clock();
	setup_gpio();
	setup_spi();
    
	initialize_lcd();
	clear_lcd();
    
	//display_image(0, 2, 128, 64, DDRAM_BUFFER_01);
    //display_image(0, 2, 128, 64, DDRAM_BUFFER_02);
    display_image(112, 2, 16, 16, diamond_16x16);
    //display_image(0, 2, 32, 48, archer_32x48);
    //display_image(0, 2, 32, 48, archer_release_32x48);
    //display_image(0, 2, 32, 16, arrow_32x16);
    //display_image(0, 2, 128, 64, monster_128x64);
}
#endif
