from model.typsconvert import *
from model.globalsvar import *
from presenter.buttons import Buttons
import time

class SpiMSG(object):
    
    def __init__(self, spi, buttons):
        self.spi = spi
        self.buttons = Buttons()
        self.buttons = buttons
        self.msgsStack =[]
        self.isMSG = 0
        self.resetruntime()


    
    def getMSG(self):
        self.isMSG  = self.spi.isWaitingMsg()
        if isInt(self.isMSG) > 0:
            self.msgsStack.append(self.spi.getOneMsg(1))
            return self.isMSG
        return self.isMSG 

    
    def resetruntime(self):
        self.nextruntime = time.time() + SPI_SLEEPBETWINMSGGET
    
    
    def runtime(self):
        if time.time() < self.nextruntime: return
        self.resetruntime()
        self.getMSG()
        return self.rutineMSGStack()

    
    def rutineMSGStack(self):
        if len(self.msgsStack) == 0 : return False
        while len(self.msgsStack):
            result = None
            msg = self.msgsStack.pop()
            if msg[0] == 0:
                print("ERROR MSG in msg rutine")
                result = False
                continue
            if msg[0] == VN_BUTTONVAULT01:
                print("Get Button")
                print(bin(msg[1]))
                self.buttons.set(msg[1])
                print(self.buttons.presed)
                result = True
                continue
            if result == None:
                print("ERROR MSG No such variable")
                result = False
                continue
        return result


    
    
    
    
    
    



