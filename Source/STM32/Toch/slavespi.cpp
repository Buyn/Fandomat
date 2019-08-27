#include "SlaveSPI.h"

/*   SlaveSPI::SlaveSPI   * {{{ */
SlaveSPI::SlaveSPI(int adrress) {
	command_stak.resize(STACK_COMMAND_SIZE);
	msg_stak.resize(STACK_MSG_SIZE);
	spiaddress = adrress;
	} //}}}

/*   SlaveSPI::spinit   * {{{ */
void SlaveSPI::spinit(void){
   // The clock value is not used
   // SPI1 is selected by default
   // MOSI, MISO, SCK and NSS PINs are set by the library
#ifndef UNITTEST/*{{{*/
   SPI.beginTransactionSlave(SPISettings(18000000, MSBFIRST, SPI_MODE0, DATA_SIZE_16BIT));
#endif/*UNITTEST }}}*/
	} //}}}

/*   SlaveSPI::add_to_stak   * {{{ */
void SlaveSPI::add_to_stak(void){
#ifdef DEBUGMSG_EXECUTESTAK/*{{{*/
	Serial.print(": command waiting: ");
	Serial.println(commands_waiting);
#endif/*}}}*/
	commands_waiting--;
	command_stak.push(msg);
	back_msg = msg;	
	} //}}}

/*   SlaveSPI::execute_command   *  {{{ */
void SlaveSPI::execute_command(void){
#ifdef DEBUGMSG_EXECUTESTAK/*{{{*/
	Serial.println(micros());
#endif/*}}}*/
	//{{{ is adding list command
	if (msg <= 15) {
		commands_waiting = msg;	
#ifdef DEBUGMSG_EXECUTESTAK/*{{{*/
		Serial.print(micros());
		Serial.print(": Command waiting - ");
		Serial.println(commands_waiting);
#endif/*}}}*/
		back_msg = command_stak.count();
		return;
		}/*}}}*/
#ifdef DEBUGMSG_EXECUTESTAK/*{{{*/
	Serial.println(": Command Exekution  ");
#endif/*}}}*/
	switch (msg) {/* {{{*/
		case EXECUTE:/*{{{*/
#ifdef DEBUGMSG_EXECUTESTAK/*{{{*/
			Serial.println("Execute Last");
#endif/*DEBUGMSG_EXECUTESTAK}}}*/
			commands_waiting = 0;
			back_msg = msg;
			command_to_execute	= true;
			break;/*}}}*/
		case SC_GETMSGBYCOUNT:/*{{{*/
#ifdef DEBUGMSG_INFO /*{{{*/
			Serial.print("given back MSG: ");
			Serial.println(msg_stak.count());
#endif/*DEBUGMSG_INFO  }}}*/
			back_msg = msg_stak.pop();
			msg_waiting = 1;
			break;/*}}}*/
		case SC_ISMSGWATING:/*{{{*/
#ifdef DEBUGMSG_INFO /*{{{*/
			Serial.print("Asket number of MSG: ");
			Serial.println(msg_stak.count());
#endif/*DEBUGMSG_INFO }}}*/
			back_msg = msg_stak.count();
			break;/*}}}*/
		case ENDOFFILE:/*{{{*/
#ifdef DEBUGMSG_INFO /*{{{*/
			Serial.println("ENDOFFILE");
#endif/*DEBUGMSG_INFO }}}*/
			commands_waiting = 0;
			back_msg = msg_stak.count();
			break;/*}}}*/
		case ENDOFSESION:/*{{{*/
#ifdef DEBUGMSG_INFO /*{{{*/
			Serial.println("ENDOFSESION");
#endif/*DEBUGMSG_INFO }}}*/
			back_msg = msg;
			spi_sesion = false;
			commands_waiting = 0;
			msg_waiting = 0;
			break;/*}}}*/
		default:/*{{{*/
			Serial.println("Error in stek command execute!!!");
			Serial.println("ENDOFSESION");
			spi_sesion = false;
			commands_waiting = 0;
			back_msg = STAKERRORCOMAND;
			/*}}}*/
			}/*}}}*/
	} //}}}

/*   SlaveSPI::sendFromStack   * {{{ */
void SlaveSPI::sendFromStack(void){
#ifdef DEBUGMSG_EXECUTESTAK/*{{{*/
	Serial.print("given back value : ");
	Serial.println(msg_waiting);
#endif/*}}}*/
	back_msg = msg_stak.pop();
	//if( msg_waiting > 0 ) msg_waiting--;
	msg_waiting = msg;
	} //}}}

/*   SlaveSPI::addMSG   * {{{ */
int SlaveSPI::addMSG(int name, unsigned int value){
	msg_stak.push(name);
#ifdef DEBUGMSG_MSGSTASK/*{{{*/
	Serial.print(name);
	Serial.print(" :Pushing in MSG stack : ");
	Serial.println(value);
	Serial.print(" MSG in stack : ");
	Serial.println( msg_stak.count());
#endif/*DEBUGMSG_MSGSTASK}}}*/
	msg_stak.push(value);
	return msg_stak.count();
	} //}}}

/*   SlaveSPI::isSesionEnd   * {{{ */
bool SlaveSPI::isSesionEnd(void){
	if (!spi_sesion) return true;
	if (millis() >= sesionend){
		back_msg = TIMEOUTSESION;	
		spi_sesion = false;
		commands_waiting = 0;
		msg_waiting = 0;
		Serial.print(micros());
		Serial.println(": Sesion end: Timeout Error");
		return true;
		}
	return false;
	} //}}}

/*   SlaveSPI::peek   * {{{ */
int SlaveSPI::peek(void){
	return command_stak.peek();
	} //}}}

/*   SlaveSPI::pull   * {{{ */
int SlaveSPI::pull(void){
		if (command_to_execute){
#ifdef DEBUGMSG_EXECUTESTAK/*{{{*/
			Serial.print( command_stak.peek());
			Serial.println(" : Set command to false");
#endif/*}}}*/
			command_to_execute = false;
			}
#ifdef DEBUGMSG_EXECUTESTAK/*{{{*/
		Serial.print( command_stak.peek());
		Serial.println(" - Get form stak ");
#endif/*}}}*/
		return command_stak.pop();
	} //}}}

/*   SlaveSPI::staksize   * {{{ */
int SlaveSPI::staksize(void){
	return command_stak.count();
	} //}}}

/*   SlaveSPI::isExecute   * {{{ */
bool SlaveSPI::isExecute(void){
	return command_to_execute;
	} //}}}

/*   SlaveSPI::setmsg   * {{{ */
void SlaveSPI::setmsg(int newmsg){
	back_msg = newmsg;
	} //}}}

/*   SlaveSPI::setSPIbackmsg   * {{{ */
void SlaveSPI::setSPIbackmsg(spi_dev * spi_d){
#ifndef UNITTEST/*{{{*/
	while (spi_is_busy(spi_d)); // "... and then wait until BSY=0 before disabling the SPI."
	spi_tx_reg(spi_d, back_msg); // write the data to be transmitted into the SPI_DR register (this clears the TXE flag)
#endif/*UNITTEST }}}*/
	} //}}}

/*   SlaveSPI::testmsg   * {{{ */
#ifdef UNITTEST/*{{{*/
void SlaveSPI::testmsg(int newmsg){
	msg = newmsg;
	spirutine( (spi_dev *) & newmsg);
	//spi_sesion = true;
	} //}}}
#endif /*UNITTEST}}}*/

/*   SlaveSPI::runtime   * {{{ */
bool SlaveSPI::runtime(void){
#ifndef UNITTEST/*{{{*/
   //spi_dev * spi_d = SPI.dev();
   spi_d = SPI.dev();
	if ( spi_is_tx_empty(spi_d) && !spi_is_busy(spi_d)) { /*{{{*/
		setSPIbackmsg(spi_d);
		}/*}}}*/
	if ( spi_is_rx_nonempty(spi_d) && !spi_is_busy(spi_d)) { /*{{{*/
		spirutine(spi_d);
		}/*}}}*/
#endif/*UNITTEST }}}*/
	return command_to_execute;
	} //}}}

/*   SlaveSPI::readyTransfer   * {{{ */
UINT SlaveSPI::readyTransfer(spi_dev * spi_d){
#ifndef UNITTEST/*{{{*/
   //spi_dev * spi_d = SPI.dev();
	if ( spi_is_tx_empty(spi_d)) { 
		while (spi_is_busy(spi_d)); // "... and then wait until BSY=0 before disabling the SPI."
#ifdef DEBUGMSG_INFO/*{{{*/
		Serial.print("spi tx wose empty");
#endif /*DEBUGMSG_INFO}}}*/
		spi_tx_reg(spi_d, back_msg); // write the data to be transmitted into the SPI_DR register (this clears the TXE flag)
		}
	while (spi_is_busy(spi_d)); // "... and then wait until BSY=0 before disabling the SPI."
	return (UINT)spi_rx_reg(spi_d);
#endif/*UNITTEST }}}*/
#ifdef UNITTEST/*{{{*/
	return back_msg;
#endif/*UNITTEST }}}*/
	} //}}}

/*   SlaveSPI::spirutine   *  {{{ */
void SlaveSPI::spirutine(spi_dev * spi_d){
	msg = readyTransfer(spi_d);
	isSesionEnd();
#ifdef DEBUGMSG_RECIVSEND/*{{{*/
	Serial.print("Recived = 0x");
	Serial.print(msg, HEX);
	Serial.print(", ");
	Serial.println(msg);
	Serial.print("Send = ");
	Serial.println(back_msg);
#endif/*}}}*/
	if (!spi_sesion && msg == spiaddress) {/*{{{*/
		back_msg = msg;	
		setSPIbackmsg(spi_d);
		spi_sesion = true;
		commands_waiting = 0;
		msg_waiting = 0;
		sesionend = millis() + SESIONTIMEOUT;
#ifdef DEBUGMSG_INFO /*{{{*/
		//Serial.print(micros());
		Serial.println("Connected: Start sesion");
		//Serial.println(sesionend);
#endif/*DEBUGMSG_INFO }}}*/
		return;
		}/*}}}*/
	else if (spi_sesion && msg_waiting != 0 && !isSesionEnd()) {/*{{{*/
		sendFromStack();
		setSPIbackmsg(spi_d);
		}/*}}}*/
	else if (spi_sesion && commands_waiting == 0 && !isSesionEnd()) {/*{{{*/
		execute_command();
		setSPIbackmsg(spi_d);
		}/*}}}*/
	else if (spi_sesion && commands_waiting > 0 && !isSesionEnd()) {/*{{{*/
		add_to_stak();
		setSPIbackmsg(spi_d);
		}/*}}}*/
	else  {/*{{{ Error*/
		Serial.print(micros());
		Serial.println(": Disinhron!  Error  ");
		Serial.println("ENDOFSESION");
		back_msg = DISINHRONERROR;
		spi_sesion = false;
		commands_waiting = 0;
		msg_waiting = 0;
		if(msg != spiaddress) back_msg = DISINHRONADRESSERROR;
		setSPIbackmsg(spi_d);
		}/*}}}*/
	} //}}}
