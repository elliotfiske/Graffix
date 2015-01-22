#!/bin/sh
bindir=$(pwd)
cd /Users/elliotfiske/Downloads/Ass ass ass ass/OpenGL-tutorial_v0014_21/playground/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/elliotfiske/471/CMake\ lovelies/Debug/playground 
	else
		"/Users/elliotfiske/471/CMake\ lovelies/Debug/playground"  
	fi
else
	"/Users/elliotfiske/471/CMake\ lovelies/Debug/playground"  
fi
