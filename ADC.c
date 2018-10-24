/*
 * ADC.c
 *
 *  Created on: Mar 2, 2018
 *      Author: saldanha
 */

#include "ADC.h"
#include "Timer.h"
#include "driverlib/interrupt.h"
#include "Math.h"

void ADC_init()
{
    //enableADC 0 module on port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    //enable clock for ADC0
    SYSCTL_RCGCADC_R |= 0x1;

    //enable port B pin 4 to work as alternate functions
    GPIO_PORTB_AFSEL_R |= 0x10;

    //set pin to input -4
    GPIO_PORTB_DEN_R &= 0b11101111;

    //enable GPIO port b direction
    GPIO_PORTB_DIR_R &= 0b11101111;

    //disable analog isolation for the pin
    GPIO_PORTB_AMSEL_R |= 0x10;

    //initialize the port trigger source as processor (default)
    GPIO_PORTB_ADCCTL_R = 0x00;

    //disable SS0 sample sequencer to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    //initialize the ADC trigger source as processor (default)
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;

    //set 1st sample to use the AIN10 ADC pin
    ADC0_SSMUX0_R |= 0x000A;

    //enable raw interrupt status
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);

    //enable oversampling to average
    ADC0_SAC_R |= ADC_SAC_AVG_64X;

    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;

    //clear interrupt flags
    ADC0_ISC_R |= ADC_ISC_IN0;

    //enable global interrupts
    IntMasterEnable();
}

unsigned int ADC_read(char channel)
{
    //disable ADC0SS0 sample sequencer to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    //set 1st sample to use the channel ADC pin
    ADC0_SSMUX0_R |= channel;

    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;

    //initiate SS0 conversion
    ADC0_PSSI_R = ADC_PSSI_SS0;

    while((ADC0_RIS_R & ADC_RIS_INR0) == 0)
    {
        //wait
    }

    //clear interrupt
    ADC0_ISC_R=ADC_ISC_IN0;

    return ADC0_SSFIFO0_R;

}

int ADC_distance(int d) // power regression for calculating distance based on voltage
{
  //static double A = 164724; //cybot 12
  //static double B = -1.20943; //cybot 12
  static double A = 64552.0; //cybot11
  static double B = -1.09; //cytbot11
    //static double A = 20660.431; //cybot 1
    //static double B = -1.07689316;
  return A * pow(d, B); // power regression formula
}



