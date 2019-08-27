'''# {{{
Created on 28 янв. 2019 г.

@author: BuYn
'''
# }}}
import unittest# {{{
from model.globalsvar import *
from presenter.spicom import SPICom
from veiw.termenu import TerMenu
import time
from presenter.leds import LEDs
# }}}
class Test(unittest.TestCase):# {{{

    @classmethod# {{{
    def setUpClass(self):
        print("*"*33,"*"*33)
        print("file opened")
        print("*"*33,"*"*33)
        self.spi = SPICom(LEDSTM_ADRRESS, debugmode=2)
        self.leds= LEDs(self.spi)
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
        self.terMenu = TerMenu(self.spi, self.leds)
        # }}}

    def tearDown(self):# {{{
        i ="End Test Log"
        print("-++-"*10,i,"-++-"*33)
        i = "tear Down"
        print("-++-"*10,i,"-++-"*33)
        # }}}

    def test_init(self):# {{{
        var = "leds 8"
        print(var.split(" "))
        self.assertEqual(
            self.terMenu.isCommandList( var.split(" "))
            , True)
        self.assertEqual(
            self.leds.chenged , True)
        self.assertEqual(
            self.leds.bitWordLast , 256)
        # }}}
        
if __name__ == "__main__":# {{{
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
# }}}
# }}}
