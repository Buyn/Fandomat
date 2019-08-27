/* coment bloc  {{{
 *
 * Class for Workig with shift microshem
 * in pseudo multithrid evoroment
 * SN74HC165N_shift_reg
 *
 * Program to shift in the bit values from a SN74HC165N 8-bit
 * parallel-in/serial-out shift register.
 *
 *   16 digital states from a
 * pair of daisy-chained SN74HC165N shift registers while using
 * only 4 digital pins on the Arduino.
 *
 * You can daisy-chain these chips by connecting the serial-out
 * (Q7 pin) on one shift register to the serial-in (Ds pin) of
 * the other.
 * 
 * Of course you can daisy chain as many as you like while still
 * using only 4 Arduino pins (though you would have to process
 * them 4 at a time into separate unsigned long variables).
***************************************
***************************************
 *  }}}*/
#ifndef SHIFTOUT_H/*{{{*/
#define SHIFTOUT_H
/* include bloc {{{*/
// the #include statment and code go here...
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
/*}}}*/
//define bloc  {{{
/* How many shift register chips are daisy-chained.  */
#define NUMBER_OF_SHIFT_CHIPS   2
/* Width of data (how many ext lines).  */
#define DATA_WIDTH   16
/* Width of pulse to trigger the shift register to read and latch.  */
#define PULSE_WIDTH_USEC   1
#define BYTES_VAL_T unsigned int
//Пин подключен к ST_CP входу 74HC595
#define		 	LATCHPIN  	PA2  
//Пин подключен к SH_CP входу 74HC595
#define 			CLOCKPIN  	PA3
//Пин подключен к DS входу 74HC595
#define 			DATAPIN  	PA1
/*}}}*/
// Variable block{{{
/*}}}*/
// ShiftOut calss{{{
class ShiftOut {
 public: // {{{
	ShiftOut();
	bool send16(BYTES_VAL_T);
	void display_pin_values();
	void initpins(void);
	/*}}}*/
 private:/*{{{*/
	BYTES_VAL_T oldPinValues;
	/*}}}*/
 };
 /*}}}*/
#endif/*SHIFTOUT_H}}}*/
