import os
import subprocess
from distutils.cmd import Command

class CmakeBuildCommand(Command):
    
    BOOST_DIR = None

    user_options = []
    def initialize_options(self):
        pass
        
    def finalize_options(self):
        pass
    
    def run(self):
        boost_library_dir = os.path.join(CmakeBuildCommand.BOOST_DIR, 'stage', 'lib')
        os.chdir('build')
        command = ['cmake']
        command.append('..')
        command.append('-G')
        command.append('MinGW Makefiles')
        command.append('-DBoost_INCLUDE_DIR={0}'.format(CmakeBuildCommand.BOOST_DIR))
        command.append('-DBoost_REGEX_LIBRARY_RELEASE={0}'.format(os.path.join(boost_library_dir, 'libboost_regex-mgw49-mt-1_56.a')))
        command.append('-DBoost_FILESYSTEM_LIBRARY_RELEASE={0}'.format(os.path.join(boost_library_dir, 'libboost_filesystem-mgw49-mt-1_56.a')))
        command.append('-DBoost_SYSTEM_LIBRARY_RELEASE={0}'.format(os.path.join(boost_library_dir, 'libboost_system-mgw49-mt-1_56.a')))
        
        subprocess.check_call(command)
        
        subprocess.check_call(['mingw32-make'])
