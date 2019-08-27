#include "ShiftOut.h"

/*   ShiftOut::ShiftOut   * {{{ */
ShiftOut::ShiftOut(void) {
	oldPinValues = 0 ;
	} //}}}

/*   ShiftOut::initpins   * {{{ */
void ShiftOut::initpins(void){
   pinMode(LATCHPIN, OUTPUT);
   pinMode(CLOCKPIN, OUTPUT);
   pinMode(DATAPIN , OUTPUT);
	allOff();
	} //}}}

/*   ShiftOut::send16   * {{{ */
bool ShiftOut::send16(BYTES_VAL_T value){
	if (value == oldPinValues) return false;
#ifdef UNITTEST/*{{{*/
	std::cerr << "\n Start new test:";
	for ( int i=0 ; i < 16 ; i++ ) {/*{{{*/
		std::cerr << "\n pin "<<i <<" : ";
		std::cerr  << !!(value & (1 << i));
		}/*}}}*/
	std::cerr << "\n End of test:";
	oldPinValues = value;
	return  !!(value & (1 << 4));
#endif /* UNITTEST }}}*/
	#ifndef UNITTEST/*{{{*/
	// устанавливаем синхронизацию "защелки" на LOW
	digitalWrite(LATCHPIN, LOW);
	for ( int i=0 ; i < 16 ; i++ ) {/*{{{*/
		digitalWrite( DATAPIN, !!(value & (1 << i)) ) ;
		digitalWrite( CLOCKPIN, HIGH ) ;
		digitalWrite( CLOCKPIN, LOW ) ;		
		}/*}}}*/
	//"защелкиваем" регистр, тем самым устанавливая значения на выходах
	digitalWrite(LATCHPIN, HIGH);
	oldPinValues = value;
	return true;
	#endif /* UNITTEST }}}*/
	} //}}}

/*   ShiftOut::allOff   * {{{ */
void ShiftOut::allOff(){
#ifdef UNITTEST/*{{{*/
	std::cerr << "\n Start new test:";
	for ( int i=0 ; i < 16 ; i++ ) {/*{{{*/
		std::cerr << "\n pin "<<i <<" : ";
		std::cerr  << LOW;
		}/*}}}*/
	std::cerr << "\n End of test:";
	oldPinValues = 0;
#endif /* UNITTEST }}}*/
	#ifndef UNITTEST/*{{{*/
	// устанавливаем синхронизацию "защелки" на LOW
	digitalWrite(LATCHPIN, LOW);
	for ( int i=0 ; i < 16 ; i++ ) {/*{{{*/
		digitalWrite( DATAPIN, LOW ) ;
		digitalWrite( CLOCKPIN, HIGH ) ;
		digitalWrite( CLOCKPIN, LOW ) ;		
		}/*}}}*/
	//"защелкиваем" регистр, тем самым устанавливая значения на выходах
	digitalWrite(LATCHPIN, HIGH);
	oldPinValues = 0;
	return ;
	#endif /* UNITTEST }}}*/
	} //}}}

/*   ShiftOut::isOn   * {{{ */
bool ShiftOut::isOn(int pin){
	return bitRead(oldPinValues , pin - 1); 
	} //}}}

/*   ShiftOut::on   * {{{ */
BYTES_VAL_T ShiftOut::on(int pin){
	tmpPinValues = oldPinValues;
	bitSet(tmpPinValues, pin );
	send16(tmpPinValues);
	return oldPinValues; 
	} //}}}

/*   ShiftOut::off   * {{{ */
BYTES_VAL_T ShiftOut::off(int pin){
	tmpPinValues = oldPinValues;
	bitClear(tmpPinValues, pin );
	send16(tmpPinValues);
	return oldPinValues; 
	} //}}}

/* display_pin_values {{{
Dump the list of zones along with their current status.
*/
void ShiftOut::display_pin_values() {
	 #ifdef DEBUGMSG_PINS/*{{{*/
    Serial.print("Pin States:\r\n");
    for(int i = 0; i < DATA_WIDTH; i++) {/*{{{*/
       Serial.print("  Pin-");
       Serial.print(i);
       Serial.print(": ");
       if((oldPinValues >> i) & 1)
           Serial.print("HIGH");
       else
           Serial.print("LOW");

       Serial.print("\r\n");
		 }/*}}}*/
    Serial.print("\r\n");
	 #endif/*DEBUGMSG_PINS}}}*/
	}/*}}}*/

