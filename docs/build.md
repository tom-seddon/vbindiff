You can build vbindiff from source.

# Prerequisites

- Python 3.x
- CMake 3.20+
- GNU Make 4 or later (prebuilt Windows EXE supplied)
- Working C compiler and all that

If using Windows, the Python and CMake supplied with Visual Studio
2019 are good enough.

# Clone the repo

This repo has submodules. Clone it with `--recursive`:

    git clone --recursive https://github.com/tom-seddon/vbindiff
	
Alternatively, if you already cloned it non-recursively, you can do
the following from inside the working copy:

    git submodule init
	git submodule update

(The source zip files that GitHub makes available are no good. The
only supported way to build this project is to clone it from GitHub as
above.)

# Build

This project uses CMake. There's a one-time setup step to get CMake to
generate the build files.

## Visual Studio 2019

For the one time setup, run this command at the command prompt from
the working copy folder:

    make init_vs2019
	
To build the code, load `build/vs2019/vbindiff.sln` into Visual Studio
and compile.
