#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
//#define LED 0
#define SW_L 10
#define SW_R 11
void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
void Enable_EINT0(void);
void Enable_EINT1(void);
int main() {
        int i,left=0,right=0,LED=0;
        IODIR0 |= 0xFF<<LED;
		IOPIN0=0xFF<<LED;
        //IODIR0 &= ~((1 << SW_L) | (1 << SW_R));
        while (1) {

                if(((IOPIN0 >> SW_L) & 1) == 0){
                        while (((IOPIN0 >> SW_L) & 1)==0&&((IOPIN0 >> SW_R) & 1)!= 0)
                        {
                                right=1;
                                left=0;
                                for (i = 0; i <= 7 ; i++) {
								LED=i;
                                        IOSET0 = (1 << LED);
                                        delay_ms(100);
                                        IOCLR0 = (1 << LED);
                                }
                        }
                }
                else if(((IOPIN0 >> SW_R) & 1) == 0){
                        while (((IOPIN0 >> SW_R) & 1) == 0&&((IOPIN0 >> SW_L) & 1)!= 0)
                        {
                                left=1;
                                right=0;
                                for(i = 7; i >= 0 ;i--){
								LED=i;
                                        IOSET0 = (1 << LED);
                                        delay_ms(100);
                                        IOCLR0 = (1 << LED);
                                }
                        }
                }
                if((((IOPIN0 >> SW_R) & 1) == 0)&&(((IOPIN0 >> SW_R) & 1) == 0)){
                        if(left){
                                for (i = 0; i <=7; i++) {
								LED=i;
                                        IOSET0 = (1 << LED);
                                        delay_ms(100);
                                        IOCLR0 = (1 << LED);
                                }

                        }
                        if(right){

                                for(i = 7; i >= 0; i--){
								LED=i;
                                        IOSET0 = (1 << LED);
                                        delay_ms(100);
                                        IOCLR0 = (1 << LED);
                                }


                        }
                }
                IOCLR0 = 0xFF;
        }
}
