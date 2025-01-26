cmake_minimum_required(VERSION 3.20)
project(vbindiff)
set(CMAKE_CONFIGURATION_TYPE Debug RelWithDebInfo)
set(CMAKE_SKIP_INSTALL_RULES YES)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT vbindiff)

add_executable(vbindiff)
target_compile_definitions(vbindiff PRIVATE PACKAGE_VERSION="3.0_beta6tom")
target_sources(vbindiff PRIVATE
  vbindiff.cpp
  tables.h
  GetOpt/GetOpt.cpp GetOpt/GetOpt.hpp)
if(WIN32)
  target_sources(vbindiff PRIVATE
    win32/ConWin.cpp win32/ConWin.hpp
    win32/FileIO.hpp
    win32/config.h)
  target_include_directories(vbindiff PRIVATE win32/)
else()
  message(FATAL_ERROR Non-Windows = TODO...)
endif()
