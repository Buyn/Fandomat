'''
Created on 28 янв. 2019 г.

@author: BuYn
import test.test_buttons
'''

class Buttons(object):

    def __init__(self):
        self.change     = False
        self.lastBitWord= 0
        self.commandsOnPress   = {}
        self.commandsOnRelise   = {}
        self.presed     = []


    def set(self, newBits):
        if self.lastBitWord == newBits: return False
        self.lastBitWord = newBits
        newpress = []
        self.change = True
        for i in range (16):
            if newBits >> i&1 :
                newpress.append(i)
                if not self.isPressed(i):
                   self.exeCommand(i) 
        self.presed = newpress


    def setComandOnPress(self, key, command):
        self.commandsOnPress.update({key:command})


    def exeCommand(self, key):
        if self.commandsOnPress.get(key, False) == False:
            return False
        return self.commandsOnPress.get(key, False)()


    def removeCommandOnPress(self, key):
        return self.commandsOnPress.pop(key)

    
    def isPressed(self, key):
        try:
            self.presed.index(key)
            return True
        except (ValueError ):
            return False
    
    













