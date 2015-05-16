import unittest
from xplane import __version__

class Test(unittest.TestCase):

    def testName(self):

        from xplane import _binding
        self.assertEqual(_binding.__version__, __version__)  # @UndefinedVariable
        
if __name__ == "__main__":
    unittest.main()
