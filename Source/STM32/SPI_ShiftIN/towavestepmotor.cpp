#include "ToWaveStepMotor.h"

/*   ToWaveStepMotor::ToWaveStepMotor   * {{{ */
ToWaveStepMotor::ToWaveStepMotor(int _pin) {
	pin 			= _pin;
	value 		= 0;
	timeout	 	= START_TIME_OUT;
	longs		 	= DEBAG_STEP_LONGS;
	enable		= false;
	steps_from_last = 0;
	resetimer();
	pinMode(pin, OUTPUT);
	} //}}}
/*   ToWaveStepMotor::ToWaveStepMotor   * {{{ */
ToWaveStepMotor::ToWaveStepMotor() {
	pin = 0;
	value = 0;
	timeout = START_TIME_OUT;
	update_time = micros() + timeout;
	} //}}}

/*   ToWaveStepMotor::set_speed   * {{{ */
void ToWaveStepMotor::set_speed(int new_speed){
	timeout = new_speed;
	resetimer();
	} //}}}
/*   ToWaveStepMotor::set_timeout   * {{{ */
void ToWaveStepMotor::set_timeout(int _new){
	timeout = _new;
	resetimer();
	} //}}}
/*   get_longs   * {{{ */
unsigned long ToWaveStepMotor::get_longs(void){
	return longs;
	} //}}}

/*   get_timeout   * {{{ */
unsigned long ToWaveStepMotor::get_timeout(void){
	return timeout;
	} //}}}
/*   ToWaveStepMotor::set_longs   * {{{ */
void ToWaveStepMotor::set_longs(int _new){
	longs = _new;
	resetimer();
	} //}}}
/*   ToWaveStepMotor::move   * {{{ */
void ToWaveStepMotor::move(long new_value){
	value += new_value;
	checked = false;
	} //}}}

/*   ToWaveStepMotor::stop   * {{{ */
void ToWaveStepMotor::stop(long new_value){
	value = new_value;
	} //}}}
/*   ToWaveStepMotor::stop   * {{{ */
void ToWaveStepMotor::stop(void){
	value = 0;
	} //}}}

/*   ToWaveStepMotor::set_enable   * {{{ */
void ToWaveStepMotor::set_enable(int new_value){
	if (new_value == 0) {
		enable = false;
	}else{	
		enable = true;
		}
	} //}}}

/*   ToWaveStepMotor::update   * {{{ */
void ToWaveStepMotor::update(void){
	if ( value == 0) {
		if (enable) off();
		return;
		}
	if (enable) off();
	else on();
	} //}}}

/*   ToWaveStepMotor::resetimer   * {{{ */
void ToWaveStepMotor::resetimer(void){
	if (enable) update_time = micros() + longs;
	else update_time = micros() + timeout;
	} //}}}

/*   ToWaveStepMotor::runtime   * {{{ */
void ToWaveStepMotor::runtime(void){
	if (micros() < update_time) return;
	update();
	resetimer();
	} //}}}
/*   ToWaveStepMotor::done   * {{{ */
bool ToWaveStepMotor::done(void){
	if ( value == 0 && !checked) {
		checked = true;
		return true;
		}
	else return false;
	} //}}}

/*   ToWaveStepMotor::step   * {{{ */
void ToWaveStepMotor::step(void){
	if ( value == 0) return;
	analogWrite(pin, HIGH);
	value--;
	steps_from_last++;
	#ifdef DEBAG_STEP_LONGS//{{{
	delayMicroseconds(DEBAG_STEP_LONGS);
	#endif /* DEBAG_STEP_LONGS }}}*/
	analogWrite(pin, LOW);
	} //}}}

/*   ToWaveStepMotor::on   * {{{ */
void ToWaveStepMotor::on(void) {
	digitalWrite(pin, HIGH);
	enable = true;
	value--;
	steps_from_last++;
	} //}}}
/*   ToWaveStepMotor::off   * {{{ */
void ToWaveStepMotor::off(void) {
	digitalWrite(pin, LOW);
	enable = false;
	} //}}}



