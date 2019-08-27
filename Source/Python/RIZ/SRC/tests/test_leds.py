'''# {{{
Created on 28 янв. 2019 г.

@author: BuYn
'''# }}}
# {{{
import unittest
from model.globalsvar import *
from presenter.spicom import SPICom
from model.spimsg import SpiMSG
from presenter.leds import LEDs
import time
# }}}

class Test(unittest.TestCase):

    @classmethod# {{{
    def setUpClass(self):
        print("*"*33,"*"*33)
        print ("file opened")
        print("*"*33,"*"*33)
        self.spi = SPICom(LEDSTM_ADRRESS, debugmode=4)
    # }}}
        
    @classmethod# {{{
    def tearDownClass(cls):
        print("*"*33,"*"*33)
        print("tear down module")
        print("*"*33,"*"*33)
# }}}

    def setUp(self):# {{{
        i ="set up"
        print("-++-"*10,i,"-++-"*33)
        i ="Start Test Log"
        print("-++-"*10,i,"-++-"*33)
        self.leds = LEDs(self.spi)
        # }}}

    def tearDown(self):# {{{
        i ="End Test Log"
        print("-++-"*10,i,"-++-"*33)
        i = "tear Down"
        print("-++-"*10,i,"-++-"*33)
        # }}}

    def test_LEDsinit(self):# {{{
#         isCommandList( var.split(" "))
        self.assertEqual(
            self.leds.bitWordLast , 0)
        self.assertEqual(
            self.leds.chenged , False)
        # }}}
        
    def test_bitOperatioons(self):# {{{
        x = 11
        print(bin(x))
        y =1
        y <<=2
        print(bin(y))
        c = x|y
        print("c = ", bin(c))
        y <<=1
        c = x&y
        print("c = ", bin(c))
        y >>=2
        print("y = ", bin(y))
        c = x^y
        print("c = ", bin(c))
        c = x^0
        print("c = ", bin(c))
        c = x^1
        print("c = ", bin(c))
        #}}}

    def printbit(self, x):
        result =[]
        for i in range (16):
            if x >> i&1 :
                result.append(i)
        print(result)
        return result

    def test_ledOn(self):# {{{
        print(self.leds.bitWordLast)
        self.printbit(self.leds.bitWordLast)
        self.assertEqual(
            self.leds.chenged , False)
        print(L_READY)
        self.leds.ledOn(L_READY) 
        print(self.leds.bitWordLast)
        self.printbit(self.leds.bitWordLast)
        self.assertEqual(
            self.leds.chenged , True)
        self.assertNotEqual(
            self.leds.bitWordLast, 0)
        self.leds.ledOn(L_FULLCYCLE) 
        print(self.leds.bitWordLast)
        self.printbit(self.leds.bitWordLast)
        self.assertEqual(
            len(self.printbit(self.leds.bitWordLast))
            , 2)
        # }}}
        
    def test_Send(self):# {{{
        self.assertEqual(
            self.leds.send(), False)
        self.leds.ledOn(L_READY) 
        self.assertEqual(
            self.leds.send(), True)
        self.assertEqual(
            self.leds.send(), False)
        # }}}

    def test_ledOff(self):# {{{
        self.leds.bitWordLast = 8448
        print(self.leds.bitWordLast)
        self.assertEqual(
            len(self.printbit(self.leds.bitWordLast))
            , 2)
        self.assertEqual(
            self.leds.chenged , False)
        print(L_READY)
        self.leds.ledOff(L_READY) 
        print(self.leds.bitWordLast)
        self.assertEqual(
            len(self.printbit(self.leds.bitWordLast))
            , 1)
        self.assertEqual(
            self.leds.chenged , True)
        self.leds.ledOff(L_FULLCYCLE) 
        self.assertEqual(
            self.leds.bitWordLast, 0)
        self.leds.ledOff(L_FULLCYCLE) 
        self.assertEqual(
            self.leds.bitWordLast, 0)
        self.assertEqual(
            self.leds.chenged , True)
        # }}}

    def test_ledTrig(self):# {{{
        self.leds.bitWordLast = 8448
        print(self.leds.bitWordLast)
        self.assertEqual(
            len(self.printbit(self.leds.bitWordLast))
            , 2)
        self.assertEqual(
            self.leds.chenged , False)
        print(L_READY)
        self.leds.ledTrig(L_READY) 
        print(self.leds.bitWordLast)
        self.assertEqual(
            len(self.printbit(self.leds.bitWordLast))
            , 1)
        self.assertEqual(
            self.leds.chenged , True)
        self.leds.ledTrig(L_FULLCYCLE) 
        self.assertEqual(
            self.leds.bitWordLast, 0)
        self.leds.ledTrig(L_FULLCYCLE) 
        self.assertNotEqual(
            self.leds.bitWordLast, 0)
        self.assertEqual(
            self.leds.chenged , True)
        # }}}

    def test_blink(self):# {{{
        self.assertEqual(
            self.leds.blinkTime, 0)
        self.assertEqual(
            self.leds.blink(L_CERAMICKNIFE), True)
        self.assertNotEqual(
            self.leds.blinkTime, 0 )
        self.assertEqual(
            self.leds.blink(L_CERAMICKNIFE), False)
        time.sleep(1)
        self.assertEqual(
            self.leds.blink(L_CERAMICKNIFE), True)
        self.assertEqual(
            self.leds.blink(L_CERAMICKNIFE), False)
        # }}}

if __name__ == "__main__":# {{{
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
# }}}
