#!/bin/sh
bindir=$(pwd)
cd /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/tutorial04_colored_cube/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/elliotfiske/471/Cmake/Debug/tutorial04_colored_cube 
	else
		"/Users/elliotfiske/471/Cmake/Debug/tutorial04_colored_cube"  
	fi
else
	"/Users/elliotfiske/471/Cmake/Debug/tutorial04_colored_cube"  
fi
