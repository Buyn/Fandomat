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
from presenter.buttons import Buttons
from veiw.ledsMenu import *
import os
# }}}



class Test(unittest.TestCase):

    os.chdir('D:/tools.win/Fast/Evol_fast/vadim/tradomat/Toch/Source/Python/RIZ/SRC/')

    @classmethod# {{{
    def setUpClass(self):
        print("*"*33,"*"*33)
        print ("file opened")
        print("*"*33,"*"*33)
        self.spi = SPICom(LEDSTM_ADRRESS, debugmode=4)
        self.buttons = Buttons()
        self.leds = LEDs(self.spi)
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
        self.ledsMenu = LEDsMenu(
                            spi     = self.spi, 
                            buttons = self.buttons,
                            leds    = self.leds 
                            )
        # }}}

    def tearDown(self):# {{{
        i ="End Test Log"
        print("-++-"*10,i,"-++-"*33)
        i = "tear Down"
        print("-++-"*10,i,"-++-"*33)
        # }}}

    def test_init(self):# {{{
        self.assertEqual(
            State.NOTREADY.value , 0)
        self.assertIsNotNone(
                    self.ledsMenu.menu )
        self.assertEqual(
            len(self.ledsMenu.menu.itemslist)
            , len(State.list()))
        self.assertEqual(
            self.ledsMenu.menu.lessKey
            , State.FULL_CYCLE.value)
        self.assertEqual(
            self.ledsMenu.menu.mostKey
            , State.SHARPENNING.value)
#         self.assertEqual(
#             self.ledsMenu.oldState , 0)
        # }}}
        
    def test_runtime(self):# {{{
        self.ledsMenu.setRuntime(self.ledsMenu.readyState)
        self.assertEqual(
            self.ledsMenu.runtime() , True)
        self.assertEqual(
            self.ledsMenu.changed , False)
        self.ledsMenu.setNewState(self.ledsMenu.setReadyState)
        self.assertEqual(
            self.ledsMenu.changed , True)
        print(State.list())
        # }}}

    def test_ready(self):# {{{
        self.assertEqual(
            self.ledsMenu.menu.activeItem , State.NOTREADY.value)
        self.ledsMenu.setReadyState()
        self.assertEqual(
            self.ledsMenu.runtime() , True)
        self.assertEqual(
            self.ledsMenu.changed , False)
        self.assertEqual(
            self.ledsMenu.state , State.READY.value+1)
        self.buttons.set(1<<B_CHOICE)
        self.assertEqual(
            self.ledsMenu.state , State.READY.value +2)
        self.buttons.set(1<<B_OK)
        self.assertEqual(
            self.ledsMenu.state , State.READY.value +2)
        # }}}

    def test_nextStatus(self):# {{{
        self.assertEqual(
            self.ledsMenu.menu.activeItem.key  , State.NOTREADY.value)
        self.ledsMenu.nextStatus()
        self.assertEqual(
            self.ledsMenu.state , State.READY.value)
        self.ledsMenu.nextStatus()
        self.assertEqual(
            self.ledsMenu.state , State.READY.value +1)
        self.ledsMenu.state = State.SHARPENNING.value
        self.assertEqual(
        self.ledsMenu.nextStatus() , State.READY.value+1)
        # }}}

if __name__ == "__main__":# {{{
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
# }}}
