cmake_minimum_required(VERSION 3.1)
project(wav2mp3)

#Enabling Debug
OPTION(DEBUG "Build the project using DEBUG flag" OFF)

#Set variables
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_EXE_LINKER_FLAGS "-flto")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 --std=c++11 -Wall -flto" )

IF(DEBUG)
message("Enabling Debug flag...")
add_definitions(-DDEBUG)
set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG" )
ENDIF()


#Enable C++ 
enable_language(CXX)

#Lame library
set(LAME_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lame-3.100)
set(LAME_INCLUDE_DIRS ${LAME_PATH}/include)
include_directories(${LAME_INCLUDE_DIRS})

#Static linking
IF(WIN32)
set(LAMEMP3LIB ${LAME_PATH}/output/libmp3lame-static.lib)
find_package (Threads REQUIRED)
ELSE()
find_library(LAMEMP3LIB
    NAMES mp3lame
    HINTS "${LAME_PATH}/libmp3lame/.libs"
)
ENDIF()

#Build options
add_executable(wav2mp3 ${CMAKE_CURRENT_SOURCE_DIR}/wav2mp3.cpp)
IF(WIN32)
target_link_libraries(wav2mp3 ${LAMEMP3LIB} Threads::Threads)
ELSE()
target_link_libraries(wav2mp3 ${LAMEMP3LIB} pthread)
ENDIF()
