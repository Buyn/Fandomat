#include "RGB_LED.h"

/*   RGB_LED::encounter   * {{{ */
RGB_LED::RGB_LED(int red_pin, int green_pin, int blue_pin) {
	red.pin = red_pin;
	green.pin = green_pin;
	blue.pin = blue_pin;
	fade_speed = 100;
	update_time = millis() + fade_speed;
	pinMode(red_pin, OUTPUT);
	pinMode(green_pin, OUTPUT);
	pinMode(blue_pin, OUTPUT);
	} //}}}

/*   RGB_LED::set_speed   * {{{ */
void RGB_LED::set_speed(int new_speed){
	fade_speed = new_speed;
	} //}}}

/*   RGB_LED::fade_to   * {{{ */
void RGB_LED::fade_to(int r, int g, int b){
	red.fade_to(r);
	green.fade_to(g);
	blue.fade_to(b);
	} //}}}

/*   RGB_LED::set_to   * {{{ */
void RGB_LED::set_to(int r,int g,int b){
	red.set_to(r);
	green.set_to(g);
	blue.set_to(b);
	} //}}}

/*   RGB_LED::update   * {{{ */
void RGB_LED::update(void){
	red.update();
	green.update();
	blue.update();
	} //}}}

/*   RGB_LED::runtime   * {{{ */
void RGB_LED::runtime(void){
	if (millis() < update_time) return;
	if ( !red.done() || !green.done() || !blue.done() ) update();
	update_time = millis() + fade_speed;
	} //}}}
/*   RGB_LED::done   * {{{ */
bool RGB_LED::done(void){
	if ( red.done() && green.done() && blue.done() ) return true;
	else return false;
	} //}}}






