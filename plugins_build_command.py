import os
import subprocess
from distutils.cmd import Command

class PluginsBuildCommand(Command):
    
    BOOST_DIR = None
    XPLM_INCLUDE_DIR = None
    PLATFORM = 'APL'
    PLUGIN_SCRIPTS_DIR_NAME = None

    user_options = [('install', None, 'install to X-Planes plugin directory')]
    def initialize_options(self):
        self.install = False
        
    def finalize_options(self):
        pass
    
    def run(self):
        boost_library_dir = os.path.join(PluginsBuildCommand.BOOST_DIR, 'stage', 'lib')
        os.chdir('build')
        command = ['cmake']
        command.append('..')
        command.append('-G')
        command.append('MinGW Makefiles')
        command.append('-DBoost_INCLUDE_DIR={0}'.format(PluginsBuildCommand.BOOST_DIR))
        command.append('-DBoost_REGEX_LIBRARY_RELEASE={0}'.format(os.path.join(boost_library_dir, 'libboost_regex-mgw49-mt-1_56.a')))
        command.append('-DBoost_FILESYSTEM_LIBRARY_RELEASE={0}'.format(os.path.join(boost_library_dir, 'libboost_filesystem-mgw49-mt-1_56.a')))
        command.append('-DBoost_SYSTEM_LIBRARY_RELEASE={0}'.format(os.path.join(boost_library_dir, 'libboost_system-mgw49-mt-1_56.a')))
        command.append('-DXPLM_INCLUDE_DIR={0}'.format(PluginsBuildCommand.XPLM_INCLUDE_DIR))
        command.append('-DCMAKE_CXX_FLAGS=-D{0} -D__PLUGIN_SCRIPTS_DIR_NAME__={1}'.format(PluginsBuildCommand.PLATFORM,
                                                                                         PluginsBuildCommand.PLUGIN_SCRIPTS_DIR_NAME))
        
        subprocess.check_call(command)
        
        make_command = ['mingw32-make']
        if self.install:
            make_command.append('install')
        subprocess.check_call(make_command)
