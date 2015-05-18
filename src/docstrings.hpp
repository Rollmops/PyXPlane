
const char *XPLMGetMyID_doc = "This routine returns the plugin ID of the calling plug-in. Call this to get your own ID.";
const char *XPLMCountPlugins_doc = "This routine returns the total number of plug-ins that are loaded, both disabled and enabled.";

const char *XPLMGetNthPlugin_doc = 	"This routine returns the ID of a plug-in by index.\n"
									"\n"
									"Index is 0 based from 0 to XPLMCountPlugins-1, inclusive.\n"
									"Plugins may be returned in any arbitrary order.";

const char *XPLMFindPluginByPath_doc = 	"This routine returns the plug-in ID of the plug-in whose file exists at the passed in absolute file system path.\n"
										"\n"
										"XPLM_NO_PLUGIN_ID is returned if the path does not point to a currently loaded plug-in.";

const char *XPLMFindPluginBySignature_doc = "This routine returns the plug-in ID of the plug-in whose signature matches what is passed in or XPLM_NO_PLUGIN_ID if no running plug-in has this signature.\n\n"
											"Signatures are the best way to identify another plug-in as they are independent of the file system path of a plug-in or the human-readable plug-in name,\n"
											"and should be unique for all plug-ins. Use this routine to locate another plugin that your plugin interoperates with";


const char *XPLMGetPluginInfo_doc = "This routine returns information about a plug-in.\n\n"
									"Each parameter should be a pointer to a buffer of at least 256 characters, or NULL to not receive the information.\n"
									"outName - the human-readable name of the plug-in."
	 								"outFilePath - the absolute file path to the file that contains this plug-in."
	 								"outSignature - a unique string that identifies this plug-in."
	 								"outDescription - a human-readable description of this plug-in.";
