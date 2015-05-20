#include <iostream>
#include <fstream>
#include <list>

#include <Python.h>

#define BOOST_FILESYSTEM_VERSION 3
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#include <XPLMDefs.h>
#include <XPLMUtilities.h>
#include "common.hpp"

//using namespace boost;

#ifndef __PLUGIN_SCRIPTS_DIR_NAME__
#error "__PLUGIN_SCRIPTS_DIR_NAME__ not defined"
#endif

static std::list<boost::shared_ptr<boost::thread> > threadList;

void run_script(const boost::filesystem::path &p)
{
	std::ifstream python_file(p.string().c_str());
	if( python_file.is_open()) {
		Py_Initialize();
		std::string python_code((std::istreambuf_iterator<char>(python_file)),
		                 std::istreambuf_iterator<char>());

		const int retval = PyRun_SimpleString(python_code.c_str());
		std::stringstream resultMsg;
		if (retval != 0) {
			resultMsg << "PyXPlane: ERROR! Python script [" << p.string() << "] returned code: " << retval << std::endl;
			XPLMDebugString(resultMsg.str().c_str());
		} else {
			resultMsg << "PyXPlane: Python script [" << p.string() << "] exited with no error" << std::endl;
		}
		Py_Finalize();
	}
}


void run_scripts(const boost::filesystem::path &p) {
	boost::regex filePattern("^.+\\.py$");

	if (!boost::filesystem::is_directory(p)) {
		if (boost::regex_match(p.leaf().string(), filePattern))
		{
			std::stringstream debugOut1;
			debugOut1 << "PyXPlane: Loading python script [" << p.string() << "]" << std::endl;
			XPLMDebugString(debugOut1.str().c_str());

			threadList.push_back( boost::shared_ptr<boost::thread>(new boost::thread(run_script, p)) );
		}
	}
}


PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {
	strcpy(outName, "PythonScriptLoader");
	strcpy(outSig, "pyxplane.scriptloader");
	strcpy(outDesc,
			"A plugin that is responsible for loading the python plugins.");

	boost::filesystem::path workingDir = boost::filesystem::path(
			boost::filesystem::current_path());
	workingDir /= "Resources";
	workingDir /= "plugins";
	workingDir /= xstr(__PLUGIN_SCRIPTS_DIR_NAME__);
	workingDir /= "Scripts";

	if (boost::filesystem::exists(workingDir)) {
		for (boost::filesystem::directory_iterator itr(workingDir);
				itr != boost::filesystem::directory_iterator(); ++itr) {
			run_scripts(*itr);

		}
	}
	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	BOOST_FOREACH(std::list<boost::shared_ptr<boost::thread> >::const_reference t, threadList)
	{

	}
}

PLUGIN_API void XPluginDisable(void)
{
}

PLUGIN_API int XPluginEnable(void)
{
	return 1;
}

PLUGIN_API void XPluginReceiveMessage(
					XPLMPluginID	inFromWho,
					long			inMessage,
					void *			inParam)
{
}

