#include "StepMotor.h"

/*   StepMotor::StepMotor   * {{{ */
StepMotor::StepMotor(int _pin) {
	pin 			= _pin;
	value 		= 0;
	timeout	 	= START_TIME_OUT;
	steps_from_last = 0;
	update_time = micros() + timeout;
	pinMode(pin, OUTPUT);
	} //}}}
/*   StepMotor::StepMotor   * {{{ */
StepMotor::StepMotor() {
	pin = 0;
	value = 0;
	timeout = START_TIME_OUT;
	update_time = micros() + timeout;
	} //}}}

/*   StepMotor::set_speed   * {{{ */
void StepMotor::set_speed(int new_speed){
	timeout = new_speed;
	resetimer();
	} //}}}
/*   StepMotor::move   * {{{ */
void StepMotor::move(long new_value){
	value += new_value;
	checked = false;
	} //}}}

/*   StepMotor::stop   * {{{ */
void StepMotor::stop(long new_value){
	value = new_value;
	} //}}}
/*   StepMotor::stop   * {{{ */
void StepMotor::stop(void){
	value = 0;
	} //}}}

/*   StepMotor::set_enable   * {{{ */
void StepMotor::set_enable(int new_value){
	if (new_value == 0) {
		enable = false;
	}else{	
		enable = true;
		}
	} //}}}

/*   StepMotor::update   * {{{ */
void StepMotor::update(void){
	if ( value != 0) step();
	} //}}}

/*   StepMotor::resetimer   * {{{ */
void StepMotor::resetimer(void){
	update_time = micros() + timeout;
	} //}}}

/*   StepMotor::runtime   * {{{ */
void StepMotor::runtime(void){
	if (micros() < update_time) return;
	step();
	update_time = micros() + timeout;
	} //}}}
/*   StepMotor::done   * {{{ */
bool StepMotor::done(void){
	if ( value == 0 && !checked) {
		checked = true;
		return true;
		}
	else return false;
	} //}}}

/*   StepMotor::step   * {{{ */
void StepMotor::step(void){
	if ( value == 0) return;
	digitalWrite(pin, HIGH);
	value--;
	if (posUp) pos++;
	else pos--;
	steps_from_last++;
	#ifdef DEBAG_STEP_LONGS//{{{
	delayMicroseconds(DEBAG_STEP_LONGS);
	#endif /* DEBAG_STEP_LONGS }}}*/
	digitalWrite(pin, LOW);
	} //}}}

/*   StepMotor::on   * {{{ */
void StepMotor::on(void) {
	digitalWrite(pin, HIGH);
	} //}}}
/*   StepMotor::off   * {{{ */
void StepMotor::off(void) {
	digitalWrite(pin, LOW);
	} //}}}



