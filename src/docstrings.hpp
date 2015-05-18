
const char *XPLMGetMyID_doc = 	"This routine returns the plugin ID of the calling plug-in.\n"
								"Call this to get your own ID.";

const char *XPLMCountPlugins_doc = "This routine returns the total number of plug-ins that are loaded, both disabled and enabled.";

const char *XPLMGetNthPlugin_doc = 	"This routine returns the ID of a plug-in by index.\n"
									"Index is 0 based from 0 to XPLMCountPlugins-1, inclusive."
									"Plugins may be returned in any arbitrary order.";

const char *XPLMFindPluginByPath_doc = 	"This routine returns the plug-in ID of the plug-in whose file exists at the passed in absolute file system path.\n"
										"XPLM_NO_PLUGIN_ID is returned if the path does not point to a currently loaded plug-in.";

const char *XPLMFindPluginBySignature_doc = "This routine returns the plug-in ID of the plug-in whose signature matches what is passed in or XPLM_NO_PLUGIN_ID if no running plug-in has this signature.\n"
											"Signatures are the best way to identify another plug-in as they are independent of the file system path of a plug-in or the human-readable plug-in name,"
											"and should be unique for all plug-ins. Use this routine to locate another plugin that your plugin interoperates with";


const char *XPLMGetPluginInfo_doc = "This routine returns information about a plug-in.\n"
									"Each parameter should be a pointer to a buffer of at least 256 characters, or NULL to not receive the information."
									"outName - the human-readable name of the plug-in."
	 								"outFilePath - the absolute file path to the file that contains this plug-in."
	 								"outSignature - a unique string that identifies this plug-in."
	 								"outDescription - a human-readable description of this plug-in.";


const char *XPLMIsPluginEnabled_doc = "Returns whether the specified plug-in is enabled for running.";

const char *XPLMEnablePlugin_doc = "This routine enables a plug-in if it is not already enabled.\n"
									"It returns 1 if the plugin was enabled or successfully enables itself, 0 if it does not."
									"Plugins may fail to enable (for example, if resources cannot be acquired) by returning 0 from their XPluginEnable callback.";

const char *XPLMDisablePlugin_doc = "This routine disableds an enabled plug-in.";

const char *XPLMReloadPlugins_doc = "This routine reloads all plug-ins.\n"
									"Once this routine is called and you return from the callback you were within (e.g. a menu select callback)"
									"you will receive your XPluginDisable and XPluginStop callbacks and your DLL will be unloaded,"
									"then the start process happens as if the sim was starting up.";

const char *XPLMSendMessageToPlugin_doc = 	"This function sends a message to another plug-in or X-Plane.\n"
											"Pass XPLM_NO_PLUGIN_ID to broadcast to all plug-ins."
											"Only enabled plug-ins with a message receive function receive the message.";

const char *XPLMHasFeature_doc = "This returns 1 if the given installation of X-Plane supports a feature, or 0 if it does not.";

const char *XPLMIsFeatureEnabled_doc = "This returns 1 if a feature is currently enabled for your plugin, or 0 if it is not enabled.\n"
										"It is an error to call this routine with an unsupported feature.";

const char *XPLMEnableFeature_doc  = 	"This routine enables or disables a feature for your plugin.\n"
										"This will change the running behavior of X-Plane and your plugin in some way, depending on the feature.";

const char *XPLMEnumerateFeatures_doc = "This routine calls your enumerator callback once for each feature that this running version of X-Plane supports.\n"
										"Use this routine to determine all of the features that X-Plane can support.";
