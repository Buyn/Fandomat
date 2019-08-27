/* coment bloc  {{{
 *
 * Класс сканера поверехности ножа
 * спомошью енкодера
 * version 0.0
***************************************
***************************************
 *  }}}*/
/* include bloc {{{*/
#ifndef EnScaner_h
#define EnScaner_h
// the #include statment and code go here...
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "simplencoder.h"
#include "slavespi.h"
#include "postepmotor.h"
/*}}}*/
//define bloc  {{{
/*}}}*/
// EnScaner calss{{{
typedef void (*GeneralMessageFunction) ();
class EnScaner {
 public: // {{{
	EnScaner(SimplEncoder * , SlaveSPI * , POStepMotor * , GeneralMessageFunction );
	void stop(void);
	void start(void);
	unsigned long pos, steps_from_last;
	/*}}}*/
	/* private: * {{{*/
#ifndef UNITTEST/*{{{*/
 private:
#endif /* UNITTEST }}}*/
	SimplEncoder * encoder; 
	SlaveSPI * spi; 
	POStepMotor * posm; 
	GeneralMessageFunction loopMain; 
	void waitloop(void);
	/*}}}*/
 };
 /*}}}*/
#endif
