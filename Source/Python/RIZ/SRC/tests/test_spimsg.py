'''# {{{
Created on 28 янв. 2019 г.

@author: BuYn
'''# }}}
# {{{
import unittest
from model.globalsvar import *
from presenter.spicom import SPICom
from model.spimsg import SpiMSG
from presenter.buttons import Buttons
import time
# }}}
class Test(unittest.TestCase):# {{{

    @classmethod# {{{
    def setUpClass(self):
        print("*"*33,"*"*33)
        print ("file opened")
        print("*"*33,"*"*33)
        self.spi = SPICom(LEDSTM_ADRRESS, debugmode=2)
        self.button = Buttons()
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
        self.smsg = SpiMSG(self.spi, self.button)
# }}}

    def tearDown(self):# {{{
        i ="End Test Log"
        print("-++-"*10,i,"-++-"*33)
        i = "tear Down"
        print("-++-"*10,i,"-++-"*33)
# }}}

    def test_getmsg(self):# {{{
        self.assertEqual(
            self.smsg.msgsStack ,[] )
        self.assertEqual(
            self.smsg.getMSG() ,255 )
        self.assertEqual(
            len(self.smsg.msgsStack) , 1 )
        self.assertEqual(
            len(self.smsg.msgsStack[0]) , 2 )
        self.assertEqual(
            self.smsg.msgsStack[0] , [255, 0] )
        # }}}
        
    def test_runtime(self):# {{{
        time.sleep(SPI_SLEEPBETWINMSGGET / 2)
        print(self.smsg.nextruntime)
        print(time.time())
        self.assertEqual(
            self.smsg.runtime() , None )
        self.assertEqual(
            len(self.smsg.msgsStack) , 0 )
        time.sleep(SPI_SLEEPBETWINMSGGET)
        self.assertEqual(
            self.smsg.runtime() , False )
        self.assertEqual(
            len(self.smsg.msgsStack) , 0 )
        # }}}
        
    def test_rutineMSGStack(self):# {{{
        self.assertEqual(
            self.smsg.getMSG() , 255 )
        self.assertEqual(
            len(self.smsg.msgsStack) , 1 )
        self.assertEqual(
            self.smsg.rutineMSGStack() , False )
        self.assertEqual(
            len(self.smsg.msgsStack) , 0 )
        self.smsg.msgsStack.append([1, 1])
        self.assertEqual(
            self.smsg.rutineMSGStack() , True )
        self.assertEqual(
            len(self.smsg.msgsStack) , 0 )
        # }}}
        
    def test_buttonMSG(self):# {{{
        self.assertEqual(
            len(self.button.presed) , 0 )
        self.smsg.msgsStack.append([VN_BUTTONVAULT01, 1])
        self.assertEqual(
            self.smsg.rutineMSGStack() , True )
        self.assertEqual(
            len(self.smsg.msgsStack) , 0 )
        self.assertEqual(
            len(self.button.presed) , 1 )
        self.smsg.msgsStack.append([VN_BUTTONVAULT01, 200])
        self.assertEqual(
            self.smsg.rutineMSGStack() , True )
        self.assertEqual(
            len(self.smsg.msgsStack) , 0 )
        self.assertEqual(
            len(self.button.presed) , 3 )
        # }}}
        
if __name__ == "__main__":# {{{
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
    # }}}
# }}}

