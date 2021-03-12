#include <stm32f10x.h>
#include "systick.h"
#include "spi.h"
#include "nokia5110.h"
#include "walk_animation_test.h"


void walkman(void)
{
	int i,j;
	ImgType walkmen = {.h = walkmen_4_rows, .w = walkmen_4_cols, .xpos = 0, .ypos = 0};
	walkmen.image[0] = walkmen_0;
	walkmen.image[1] = walkmen_1;
	walkmen.image[2] = walkmen_2;
	walkmen.image[3] = walkmen_3;
	walkmen.image[4] = walkmen_4;
	
	nokia5110_clear();
	nokia5110_clear_buffer(nokia5110_buffer);
	
	for(i=0;i<83;i++)
		{
			walkmen.xpos = i;
			if(i == 32)
			{
				nokia5110_clear_buffer(nokia5110_buffer);
				nokia5110_update_buffer(walkmen,j,nokia5110_buffer);
				nokia5110_update_str_buffer(5,40,"Abhinav",nokia5110_buffer);
				nokia5110_print_buffer(nokia5110_buffer);
				delayms(2000);
			}
			else
			{
				for(j=0;j<4;j++)
				{
					nokia5110_clear_buffer(nokia5110_buffer);
					nokia5110_update_buffer(walkmen,j,nokia5110_buffer);
					nokia5110_print_buffer(nokia5110_buffer);
					delayms(50);
				}
			}
			
		}
}

