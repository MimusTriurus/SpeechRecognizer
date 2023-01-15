cmake_minimum_required(VERSION 3.17)

set(ProjectName "SpeechRecognizer")
project(${ProjectName})

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        link_directories(${CMAKE_HOME_DIRECTORY}/lib/win/x64)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        link_directories(${CMAKE_HOME_DIRECTORY}/lib/win/x32)
    endif()

    set( CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO" )
    set( CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /MANIFEST:NO" )
    set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO" )
endif( )

include_directories(
        ${CMAKE_HOME_DIRECTORY}/include/
        ${CMAKE_HOME_DIRECTORY}/include/pocketsphinx
        ${CMAKE_HOME_DIRECTORY}/include/sphinxbase
        ${CMAKE_HOME_DIRECTORY}/include/win32
)

#add_executable(${ProjectName} main.cpp
add_library(${ProjectName} SHARED
        speechrecognizer.h
        speechrecognizer.cpp
        speechrecognizerwrapper.cpp
        speechrecognizerwrapper.h
)

target_link_libraries(
        ${ProjectName}
        pocketsphinx
        sphinxbase
)