#include "app.h"

void time0_init()
{
	TCFG0 = 99;
	TCFG1 = 0X03;
	TCNTB0 = 41250;
	
	TCON |= (1 << 1);
	TCON &= ~(1 << 1);
	TCON |= (1 << 3);
	INTMSK &= ~(1 << 10);
	TCON |= (1 << 0);
}


