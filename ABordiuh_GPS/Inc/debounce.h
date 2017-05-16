/*
 * debounce.h
 *
 *  Created on: Dec 28, 2016
 *      Author: rhofer
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

void deBounceInit(int16_t pin, char port, int8_t mode);
GPIO_PinState deBounceReadPin(int16_t pin, char port, int8_t stableInterval);

#endif /* DEBOUNCE_H_ */
