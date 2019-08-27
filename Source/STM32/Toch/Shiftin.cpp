#include "ShiftIn.h"

/*   ShiftIn::ShiftIn   * {{{ */
ShiftIn::ShiftIn(void) {
	update_time = millis() + POLL_DELAY_MSEC;
	bitVal = 0;
	bytesVal = 0;
	} //}}}

/*   ShiftIn::initpins   * {{{ */
void ShiftIn::initpins(void){
   pinMode(SHIFTIN_PLOADPIN, OUTPUT);
   pinMode(SHIFTIN_CLOCKENABLEPIN, OUTPUT);
   pinMode(SHIFTIN_CLOCKPIN, OUTPUT);
   pinMode(SHIFTIN_DATAPIN, INPUT);
   digitalWrite(SHIFTIN_CLOCKPIN, LOW);
   digitalWrite(SHIFTIN_PLOADPIN, HIGH);
	} //}}}
/*   ShiftIn::update   * {{{ */
void ShiftIn::update(void){
   /* Read the state of all zones.  */
   read_shift_regs();
   /* If there was a chage in state, display which ones changed.  */
   if(bytesVal != oldPinValues) {
      changed = true;
      oldPinValues = bytesVal;
		}
	} //}}}


/*   ShiftIn::isOn   * {{{ */
bool ShiftIn::isOn(int pin){
	return bitRead(bytesVal , pin); 
	} //}}}

/*   ShiftIn::isChenged   * {{{ */
bool ShiftIn::isChenged(void){
	runtime();
	if(changed){
		changed = false;
		return  true;
		}
	return false;
	} //}}}

/* display_pin_values {{{
Dump the list of zones along with their current status.
*/
void ShiftIn::display_pin_values()
{
    Serial.print("Pin States:\r\n");

    for(int i = 0; i < DATA_WIDTH; i++)
    {
        Serial.print("  Pin-");
        Serial.print(i);
        Serial.print(": ");

        if((bytesVal >> i) & 1)
            Serial.print("HIGH");
        else
            Serial.print("LOW");

        Serial.print("\r\n");
    }

    Serial.print("\r\n");
}/*}}}*/

/*   ShiftIn::runtime   * {{{ */
void ShiftIn::runtime(void){
	if (millis() < update_time) return;
	update();
	update_time = millis() + POLL_DELAY_MSEC;
	} //}}}

/* ShiftIn::read_shift_regs   {{{
This function is essentially a "shift-in" routine reading the
 * serial Data from the shift register chips and representing
 * the state of those pins in an unsigned integer (or long).
*/
void ShiftIn::read_shift_regs(void) {
   /* Trigger a parallel Load to latch the state of the data lines, */
   digitalWrite(SHIFTIN_CLOCKENABLEPIN, HIGH);
   digitalWrite(SHIFTIN_PLOADPIN, LOW);
   delayMicroseconds(PULSE_WIDTH_USEC);
	bytesVal = 0;
   bitVal 	= 0;
   digitalWrite(SHIFTIN_PLOADPIN, HIGH);
   digitalWrite(SHIFTIN_CLOCKENABLEPIN, LOW);
   /* Loop to read each bit value from the serial out line {{{
    * of the SN74HC165N.  */
   for(int i = 0; i < DATA_WIDTH; i++) {
      bitVal = digitalRead(SHIFTIN_DATAPIN);
      /* Pulse the Clock (rising edge shifts the next bit).  */
      digitalWrite(SHIFTIN_CLOCKPIN, HIGH);
      /* Set the corresponding bit in bytesVal.  */
      bytesVal |= (bitVal << ((DATA_WIDTH-1) - i));
      //delayMicroseconds(PULSE_WIDTH_USEC);
      digitalWrite(SHIFTIN_CLOCKPIN, LOW);
	   }/*}}}*/
	}/*}}}*/


