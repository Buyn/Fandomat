from enum import Enum, unique


DEBUGMODE = False

# SPI Devise
BUS     = 0 
DEVICE  = 0

#Setings
ST_VOLUME   = 0.5

# buttons pins
B_RESET     = 13
B_OK        = 14
B_CHOICE    = 15
# LEDs pins
ledsPins = {
   "Sharpenning"           	: 15,
   "Polishing"             	: 14,
   "Ready"                 	: 13,
   "Right side"             	: 12,
   "Left side"              	: 11,
   "Ceramic knife"          	: 10,
   "Polishing disk cleaning"	: 9 ,
   "Full cycle"             	: 8 ,
   "Middle cycle"           	: 7
    }
L_SHARPENNING            = 15
L_POLISHING              = 14
L_READY                  = 13
L_RIGHTSIDE              = 12
L_LEFTSIDE               = 11
L_CERAMICKNIFE           = 10
L_POLISDHINGDISKCLEANING = 9
L_FULLCYCLE              = 8
L_MIDDLECYCLE            = 7

# SPI Adresses
LEDSTM_ADRRESS = 0x08
# SPI Timing
SPI_SLEEPAFTERSEND      = 0.1
SPI_SLEEPBETWINMSGGET   = 0.3
# SPI stek command
SC_EXECUTECOMMAND   = 0xAA
SC_ISMSGWATING      = 0xB0
SC_GETVARBYNAME     = 0xBA
SC_GETMSGBYCOUNT    = 0xBC
SC_ENDOFFILE        = 0xEF
SC_ENDOFSESION      = 0xFF
#define Vars Names
VN_BUTTONVAULT01    = 0x01
#define ERROR bloc  
DISINHRONERROR                    = 0x10
DISINHRONADRESSERROR              = 0x11
STAKERRORCOMAND                   = 0x20
TIMEOUTSESION                     = 0x30

# Commands list
# LED comands
SC_LEDSTOP         = 0x10
SC_LEDSTART        = 0x11
SC_LEDSET          = 0x14
SC_LED01SET        = 0x1A
SC_LED02SET        = 0x1B
SC_LED03SET        = 0x1C
#ShiftOut comands
SC_SETSHIFTOUT     = 0x21
#Step Motor comands
STARTDRIVER    =0x31
STOPDRIVER     =0x32
SM_STEP             = 0x33
SM_SPEED            = 0x34
SM_ENABLE           = 0x35
SM_DIR              = 0x36
SM_LONGS            = 0x37
SM_POS              = 0x38
SM_MNT              = 0x39

#encounter comands
STARTECOUNTER    =0x41
STOPECOUNTER     =0x42

@unique
class State(Enum):# {{{
    SHARPENNING           	= 15
    POLISHING             	= 14
    MIDDLE_CYCLE           	= 13
    RIGHT_SIDE             	= 12
    LEFT_SIDE              	= 11
    CERAMIC_KNIFE          	= 10
    POLISHING_DISK_CLEANING	= 9 
    FULL_CYCLE             	= 8 
    READY                 	= 7
    NOTREADY                    = 0
    
    @staticmethod
    def list():
        return list(map(lambda c: c.value, State))
    # }}}

class StepMotorsList(Enum):# {{{
#   name    TAG, DIR, ENBL
    X       = [0, 0, 1]
    Y       = [1, 2, 3] 
    Z       = [2, 4, 5]
    A       = [3, 6, 7]
    I      = [4, 8, 9]
    # }}}

