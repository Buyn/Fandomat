#include "simplencoder.h"

/*   SimplEncoder::SimplEncoder   * {{{ */
SimplEncoder::SimplEncoder(int _enc_pin1, int _enc_pin2, int _enc_pin3, unsigned long _delay){
	enc_pin1 = _enc_pin1;	
	enc_pin2 = _enc_pin2;	
	enc_pin3 = _enc_pin3;	
	delay_time	= _delay;
	reset_time();
	//set_interrupts();
	} //}}}
/*    SimplEncoder::reset_time   {{{ */
void SimplEncoder::reset_time(){ 
	sensor_time	= millis() + delay_time;
	} //}}}
/*   SimplEncoder::set_interapts   * {{{ */
void SimplEncoder::set_interrupts(void){
//   attachInterrupt(digitalPinToInterrupt(enc_pin1), encoder1, CHANGE );
	} //}}}

/*   SimplEncoder::encoder1   * {{{ */
void SimplEncoder::encoder1(void){
	if (digitalRead(enc_pin1) == HIGH){
		if (digitalRead(enc_pin2) == HIGH) counter3--;
		else  counter3++;
		return;	
		}
	else {
		if (digitalRead(enc_pin2) == HIGH) counter3++;
		else  counter3--;
		return;	
		}
	} //}}}
/*   SimplEncoder::encoder2   * {{{ */
void SimplEncoder::encoder2(void){
	if (digitalRead(enc_pin2) == HIGH){
		if (digitalRead(enc_pin1) == HIGH) counter3++;
		else  counter3--;
		return;	
		}
	else {
		if (digitalRead(enc_pin1) == HIGH) counter3--;
		else  counter3++;
		return;	
		}
	} //}}}
/*   SimplEncoder::have_data   * {{{ */
bool SimplEncoder::have_data(void){
  if (millis() >= sensor_time) 
  		return true;
	else 
  		return false;
  } //}}}

/*   SimplEncoder::reset_countes   * {{{ */
String SimplEncoder::reset_countes(void){
	temptxt = get_sensor_txt();	
	counter1 = 0;
	//counter3 = 0;
	reset_time();
	return temptxt; 
	} //}}}
/*   SimplEncoder::reset_uint   * {{{ */
	unsigned int SimplEncoder::reset_uint(void){
	//temptxt = get_sensor_txt();	
	//temptxt += counter3 ;
	counter1 = 0;
	//counter3 = 0;
	reset_time();
	return counter3; 
	} //}}}
/*   SimplEncoder::get_sensor_txt   * {{{ */
String SimplEncoder::get_sensor_txt(void){
	temptxt = "c1 =" + counter1;
	temptxt += ", c3 =" ;
	temptxt += counter3 ;
	return temptxt;
	} //}}}
