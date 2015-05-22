const char *XPLMFindDataRef_doc = 	"Given a c-style string that names the data ref, this routine looks up the actual opaque XPLMDataRef that you use to read and write the data."
									"The string names for datarefs are published on the x-plane SDK web site."
									"This function returns NULL if the data ref cannot be found."
									"NOTE: this function is relatively expensive; save the XPLMDataRef this function returns for future use."
									"Do not look up your data ref by string every time you need to read or write it";

const char *XPLMCanWriteDataRef_doc = 	"Given a data ref, this routine returns true if you can successfully set the data, false otherwise."
										"Some datarefs are read-only.";

const char *XPLMGetDataRefTypes_doc = 	"This routine returns the types of the data ref for accessor use."
										"If a data ref is available in multiple data types, they will all be returned.";
