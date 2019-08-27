/* coment bloc {{{
 *
 * Protatip of encoder class in siplefaed form
 }}}*/
/* include bloc {{{*/
#ifndef postepmotor_h
#define postepmotor_h
// the #include statment and code go here...
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "towavestepmotor.h"
#include "Shiftin.h"
#include "shiftout.h"
#include "slavespi.h"
/*}}}*/
//define bloc  {{{
#define ARRMAX 		1
/*}}}*/
// Absolut position Step motor calss{{{
class POStepMotor {
 public: // {{{
   POStepMotor(ShiftIn * ,ShiftOut *, SlaveSPI *);
   void addMotor(int ,int, int, bool);//(step pin, zero pin, dir pin, dir to zero)
   void setMotor(int, int ,int, int, bool);//(rewrite motor, step pin, enable pin, dir pin, dir to zero)
   void delMotor(int);
   ToWaveStepMotor * getMotor(int);
   bool runtime();
   bool runtime(int);
	void startManteins(int);
	void manteins(int);
	unsigned long gotoPOS(int, unsigned long);
	bool setDirToZero(ToWaveStepMotor *);
	bool setDirFromZero(ToWaveStepMotor *);
	bool isOnZero(int);
	void setSpeed(int, unsigned int, unsigned int);
	void setSpeed(int, unsigned int);
	unsigned long getPOS(int);
	int  getSize();
	/*}}}*/
	/*private{{{*/
	#ifndef UNITTEST
 private: 
	#endif /* UNITTEST */	
   ShiftIn 				* shIn;
	ShiftOut 			* shOt; 
	SlaveSPI 			* spi;
	int 					size;
	ToWaveStepMotor 	* sm;
	ToWaveStepMotor 	* tmpSM ;
	/*}}}*/
 };
 /*}}}*/
#endif//run onese
