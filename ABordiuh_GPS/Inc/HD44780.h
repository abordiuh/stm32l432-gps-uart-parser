/*
 * HD44780.h
 *
 *  Created on: Dec 28, 2016
 *      Author: rhofer
 */

#ifndef HD4470_H_
#define HD4470_H_

void hd44780_Delay(unsigned long del);
void hd44780_wr_hi_nibble(unsigned char data);
void hd44780_wr_lo_nibble(unsigned char data);
void hd44780_write(unsigned char data);
void hd44780_wr_cmd(unsigned char cmd);
void hd44780_wr_data(unsigned char data);

void HD44780_Init(void);
void HD44780_PutChar(unsigned char c);
void HD44780_GotoXY(unsigned char x, unsigned char y);
void HD44780_PutStr(char *str);
void HD44780_ClrScr(void);

#endif /* HD4470_H_ */
