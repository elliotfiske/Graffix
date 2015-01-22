#!/bin/sh
bindir=$(pwd)
cd /Users/elliotfiske/Downloads/Ass ass ass ass/OpenGL-tutorial_v0014_21/tutorial08_basic_shading/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/elliotfiske/471/CMake\ lovelies/Debug/tutorial08_basic_shading 
	else
		"/Users/elliotfiske/471/CMake\ lovelies/Debug/tutorial08_basic_shading"  
	fi
else
	"/Users/elliotfiske/471/CMake\ lovelies/Debug/tutorial08_basic_shading"  
fi
