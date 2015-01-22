#!/bin/sh
bindir=$(pwd)
cd /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/tutorial06_keyboard_and_mouse/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/elliotfiske/471/Cmake/Debug/tutorial06_keyboard_and_mouse 
	else
		"/Users/elliotfiske/471/Cmake/Debug/tutorial06_keyboard_and_mouse"  
	fi
else
	"/Users/elliotfiske/471/Cmake/Debug/tutorial06_keyboard_and_mouse"  
fi
