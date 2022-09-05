#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8.12)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#-------------------------------------------------------------------------------
#	SOURCE CODE
#-------------------------------------------------------------------------------

# .cpp files
list(APPEND SOURCE_FILES
src/exception.h
src/matrix2d.h
src/main.cpp
src/matrix2d.cpp
)

#-------------------------------------------------------------------------------
#	PROJECT SETTINGS
#-------------------------------------------------------------------------------

set(TARGET_NAME matrix2d_Demo)

# Set the project name
PROJECT(matrix2d_Demo)

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

if(MSVC)
	add_compile_options(/MP)
	add_compile_options(/std:c++20)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(-std=c++20)
endif(MSVC)

#-------------------------------------------------------------------------------
#	SOURCE GROUPS
#-------------------------------------------------------------------------------

source_group(source REGULAR_EXPRESSION ".*[.]cpp")
source_group(headers REGULAR_EXPRESSION ".*[.]h")

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------

# Generate the executable
add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Use the automatically determined RPATH values
set_target_properties(${TARGET_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)


