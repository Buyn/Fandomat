#!/usr/bin/env python
# -*- coding: utf-8 -*- 
import spidev
from model.globalsvar import * 
import time
from veiw.debugprint import DebugPrint


class SPICom(object):
    def __init__(self, address, debugmode = DEBUGMODE):
        self.address = address
#        self.debugmode = debugmode
        self.dp = DebugPrint(debugmode)
        self.spi = spidev.SpiDev()


    def pack(self, tup) :
        #reversed(tup)
        sum = 0
        for i in range(len(tup)) :
            sum |= tup[i]<<(i<<3)
        return sum


    def send(self, word):
        self.dp(3,"sending = [ ", word, " ] ")
        self.spi.open(BUS,DEVICE)
        self.spi.max_speed_hz = 18000000
        self.spi.mode = 0b00
        self.spi.lsbfirst = False
#         c = (word >> 8) & 0xff
#         f = word & 0xff
        resp = self.spi.xfer3([(word >> 8) & 0xff,word & 0xff])
        self.spi.close()
        self.dp(3,"send = [ ", 
                [hex((word >> 8) & 0xff),
                hex(word & 0xff)],
                " ] , resiv = [ ", resp, " ]")
        #time.sleep (SPI_SLEEPAFTERSEND);
        return self.pack(resp[::-1])
    
    
    def sendEOF(self):
        self.dp(2, "send = [ END OF FILE ] ")
        return self.send(SC_ENDOFFILE)
    
    
    def sendExecude(self):
        self.dp(2, "send = [ EXECUTE LAST ONE COMMAND ] ")
        return self.send(SC_EXECUTECOMMAND)
    
    
    def sendEndSession(self):
        self.dp(2, "send = [ END OF SESION ] ")
        return self.send(SC_ENDOFSESION)
    
    
    def sendWordsList(self, command, testmsg = None):
        result = []
        # send waiting one word
        self.dp(3,"comad list = ",  command)
        self.dp(3,"lens is = ", "0x0" + str((len(command))))
        self.send((len(command)))
        for t in command:
            # send command
            result.append(self.send(t))
        return result
    
    
    def sendGetVar(self):
        return self.send(SC_GETVARBYNAME)
    
    
    def decodeError(self, error):
        if (error == 0): return " ok [ NO ERROR ]"
        elif (error == DISINHRONERROR): return " [ DISINHRONERROR ]"
        elif (error == DISINHRONADRESSERROR): return " [ DISINHRONADRESSERROR ]"
        elif (error == STAKERRORCOMAND): return " [ STAKERRORCOMAND ]"
        elif (error == TIMEOUTSESION): return " [ TIMEOUTSESION ]"
        elif (error == SC_ENDOFSESION): return " ok [ SC_ENDOFSESION ]"
        return "Unknowe error code : " + str(error)
    

    def execute(self, command):
        self.dp(2, "Sending to Adress = ", hex(self.address))
        self.dp(2,"Last Sesion Ends whith = ",
                      self.decodeError(self.send(self.address))) 
        resivlist = self.sendWordsList(command)
        self.dp(2, "MsgStakList elements waiting = ", resivlist[0]) 
        resivlist.append((self.sendExecude()))
        self.dp(2, "commandStak send = ", command) 
        self.dp(2, "commandStak resiv = ", resivlist) 
        self.dp(2, "Last command result = ",
                      self.decodeError(self.sendEndSession()))
        return resivlist
            
            
    def getVar(self, varName):
        self.dp(2, "Sending to Adress = ", hex(self.address))
        self.dp(2,"Last Sesion Ends whith = ",
                      self.decodeError(self.send(self.address)))
        resivlist = self.sendWordsList([varName])
        self.dp(2, "MsgStakList elements waiting = ", resivlist[0]) 
        resivlist.append((self.sendGetVar()))
        self.dp(2, "commandStak send = ", 1, varName) 
        self.dp(2, "commandStak resiv = ", resivlist) 
        self.dp(2, "MsgStakList elements waiting = ", resivlist[0]) 
        self.dp(2, "Send Var Name = ", varName)
        self.dp(2, "SPI get Name = ", self.sendGetVar())
        return self.sendEndSession()

    
    def sendIsMsgWating(self):
        self.dp(2, "send = [ IS MESAGES WATING ] ")
        return self.send(SC_ISMSGWATING)
    

    def sendGetMsgByCount(self):
        self.dp(2, "send = [ GET MESAGES BY COUNT] ")
        return self.send(SC_GETMSGBYCOUNT)
    
    
    def getAllMsg(self, testmsg=None):
        self.dp(2, "Sending to Adress = ", hex(self.address))
        self.dp(2, "Last Sesion Ends whith = ",
                      self.decodeError(self.send(self.address)))
        resivlist = self.sendIsMsgWating()
        if testmsg == 0 :
            resivlist = self.send(0)
        if resivlist == 0 :
            self.dp(2, "No Mesages") 
            self.sendEndSession()
            return 0
        self.dp(2, "MsgStakList elements waiting = ", resivlist) 
        msglist = []
        sendmsg = resivlist
        for t in range(resivlist):
            msglist.append(self.send(sendmsg))
            sendmsg = t
        self.dp(2, "resiv mesages list = ", msglist)
        self.sendEndSession()
        return msglist 

    
    def startSesion(self):
        self.dp(2, "Sending to Adress = ", hex(self.address))
        self.dp(2, "Sending to Adress = ", hex(self.address))
        self.dp(2, "Last Sesion Ends whith = ",
                      self.decodeError(self.send(self.address)))

    
    def isWaitingMsg(self, testmsg = 0):
        self.startSesion()
        self.isAdressCorrect(   self.sendIsMsgWating())
        return                  self.sendEndSession()

    
    def isAdressCorrect(self, resiv):
        self.dp(2, "We Sending to ", 
                "" if resiv == self.address 
                    else "not", "correct Adress")
    
    
    def getOneMsg(self, number, testmsg = 0):
        self.startSesion() 
        self.isAdressCorrect(self.sendGetMsgByCount())
        self.dp(2, "Sending Number of values we wating = ", hex(number))
        resiv = [self.send(0)]
        self.dp(2, "Resivid value whith name= ", resiv[0])
        resiv.append(self.sendEndSession())
        self.dp(2, "We Get", resiv.reverse())
        return resiv
