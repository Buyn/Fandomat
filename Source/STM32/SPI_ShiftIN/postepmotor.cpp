#include "postepmotor.h"

/*   POStepMotor::POStepMotor   * {{{ */
POStepMotor::POStepMotor(ShiftIn * _shIn, ShiftOut * _shOt, SlaveSPI * _spi){
   shIn	= _shIn;
	shOt	= _shOt; 
	spi 	= _spi;
	size 	= 0;
	sm = (ToWaveStepMotor *)malloc ( sizeof (ToWaveStepMotor) * ARRMAX);
	} //}}}

/*   POStepMotor::addMotor   * {{{ */
void POStepMotor::addMotor(int _steppin,int _zeropin, int _dirpin, bool _isDirToZero){
// TODO легко может поломатся нужно сделать прочнее
// TODO или хоть добавить сообшения перед смертью
	size++;
	int tmp = size -1;
	sm = (ToWaveStepMotor *) realloc (sm, sizeof (ToWaveStepMotor) * size);
	sm [tmp] = ToWaveStepMotor(_steppin);
	sm [tmp].zeropin = _zeropin ;
	sm [tmp].dirpin = _dirpin ;
	sm [tmp].isDirToZero = _isDirToZero;
	sm [tmp].pos = 0;
	sm [tmp].isMaintenance = false;
	sm [tmp].steps_from_last = 0;
	} //}}}

/*   POStepMotor::getMotor   * {{{ */
ToWaveStepMotor * POStepMotor::getMotor(int motorNum){
	return & sm[motorNum];
	} //}}}

/*   POStepMotor::startManteins   * {{{ */
void POStepMotor::startManteins(int motorNum){
	sm[motorNum].isMaintenance = true;
	} //}}}
/*   POStepMotor::manteins   * {{{ */
void POStepMotor::manteins(int motorNum){
	tmpSM = getMotor(motorNum);
	if(!tmpSM->isMaintenance)return ;
	//TODO Function add shIn->Update(micros from last update)
	if (!shIn->isOn(tmpSM->zeropin) ){
		tmpSM->isMaintenance		= true;
		tmpSM->pos 					= 10;
		tmpSM->stop(100);
		gotoPOS(motorNum, 0);
		return ;
		}
	tmpSM->steps_from_last 	= 0;
	tmpSM->pos 					= 0;
	tmpSM->stop(0);
	tmpSM->isMaintenance		= false;
	return ;
	} //}}}

/*   POStepMotor::runtime   * {{{ */
bool POStepMotor::runtime(void){
	for (int i = 0; i < size; i++) {
		manteins(i);
		runtime(i);
		}
	} //}}}
/*   POStepMotor::runtime   * {{{ */
bool POStepMotor::runtime(int motorNum){
	sm[motorNum].runtime();
	} //}}}

/*   POStepMotor::gotoPOS   * {{{ */
unsigned long POStepMotor::gotoPOS(int motorNum, unsigned long newPos){
	tmpSM = getMotor(motorNum);
	if( tmpSM->pos == newPos){
		return tmpSM->pos;
		}
	if( tmpSM->pos > newPos){
		tmpSM->move( tmpSM->pos - newPos);
		setDirToZero(tmpSM);
		return tmpSM->pos;
		}
	if( tmpSM->pos < newPos){
		tmpSM->move( newPos - tmpSM->pos );
		setDirFromZero(tmpSM);
		return tmpSM->pos;
		}
	} //}}}

/*   POStepMotor::setDirToZero   * {{{ */
bool POStepMotor::setDirToZero(ToWaveStepMotor * pSM){
	if (pSM->isDirToZero) shOt->on( pSM->dirpin);
	else  shOt->off( pSM->dirpin);
	pSM->posUp = false;
	return pSM->isDirToZero;
	} //}}}
/*   POStepMotor::setDirFromZero   * {{{ */
bool POStepMotor::setDirFromZero(ToWaveStepMotor * pSM){
	if (!pSM->isDirToZero) shOt->on( pSM->dirpin);
	else  shOt->off( pSM->dirpin);
	pSM->posUp = true;
	return !pSM->isDirToZero;
	} //}}}

