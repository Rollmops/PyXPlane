import unittest
from xplane import api  # @UnresolvedImport

class Test(unittest.TestCase):


    def test_read(self):
        def get_float(refCon):
            self.assertEqual(refCon, 'float')
            return 1.23456789

        def get_int(refCon):
            self.assertEqual(refCon, 'int')
            return 99

        def get_double(refCon):
            self.assertEqual(refCon, 'double')
            return 5.987654

        refFloat = api.XPLMRegisterDataAccessor("pyxplane/testdata/float",
                                api.xplmType_Float,
                                0,
                                None, None,
                                get_float, None,
                                None, None,
                                None, None,
                                None, None,
                                None, None,
                                "float", None)
                                
        refInt = api.XPLMRegisterDataAccessor("pyxplane/testdata/int",
                                api.xplmType_Int,
                                0,
                                get_int, None,
                                None, None,
                                None, None,
                                None, None,
                                None, None,
                                None, None,
                                "int", None)

        refDouble = api.XPLMRegisterDataAccessor("pyxplane/testdata/double",
                                api.xplmType_Double,
                                0,
                                None, None,
                                None, None,
                                get_double, None,
                                None, None,
                                None, None,
                                None, None,
                                "double", None)

        dataRefFloat = api.XPLMFindDataRef('pyxplane/testdata/float')
        dataRefInt = api.XPLMFindDataRef('pyxplane/testdata/int')
        dataRefDouble = api.XPLMFindDataRef('pyxplane/testdata/double')

        self.assertEqual(refFloat, dataRefFloat)
        self.assertEqual(refInt, dataRefInt)
        self.assertEqual(refDouble, dataRefDouble)
        

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()