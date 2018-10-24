/*
 * ADC.h
 *
 *  Created on: Mar 2, 2018
 *      Author: saldanha
 */

#ifndef ADC_H_
#define ADC_H_

#include <inc/tm4c123gh6pm.h>

void ADC_init();

int ADC_distance(int d);


unsigned int ADC_read(char channel);


#endif /* ADC_H_ */
