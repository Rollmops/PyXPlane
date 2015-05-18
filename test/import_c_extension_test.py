import unittest
from xplane import __version__

class Test(unittest.TestCase):

    def test_version(self):

        from xplane import api  # @UnresolvedImport
        self.assertEqual(api.__version__, __version__)  # @UndefinedVariable
        
if __name__ == "__main__":
    unittest.main()
