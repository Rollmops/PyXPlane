#include <iostream>
#include <fstream>

#include <Python.h>

#define BOOST_FILESYSTEM_VERSION 3
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>

#include <XPLMDefs.h>
#include <XPLMUtilities.h>
#include "common.hpp"

//using namespace boost;

#ifndef __PLUGIN_SCRIPTS_DIR_NAME__
#error "__PLUGIN_SCRIPTS_DIR_NAME__ not defined"
#endif

void run_script(const boost::filesystem::path &p)
{
	Py_Initialize();
	FILE *file = fopen(p.string().c_str(), "r");
	if (file != NULL) {
		fseek(file, 0, SEEK_END);
		const long length = ftell(file);
		fseek(file, 0, SEEK_SET);
		char *buffer = (char*)malloc(length);
		if(buffer) {
			fread(buffer, 1 , length, file);
		}
		fclose(file);
		std::stringstream strstream;
		strstream << "Loading python script: " << p.string()
				<< std::endl;

		const int retval = PyRun_SimpleString(buffer);

		if (retval != 0) {
			std::stringstream errorMsg;
			errorMsg << "Python script returned code: " << retval << "(" <<  buffer << ")" << std::endl;
			XPLMDebugString(errorMsg.str().c_str());
		}
		XPLMDebugString("Done\n");

//		free(buffer);
	}
	Py_Finalize();
}


void run_scripts(const boost::filesystem::path &p) {
	boost::regex filePattern("^.+\\.py$");

	if (!boost::filesystem::is_directory(p)) {
		if (boost::regex_match(p.leaf().string(), filePattern))
		{
			std::stringstream strstream;
			strstream << "Loading python script: " << p.string()
							<< std::endl;
			XPLMDebugString(strstream.str().c_str());
			boost::thread script_thread(run_script, p);
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

//	filesystem::current_path(workingDir);

	if (boost::filesystem::exists(workingDir)) {
		for (boost::filesystem::directory_iterator itr(workingDir);
				itr != boost::filesystem::directory_iterator(); ++itr) {
			run_scripts(*itr);

		}
	}
	return 1;
}
//int main() {
//
//	filesystem::path workingDir = filesystem::path(
//			boost::filesystem::current_path());
//	workingDir /= "Resources";
//	workingDir /= "plugins";
//	workingDir /= xstr(__PLUGIN_SCRIPTS_DIR_NAME__);
//	workingDir /= "Scripts";
//
//	//	filesystem::current_path(workingDir);
//
//	if (filesystem::exists(workingDir)) {
//		for (filesystem::directory_iterator itr(workingDir);
//				itr != filesystem::directory_iterator(); ++itr) {
//			run_scripts(*itr);
//
//		}
//	}
//	return 1;
//}
