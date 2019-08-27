/* coment bloc {{{
 *
 * Protatip of encoder class in siplefaed form
 }}}*/
/* include bloc {{{*/
#ifndef simplencoder_h
#define simplencoder_h
// the #include statment and code go here...
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
/*}}}*/
//define bloc  {{{
/*}}}*/
// SerialPrinter calss{{{
class SimplEncoder {
 public: // {{{
   SimplEncoder(int, int, int, unsigned long);
	bool have_data();
	String get_sensor_txt();
	String reset_countes();
	unsigned int reset_uint();
	void encoder2();
	void encoder1();
	/*}}}*/
 private:/*{{{*/
	void set_interrupts(void);
	void reset_time();
	unsigned long sensor_time, delay_time;
	long position;
	String temptxt;
	int enc_pin1, enc_pin2, enc_pin3;
	int counter1, counter3;
	/*}}}*/
 };
 /*}}}*/
#endif
