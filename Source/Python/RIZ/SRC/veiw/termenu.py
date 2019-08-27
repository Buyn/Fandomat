#!/usr/bin/env python
# -*- coding: utf-8 -*- 
# Menu Class with commads in termenal{{{
'''
Created on 10 февр. 2019 г.
@author: BuYn
'''
# }}}
# get Library {{{
# from array import array
import pygame
import time
import sys
from model.globalsvar import * 
from veiw.debugprint import DebugPrint
from presenter.stepmotor import StepMotor
# }}}

class TerMenu(object):# {{{

    def __init__(self, spi, leds, debugmode = DEBUGMODE):# {{{
        self.leds = leds
        self.debugmode = debugmode
        self.dp = DebugPrint(debugmode)
        self.spi = spi
        self.inputOn = True
        self.pauseEnd = 0
        self.inputOff = False 
        self.exit = False
        self.smotors = StepMotor(spi, leds)
        # }}}

    def writeNumber(self, number):# {{{
        print ("RPI: Hi Arduino, I sent you ", number)
        number =self.spi.send(number)
        print ("Arduino: Hey RPI, I received a digit ", number)
        return number
        # }}}

    def sth(self, param0):# {{{
        return hex(self.isInt(param0))
        # }}}

    def fillLEDset(self, setlist, command):# {{{
        """Filling list from arrey and adding command"""
        return [
              self.isInt(setlist[5]),
              self.isInt(setlist[4]), 
              self.isInt(setlist[3]), 
              self.isInt(setlist[2]), 
              command 
              ] 
        # }}}

    def ledcommand(self, elm_var):# {{{
        if (elm_var[1] == "set"):
            print("Set led  = ", 
                    self.fillLEDset(elm_var, hex(SC_LEDSET)))
            self.spi.execute( self.fillLEDset(elm_var, SC_LEDSET))
        if (elm_var[1] == "01"):
            print("Set led 01 = ", 
                    self.fillLEDset(elm_var, hex(SC_LED01SET)))
            self.spi.execute( self.fillLEDset(elm_var, SC_LED01SET))
        if (elm_var[1] == "02"):
            print("Set led 02 = ", 
                    self.fillLEDset(elm_var, hex(SC_LED02SET)))
            self.spi.execute( self.fillLEDset(elm_var, SC_LED02SET)) 
        # }}}

    def isInt(self, var):# {{{
        if isinstance(var, int):
            return var
        if isinstance(var, list) and len(var) == 1:
            return var[0]
        try:
            return int(var)
        except ValueError:
            print("Not know Command or number")
            return 0
        # }}}

    def getUserInput(self):# {{{
        while True:
            print ("Enter h for help(list of command)")
            var = input("Enter Command: ")
            return var
        # }}}

    def printHelp(self):# {{{
        """on h printing hel to log"""
        print ( "ledstart "," Start LED")
        print (  "ledstop ", "Stop LED")
        print (  "t ", "Test")
        print (  "b ", "Blue")
        print (  "r ", "Red")
        print (  "g ", "Green")
        print (  "w ", "White")
        print (  "o ", "OFF")
        print ( 'led ', "set", " red green blue speed  ", "Set led  = ")
        print ( 'led ', "01" , " red green blue speed  ", "Set led 01 = ") 
        print ( 'led ', "02" , " red green blue speed  ", "Set led 02 = ") 
        print ( 'debug ', "paramMode" , " set debug mode to new value") 
        print ( 'im '   , " isWaitingMsg") 
        print ( 'gm '   , " getOneMsg") 
        print ( 'rd  = ready ', " To ready Status") 
        print ( 'leds', " Triger one shift out LED") 
        print("Encoder ON", "encon")
        print("Encoder OFF", "encoff")
        print("step motor comands - Exempls:")
        print("step dir x 1")
        print("step go 1 100")
        print("step go Z 1000")
        print("go - Move step motor  on number of step ")
        print('dir - ',"Step motor dir is set to ")
        print("enb - Step motor  enable state is set to ")
        print("spd - Move step motor speed is set ")
        print("longs - Step motor [] Long of pulse is set to")
        print("pos - Step motor [] position is set to")
        print("mnt - Step motor [] maintanse is start")
        # }}}

    def setReadyStatus(self):# {{{
        pygame.mixer.init()
        pygame.mixer.music.load("file.wav")
        pygame.mixer.music.set_volume(1.0)
        pygame.mixer.music.play()
        self.spi.execute([SC_LEDSTOP])
        # }}}

    def isLEDCommand(self, var):# {{{
        if  var == "ledstart":
            print ("Start LED")
            self.spi.execute([SC_LEDSTART])
            return True
        if  var == "ledstop":
            print ("Stop LED")
            self.spi.execute([SC_LEDSTOP])
            return True
        if  var == "t":
            print ("Test")
            self.spi.execute([0x0f, 0x01, 0xf1, 0xf0, SC_LEDSET])
            return True
        if  var == "b":
            print ("Blue")
            self.spi.execute([0x0f, 0xff, 0x00, 0x00, SC_LEDSET])
            return True
        if  var == "r":
            print ("Red")
            self.spi.execute([0x0f, 0x00, 0xff, 0x00, SC_LEDSET])
            return True
        if  var == "g":
            print ("Green")
            self.spi.execute([0x0f, 0x00, 0x00, 0xff, SC_LEDSET])
            return True
        if  var == "w":
            print ("White")
            self.spi.execute([0x0f, 0xff, 0xff, 0xff, SC_LEDSET])
            return True
        if  var == "o":
            print ("OFF")
            self.spi.execute([0x0f, 0x00, 0x00, 0x00, SC_LEDSET])
            return True
        if  var == "i":
            sec = 60
            print ("Input loop Start on ", sec, " sec.")
            self.setInputPause(sec = sec)
            return True
        if  var == "io":
            print ("Menu is OFF")
            self.inputOff = True 
            return True
        if  var == "h":
            self.printHelp()
            return True
        if  var == "im":
            print( self.spi.isWaitingMsg())
            return True
        if  var == "gm":
            print( self.spi.getOneMsg(0))
            return True
        if  var == "rd":
            print("To ready Status")
            self.setReadyStatus()
            return True
        if  var == "encon":
            print("Encoder ON")
            self.spi.execute([STARTECOUNTER])
            return True
        if  var == "encoff":
            print("Encoder OFF")
            self.spi.execute([STOPECOUNTER])
            return True
        if  var == "exit":
            print("Exit")
            sys.exit(0)
            return True
        if  var == "stepooff":
            print("Step driver OFF")
            self.spi.execute([STOPDRIVER])
            return True
        if  var == "stepon":
            print("Step driver ON")
            self.spi.execute([STARTDRIVER])
            return True
        return False
        # }}}

    def debugcommand(self, elm_var):# {{{
        self.spi.dp(self.isInt(elm_var[1]))
        print("Debug mode set to ", elm_var[1])
        # }}}


    def setLED(self, ledpin):
        print("LED trigered on pin = ", ledpin)
        self.leds.ledTrig(ledpin)
    
    
    def stepCommand(self, elm_var):
        self.dp(1, elm_var)
        try:
            self.smotors.getTag(elm_var[1])
        except:
            print("no such motor Name")
            return False
        if (elm_var[0] == 'go'):
            print("Move step motor [", elm_var[1], "] on number of step =", elm_var[2])
            return self.smotors.move(elm_var[1],elm_var[2])
        if (elm_var[0] == 'dir'):
            print("Step motor [", elm_var[1], "] dir is set to =", elm_var[2])
            return self.smotors.setDir(elm_var[1],elm_var[2])
        if (elm_var[0] == 'enb'):
            print("Step motor [", elm_var[1], "] enable state is set to =", elm_var[2])
            return self.smotors.setEnable(elm_var[1],elm_var[2])
        if (elm_var[0] == 'spd'):
            print("Step motor [", elm_var[1], "] speed is set =", elm_var[2])
            return self.smotors.setSpeed(elm_var[1],elm_var[2])
        if (elm_var[0] == 'longs'):
            print("Step motor [", elm_var[1], "] Long of pulse is set =", elm_var[2])
            return self.smotors.setLongs(elm_var[1],elm_var[2])
        if (elm_var[0] == 'pos'):
            print("Step motor [", elm_var[1], "] position is set to =", elm_var[2])
            return self.smotors.setPosition(elm_var[1],elm_var[2])
        if (elm_var[0] == 'mnt'):
            print("Step motor [", elm_var[1], "] maintanse is start =", elm_var[2])
            return self.smotors.maintanse(elm_var[1],elm_var[2])
        print("No such Step motor Command")
        return False
    
    
    def isCommandList(self, elm_var):# {{{
        if (not isinstance(elm_var, str) and len(elm_var) > 1):
            if (elm_var[0] == 'led'):
                self.ledcommand(elm_var)
            if (elm_var[0] == 'debug'):
                self.debugcommand(elm_var)
            if (elm_var[0] == 'step'):
                elm_var.pop(0)
                return self.stepCommand(elm_var)
            if (elm_var[0] == 'leds'):
                self.setLED(self.isInt(elm_var[1]))
            return True
        return False
        # }}}

    def pruntMenu(self):# {{{
        if not self.setInputPause(): return False
        var = self.getUserInput()
        if var == None or var == "": return False
        if self.isLEDCommand(var): return True
        if self.isCommandList(var.split(' ')): return True
        return self.writeNumber(self.isInt(var))
        # }}}
    
    def setInputPause(self, sec = None):
        if self.inputOff: return False
        timenow = time.time()
        if sec == None and self.pauseEnd > timenow: 
            return False
        if sec == None and self.pauseEnd < timenow: 
            self.inputOn = True
            return True
        if isinstance(sec, int):
            self.pauseEnd = timenow + sec
            self.inputOn = False

# }}}

