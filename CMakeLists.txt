cmake_minimum_required(VERSION 2.6.8)

project(xplane_script_loader)

find_package(PythonLibs 3.4 REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system regex )

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_library(script_loader SHARED tools/script_loader.cpp ) 
target_link_libraries(script_loader  ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(script_loader PROPERTIES SUFFIX .xpl)
SET_TARGET_PROPERTIES(script_loader PROPERTIES PREFIX "")
