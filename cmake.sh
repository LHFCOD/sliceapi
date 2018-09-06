#!/bin/bash
#CompilePath=/c/Users/BvSsh_VirtualUsers/software/mingw64/bin
cmake -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" 
mingw32-make.exe -f Makefile
#-D CMAKE_C_COMPILER=${CC} -D CMAKE_CXX_COMPILER=${CXX} .
#-DCMAKE_SH="CMAKE_SH-NOTFOUND" 
#-D"CMAKE_MAKE_PROGRAM:PATH=C:/MinGW-32/bin/make.exe" .

