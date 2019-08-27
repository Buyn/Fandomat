/* coment bloc  {{{
 *
 * Step motor class 
 * to control singl Step Motor driver
***************************************
***************************************
 *  }}}*/
/* include bloc {{{*/
#ifndef ToWaveStepMotor_h
#define ToWaveStepMotor_h
// the #include statment and code go here...
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
/*}}}*/
//define bloc  {{{
#define DEBAG_STEP_LONGS 10
#define START_TIME_OUT 1000
/*}}}*/
// encounter calss{{{
class ToWaveStepMotor {
 public: // {{{
	ToWaveStepMotor(int );
	ToWaveStepMotor();
	void move(long);
	void set_speed(int);
	void set_timeout(int);
	void set_longs(int);
	unsigned long get_timeout();
	unsigned long get_longs();
	void set_enable(int);
	void resetimer(void);
	void stop(void);
	void stop(long);
	void update(void );
	void runtime(void );
	bool done(void);
	void on(void );
	void off(void );
	int dirpin, enablepin, zeropin;
	bool isDirToZero, isMaintenance, posUp;
	unsigned long pos, steps_from_last;
	/*}}}*/
	/* private: * {{{*/
#ifndef UNITTEST/*{{{*/
 private:
#endif /* UNITTEST }}}*/
	unsigned long update_time, value, timeout, longs;
	int pin;
	bool enable, checked;
	void step(void);
	/*}}}*/
 };
 /*}}}*/
#endif
