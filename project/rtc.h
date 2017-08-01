#ifndef RTC_H_
#define RTC_H_

#define RTCCON (*(volatile unsigned *)0x57000040 )	
#define TICNT0 (*(volatile unsigned *)0x57000044 )	
#define TICNT1 (*(volatile unsigned *)0x57000048 )	
#define TICNT2 (*(volatile unsigned *)0x5700004C )	
#define RTCALM (*(volatile unsigned *)0x57000050 )	
#define ALMSEC (*(volatile unsigned *)0x57000054 )	
#define ALMMIN (*(volatile unsigned *)0x57000058 )	

#define SRCPND1 (*(volatile unsigned *)0x4A000000 )	
#define INTMOD1 (*(volatile unsigned *)0x4A000000 )
#define INTMSK1 (*(volatile unsigned *)0x4A000000 )
#define INTPNP1 (*(volatile unsigned *)0x4A000000 )

#define BCDHOUR (*(volatile unsigned *)0X57000078 )	
#define BCDMIN (*(volatile unsigned *)0X57000074 )
#define BCDSEC (*(volatile unsigned *)0X57000070 )

#define BCDDAY (*(volatile unsigned *)0X57000080 )	
#define BCDMONTH (*(volatile unsigned *)0X57000084 )
#define BCDYEAR (*(volatile unsigned *)0X57000088 )
#define BCDDATE (*(volatile unsigned *)0X5700007C )

unsigned int Str2BCD(const char * str);
void rtc_init(void);
int rtc_work(void);
void RTC_S(void);


#endif

