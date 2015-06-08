from xplane import api

import unittest

class DataAccessTestCase:

	def test_read(self):
		
		def get_int_list(refCon):
			assert refCon == "read_refcon"
			return [1,2,3,4,7]
			
		def get_float_list(refCon):
			assert refCon == "read_refcon"
			return [1.2, 2.3, 5.4]

		int_ref = api.XPLMRegisterDataAccessor("pyxplane/testdata/read",
								api.xplmType_IntArray + api.xplmType_FloatArray,
								0,
								None, None,
								None, None,
								None, None,
								get_int_list, None,
								get_float_list, None,
								None, None,
								"read_refcon", None)

		read_data_ref = api.XPLMFindDataRef("pyxplane/testdata/read")

		#assert api.XPLMGetDatai(read_data_ref) == 654321
		print(api.XPLMGetDatavi(read_data_ref,0,10))
		print(api.XPLMGetDatavf(read_data_ref))
		
	

if __name__ == '__main__':
	DataAccessTestCase().test_read()
	#print(api.ret_float())