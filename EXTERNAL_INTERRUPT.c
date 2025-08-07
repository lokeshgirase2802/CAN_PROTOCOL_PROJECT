//EXTERNAL_INTERRUPTS.c
#include <lpc21xx.h>
#include "pin_function_defines.h"
#include "defines.h"
#include "delay.h"

void eint0_isr(void) __irq;
void eint1_isr(void) __irq;

void Enable_EINT0(void);
void Enable_EINT1(void);

unsigned int count;

#define AL_LED_8 14
#define L_SW 8
#define R_SW 9

#define EINT0_LED 10
#define EINT1_LED 11

#include <lpc21xx.h>

#include "pin_function_defines.h"

#include "defines.h"


#define AL_LED_8 21


#define EINT0_LED 10

#define EINT1_LED 11

void delay_ms(unsigned dlyMS);


void eint0_isr(void) __irq;

void eint1_isr(void) __irq;

void Enable_EINT0(void);

void Enable_EINT1(void);

unsigned int count;


main()

{

	Enable_EINT0();

	Enable_EINT1();
	while(1);	

}
void eint0_isr(void) __irq
{
				int i;
					for(i=0;i<=16;i++)
					{
        		IOSET0 = 0X0F<<AL_LED_8;														   
						IOCLR0 = i<<AL_LED_8;
						//delay_ms(10);
				
						IOCLR0 = 0XF0<<AL_LED_8;
					}

        CPLBIT(IOPIN0,EINT0_LED);//isr activity
        SSETBIT(EXTINT,0);//clear EINT0 flag
        VICVectAddr=0;//dummy write to clear 
        //interrupt flag in VIC
        delay_ms(100);

}

void eint1_isr(void) __irq
{
        int i;
			for(i=256;i>=17;i--)
			  {
        	IOSET0 = 0XF0<<AL_LED_8;
					IOCLR0 = i<<AL_LED_8;
					//delay_ms(10);
				
					IOCLR0 = 0X0F<<AL_LED_8;
				}

        CPLBIT(IOPIN0,EINT1_LED);//isr activity
        SSETBIT(EXTINT,1);//clear EINT1 flag
        VICVectAddr=0;//dummy write;
        delay_ms(100);

}

void Enable_EINT0(void)
{
        CFGPIN(PINSEL0,1,FUNC4);
        SETBIT(IODIR0,EINT0_LED);
        SSETBIT(VICIntEnable,14);
        VICVectCntl0=0x20|14;
        VICVectAddr0=(unsigned)eint0_isr;
        SCLRBIT(EXTINT,0);
        SETBIT(EXTMODE,0);
        SETBIT(EXTPOLAR,0);
}

void Enable_EINT1(void)
{
        CFGPIN(PINSEL0,3,FUNC4);
        SETBIT(IODIR0,EINT1_LED);
        SSETBIT(VICIntEnable,15);
        VICVectCntl1=0x20|15;
        VICVectAddr1=(unsigned)eint1_isr;
        SCLRBIT(EXTINT,1);
        SETBIT(EXTMODE,1);
        SETBIT(EXTPOLAR,1);
}


