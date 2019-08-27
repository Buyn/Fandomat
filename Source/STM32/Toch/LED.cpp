#include "LED.h"

/*   LED::LED   * {{{ */
LED::LED(int _pin) {
	pin = _pin;
	to_value = 0;
	value = 0;
	fade_speed = 10;
	update_time = millis() + fade_speed;
	pinMode(pin, OUTPUT);
	} //}}}
/*   LED::LED   * {{{ */
LED::LED() {
	pin = 0;
	to_value = 0;
	value = 0;
	fade_speed = 10;
	update_time = millis() + fade_speed;
	} //}}}

/*   LED::set_speed   * {{{ */
void LED::set_speed(int new_speed){
	fade_speed = new_speed;
	} //}}}

/*   LED::fade_to   * {{{ */
void LED::fade_to(int new_value){
	to_value = new_value;
	} //}}}

/*   LED::set_to   * {{{ */
void LED::set_to(int new_value){
	to_value = new_value;
	value = new_value;
	set_on();
	} //}}}

/*   LED::set_on   * {{{ */
void LED::set_on(void){
	analogWrite(pin, to_value);
	} //}}}

/*   LED::update   * {{{ */
void LED::update(void){
	if ( value > to_value) fade_Down();
	if ( value < to_value) fade_Up();
	} //}}}

/*   LED::runtime   * {{{ */
void LED::runtime(void){
	if (millis() < update_time) return;
	if ( value != to_value ) update();
	update_time = millis() + fade_speed;
	} //}}}
/*   LED::done   * {{{ */
bool LED::done(void){
	if ( value == to_value ) return true;
	else return false;
	} //}}}

/*   LED::fade_Up   * {{{ */
void LED::fade_Up(void){
	if ( value == LED_MAX_VALUE) return;
	analogWrite(pin, value++);
	//value++;
	} //}}}

/*   LED::fade_Down   * {{{ */
void LED::fade_Down(void){
	if ( value == 0) return;
	analogWrite(pin, value--);
	//to_value--;
	} //}}}

/*   LED::on   * {{{ */
void LED::on(void) {
	digitalWrite(pin, HIGH);
	} //}}}
/*   LED::off   * {{{ */
void LED::off(void) {
	digitalWrite(pin, LOW);
	} //}}}
/*   LED::trige   {{{ */
void LED::trige(void) {
	if (value == 0) {
		on();
		value = 1;
		}
	else{
		off();
		value = 0;
		}
	} //}}}



