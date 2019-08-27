from model.globalsvar import * 

class SpiDev(object):
    
    
    def __init__(self, debugmode = DEBUGMODE):
        self.debugmode = debugmode

    
    def open(self, BUS, DEVICE):
        if (self.debugmode): print("open", BUS, DEVICE)

    
    def xfer2(self, build_read_command):
        if (self.debugmode): print('xfer2', build_read_command)

    
    def writebytes(self, hex):
        if (self.debugmode): print('writebytes', hex)

    
    def close(self):
        if (self.debugmode): print('close')

    
    def xfer(self, param1):
        if (self.debugmode): print('xfer = ', param1)
        if isinstance(param1, int): return {param1 + 1}
        if not isinstance(param1[0], int): raise "not int"
        return [param1[0]]


    def xfer3(self, param1):
        if (self.debugmode): print('xfer = ', param1)
        if isinstance(param1, int): return (1, param1 + 1)
        if not isinstance(param1[1], int): raise "not int"
        return (param1[0], param1[1]) 
    
    
    def readbytes(self, param1):
        result = []
        for i in range(param1):
            if (self.debugmode): print(i, " = ", result)
            result.append(i)
        return result
    
    
    
    
    
    
    
    
    
    
    
    

