# -*- mode:makefile-gmake; -*-

##########################################################################
##########################################################################

ifeq ($(OS),Windows_NT)
PYTHON:=py -3
SHELL:=$(windir)\system32\cmd.exe
else
PYTHON:=/usr/bin/python3
endif

##########################################################################
##########################################################################

PWD:=$(shell $(PYTHON) submodules/shellcmd.py/shellcmd.py realpath .)
SHELLCMD:=$(PYTHON) "$(PWD)/submodules/shellcmd.py/shellcmd.py"

##########################################################################
##########################################################################

_V:=$(if $(VERBOSE),,@)

##########################################################################
##########################################################################

.PHONY:default
default:
	@echo Must specify target: init_vs2019

##########################################################################
##########################################################################

.PHONY:init_vs2019
init_vs2019:
	$(_V)$(MAKE) _init_newer_vs VSYEAR=2019 VSVER=16

##########################################################################
##########################################################################

_init_newer_vs: _VS_PATH:=$(shell "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -version $(VSVER) -property installationPath)
_init_newer_vs: _CMAKE:=$(_VS_PATH)\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe
_init_newer_vs: _BUILD:=build/vs$(VSYEAR)
_init_newer_vs:
	$(_V)$(SHELLCMD) rm-tree "$(_BUILD)"
	$(_V)$(SHELLCMD) mkdir "$(_BUILD)"
	$(_V)cd "$(_BUILD)" && "$(_CMAKE)" -G "Visual Studio $(VSVER)" -A x64 ../../

##########################################################################
##########################################################################
