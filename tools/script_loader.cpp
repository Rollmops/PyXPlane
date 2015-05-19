#include <iostream>
#include <fstream>

#include <Python.h>

#define BOOST_FILESYSTEM_VERSION 3
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <XPLMDefs.h>

using namespace boost;

void run_scripts(const boost::filesystem::path &p) {
	regex filePattern("^.+\\.py$");

	if (!filesystem::is_directory(p)) {
		if (regex_match(p.leaf().string(), filePattern)) {
			std::ifstream input(p.string().c_str());

			if (input.is_open()) {

				std::string str((std::istreambuf_iterator<char>(input)),
						std::istreambuf_iterator<char>());

				Py_Initialize();
				PyRun_SimpleString(str.c_str());
				Py_Finalize();
			}
			input.close();
		}
	}
}

PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {
	strcpy(outName, "PythonScriptLoader");
	strcpy(outSig, "pyxplane.scriptloader");
	strcpy(outDesc,
			"A plugin that is responsible for loading the python plugins.");

	filesystem::path workingDir = filesystem::path(
			boost::filesystem::current_path());
	workingDir /= "Resources";
	workingDir /= "plugins";
	workingDir /= "PythonTest";
	workingDir /= "Scripts";

	if (filesystem::exists(workingDir)) {
		for (filesystem::directory_iterator itr(workingDir);
				itr != filesystem::directory_iterator(); ++itr) {
			run_scripts(*itr);

		}
	}
	return 1;
}

