# Copyright (C) 2018 Tomasz Gałaj

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(MeiRenderer)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# Configure assets header file
# configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)
# include_directories(${CMAKE_BINARY_DIR}/src)
	
# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#######################################
# LOOK for the packages that we need! #
#######################################

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# # GLM
# find_package(glm REQUIRED)
# message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# # ASSIMP
# find_package(ASSIMP REQUIRED)
# message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

# # STB_IMAGE
# add_library(STB_IMAGE "thirdparty/stb_image.cpp")

# GLAD
add_library(GLAD "deps/glad/src/glad.c")

# Put all libraries into a variable
set(LIBS ${glfw3_LIBRARY} ${OPENGL_LIBRARY} ) #GLAD ${CMAKE_DL_LIBS} ${ASSIMP_LIBRARY} STB_IMAGE)

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/deps/glad/include"
)

# Define the link libraries
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lglfw -lGL -lX11
    -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread)
