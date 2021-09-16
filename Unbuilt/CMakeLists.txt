# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (FlightSim)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory!" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
   message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
   message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

include_directories(
   external/AntTweakBar-1.16/include/
   external/glfw-3.1.2/include/
   external/glm-0.9.7.1/
   external/glew-1.13.0/include/
   external/assimp-3.0.1270/include/
   external/bullet-2.81-rev2613/src/
   .
)

set(ALL_LIBS
   ${OPENGL_LIBRARY}
   glfw
   GLEW_1130
)

add_definitions(
   -DTW_STATIC
   -DTW_NO_LIB_PRAGMA
   -DTW_NO_DIRECT3D
   -DGLEW_STATIC
   -D_CRT_SECURE_NO_WARNINGS
)


set(MY_HEADER_FILES
	# put all your .h here. Right now we have none.
	# Example : 
	# ../common/shader.hpp
)

set(MY_SOURCE_FILES
	# put all your .c/.cpp here.
	src/main.cpp
	# ../common/shader.cpp
)

add_executable(FlightSim
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
)
target_link_libraries(FlightSim
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
	${GLFW_LIBRARY}
	${GLEW_LIBRARY}
	${ALL_LIBS}
)





# Add a preprocessor define : 

#if(SOME_STUFF)
#	add_definitions(
#		-DCOMPILE_WITH_SOME_PREPROCESSOR_DIRECTIVE
#	)
#endif(SOME_STUFF)
