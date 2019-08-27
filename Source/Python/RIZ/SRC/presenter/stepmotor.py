from model.globalsvar import *
# from presenter.spicom import SPICom
from model.typsconvert import *

TAG     = 0    
DIR     = 1    
ENB     = 2    

class StepMotor(object):
    
    def __init__(self, spi, leds):
#         self.spi = SPICom(LEDSTM_ADRRESS, debugmode=2)
        self.leds = leds
        self.spi = spi

    
    def move(self, tag, steps):
        return self.spi.execute([isInt(steps), self.getTag(tag)[TAG], SM_STEP])

    
    def getTag(self, tag):
        if isinstance(tag, int):
            return tag
        if isinstance(tag, str):
            tag = tag.capitalize()
            return StepMotorsList[tag].value
        raise ValueError('is not a valid type'.format(tag))

    
    def setSpeed(self, tag, steps):
        return self.spi.execute([isInt(steps), self.getTag(tag)[TAG], SM_SPEED])
    
    def setEnable(self, tag, steps):
        if isInt(steps)  == 0:# {{{
            return self.leds.ledOff(self.getTag(tag)[ENB]) 
        if isInt(steps)  == 1:# {{{
            return self.leds.ledOn(self.getTag(tag)[ENB]) 
#         return self.spi.execute([isInt(steps), self.getTag(tag), SM_ENABLE])
            # }}}
    
    
    def setDir(self, tag, steps):
        if isInt(steps) == 0:# {{{
            return self.leds.ledOff(self.getTag(tag)[DIR]) 
        if isInt(steps) == 1:# {{{
            return self.leds.ledOn(self.getTag(tag)[DIR]) 

    
    def setLongs(self, tag, steps):
        return self.spi.execute([isInt(steps), self.getTag(tag)[TAG], SM_LONGS])

    
    def setPosition(self, tag, steps):
        return self.spi.execute([isInt(steps), self.getTag(tag)[TAG], SM_POS])

    
    def maintanse(self, tag, steps):
        return self.spi.execute([isInt(steps), self.getTag(tag)[TAG], SM_MNT])
    
    
    
    
    
    
    
    
    
    
    
    
    



