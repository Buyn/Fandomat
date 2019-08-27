from enum import Enum, unique
from model.globalsvar import *
import pygame
from presenter.leds import LEDs
import time
from model.commandmenu import *

@unique
class FuncList (Enum):# {{{
    RUNTIME           	= 0
    ONSTART            	= 1
    ONEND           	= 2

    @staticmethod
    def list():
        return list(map(lambda c: c.value, FuncList))
    # }}}


class LEDsMenu(object):
    

    def initCommandsItems(self):
        list = State.list()
        list.remove(State.NOTREADY.value)
        self.menu.addItems(list)
            
    
    def __init__(self, spi, buttons, leds):# {{{
        self.spi = spi
        self.buttons = buttons
        self.leds = leds
#         self.changed = False
        self.menu = CommandMenu(key = State.NOTREADY.value)
        self.initCommandsItems()
        self.menu.lessKey = State.FULL_CYCLE.value
        pygame.mixer.init()
        pygame.mixer.music.set_volume(ST_VOLUME)

    
    def runtime(self):
        if self.changed:
            self.oldState = self.newState
            self.newState()
            self.changed =False
        return self.runtimeCommand()

    
    def setRuntime(self, command):
        self.runtimeCommand = command 

    
    def readyState(self):
        self.leds.blink(self.state)
        return True

    def notreadyState(self):
        return False
    
    def setNewState(self, onChegeCommand):
        self.newState = onChegeCommand
        self.changed = True

    
    def executeStatus(self):
        self.leds.ledTrig(self.state)
        if self.state == State.SHARPENNING.value:
#         set blue
            self.spi.execute([0x0A, 0xff, 0x00, 0x00, SC_LED01SET])
            print("c1")
            time.sleep(0.2)
            self.spi.execute([0x0A, 0xff, 0x00, 0x00, SC_LED02SET])
            print("c2")
            time.sleep(0.2)
            self.spi.execute([0x0A, 0xff, 0x00, 0x00, SC_LED03SET])
            print("c3")
            time.sleep(0.2)
            pygame.mixer.music.load("toch.wav")
            pygame.mixer.music.play()
            self.spi.execute([STARTDRIVER])
            print("e")
            time.sleep(0.2)
        if self.state == State.POLISHING_DISK_CLEANING.value:
#         set orange
            self.spi.execute([0x0A, 0x00, 0xff, 0xff, SC_LED01SET])
            print("c1")
            time.sleep(0.2)
            self.spi.execute([0x0A, 0x00, 0xff, 0xff, SC_LED02SET])
            print("c2")
            time.sleep(0.2)
            self.spi.execute([0x0A, 0x00, 0xff, 0xff, SC_LED03SET])
            print("c3")
            time.sleep(0.2)
            pygame.mixer.music.load("file.wav")
            pygame.mixer.music.play()
        if self.state == State.POLISHING.value or self.state == State.CERAMIC_KNIFE.value:
#         set Ylow
            self.spi.execute([0x0A, 0xff, 0x00, 0xff, SC_LED01SET])
            print("c1")
            time.sleep(0.2)
            self.spi.execute([0x0A, 0xff, 0x00, 0xff, SC_LED02SET])
            print("c2")
            time.sleep(0.2)
            self.spi.execute([0x0A, 0xff, 0x00, 0xff, SC_LED03SET])
            print("c3")
            time.sleep(0.2)
            pygame.mixer.music.load("poll.wav")
            pygame.mixer.music.play()
            self.spi.execute([STARTECOUNTER])
            print("e")
            time.sleep(0.2)

    
    def setReadyState(self):
        print("ready to work")
        self.changed = False
        self.leds.bitWordLast = 0
        self.leds.ledOn(State.READY.value)
        self.runtimeCommand = self.readyState
        self.state = State.READY.value +1
        pygame.mixer.music.load("ready.wav")
        pygame.mixer.music.play()
        self.spi.execute([SC_LEDSTART])
#         set green
        self.spi.execute([0x0A, 0x00, 0x00, 0xff, SC_LED01SET])
        self.spi.execute([0x0A, 0xff, 0x00, 0x00, SC_LED01SET])
        print("c1")
        time.sleep(0.2)
        self.spi.execute([0x0A, 0x00, 0x00, 0x00, SC_LED02SET])
        self.spi.execute([0x0A, 0xff, 0x00, 0x00, SC_LED02SET])
        print("c2")
        time.sleep(0.2)
#         set green
        self.spi.execute([0x0A, 0x00, 0x00, 0xff, SC_LED03SET])
        print("c3")
        time.sleep(0.2)
        self.buttons.setComandOnPress(B_CHOICE, 
            lambda: print("B_CHOICE", self.nextStatus()))
        self.buttons.setComandOnPress(B_OK, 
            lambda: print("B_OK", self.executeStatus()))
        self.buttons.setComandOnPress(B_RESET, 
            lambda: print("B_RESET", self.setReadyState()))
        #self.spi.execute([STOPDRIVER])
        #self.spi.execute([STOPECOUNTER])

    
    def nextStatus(self):
        self.leds.ledOff(self.state)
        if self.state == State.NOTREADY.value:
            self.state = State.READY.value
            self.leds.ledOn(self.state)
            return self.state 
        if self.state == State.SHARPENNING.value:
            self.state = State.READY.value + 1
            self.leds.ledOn(self.state)
            return self.state 
        self.state += 1
        self.leds.ledOn(self.state)
        return self.state 
    
    # }}}
    



