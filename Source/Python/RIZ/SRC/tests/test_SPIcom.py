'''
Created on 28 янв. 2019 г.

@author: BuYn
'''
import unittest
from model.globalsvar import *
from presenter.spicom import SPICom

class Test(unittest.TestCase):


    @classmethod
    def setUpClass(self):
        print("*"*33,"*"*33)
        print ("file opened")
        print("*"*33,"*"*33)

        
    @classmethod
    def tearDownClass(cls):
        print("*"*33,"*"*33)
        print("tear down module")
        print("*"*33,"*"*33)


    def setUp(self):
        i ="set up"
        self.ledstm = SPICom(LEDSTM_ADRRESS, debugmode=2)
        print("*"*33,i,"*"*33)


    def tearDown(self):
        i = "tear Down"
        print("*"*33,i,"*"*33)


    def testSpidevXref(self):
        self.ledstm.dp(4)
        self.assertEqual(
            self.ledstm.send( 200 ) , 200 )
        print(hex(20000))
        self.assertEqual(
            self.ledstm.send( 0x4e20 ) , 0x4e20 )

        
    def testGetVar(self):
        self.assertEqual(
            self.ledstm.getVar( 100 )
            , SC_ENDOFSESION )

        
    def testGetAllMsg(self):
        #self.ledstm.dp(3)
        self.assertEqual( 
            self.ledstm.getAllMsg(testmsg = 0) , 0)
        self.assertEqual(
            self.ledstm.getAllMsg()
            , [176, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174] )

        
    def testisWatingMsg(self):
        #self.ledstm.dp(3)
        self.assertEqual( 
            self.ledstm.isWaitingMsg(testmsg = 0) , 255)

        
    def testsendWordsList(self):
        self.ledstm.dp(3)
        self.assertEqual( 
            self.ledstm.sendWordsList(
                [1,2,3,4,5,6,7,8,9,0], testmsg = 0 ) , [1,2,3,4,5,6,7,8,9,0])

        
    def test_getOneMsg(self):
        #self.ledstm.dp(3)
        self.assertEqual( 
            self.ledstm.getOneMsg(0, testmsg = 0) , [255, 0])

        
if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
