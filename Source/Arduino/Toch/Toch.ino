/*  Driver Control C Programm {{{ 
	
  modified 8 May 2014
  by BuYn 
* }}} */
//   Constants   {{{
#define MENU_DELAY			200
#define SENSOR_DELAY			100
#define ANALOG_P				A3
#define ANALOG_R				A2
#define LED_PIN            13
#define COUNT_PIN           2
#define X_STEP_PIN         A0
#define X_DIR_PIN          A1
#define X_ENABLE_PIN       38
#define X_MAX_PIN          11
#define X_MIN_PIN          12


//}}}
/*Global Values {{{*/
unsigned long step_period = 1000;
unsigned long step_signsl_duration = 100;
unsigned long def_delay			 = 1000;
int sensor_multip	=100;
bool dirbutton_down;
bool dirbutton_up;
bool potenzbutton_down;
bool potenzbutton_up;
bool potenz_on				=true;
bool DIR_pin_X				=false;
bool test_mod				=false;
bool is_se_counter		=false;
bool is_step_counter		=false;
bool is_min_counter		=false;
bool is_midlerange_counter	=false;
int sensorValue 	=100;
int se_interaps 	=0;
int min_interaps 	=0;
int i_midlerange_counter 	= 0;
int i_step_counter 			= 0;
unsigned long serial_time 	= 0;
unsigned long sensor_time 	= 0;
unsigned long step_time  	= 0;
unsigned long se_counter_time    = 0;
unsigned long min_counter_time   = 0;
unsigned long midlerange_sum	   = 0;
unsigned long midlerange_counter_time = 0;
String last_text 	="";
int last_int 		=100;
String s_temp_serial = "";
/*}}}*/
// the setup function {{{
// runs once when you press reset or power the board
void setup() {
	pinMode(ANALOG_P, INPUT);
	pinMode(ANALOG_R, INPUT);
	pinMode(X_STEP_PIN, OUTPUT);
	pinMode(X_DIR_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);
	pinMode(X_MIN_PIN, INPUT);
	pinMode(X_MAX_PIN, INPUT);
   attachInterrupt(digitalPinToInterrupt(COUNT_PIN), encounter, RISING);
	Serial.begin(9600);
	while (!Serial) {
		delay(1); // wait for serial port to connect. Needed for native USB port only
		}
	last_int = analogRead(ANALOG_P);
	printHelp();
	oneprint_text("Setup End");
}
//}}}
// the loop function  {{{
// runs over and over again forever
void loop() {
  if (micros() >= step_time) steps_loop();
  if (millis() >= sensor_time) {//{{{
	  get_sensor_date();
	  set_motorDIR();
	  sensor_time = millis() + SENSOR_DELAY;
	  }/*}}}*/
  if (is_se_counter && millis() >= se_counter_time) se_counter();  
  if (is_min_counter && millis() >= min_counter_time) min_counter();  
  if (is_midlerange_counter && micros() >= midlerange_counter_time) midlerange_counter();  
  if (millis() >= serial_time) serial_worker();
}/*}}}*/

/*   serial_worker   * {{{
*/
void serial_worker(void){
   if(Serial.available()) {/*{{{*/
     s_temp_serial = Serial.readStringUntil('\n');
    for(int i = 0 ; (int)s_temp_serial.length() >= i ; i++) { //{{{
            switch ( char(s_temp_serial.charAt(i))){
              case '+':/*{{{*/
                def_delay  += 10;
					 Serial.println("Period bitwin Steps +100 = ");
					 Serial.println(step_period);
                break;/*}}}*/
              case '-':/*{{{*/
                def_delay  -= 10;
					 Serial.println("Period bitwin Steps -100 = ");
					 Serial.println(step_period);
                break;/*}}}*/
              case '*':/*{{{*/
                sensor_multip  += 1;
					 Serial.println("multiplaer +1 = ");
					 Serial.println(sensor_multip);
                break;/*}}}*/
              case '/':/*{{{*/
                sensor_multip  -= 1;
					 Serial.println("multiplaer -1 = ");
					 Serial.println(sensor_multip);
                break;/*}}}*/
              case 'a':/*{{{*/
						//printText("Reading:a ");
						Serial.println("Reading: a ");
                  //do something when var equals 1
                  break;/*}}}*/
              case 'm':/*{{{*/
						//printText("Reading:a ");
						Serial.println("Set value for multiplaer");
						sensor_multip	=get_int_from_serial();

                  break;/*}}}*/
              case 'p':/*{{{*/
						Serial.println("Set value for step_period");
						def_delay	=get_int_from_serial();

                  break;/*}}}*/
              case 'd':/*{{{*/
						Serial.println("Set value for step signal duration");
						step_signsl_duration	=get_int_from_serial();

                  break;/*}}}*/
              case 'z':/*{{{*/
						//printText("Reading:z ");
						Serial.println("Reading: z ");
						//do something when var equals 1
                break;/*}}}*/
              case 0:/*{{{*/
						Serial.println("Reading: NULL ");
                break;/*}}}*/
              case '?':/*{{{*/
						Serial.println("printing Help: ... ");
						printHelp() ;
						break;/*}}}*/
              case 't':/*{{{*/
						togle_test_mode();
						break;/*}}}*/
              case 's':/*{{{*/
						is_se_counter = !is_se_counter;
						se_counter();
						Serial.println("s : secunds mode togler");
						break;/*}}}*/
              case 'e':/*{{{*/
						Serial.print("e : enter steps to do ");
						Serial.println(is_step_counter);
						i_step_counter = get_int_from_serial();
						break;/*}}}*/
              case 'E':/*{{{*/
						is_step_counter = !is_step_counter;
						Serial.print("E : Steper mode togler - ");
						Serial.println(is_step_counter);
						Serial.println("enter steps to do ");
						i_step_counter = get_int_from_serial();
						break;/*}}}*/
              case 'M':/*{{{*/
						is_min_counter = !is_min_counter;
						min_counter();
						Serial.println("M : Minuts mode togler");
						break;/*}}}*/
              case 'r':/*{{{*/
						is_midlerange_counter = !is_midlerange_counter;
						midlerange_counter();
						Serial.println("r : megering range mode togler");
						break;/*}}}*/
              case ' ':/*{{{*/
					 Serial.println(" geting SPACE");
                break;/*}}}*/
              default:/*{{{*/
                //renderText(); 
					 Serial.print("serial_worker : (");
					 Serial.print(s_temp_serial.charAt(i));
					 Serial.print(" - ");
					 Serial.println((int)s_temp_serial.charAt(i));
					 Serial.println(")");
                // if nothing else matches, do the default
                // default is optional
					 break;/*}}}*/
            }/*}}}*/
     }
   }/*}}}*/
	serial_time = millis() + MENU_DELAY;
	} //}}}
int get_int_from_serial() {/*{{{*/
	while (Serial.available() == 0) {
		delay(10);
		}
	int result = Serial.readStringUntil('\n').toInt();
	Serial.println(result);
	return result;
	}
	/*}}}*/

/*   encounter   * {{{
*/
void encounter(void){
	se_interaps++;
	min_interaps++;
	} //}}}
/*   se_counter   * {{{
*/
void se_counter(void){
	Serial.print("counts in secund : ");
	Serial.println(se_interaps);
	se_interaps = 0;
	se_counter_time = millis() + 1000;
	} //}}}
/*   min_counter   * {{{
*/
void min_counter(void){
	Serial.print("counts in minut : ");
	Serial.println(min_interaps);
	min_interaps = 0;
	min_counter_time = millis() + 60000;
	} //}}}

void togle_test_mode() {/*{{{*/
	if (test_mod){	
		test_mod = !test_mod;
		Serial.println("Test mode on");
		Serial.println("Set value for step signal duration = 9999999 ~ 9 secunds");
		step_signsl_duration	=9999999;
		}
	else{
		test_mod = !test_mod;
		Serial.println("Test mode off");
		Serial.println("Set value for step signal duration = 50000 ");
		step_signsl_duration	=50000;
		}
	}
/*}}}*/

/*   oneprint_text  int filter* {{{
 *   Printin text onli if its new
*/
void oneprint_text(int text, int filter){
	if (  (last_int - filter) >= text || text <= (last_int + filter)) {
		last_int = text;
		Serial.println(text);
		}
	} //}}}
/*   oneprint_text   * {{{
 *   Printin text onli if its new
*/
void oneprint_text(String text){
	if ( text.equals ( last_text ) ) return ;
	last_text = text;
	Serial.println(text);} //}}}
void printHelp() {/*{{{*/
	Serial.println("+ : Period bitwin Steps +10 = ");
	Serial.println("- : Period bitwin Steps -10 = ");
	Serial.println("* : multiplaer +1 = ");
	Serial.println("/ : multiplaer -1 = ");
	Serial.println("m : Set value for multiplaer");
	Serial.println("p : Set value for step_period");
	Serial.println("d : Set value for step signal duration");
	Serial.println("E : Steper mode togler ");
	Serial.println("M : Minuts mode togler");
	Serial.println("r : megering range mode togler");
	Serial.println("s : secunds mode togler");
	Serial.println("e : ascing steps to do ");
	Serial.println("? : printing Help: ... ");
	Serial.println("t : Test mode togler");
	Serial.println("Set value for step signal duration = 999999 ~ 1 secund");
	}
	/*}}}*/

/* Step function  {{{
 */
void step(int step_pin) {
  digitalWrite(step_pin, HIGH);   
  delayMicroseconds(step_signsl_duration);   //delayMicroseconds(step_pin);
  digitalWrite(step_pin, LOW);}
/*}}}*/
/*   steps_loop   * {{{
*/
void steps_loop(void){
	if (!is_step_counter || i_step_counter > 0) {
		step(X_STEP_PIN);
		}
	if (is_step_counter && i_step_counter > 0) i_step_counter--; 
	step_time = micros() + (unsigned long)sensorValue*sensor_multip;
  } //}}}
/*   set_motorDIR   * {{{
*/
void set_motorDIR(void){
	if (dirbutton_up){
			triger_Pin(X_DIR_PIN);
			dirbutton_up= false;
			} 
	} //}}}
/*   triger_Pin   * {{{
*/
void triger_Pin(int pin){
	Serial.println(pin);
	Serial.print("DIR_pin_X=");
	if (DIR_pin_X) {
		 digitalWrite(pin, LOW);
		 DIR_pin_X = false;
		 Serial.println(DIR_pin_X);
   }else{
		 digitalWrite(pin, HIGH); 
		 DIR_pin_X = true;
		 Serial.println(DIR_pin_X);
		 } 
  }
	//	}}}

/*   get_sensor_date   * {{{
*/
void get_sensor_date(void){
	read_DIR_button();
	read_potenz_button();
	read_sensorValue();
	} //}}}
/*   read_sensorValue   * {{{
*/
void read_sensorValue(void){

	if (potenzbutton_up) {
		potenz_on = !potenz_on;
		potenzbutton_up = false;
		Serial.print("potentiometrs is ");
		Serial.println(potenz_on);
		last_int = analogRead(ANALOG_P);
		}
	if (!potenz_on) {
		sensorValue = def_delay;
		oneprint_text("potentiometrs is OFF");
		return;
		}
	sensorValue = analogRead(ANALOG_P);
	oneprint_text((String)sensorValue);
	//oneprint_text(sensorValue, 1);
	} //}}}
/*   read_DIR_button   * {{{
*/
void read_DIR_button(void){
	if (digitalRead(X_MIN_PIN)>=HIGH){
		if (dirbutton_down) {
			dirbutton_up=true;	
			dirbutton_down=false;
			Serial.println("dirbutton_up");
			digitalWrite(LED_PIN, LOW);   
			}
		else return;
		}
	else{
		if (dirbutton_down) return;	
		else {
			dirbutton_down=true;
			dirbutton_up=false;
			Serial.println("dirbutton_down");
			digitalWrite(LED_PIN, HIGH);   
			}
		}	
	} //}}}
/*   read_potenz_button   * {{{
*/
void read_potenz_button(void){
	if (digitalRead(X_MAX_PIN)>=HIGH){
		if (potenzbutton_down) {
			potenzbutton_up=true;	
			potenzbutton_down=false;
			digitalWrite(LED_PIN, LOW);   
			Serial.println("potenzbutton_up");
			}
		else return;
		}
	else{
		if (potenzbutton_down) return;	
		else {
			potenzbutton_down=true;
			potenzbutton_up=false;
			Serial.println("potenzbutton_down");
			digitalWrite(LED_PIN, HIGH);   
			}
		}
	} //}}}
/*   midlerange_counter   * {{{
*/
void midlerange_counter(void){
	midlerange_sum += analogRead(ANALOG_R);
	i_midlerange_counter++;
	if (i_midlerange_counter >= 1000){/*{{{*/
		Serial.print("midlerange counts of range : ");
		Serial.println(midlerange_sum/i_midlerange_counter);
		Serial.print("Last : ");
		Serial.println(analogRead(ANALOG_R));
		i_midlerange_counter = 0;
		midlerange_sum = 0;
		}/*}}}*/
	midlerange_counter_time = micros() + 100;
	} //}}}

