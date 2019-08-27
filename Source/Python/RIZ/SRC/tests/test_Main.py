'''
Created on 28 янв. 2019 г.

@author: BuYn
'''
import unittest
import main
from model.globalsvar import *

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
        print("-++-"*10,i,"-++-"*33)
        i ="Start Test Log"
        print("-++-"*10,i,"-++-"*33)
        self.main = main


    def tearDown(self):
        i ="End Test Log"
        print("-++-"*10,i,"-++-"*33)
        i = "tear Down"
        print("-++-"*10,i,"-++-"*33)


    def testInpitLoop(self):
        self.assertEqual(
            255
            , 255)
        self.assertEqual(
            255
            , 255)
        
                
    def test_initButtons(self):
        self.main.initButtons()
        self.main.buttons.setComandOnPress(B_CHOICE, lambda: print("hi test"))
        self.assertEqual(
            self.main.buttons.isPressed(B_CHOICE) , False)
        self.main.buttons.set(1<<B_CHOICE) 
        print(self.main.buttons.presed)
        self.main.buttons.set(0) 
        print(self.main.buttons.presed)
        self.main.buttons.set(1<<B_CHOICE) 
        print(self.main.buttons.presed)
        self.assertEqual(
            self.main.buttons.isPressed(B_CHOICE) , True)
        
if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
