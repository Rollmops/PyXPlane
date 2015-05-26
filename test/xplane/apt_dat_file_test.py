import unittest
from xplane.apt_dat_file import AptDatFile
import os
from matplotlib import pyplot
from matplotlib import patches


class Test(unittest.TestCase):

    def setUp(self):
        self.sample_file = os.path.join(os.path.dirname(__file__), 'data', 'apt.dat')

    def testName(self):
        apt_dat = AptDatFile(self.sample_file)
        
        
        
        fig = pyplot.figure()
        ax = fig.add_subplot(111)
        ax.set_xlim(51.11, 51.15)
        ax.set_ylim(13.75, 13.79)
        for path in apt_dat.data['taxiways'][:1]:
            patch = patches.PathPatch(path[1], facecolor='orange', lw=2)
            print(path)
            ax.add_patch(patch)
        pyplot.show() 
        


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
#     verts = [
#     (51.12448661, 013.75506612),
#     (51.12404884, 013.75587620), # left, top
#     (51.12356077, 013.75769109), # right, top
#     (51.12396248, 013.75824684), # right, bottom
#     (51.12396248, 013.75824684), (51.12392349, 013.75819283),
#     (51.12389883, 013.75763792), (51.12393694, 013.75745574),
#     (51.12389883, 013.75763792),
#     (51.12429678, 013.75612244),
#     (51.12466676, 013.75543868),
#     (51.12467805, 013.75542115),
#     (51.12470883, 013.75543117),
#     (51.12515588, 013.75604511),
#     (51.12517623, 013.75600855),
#     (51.12448661, 013.75506612)
#     ]
# 
#     codes = [Path.MOVETO,
#          Path.LINETO,
#          Path.LINETO,
#          Path.LINETO,
#          Path.CURVE3,
#          Path.CURVE3,
#          Path.CURVE3,
#          Path.CURVE3,
#          Path.LINETO,
#          Path.LINETO,
#          Path.CURVE3,
#          Path.CURVE3,
#          Path.LINETO,
#          Path.LINETO,
#          Path.LINETO,
#          Path.CLOSEPOLY,
#          ]
#     
#     path = Path(verts, codes)
# 
#     print(path.contains_point((51.124473, 13.755383)))
#     