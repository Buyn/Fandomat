from model.commanditem import *
from array import array


class CommandMenu(object):
    
    def __init__(self, key=0):
        self.itemslist = {}
        self.activeItem = CommandItem(key)
        self.itemslist.update({key : self.activeItem})
        self.runtimeList = []
        self.lastItem = None
        self.lessKey = None
        self.mostKey = None
        

    def addOneItem(self, key):
        if isinstance(key, int):
            result = CommandItem(key)
            self.itemslist.update({key : result})
            if self.lessKey == None or self.mostKey == None:
                self.lessKey = key
                self.mostKey = key
            if self.lessKey > key:
                self.lessKey = key
            if self.mostKey < key:
                self.mostKey = key
            return result
        else : return None


    def addItems(self, key):
        if isinstance(key, int):
            return self.addOneItem(key)
        elif isinstance(key, list) or  isinstance(key, array) or isinstance(key, tuple):
            result = []
            for item in key:
                result.append(self.addOneItem(item))
            return result
        else  : return None
    

    def getItem(self, key):
        return self.itemslist.get(key, None)

    
    def runtime(self, value = None):
        for item in self.runtimeList:
            if not item.runtime(value) == None :
                return item.lastreturn
        return None

    
    def setRunTimeCommand(self, key , command  , timeout ):
#         item = CommandItem()
        item = self.getItem(
            key)
        if not item:
            return None
        else:
            item.set_runtime_command(
                    command, timeout)
            self.runtimeList.append(item)
            return item

    
    def switchActiv(self, key, last = None, new = None):
        item = self.getItem(key)
        if item == None:# {{{
            return None
        else:
            self.lastItem = self.activeItem
            self.activeItem = item
            self.lastItem.lastreturn = self.lastItem.onEndCommand(last)
            self.activeItem.lastreturn = self.activeItem.onStartCommand(new)
            return item

    
    def getKeyList(self):
        return list(map(lambda c: c.value, self.itemslist))
  
    
    def setNextActiv(self,last = None,new = None):
        next = 0
        if self.mostKey == self.activeItem.key:
            next = self.lessKey  
        else : 
            next = self.activeItem.key + 1
        return self.switchActiv(next , last, new)
    
    
    def setPreviusActiv(self,last = None,new = None):
        next = 0
        if self.lessKey == self.activeItem.key:
            next = self.mostKey  
        else : 
            next = self.activeItem.key - 1
        return self.switchActiv(next , last, new)
            # }}}
    
    
    

    
    
    
    
    

