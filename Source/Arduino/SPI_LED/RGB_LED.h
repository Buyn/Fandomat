/* coment bloc  {{{
 *
 * Protatip of encounter class 
***************************************
***************************************
 *  }}}*/
/* include bloc {{{*/
#ifndef RGB_LED_h
#define RGB_LED_h
// the #include statment and code go here...
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "LED.h"
/*}}}*/
//define bloc  {{{
#define RGB_LED_MAX_VALUE 255
/*}}}*/
// encounter calss{{{
class RGB_LED {
 public: // {{{
	RGB_LED(int , int , int );
	void set_speed(int);
	void fade_to(int, int, int);
	void set_to(int, int, int);
	void update(void );
	void runtime(void );
	bool done(void);
	unsigned long update_time;
	LED red, green, blue;
	/*}}}*/
 private:/*{{{*/
	unsigned long fade_speed;
	void fade_Up(int);
	void fade_Down(int);
	/*}}}*/
 };
 /*}}}*/
#endif
