#!/bin/sh
bindir=$(pwd)
cd /Users/elliotfiske/old-school/471/FINAL/finalproj_trimmed/tutorial14_render_to_texture/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/elliotfiske/old-school/471/FINAL/show\ offf/RelWithDebInfo/tutorial14_render_to_texture 
	else
		"/Users/elliotfiske/old-school/471/FINAL/show\ offf/RelWithDebInfo/tutorial14_render_to_texture"  
	fi
else
	"/Users/elliotfiske/old-school/471/FINAL/show\ offf/RelWithDebInfo/tutorial14_render_to_texture"  
fi
