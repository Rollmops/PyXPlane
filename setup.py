import os
import glob
from setuptools import setup, Extension, find_packages
from xplane import __version__

XPLANE_SDK_DIR = os.environ.get('XPLANE_SDK_DIR', r'C:\SDK\XPlane')
BOOST_DIR = os.environ.get('BOOST_DIR', r'C:\SDK\boost_1_56_0')
BOOST_LIBRARY_DIR = os.path.join(BOOST_DIR, 'stage', 'lib')

XPLANE_SDK_HEADERS = os.path.join(XPLANE_SDK_DIR, 'CHeaders')
XPLANE_SDK_LIBRARY_DIR = os.path.join(XPLANE_SDK_DIR, 'Libraries', 'Win')

xplane_module = Extension('xplane._binding',
                          sources=glob.glob('src/*.cpp'),
                          include_dirs=[os.path.join(XPLANE_SDK_HEADERS, 'XPLM'),
                                        os.path.join(XPLANE_SDK_HEADERS, 'Widgets'),
                                        os.path.join(XPLANE_SDK_HEADERS, 'Wrappers'),
                                        BOOST_DIR
                                        ],
                          library_dirs=[XPLANE_SDK_LIBRARY_DIR,
                                        BOOST_LIBRARY_DIR],
                          libraries=['XPLM_64',
                                     'XPWidgets_64',
                                     'boost_python3-mgw49-mt-1_56'],
                          define_macros = [('APL', '1'),
                                           ('__BINDING_VERSION__', __version__),
                                           ('MS_WIN64', '')],
                          extra_compile_args=['-w', '-Wall'],
                        )

setup(name='xplane',
      version=__version__,
      packages=find_packages(),
      ext_modules=[xplane_module],
      zip_safe=False,
      data_files=[('xplane', glob.glob('lib/*.dll'))]
      )
