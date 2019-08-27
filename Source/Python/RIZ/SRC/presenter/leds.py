from model.globalsvar import SC_SETSHIFTOUT
import time
class LEDs(object):
    
    def __init__(self, spi):
        self.spi = spi
        self.bitWordLast = 0
        self.chenged = False
        self.blinkTime = 0
        self.timeOut = 0.5

    
    def ledOn(self, ledpin):
        self.bitWordLast |= 1<<ledpin 
        self.chenged = True
        return self.bitWordLast

    
    def send(self):
        if not self.chenged: return False
        self.spi.execute( [self.bitWordLast, SC_SETSHIFTOUT])
        self.chenged = False
        return True

    
    def ledOff(self, ledpin):
        self.bitWordLast &= ~(1<<ledpin )
        self.chenged = True
        return self.bitWordLast
    

    def ledTrig(self, ledpin):
        self.bitWordLast ^= 1<<ledpin 
        self.chenged = True
        return self.bitWordLast

    
    def blink(self, ledpin):
        if time.time() < self.blinkTime: return False
        self.blinkTime = time.time() + self.timeOut
        self.ledTrig(ledpin)
        return True
            
    
    
    
    
    
    
    
    
    



