import os
import glob
from setuptools import setup, Extension, find_packages
from xplane import __version__
from cmake_build_command import CmakeBuildCommand

BOOST_DIR = os.environ.get('BOOST_DIR', r'C:\SDK\boost_1_56_0')
BOOST_LIBRARY_DIR = os.path.join(BOOST_DIR, 'stage', 'lib')

XPLANE_SDK_DIR = os.environ.get('XPLANE_SDK_DIR', r'C:\SDK\XPlane')
XPLANE_SDK_HEADER_DIR = os.path.join(XPLANE_SDK_DIR, 'CHeaders')
XPLANE_SDK_LIBRARY_DIR = os.path.join(XPLANE_SDK_DIR, 'Libraries', 'Win')

xplane_module = Extension('xplane.api',
                          sources=glob.glob('src/*.cpp'),
                          include_dirs=[os.path.join(XPLANE_SDK_HEADER_DIR, 'XPLM'),
                                        os.path.join(XPLANE_SDK_HEADER_DIR, 'Widgets'),
                                        os.path.join(XPLANE_SDK_HEADER_DIR, 'Wrappers'),
                                        BOOST_DIR
                                        ],
                          library_dirs=[XPLANE_SDK_LIBRARY_DIR,
                                        BOOST_LIBRARY_DIR],
                          libraries=['XPLM_64',
                                     'boost_python3-mgw49-mt-1_56'],
                          define_macros = [('APL', None),
                                           ('MS_WIN64', None),
                                           ('XPLM200', None),
                                           ('XPLM210', None),
                                           ('__EXTENSION_VERSION__', __version__)
                                           ],
                          extra_compile_args=['-w', '-Wall'],
                        )

CmakeBuildCommand.BOOST_DIR = BOOST_DIR
setup(name='xplane',
      version=__version__,
      packages=find_packages(),
      ext_modules=[xplane_module],
      data_files=[('xplane', glob.glob('lib/*.dll'))],
      zip_safe=False,
      cmdclass = {'external': CmakeBuildCommand }
      )

