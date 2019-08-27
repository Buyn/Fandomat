// SPI full-duplex slave example{{{
// STM32 acts as a SPI slave and reads 8 bit data frames over SPI.
// Master also gets a reply from the slave, which is a a simple count (0, 1, 2, 3)
// that is incremented each time a data frame is received.
// Serial output is here for debug
/*}}}*/
/* Include Block{{{*/
#include "RGB_LED.h"
#include "LED.h"
#include "slaveSPI.h"
#include "Shiftin.h"
#include "ShiftOut.h"
#include <cstdint>
#include "simplencoder.h"
#include "towavestepmotor.h"
#include "postepmotor.h"
#include "stepmotor.h"
#include "EnScaner.h"
/*}}}*/

/*Define Block{{{*/
/*LEDS LINE{{{*/
#define RBG_PIN_R PA8   // пин для канала R
#define RBG_PIN_G PA9   // пин для канала G
#define RBG_PIN_B PA10  // пин для канала B
#define LED_MAX_VALUE 255    
#define MAX_STATS 3    
#define FADESPEED 10   
/*}}}*/
//debug msges {{{
//#define	DEBUGMSG_LEDLINE
//#define	DEBUGMSG_SHIFTINFO
#define	DEBUGMSG_STEPMOTORDONE
//#define SPI_CS_PIN PA4   // пин для канала B
/*}}}*/
//#define STEKSIZE 30   
#define TITLEABOUT "SPI LED v 0.1"
//Commands list
#define SPIADRRES			0x08
//LED comands{{{
#define LEDSTOP 		0x10
#define LEDSTART		0x11
#define LEDMAXSTATE 	0x12
#define LEDSET	 		0x14
#define LED01SET		0x1A
#define LED02SET		0x1B
#define LED03SET		0x1C/*}}}*/
//ShiftOut comands
#define SETSHIFTOUT     0x21
//Step Drivers{{{
/*list cods comands{{{*/
#define STARTDRIVER    0x31
#define STOPDRIVER     0x32
#define SM_STEP              0x33
#define SM_SPEED             0x34
#define SM_ENABLE            0x35
#define SM_DIR               0x36
#define SM_LONGS             0x37
#define SM_POS               0x38
#define SM_MNT               0x39
/*}}}*/
/*step motors pins{{{*/
#define STEPDRIVERTIMEOUT     1112
#define STEPDRIVERPIN01     PB9
#define STEPDRIVERPIN02     PB8
#define STEPDRIVERPIN03     PB7
#define STEPDRIVERPIN04     PB6
#define STEPDRIVERPIN05     PB5
#define STEP_X		STEPDRIVERPIN01     
#define DIR_X		0     
#define ZERO_X		9     
#define STEP_Y		STEPDRIVERPIN02     
#define DIR_Y		2     
#define ZERO_Y		8     
#define STEP_Z		STEPDRIVERPIN03     
#define ZERO_Z		2     
#define STEP_A		STEPDRIVERPIN04     
#define STEP_I		STEPDRIVERPIN05     
#define STEP_R		STEPDRIVERPIN05     
/*}}}*/
/*}}}*/
//encounter comands{{{
#define STARTECOUNTER    0x41
#define STOPECOUNTER     0x42
#define ENCPIN1				PB10
#define ENCPIN2				PB11
#define ENCPIN3				PB1
#define SENSOR_DELAY			100
/*}}}*/
/*}}}*/

/*Varibls Block{{{*/
//LEDs{{{
RGB_LED led_Line(RBG_PIN_R, RBG_PIN_G, RBG_PIN_B);
int state = 0;
unsigned int ledstate01[] = {255	, 0	, 0	, 10};
unsigned int ledstate02[] = {0	, 255	, 0	, 10};
unsigned int ledstate03[] = {0	, 0	, 255	, 10};
bool led_activ  = true;
int max_state = MAX_STATS;
LED test(LED_BUILTIN);
/*}}}*/
SlaveSPI sspi(SPIADRRES);
ShiftIn sinput;
ShiftOut shiftout;
bool encodermode = false;
SimplEncoder sencoder(ENCPIN1, ENCPIN2, ENCPIN3, SENSOR_DELAY);
ToWaveStepMotor smotors[] = {/*{{{*/
								ToWaveStepMotor(STEPDRIVERPIN01),
								ToWaveStepMotor(STEPDRIVERPIN02),
								ToWaveStepMotor(STEPDRIVERPIN03),
								ToWaveStepMotor(STEPDRIVERPIN04),
								ToWaveStepMotor(STEPDRIVERPIN05),
								};
unsigned long stepDrivetime = 0;
bool stepDriveMode = true;
POStepMotor posSM = POStepMotor( &sinput, &shiftout, &sspi);
								/*}}}*/
EnScaner eScan(
				& sencoder,
				& sspi,
				& posSM,
				& loop);
/*}}}*/

/*   setupLEDLine   * {{{ */
void setupLEDLine(void){
	// RGBLED
	pinMode(RBG_PIN_R, OUTPUT);
	pinMode(RBG_PIN_G, OUTPUT);
	pinMode(RBG_PIN_B, OUTPUT);
	test.trige();
	Serial.println("Full Red");
	led_Line.set_to( 255, 0, 0);
	delay(100);
	test.trige();
	Serial.println("Full Green");
	led_Line.set_to( 0, 255 , 0);
	delay(100);
	test.trige();
	Serial.println("Full Blue");
	led_Line.set_to(0, 0, 255);
	delay(100);
	test.trige();
	led_Line.set_speed(FADESPEED);
	} //}}}


/*   execute_command   *  {{{ */
void execute_command(void){
	Serial.print("In execut Switch");
	Serial.println(sspi.peek());
	int tag1 ;
	switch (sspi.pull()) {/*{{{*/
		case LEDSTART:/*{{{*/
			Serial.println("Start LED");
			led_activ = true;
			test.trige();
			sspi.setmsg( 0 );
			break;/*}}}*/
		case LEDSTOP:/*{{{*/
			Serial.println("Stop LED");
			led_activ = false;
			test.trige();
			sspi.setmsg( 0 );
			break;/*}}}*/
		case LED01SET:/*{{{*/
			Serial.println("Set Led 01");
				for (int i = 0; i <= 3; i++) {
					ledstate01[i] = sspi.pull();		
				}
			test.trige();
			sspi.setmsg( 0 );
			break;/*}}}*/
		case LED02SET:/*{{{*/
			Serial.println("Set Led 02");
				for (int i = 0; i <= 3; i++) {
					ledstate02[i] = sspi.pull();		
				}
			test.trige();
			sspi.setmsg( 0 );
			break;/*}}}*/
		case LED03SET:/*{{{*/
			Serial.println("Set Led 03");
				for (int i = 0; i <= 3; i++) {
					ledstate03[i] = sspi.pull();		
				}
			test.trige();
			sspi.setmsg( 0 );
			break;/*}}}*/
		case SETSHIFTOUT:/*{{{*/
#ifdef  DEBUGMSG_SHIFTINFO/*{{{*/
			Serial.print("Set LEDs pins to:");
			Serial.println(sspi.peek(), BIN);
#endif/*DEBUGMSG_SHIFTINFO}}}*/
			shiftout.send16(sspi.pull());
			test.trige();
			sspi.setmsg( 0 );
			break;/*}}}*/
		case LEDSET:/*{{{*/
			Serial.println("To Led Fade");
			led_Line.set_to( sspi.pull(), sspi.pull(), sspi.pull());
			led_Line.set_speed(sspi.pull());
			test.trige();
			sspi.setmsg( 0 );
			break;/*}}}*/
		case LEDMAXSTATE:/*{{{*/
			Serial.print("Number of LED using - ");
			Serial.println(sspi.peek());
			max_state = sspi.pull();
			test.trige();
			sspi.setmsg( 0 );
			break;/*}}}*/
		case STARTDRIVER:/*{{{*/
			Serial.print("START DRIVER");
			stepDriveMode = true;
			test.trige();
			break;/*}}}*/
		case STOPDRIVER:/*{{{*/
			Serial.print("STOP DRIVER");
			stepDriveMode = false;
			test.trige();
			break;/*}}}*/
		case SM_STEP:/*{{{*/
			Serial.print("Set move for motor = ");
			Serial.print(sspi.peek());
			smotors[sspi.pull()].move(sspi.peek());
			posSM.getMotor(sspi.pull())->move(sspi.peek());
			Serial.print(", on = ");
			Serial.println(sspi.pull());
			test.trige();
			break;/*}}}*/
		case SM_SPEED:/*{{{*/
			Serial.print("Set speed for motor = ");
			Serial.print(sspi.peek());
			tag1 =  sspi.pull();
			posSM.getMotor(tag1)->set_speed(sspi.peek());
			Serial.print(", on = ");
			Serial.println(sspi.pull());
			posSM.getMotor(tag1)->resetimer();
			test.trige();
			break;/*}}}*/
		case SM_LONGS:/*{{{*/
			Serial.print("Set longs for motor = ");
			Serial.print(sspi.peek());
			tag1 =  sspi.pull();
			posSM.getMotor(tag1)->set_longs(sspi.peek());
			Serial.print(", on = ");
			Serial.println(sspi.pull());
			posSM.getMotor(tag1)->resetimer();
			test.trige();
			break;/*}}}*/
		case SM_POS:/*{{{*/
			Serial.print("Set position for motor = ");
			Serial.print(sspi.peek());
			tag1 =  sspi.pull();
			posSM.gotoPOS(tag1,sspi.peek());
			Serial.print(", on = ");
			Serial.println(sspi.pull());
			test.trige();
			break;/*}}}*/
		case SM_MNT:/*{{{*/
			Serial.print("Start Maintanse for motor -");
			Serial.print(sspi.peek());
			tag1 =  sspi.pull();
			posSM.startManteins(tag1);
			test.trige();
			break;/*}}}*/
		case STARTECOUNTER:/*{{{*/
			Serial.print("STARTE COUNTER ");
			encodermode = true;
			test.trige();
			break;/*}}}*/
		case STOPECOUNTER:/*{{{*/
			Serial.print("STOPE COUNTER");
			encodermode = false;
			test.trige();
			break;/*}}}*/
		default:/*{{{*/
			Serial.println("Error in command execute!!!");
			test.trige();
			sspi.setmsg( 1 );
			/*}}}*/
			}/*}}}*/
	} //}}}

/*   led_loop   *{{{ */
void led_loop(void){
	switch (state) {
		case 0:/*{{{*/
			Serial.println("To LED 01");
			Serial.print(state);
			led_Line.fade_to( ledstate01[0], ledstate01[1], ledstate01[2]);
			led_Line.set_speed(ledstate01[3]);
			state++;
			state = (state)%max_state;
			Serial.println(state);
			test.trige();
			break;/*}}}*/
		case 1:/*{{{*/
			Serial.println("To LED 02");
			Serial.print(state);
			led_Line.fade_to( ledstate02[0], ledstate02[1], ledstate02[2]);
			led_Line.set_speed(ledstate02[3]);
			state++;
			state = (state)%max_state;
			Serial.println(state);
			test.trige();
			break;/*}}}*/
		case 2:/*{{{*/
			Serial.println("To LED 03");
			Serial.print(state);
			led_Line.fade_to( ledstate03[0], ledstate03[1], ledstate03[2]);
			led_Line.set_speed(ledstate03[3]);
			state++;
			state = (state)%max_state;
			Serial.println(state);
			test.trige();
			break;/*}}}*/
		default:/*{{{*/
			Serial.println("Error in LED State!!!");
			state++;
			state = (state)%MAX_STATS;
			Serial.println(state);
			test.trige();
			/*}}}*/
			}
	}/*}}}*/

void setup() {/*{{{*/
	//enable serial data print
	Serial.begin(115200);
	test.trige();
	//delay(3000);
	setupLEDLine();
	sspi.spinit();
	Serial.println(TITLEABOUT);
   /* Initialize in digital pins...  */
	sinput.initpins();
   /* Initialize our digital pins...  */
	shiftout.initpins();
   /* Read in and display the pin states at startup.  */
	sinput.runtime();
	//shiftout.send16(2048);
	shiftout.allOff();
//int perior =0;
//for (int i = 0; i < 33000; i++) {
//	if (perior == i) {
//		Serial.println(perior);
//			perior = i + 100;
//		}
//	shiftout.send16(i);
//	delay(10);
//	}
	setup_StepMotors();
	//shiftout.on(15);
	//pinMode(ENCPIN1, INPUT);
	//pinMode(ENCPIN2, INPUT);
   //attachInterrupt(digitalPinToInterrupt(ENCPIN1), encoder1, CHANGE );
   //attachInterrupt(digitalPinToInterrupt(ENCPIN2), encoder2, CHANGE );
   //digitalWrite(ENCPIN1,HIGH); //these pins do not have pull up resistors on an attiny...
   //digitalWrite(ENCPIN2,HIGH); //you must pull them up on the board.
	Serial.println("End Setup");
	}/*}}}*/

/*   setup_StepMotors   * {{{ */
void setup_StepMotors(void){
	Serial.println("step pins start int");
   pinMode(STEPDRIVERPIN01, OUTPUT);
   pinMode(STEPDRIVERPIN02, OUTPUT);
   pinMode(STEPDRIVERPIN03, OUTPUT);
   pinMode(STEPDRIVERPIN04, OUTPUT);
   pinMode(STEPDRIVERPIN05, OUTPUT);
	Serial.println("step pins setap to output");
	digitalWrite(STEPDRIVERPIN01, LOW);
	digitalWrite(STEPDRIVERPIN02, LOW);
	digitalWrite(STEPDRIVERPIN03, LOW);
	digitalWrite(STEPDRIVERPIN04, LOW);
	digitalWrite(STEPDRIVERPIN05, LOW);
	Serial.println("step pins int");
	// copy of main global initializiation del it
	//smotors[0] = ToWaveStepMotor(STEPDRIVERPIN01);
	//posSM.addMotor(STEP_X, ZERO_X, DIR_X, false);//a49(true) on big (false)
	posSM.addMotor(STEP_X, ZERO_X, DIR_X, true);//a49(true) on big (false)
	posSM.addMotor(STEP_Y, ZERO_Y, DIR_Y, false);
	posSM.startManteins(0);
	posSM.startManteins(1);
	posSM.getMotor(0)->set_longs(1);
	posSM.getMotor(0)->set_timeout(50);
	//shiftout.on(11);
	//shiftout.send16(1);
	Serial.println("step motor x add");
	//for (int i = 0; i < 5; i++) smotors[i].stop(10000);//i error all is henging
	Serial.println("step motors 100 movs add");
	} //}}}

void loop() {/*{{{*/
	if (led_activ && led_Line.done()) {/*{{{*/
#ifdef DEBUGMSG_LEDLINE/*{{{*/
		Serial.println("LED line Done");
#endif/*DEBUGMSG_LEDLINE}}}*/
		led_loop();
		}/*}}}*/
	if (sspi.runtime()) { //and return if is comand redy to exec{{{
		execute_command();
		}/*}}}*/
	led_Line.runtime();
   /* Read the state of all zones.  */
   //sinput.runtime();
   /* If there was a chage in state, display which ones changed.  */
   if(sinput.isChenged()) {/*and it do runtime(){{{*/
       Serial.print("*Pin value change detected*\r\n");
       sinput.display_pin_values();
		 sspi.addMSG(1, (unsigned int)sinput.oldPinValues); 
		 }/*}}}*/
   /*Step Motrs runtime(){{{*/
	posSM.runtime();
	for (int i = 0; i < 5; i++) {
			//smotors[i].stop(100);//i error all is henging
			smotors[i].runtime();
			#ifdef DEBUGMSG_STEPMOTORDONE//{{{
			print_on_done(i);
			#endif /* DEBUGMSG_STEPMOTORDONE }}}*/			
			}
		/*}}}*/
	/*
	if (encodermode && sencoder.have_data()) {{{
			shiftout.send16(sencoder.reset_uint());
	*/
		/*}}}*/
	//testloop();
	}/*}}}*/

/*   testloop   * {{{ */
void testloop(void){
		testOnOff();
		//testSenAdd();
		//testSenShift();
	} //}}}
/*   testOnOff   * {{{ */
void testOnOff(void){
		for (int i = 7; i <= 15; i++) {
			shiftout.on(i);
			delay(1000);
			shiftout.off(i);
		}
	} //}}}

/*   testOnOff   * {{{ */
void testSenAdd(void){
		for (int i = 0; i < 66666; i++) {
			shiftout.send16(i);
			delay(10);
		}
	} //}}}

/*   testSenShift   * {{{ */
void testSenShift(void){
		for (int i = 0; i < 16; i++) {
			shiftout.send16(1<<i);
			delay(1000);
		}
	} //}}}
/*   print_on_done   *{{{ */
#ifdef DEBUGMSG_STEPMOTORDONE
void print_on_done(int index){
	if (smotors[index].done()) {
		Serial.print(index);
		Serial.println("]-Stepmotor - done");
		}
	} 
#endif /* DEBUGMSG_STEPMOTORDONE *}}}*/			
void encoder1() {/*{{{*/
	sencoder.encoder1();	
	}
/*}}}*/
void encoder2() {/*{{{*/
	sencoder.encoder2();	
	}
/*}}}*/


