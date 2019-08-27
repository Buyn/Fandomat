#include "EnScaner.h"

/*   EnScaner::EnScaner   * {{{ */
EnScaner::EnScaner( 
						SimplEncoder * _encoder, 
						SlaveSPI * _spi, 
						POStepMotor * _posm, 
						//void (* _loopointer)){
						GeneralMessageFunction _loopMain){
	encoder = _encoder; 
	spi = _spi; 
	posm = _posm; 
	//loopointer = _loopointer;
	loopMain = _loopMain;
	} //}}}

/*   EnScaner::stop   * {{{ */
void EnScaner::stop(void){
	//value = 0;
	} //}}}



