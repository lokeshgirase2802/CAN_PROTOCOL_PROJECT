//adc_main.c
//adc_main.c
//adc_main.c


#include "types.h"
#include "adc.h"
#include "adc_defines.h"
#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"

#define VMIN 0.5   // in volts (minimum fuel sensor voltage)
#define VMAX 2.5   // in volts (maximum fuel sensor voltage)

int main()
{
    f32 eAR_voltage, eAR_temp;
    int fuel_percentage;
		f32 ch0, ch1;

    Init_UART0();
    Init_ADC();
    InitLCD();

    while (1)
    {
        // Read Voltage Sensor (e.g., fuel level)
        eAR_voltage = Read_ADC(ch0);

        UART0_Tx_str("Voltage: ");
        UART0_Tx_float(eAR_voltage, 3);  // Display actual voltage
        UART0_Tx_str(" V\r\n");

        // Read Temperature Sensor
        eAR_temp = Read_ADC(ch1);
        UART0_Tx_str("Temp: ");
        UART0_Tx_int((int)(eAR_temp * 100));  // For LM35
        UART0_Tx_str(" C\r\n");

        // Calculate Fuel Percentage based on eAR_voltage
        fuel_percentage = ((eAR_voltage - VMIN) * 100) / (VMAX - VMIN);

        if (fuel_percentage < 0) 
		fuel_percentage = 0;
        if (fuel_percentage > 100) 
		fuel_percentage = 100;
									.
        // Display on LCD
        cmdLCD(GOTO_LINE1_POS0);
        strLCD("FUEL GAUGE: ");
        InitLCD();
        charLCD('%');

        cmdLCD(GOTO_LINE2_POS0);
        if (fuel_percentage <= 20)
            UART0_Tx_str("Level: Low");
        else if (fuel_percentage <= 40)
            UART0_Tx_str("Level: MedLow");
        else if (fuel_percentage <= 60)
            UART0_Tx_str("Level: Medium");
        else if (fuel_percentage <= 80)
            UART0_Tx_str("Level: High");
        else
            UART0_Tx_str("Level: Full");

        delay_ms(1000);
    }
}


// adc_main.c
/*
#include "types.h"
#include "adc.h"
#include "adc_defines.h"
#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"

int main()
{
    f32 aR0, aR1;
    int Vc, Vmin = 0, Vmax = 1000;  // in millivolts
    int FUEL_GAUGE;

    Init_UART0();
    Init_ADC();
    InitLCD();

    while (1)
    {
        // Read voltage from ADC Channel 0
        aR0 = Read_ADC(CH0);  
        UART0_Tx_str("Voltage: ");
        UART0_Tx_float(aR0, 3);  // Send float with 3 decimal places
        UART0_Tx_str(" V\r\n");

        // Read temperature from ADC Channel 1
        aR1 = Read_ADC(CH1);
        UART0_Tx_str("Temp: ");
        UART0_Tx_int((int)(aR1 * 100));  // LM35: 10mV/°C ? 0.01V/°C
        UART0_Tx_str(" C\r\n");

        // Convert voltage to millivolts
        Vc = (int)(aR0 * 1000);  

        // Calculate fuel gauge percentage
        FUEL_GAUGE = ((Vc - Vmin) * 100) / (Vmax - Vmin);

        // Display fuel gauge on LCD
        cmdLCD(GOTO_LINE1_POS0);
        strLCD("FUEL GAUGE: ");
        intLCD(FUEL_GAUGE);  // Assuming intLCD sends an integer to LCD
        charLCD('%');

        // Display fuel level description on second line
        cmdLCD(GOTO_LINE2_POS0);
        if (FUEL_GAUGE <= 20)
            strLCD("Level: Low");
        else if (FUEL_GAUGE <= 40)
            strLCD("Level: MedLow");
        else if (FUEL_GAUGE <= 60)
            strLCD("Level: Medium");
        else if (FUEL_GAUGE <= 80)
            strLCD("Level: High");
        else
            strLCD("Level: Full");

        delay_ms(1000);  // Wait for 1 second
    }
}
*/

// adc_main.c
/*
#include "types.h"
#include "adc.h"
#include "adc_defines.h"
#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"

int main()
{
    f32 aR0, aR1;
    int Vc, Vmin = 0, Vmax = 100;  // in millivolts
    int FUEL_GAUGE;

    Init_UART0();
    Init_ADC();
    InitLCD();

    while (1)
    {
        aR0 = Read_ADC(CH0);  // Voltage input from ADC channel 0
        UART0_Tx_str("Voltage: ");
        UART0_Tx_float(aR0, 3);  // Print 3 decimal places
        UART0_Tx_str(" V\r\n");

        aR1 = Read_ADC(CH1);  // Temperature input from ADC channel 1
        UART0_Tx_str("Temp: ");
        UART0_Tx_int((int)(aR1 * 100));  // e.g., LM35 gives 10mV/°C
        UART0_Tx_str(" C\r\n");

        Vc = (int)(aR0 * 1000);  // Convert voltage to millivolts
        FUEL_GAUGE = ((Vc - Vmin) * 100) / (Vmax - Vmin);  // % full

        cmdLCD(GOTO_LINE1_POS0);
        strLCD("FUEL GAUGE: ");
        UART0_Tx_int(FUEL_GAUGE);
        charLCD('%');

        cmdLCD(GOTO_LINE2_POS0);
        if (FUEL_GAUGE <= 20)
            UART0_Tx_str(" Low");
        else if (FUEL_GAUGE <= 40)
            UART0_Tx_str(" MedLow");
        else if (FUEL_GAUGE <= 60)
            UART0_Tx_str(" Medium");
        else if (FUEL_GAUGE <= 80)
            UART0_Tx_str(" High");
        else
            UART0_Tx_str(" Full");

        delay_ms(1000);
    }
}
*/

/*
#include "types.h"
#include "adc.h"
#include "adc_defines.h"
#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"

int main()
{
        f32 aR0, aR1;
        int Vc, Vmin =0, Vmax =100, FUEL_GAUGE;

        Init_UART0();
        Init_ADC();
        InitLCD();

        while(1)
        {
                aR0 = Read_ADC(CH0);
                UART0_Tx_str("Voltage: ");
                UART0_Tx_float(aR0, 3);
                UART0_Tx_str("\r\n");

                aR1 = Read_ADC(CH1);
                UART0_Tx_str("Temp: ");
                UART0_Tx_int((int)(aR1 * 100));
                UART0_Tx_str("\r\n");

                Vc = (int)(aR0 * 1000); // convert to millivolts
                FUEL_GAUGE = ((Vc - Vmin) * 100) / (Vmax - Vmin);

                cmdLCD(GOTO_LINE1_POS0);
                strLCD("FUEL GAUGE: ");
                UART0_Tx_int(FUEL_GAUGE);
                charLCD('%');

                if(FUEL_GAUGE <= 20)
								{ 
								        cmdLCD(GOTO_LINE2_POS0);
                        UART0_Tx_str(" Low");
                }
								else if(FUEL_GAUGE <= 40)
								{
								        cmdLCD(GOTO_LINE2_POS0);
                        UART0_Tx_str(" MedLow");
                }
								else if(FUEL_GAUGE <= 60)
								 {
								        cmdLCD(GOTO_LINE2_POS0);
                       UART0_Tx_str(" Medium");
                	}
								else if(FUEL_GAUGE <= 80)
								  { 
									      cmdLCD(GOTO_LINE2_POS0);
                        UART0_Tx_str(" High");
                 }
								else
								{
								        cmdLCD(GOTO_LINE2_POS0);
                        UART0_Tx_str(" Full");
								 }
                delay_ms(1000);
        }
}
*/


/*
#include "types.h"
#include "adc_1.h"
#include "adc_defines_1.h"
#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"

int main()
{
    f32 aR0, aR1;
    int Vc, Vmin =0, Vmax =100, FUEL_GAUGE;

    Init_UART0();
    Init_ADC();
   InitLCD();

    while(1)
    {
        aR0 = Read_ADC(CH0);
        UART0_Tx_str("Voltage: ");
        UART0_Tx_float(aR0, 3);
        UART0_Tx_str("\r\n");

        aR1 = Read_ADC(CH1);
        UART0_Tx_str("Temp: ");
        UART0_Tx_int((int)(aR1 * 100));
        UART0_Tx_str("\r\n");

        Vc = (int)(aR0 * 1000); // convert to millivolts
        FUEL_GAUGE = ((Vc - Vmin) * 100) / (Vmax - Vmin);

        cmdLCD(GOTO_LINE1_POS0);
        strLCD("FUEL GAUGE: ");
        UART0_Tx_int(FUEL_GAUGE);
        charLCD('%');

        if(FUEL_GAUGE <= 20)
            strLCD(" Low");
        else if(FUEL_GAUGE <= 40)
            strLCD(" MedLow");
        else if(FUEL_GAUGE <= 60)
            strLCD(" Medium");
        else if(FUEL_GAUGE <= 80)
            strLCD(" High");
        else
            strLCD(" Full");

        delay_ms(1000);
    }
}
*/

/*
#include "types.h"

#include "adc.h"

#include "adc_defines.h"

#include "uart0.h"

#include "delay.h"


f32 aR0,aR1;


int main(void) 

{	

	Init_UART0();

  Init_ADC();

	

	while(1) 

	{

    aR0=Read_ADC(CH0);

		UART0_Tx_str("Voltage: ");

		UART0_Tx_float(aR0,3);

		UART0_Tx_str("\r\n");

		

		aR1=Read_ADC(CH1);

		UART0_Tx_str("Temp: ");

		UART0_Tx_int(aR1*100);

		UART0_Tx_str("\r\n");

		delay_ms(1000);


		

	}

}
*/
