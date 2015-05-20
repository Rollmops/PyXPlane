cmake_minimum_required(VERSION 2.6.8)

project(xplane_script_loader)

find_package(PythonLibs 3.4 REQUIRED)
find_package(Boost REQUIRED COMPONENTS python thread filesystem system regex )

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${XPLM_INCLUDE_DIR})
include_directories(src)

add_library(win SHARED tools/script_loader.cpp ) 

find_library(XPLM_LIB XPLM_64 C:/SDK/XPlane/Libraries/Win)
target_link_libraries(win ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${XPLM_LIB})

SET_TARGET_PROPERTIES(win PROPERTIES SUFFIX .xpl)
SET_TARGET_PROPERTIES(win PROPERTIES PREFIX "")

