# from enum import Enum, unique
from model.globalsvar import *
import time

@unique
class FuncList (Enum):# {{{
    RUNTIME                 = 0
    ONSTART                 = 1
    ONEND                   = 2

    @staticmethod
    def list():
        return list(map(lambda c: c.value, FuncList))
    # }}}


class CommandItem(object):
    
    def passDef(self, value = None):# {{{
        pass
    # }}}
    
    def __init__(self,# {{{
                  key, 
                  runtimeCommand = passDef, 
                  onStartCommand = passDef, 
                  onEndCommand = passDef):
        self.key = key
        self.set_runtime_command( runtimeCommand , 1000)  
        self.onStartCommand = onStartCommand
        self.onEndCommand = onEndCommand
        self.delayRunTime = 0
        self.updatetime = 0
        self.lastreturn = None
        # }}}
        
    def reseTimer(self):# {{{
        self.updatetime = time.time() + self.delayRunTime
    # }}}

    # seter geter bloc{{{
    def get_runtime_command(self):# {{{
#         print("get run")
        return self.__runtimeCommand
# }}}

    def get_on_start_command(self):# {{{
#         print("get start")
        return self.__onStartCommand
# }}}

    def get_on_end_command(self):# {{{
#         print("get end")
        return self.__onEndCommand
# }}}

    def set_runtime_command(self, value, timeout):# {{{
#         print("set rutime")
        self.delayRunTime = timeout
        self.__runtimeCommand = value
# }}}

    def set_on_start_command(self, value):# {{{
#         print("set start")
        self.__onStartCommand = value
# }}}

    def set_on_end_command(self, value):# {{{
#         print("set end")
        self.__onEndCommand = value
# }}}

    runtimeCommand = property(get_runtime_command, set_runtime_command, None, None)# {{{
    onStartCommand = property(get_on_start_command, set_on_start_command, None, None)
    onEndCommand = property(get_on_end_command, set_on_end_command, None, None)
    # }}}
    
    def runtime(self, value = None):
        if self.updatetime > time.time(): return None
        self.updatetime = time.time() + self.delayRunTime
        self.lastreturn = self.runtimeCommand(value)
        return self.lastreturn 
    
    
    # }}}



