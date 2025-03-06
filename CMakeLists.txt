cmake_minimum_required(VERSION 3.21)

PROJECT(dmlog)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

if ( MSVC )
    set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
    ADD_COMPILE_OPTIONS("/std:c++17")
endif()

ModuleInclude("dmformat" "thirdparty/dmformat")

InterfaceImport("dmlog" "include" "")

if (PROJECT_IS_TOP_LEVEL)
    ExeImport("test" "dmlog")
endif(PROJECT_IS_TOP_LEVEL)

