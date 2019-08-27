'''# {{{
Created on 28 янв. 2019 г.

@author: BuYn
'''
# }}}
import unittest# {{{
from model.globalsvar import *
from presenter.spicom import SPICom
from presenter.stepmotor import StepMotor, TAG
from presenter.leds import LEDs
# }}}
class Test(unittest.TestCase):# {{{

    @classmethod# {{{
    def setUpClass(self):
        print("*"*33,"*"*33)
        print("file opened")
        print("*"*33,"*"*33)
        self.spi = SPICom(LEDSTM_ADRRESS, debugmode=2)
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
        self.smotor = StepMotor(spi = self.spi, leds=self.leds)
        i ="Start Test Log"
        print("-++-"*10,i,"-++-"*33)
        # }}}

    def tearDown(self):# {{{
        i ="End Test Log"
        print("-++-"*10,i,"-++-"*33)
        i = "tear Down"
        print("-++-"*10,i,"-++-"*33)
        # }}}

    def test_init(self):# {{{
        self.assertEqual(self.smotor.spi, self.spi)
        # }}}

    def test_move(self):# {{{
        self.assertEqual(self.smotor.move("X", 100)
                         , [100, StepMotorsList.X.value[TAG], SM_STEP, 170])
        # }}}

    def test_commands(self):# {{{
        self.assertEqual(self.smotor.setSpeed("X", 100)
                         , [100, StepMotorsList.X.value[TAG], SM_SPEED, 170])
        self.assertEqual(self.smotor.setEnable("x", 1)
                         , 2)
        self.assertEqual(self.smotor.setDir("y", 0)
                         , 2)
        # }}}

    def test_getTag(self):# {{{
        self.assertEqual(self.smotor.getTag("X"), StepMotorsList.X.value)
        self.assertEqual(self.smotor.getTag(3), 3)
        with self.assertRaises(Exception) as context:
            self.smotor.getTag([])
        self.assertEqual(self.smotor.getTag("x"), StepMotorsList.X.value)
        # }}}

if __name__ == "__main__":# {{{
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
# }}}
# }}}
