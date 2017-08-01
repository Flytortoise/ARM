#include "app.h"


void key_init(void)
{
	GPFCON |= 0xaa;
	
	EXTINT0 = (7 << 12) | (7 << 8) | (7 << 4) | (7);
	
	SRCPND = SRCPND;
	INTPND = INTPND;
	INTMSK &= ~(0X0F);
}

