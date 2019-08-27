

class DebugPrint(object):
    
    def __init__(self, startingdebugmod):
        self.debugmod = startingdebugmod

    
    def __call__(self, printonmod, *arg):
        if len(arg)==0:
            self.debugmod = printonmod
            return -1
        return self.print(printonmod, *arg)
        
        
    def print(self, printonmod, *arg):
        if self.debugmod < printonmod: return 0
        print(*arg)
        return 1
    
    


