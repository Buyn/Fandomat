'''
Created on 28 янв. 2019 г.

@author: BuYn
'''
import unittest
from model.globalsvar import *

class Test(unittest.TestCase):


    @classmethod
    def setUpClass(self):
        print("*"*33,"*"*33)
        print ("Seting up class")
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
        import veiw.debugprint
        self.dp = veiw.debugprint.DebugPrint(3)


    def tearDown(self):
        i ="End Test Log"
        print("-++-"*10,i,"-++-"*33)
        i = "tear Down"
        print("-++-"*10,i,"-++-"*33)

        
    def test_debugprint(self):
        self.dp.debugmod = 3
        self.assertEqual(
            self.dp.print(1,"Test msg", " 01")
            , 1)
        self.assertNotEquals(
            self.dp.print(4,"Test msg", " 02")
            , 1)
        self.dp.debugmod = 1
        self.assertEqual(
            self.dp.print(3,"Test msg", " 03")
            , 0)
        self.assertEqual(
            self.dp.print(1,"Test msg", " 04")
            , 1)
        

    def test_Callable(self):
        self.dp.debugmod = 3
        self.assertEqual(
            self.dp(1,"Test msg", " 01")
            , 1)
        self.assertNotEquals(
            self.dp(4,"Test msg", " 02")
            , 1)
        self.dp.debugmod = 1
        self.assertEqual(
            self.dp(3,"Test msg", " 03")
            , 0)
        self.assertEqual(
            self.dp(1,"Test msg", " 04")
            , 1)
        self.assertEqual(
            self.dp(3)
            , -1)
        self.assertEqual(
                self.dp.debugmod
                , 3)


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
