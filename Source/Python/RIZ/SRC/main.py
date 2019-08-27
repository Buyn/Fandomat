#!/usr/bin/env python
# -*- coding: utf-8 -*- 
# Rosberi pi program controlin STM32 with SPI{{{
# MCP3008 is 8-channel 10-bit analog to digital converter
#  Connections are:
#     CLK => SCLK  
#     DOUT =>  MISO
#     DIN => MOSI
#     CS => CE0
# RPi PINOUTS
# MOSI -> GPIO10
# MISO -> GPIO9
# SCK  -> GPIO11
# CE1  -> GPIO7
# CE1  -> GPIO8
from veiw.termenu import TerMenu
from presenter.buttons import Buttons
from model.spimsg import SpiMSG
from presenter.leds import LEDs
from veiw.ledsMenu import *
from presenter import buttons
'''
Created on 10 февр. 2019 г.
@author: BuYn
'''
# }}}

# get the GPIO Library and SPI Library{{{
import pygame
import time
import sys
from model.globalsvar import * 
from presenter.spicom import SPICom
# }}}

#Initialze the SPI # {{{
spi     = SPICom(LEDSTM_ADRRESS, debugmode=DEBUGMODE)
# }}}

#Varialbes for the Debounce # {{{
buttons     = Buttons()
msg         = SpiMSG(spi, buttons)
leds        = LEDs(spi)
terMenu     = TerMenu(
                    spi,
                    leds
                    )
ledsMenu     = LEDsMenu(
                    spi=spi,
                    leds=leds,
                    buttons = buttons
                    )

# }}}

def mainloope():# {{{
    try:
        while True:
            terMenu.pruntMenu()
            msg.runtime()
            leds.send()
#             ledsMenu.runtime()
    except KeyboardInterrupt:
        print("interrupt")
        if terMenu.inputOff:
            terMenu.inputOff = False
            return
        else: sys.exit(0)
    # }}}

def parsArgList():# {{{
    print(str(sys.argv))
    for arg in sys.argv:
        if arg == "debug1":
            print("arg = ", arg)
            spi.dp(1)
            continue
        if arg == "debug2":
            print("arg = ", arg)
            spi.dp(2)
            continue
        if arg == "debug3":
            print("arg = ", arg)
            spi.dp(3)
            continue
        if arg == "inputoff":
            print("arg = ", arg)
            terMenu.inputOff = True 
            continue
        print("unknown arg = ", arg)
        # }}}

def initButtons():# {{{
    buttons.setComandOnPress(B_CHOICE, 
            lambda: print("B_CHOICE", terMenu.setReadyStatus()))
                            #terMenu.setReadyStatus)
    buttons.setComandOnPress(B_OK, 
            lambda: print("B_OK", spi.execute([SC_LEDSTOP])))
                            #lambda: spi.execute([SC_LEDSTOP]))
    buttons.setComandOnPress(B_RESET, 
            lambda: print("B_RESET", spi.execute([0x0f, 0x00, 0xff, 0x00, SC_LEDSET])))
                            #lambda: spi.execute([0x0f, 0x00, 0xff, 0x00, SC_LEDSET]))
    # }}}

if __name__ == '__main__':# {{{
    parsArgList()
    initButtons()
    while not terMenu.exit:
        mainloope()
    # }}}




