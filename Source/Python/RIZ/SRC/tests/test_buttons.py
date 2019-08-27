'''
Created on 28 янв. 2019 г.

@author: BuYn
'''
import unittest
import main
from model.globalsvar import *
from presenter.spicom import SPICom
from presenter.buttons import Buttons

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
        self.buttons = Buttons()


    def tearDown(self):
        i ="End Test Log"
        print("-++-"*10,i,"-++-"*33)
        i = "tear Down"
        print("-++-"*10,i,"-++-"*33)


    def test_Buttons(self):
        self.assertEqual(
            self.buttons.presed , [])
        self.assertEqual(
            self.buttons.change , False)
        
        
    def test_set(self):
        self.buttons.set(200)
        print(bin(200))
        self.assertEqual(
            len(self.buttons.presed) , 3)
        self.assertEqual(
            self.buttons.change , True)
        print(self.buttons.presed)
        self.buttons.set(1)
        print(bin(1))
        self.assertEqual(
            len(self.buttons.presed) , 1)
        self.assertEqual(
            self.buttons.change , True)
        print(self.buttons.presed)
        
        
    def test_Commands(self):
        y = {12: print}
        x= print
        x("on line")
        y.get(12)("on Dic")
        self.buttons.setComandOnPress(B_OK, lambda : int("10"))
        self.assertIsNotNone(
            self.buttons.commandsOnPress.get(B_OK) , 10)
        self.assertEqual(
            self.buttons.exeCommand(B_OK), 10)
        self.assertEqual(
            self.buttons.exeCommand(B_RESET) , False)
        self.buttons.removeCommandOnPress(B_OK)
        self.assertEqual(
            self.buttons.exeCommand(B_OK) , False)
        

    def test_isPressed(self):
        self.assertEqual(
            self.buttons.isPressed(10) , False)
        self.buttons.presed.append(10) 
        self.assertEqual(
            self.buttons.isPressed(10) , True)
        self.assertEqual(
            self.buttons.isPressed(11) , False)
        

    def test_execude(self):
        self.test = False
        self.assertEqual(
            self.buttons.isPressed(B_CHOICE) , False)
        self.buttons.setComandOnPress(B_CHOICE, lambda: print("hi test"))
        self.buttons.set(1<<B_CHOICE) 
        print(self.buttons.presed)
        self.buttons.set(0) 
        print(self.buttons.presed)
        self.buttons.set(1<<B_CHOICE) 
        print(self.buttons.presed)
        self.assertEqual(
            self.buttons.isPressed(B_CHOICE) , True)
        
                             
if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
