const char *XPLMFindDataRef_doc = 	"Given a c-style string that names the data ref, this routine looks up the actual opaque XPLMDataRef that you use to read and write the data."
									"The string names for datarefs are published on the x-plane SDK web site."
									"This function returns None if the data ref cannot be found."
									"NOTE: this function is relatively expensive; save the XPLMDataRef this function returns for future use."
									"Do not look up your data ref by string every time you need to read or write it";

const char *XPLMCanWriteDataRef_doc = 	"Given a data ref, this routine returns true if you can successfully set the data, false otherwise."
										"Some datarefs are read-only.";

const char *XPLMGetDataRefTypes_doc = 	"This routine returns the types of the data ref for accessor use."
										"If a data ref is available in multiple data types, they will all be returned.";


const char *XPLMGetDatai_doc = 	"Read an integer data ref and return its value."
								"The return value is the dataref value or 0 if the dataref is invalid/None or the plugin is disabled.";

const char *XPLMGetDataf_doc = 	"Read a single precision floating point dataref and return its value."
								"The return value is the dataref value or 0.0 if the dataref is invalid/None or the plugin is disabled.";

const char *XPLMGetDatad_doc =	"Read a double precision floating point dataref and return its value."
								"The return value is the dataref value or 0.0 if the dataref is invalid/None or the plugin is disabled.";

const char *XPLMSetDatai_doc =	"Write a new value to an integer data ref."
								"This routine is a no-op if the plugin publishing the dataref is disabled, the dataref is invalid, or the dataref is not writable.";

const char *XPLMSetDataf_doc =	"Write a new value to a single precision floating point data ref."
								"This routine is a no-op if the plugin publishing the dataref is disabled, the dataref is invalid, or the dataref is not writable.";

const char *XPLMSetDatad_doc = 	"Write a new value to a double precision floating point data ref."
								"This routine is a no-op if the plugin publishing the dataref is disabled, the dataref is invalid, or the dataref is not writable.";

const char *XPLMRegisterDataAccessor_doc = "This routine creates a new item of data that can be read and written."
											"Pass in the data's full name for searching, the type(s) of the data for accessing, and whether the data can be written to. "
											"For each data type you support, pass in a read accessor function and a write accessor function if necessary."
											"Pass None for data types you do not support or write accessors if you are read-only."
											"You are returned a data ref for the new item of data created."
											"You can use this data ref to unregister your data later or read or write from it.";

const char *XPLMUnregisterDataAccessor_doc = 	"Use this routine to unregister any data accessors you may have registered."
												"You unregister a data ref by the XPLMDataRef you get back from registration."
												"Once you unregister a data ref, your function pointer will not be called anymore."
												"For maximum compatibility, do not unregister your data accessors until final shutdown (when your XPluginStop routine is called)."
												"This allows other plugins to find your data reference once and use it for their entire time of operation.";
