	.section	__TEXT,__text,regular,pure_instructions
	.section	__DWARF,__debug_info,regular,debug
Lsection_info:
	.section	__DWARF,__debug_abbrev,regular,debug
Lsection_abbrev:
	.section	__DWARF,__debug_aranges,regular,debug
	.section	__DWARF,__debug_macinfo,regular,debug
	.section	__DWARF,__debug_line,regular,debug
Lsection_line:
	.section	__DWARF,__debug_loc,regular,debug
	.section	__DWARF,__debug_str,regular,debug
Linfo_string:
	.section	__DWARF,__debug_ranges,regular,debug
Ldebug_range:
	.section	__DWARF,__debug_loc,regular,debug
Lsection_debug_loc:
	.file	1 "/Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp"
	.file	2 "/Users/elliotfiske/471/OpenGL-tutorial_v0014_21/external/glfw-3.0.3/include/GLFW/glfw3.h"
	.file	3 "/Users/elliotfiske/471/OpenGL-tutorial_v0014_21/external/glew-1.9.0/include/GL/glew.h"
	.file	4 "/Users/elliotfiske/471/OpenGL-tutorial_v0014_21/external/glm-0.9.4.0/glm/./core/_detail.hpp"
	.section	__TEXT,__text,regular,pure_instructions
	.globl	__Z14window_resizedP10GLFWwindowii
	.align	4, 0x90
__Z14window_resizedP10GLFWwindowii:     ## @_Z14window_resizedP10GLFWwindowii
Lfunc_begin0:
	.loc	1 22 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:22:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp4:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str(%rip), %rax
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	.loc	1 23 0 prologue_end     ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:23:0
Ltmp5:
	movl	_width(%rip), %esi
	movl	_height(%rip), %edx
	movq	%rax, %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, %edx
	.loc	1 24 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:24:0
	movl	-12(%rbp), %esi
	movl	%esi, _width(%rip)
	.loc	1 25 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:25:0
	movl	-16(%rbp), %esi
	movl	%esi, _height(%rip)
	.loc	1 26 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:26:0
	movl	_width(%rip), %esi
	movl	_height(%rip), %ecx
	movl	%edx, %edi
	movl	%esi, -20(%rbp)         ## 4-byte Spill
	movl	%edx, %esi
	movl	-20(%rbp), %edx         ## 4-byte Reload
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	callq	_glViewport
	.loc	1 27 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:27:0
	addq	$32, %rsp
	popq	%rbp
	retq
Ltmp6:
Lfunc_end0:
	.cfi_endproc

	.section	__TEXT,__literal8,8byte_literals
	.align	3
LCPI1_0:
	.quad	4576918229304087675     ## double 0.01
	.section	__TEXT,__literal4,4byte_literals
	.align	2
LCPI1_1:
	.long	1050253722              ## float 0.300000012
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
Lfunc_begin1:
	.loc	1 30 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:30:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp10:
	.cfi_def_cfa_offset 16
Ltmp11:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp12:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	subq	$408, %rsp              ## imm = 0x198
Ltmp13:
	.cfi_offset %rbx, -40
Ltmp14:
	.cfi_offset %r14, -32
Ltmp15:
	.cfi_offset %r15, -24
	movl	$0, -28(%rbp)
	.loc	1 32 0 prologue_end     ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:32:0
Ltmp16:
	callq	_glfwInit
	cmpl	$0, %eax
	jne	LBB1_2
## BB#1:
	leaq	L_.str1(%rip), %rsi
	movq	___stderrp@GOTPCREL(%rip), %rax
	.loc	1 34 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:34:0
Ltmp17:
	movq	(%rax), %rdi
	movb	$0, %al
	callq	_fprintf
	.loc	1 35 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:35:0
	movl	$-1, -28(%rbp)
	movl	%eax, -84(%rbp)         ## 4-byte Spill
	jmp	LBB1_22
Ltmp18:
LBB1_2:
	movl	$135181, %edi           ## imm = 0x2100D
	movl	$4, %esi
	.loc	1 38 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:38:0
	callq	_glfwWindowHint
	movl	$139266, %edi           ## imm = 0x22002
	movl	$2, %esi
	.loc	1 39 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:39:0
	callq	_glfwWindowHint
	movl	$139267, %edi           ## imm = 0x22003
	movl	$1, %esi
	.loc	1 40 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:40:0
	callq	_glfwWindowHint
	leaq	L_.str2(%rip), %rdx
	movabsq	$0, %rax
	.loc	1 44 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:44:0
	movl	$800, _width(%rip)      ## imm = 0x320
	.loc	1 45 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:45:0
	movl	$800, _height(%rip)     ## imm = 0x320
	.loc	1 46 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:46:0
	movl	_width(%rip), %edi
	movl	_height(%rip), %esi
	movq	%rax, %rcx
	movq	%rax, %r8
	callq	_glfwCreateWindow
	movq	%rax, _window(%rip)
	.loc	1 47 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:47:0
Ltmp19:
	cmpq	$0, _window(%rip)
	jne	LBB1_4
## BB#3:
	leaq	L_.str3(%rip), %rsi
	movq	___stderrp@GOTPCREL(%rip), %rax
	.loc	1 48 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:48:0
Ltmp20:
	movq	(%rax), %rdi
	movb	$0, %al
	callq	_fprintf
	.loc	1 49 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:49:0
	movl	%eax, -88(%rbp)         ## 4-byte Spill
	callq	_glfwTerminate
	.loc	1 50 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:50:0
	movl	$-1, -28(%rbp)
	jmp	LBB1_22
Ltmp21:
LBB1_4:
	.loc	1 52 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:52:0
	movq	_window(%rip), %rdi
	callq	_glfwMakeContextCurrent
	.loc	1 55 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:55:0
Ltmp22:
	callq	_glewInit
	cmpl	$0, %eax
	je	LBB1_6
## BB#5:
	leaq	L_.str4(%rip), %rsi
	movq	___stderrp@GOTPCREL(%rip), %rax
	.loc	1 56 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:56:0
Ltmp23:
	movq	(%rax), %rdi
	movb	$0, %al
	callq	_fprintf
	.loc	1 57 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:57:0
	movl	$-1, -28(%rbp)
	movl	%eax, -92(%rbp)         ## 4-byte Spill
	jmp	LBB1_22
Ltmp24:
LBB1_6:
	movl	$208898, %esi           ## imm = 0x33002
	movl	$1, %edx
	.loc	1 61 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:61:0
	movq	_window(%rip), %rdi
	callq	_glfwSetInputMode
	leaq	__Z14window_resizedP10GLFWwindowii(%rip), %rsi
	.loc	1 63 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:63:0
	movq	_window(%rip), %rdi
	callq	_glfwSetWindowSizeCallback
	xorps	%xmm0, %xmm0
	.loc	1 66 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:66:0
	movss	%xmm0, -96(%rbp)        ## 4-byte Spill
	movss	-96(%rbp), %xmm1        ## 4-byte Reload
	movss	-96(%rbp), %xmm2        ## 4-byte Reload
	movss	-96(%rbp), %xmm3        ## 4-byte Reload
	movq	%rax, -104(%rbp)        ## 8-byte Spill
	callq	_glClearColor
	movl	$34370, %edi            ## imm = 0x8642
	.loc	1 67 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:67:0
	callq	_glEnable
	leaq	L_.str5(%rip), %rdi
	leaq	L_.str6(%rip), %rsi
	.loc	1 70 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:70:0
	callq	__Z11LoadShadersPKcS0_
	movabsq	$0, %rdi
	leaq	L_.str12(%rip), %rsi
	movq	___glewGetUniformLocation@GOTPCREL(%rip), %rcx
	leaq	L_.str11(%rip), %r8
	leaq	L_.str10(%rip), %r9
	leaq	L_.str9(%rip), %r10
	leaq	L_.str8(%rip), %r11
	movq	___glewGetAttribLocation@GOTPCREL(%rip), %rbx
	leaq	L_.str7(%rip), %r14
	movl	%eax, -32(%rbp)
	.loc	1 73 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:73:0
	movq	(%rbx), %r15
	movl	-32(%rbp), %eax
	movq	%rdi, -112(%rbp)        ## 8-byte Spill
	movl	%eax, %edi
	movq	%rsi, -120(%rbp)        ## 8-byte Spill
	movq	%r14, %rsi
	movq	%rbx, -128(%rbp)        ## 8-byte Spill
	movq	%r10, -136(%rbp)        ## 8-byte Spill
	movq	%r11, -144(%rbp)        ## 8-byte Spill
	movq	%rcx, -152(%rbp)        ## 8-byte Spill
	movq	%r8, -160(%rbp)         ## 8-byte Spill
	movq	%r9, -168(%rbp)         ## 8-byte Spill
	callq	*%r15
	movl	%eax, -36(%rbp)
	.loc	1 74 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:74:0
	movq	-128(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx), %rsi
	movl	-32(%rbp), %edi
	movq	-144(%rbp), %r8         ## 8-byte Reload
	movq	%rsi, -176(%rbp)        ## 8-byte Spill
	movq	%r8, %rsi
	movq	-176(%rbp), %r9         ## 8-byte Reload
	callq	*%r9
	movl	%eax, -40(%rbp)
	.loc	1 75 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:75:0
	movq	-152(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx), %rsi
	movl	-32(%rbp), %edi
	movq	-136(%rbp), %r8         ## 8-byte Reload
	movq	%rsi, -184(%rbp)        ## 8-byte Spill
	movq	%r8, %rsi
	movq	-184(%rbp), %r9         ## 8-byte Reload
	callq	*%r9
	movl	%eax, -44(%rbp)
	.loc	1 76 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:76:0
	movq	-152(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx), %rsi
	movl	-32(%rbp), %edi
	movq	-168(%rbp), %r8         ## 8-byte Reload
	movq	%rsi, -192(%rbp)        ## 8-byte Spill
	movq	%r8, %rsi
	movq	-192(%rbp), %r9         ## 8-byte Reload
	callq	*%r9
	movl	%eax, -48(%rbp)
	.loc	1 77 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:77:0
	movq	-152(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx), %rsi
	movl	-32(%rbp), %edi
	movq	-160(%rbp), %r8         ## 8-byte Reload
	movq	%rsi, -200(%rbp)        ## 8-byte Spill
	movq	%r8, %rsi
	movq	-200(%rbp), %r9         ## 8-byte Reload
	callq	*%r9
	movl	%eax, -52(%rbp)
	.loc	1 78 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:78:0
	movq	-152(%rbp), %rcx        ## 8-byte Reload
	movq	(%rcx), %rsi
	movl	-32(%rbp), %edi
	movq	-120(%rbp), %r8         ## 8-byte Reload
	movq	%rsi, -208(%rbp)        ## 8-byte Spill
	movq	%r8, %rsi
	movq	-208(%rbp), %r9         ## 8-byte Reload
	callq	*%r9
	movl	%eax, -56(%rbp)
	.loc	1 81 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:81:0
	movq	-112(%rbp), %rdi        ## 8-byte Reload
	callq	_time
	movl	%eax, %edx
	movl	%edx, %edi
	callq	_srand
	.loc	1 82 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:82:0
Ltmp25:
	movl	$0, -60(%rbp)
LBB1_7:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$80, -60(%rbp)
	jge	LBB1_10
## BB#8:                                ##   in Loop: Header=BB1_7 Depth=1
	.loc	1 83 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:83:0
Ltmp26:
	callq	_rand
	leaq	__ZZ4mainE19g_point_buffer_data(%rip), %rcx
	movabsq	$1, %rdx
	cvtsi2ssq	%rdx, %xmm0
	movabsq	$1073741824, %rdx       ## imm = 0x40000000
	cvtsi2ssq	%rdx, %xmm1
	cvtsi2ssl	%eax, %xmm2
	divss	%xmm1, %xmm2
	subss	%xmm0, %xmm2
	movss	%xmm2, -64(%rbp)
	.loc	1 84 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:84:0
	movss	-64(%rbp), %xmm0
	movslq	-60(%rbp), %rdx
	movss	%xmm0, (%rcx,%rdx,4)
Ltmp27:
## BB#9:                                ##   in Loop: Header=BB1_7 Depth=1
	.loc	1 82 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:82:0
	movl	-60(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -60(%rbp)
	jmp	LBB1_7
Ltmp28:
LBB1_10:
	movabsq	$2, %rax
	cvtsi2ssq	%rax, %xmm0
	xorps	%xmm1, %xmm1
	movl	$34962, %ecx            ## imm = 0x8892
	movabsq	$24, %rsi
	leaq	__ZZ4mainE19g_color_buffer_data(%rip), %rax
	movl	$35044, %edx            ## imm = 0x88E4
	movq	___glewBufferData@GOTPCREL(%rip), %rdi
	movq	___glewBindBuffer@GOTPCREL(%rip), %r8
	movl	$1, %r9d
	leaq	-72(%rbp), %r10
	movq	___glewGenBuffers@GOTPCREL(%rip), %r11
	movabsq	$320, %rbx              ## imm = 0x140
	leaq	__ZZ4mainE19g_point_buffer_data(%rip), %r14
	leaq	-68(%rbp), %r15
Ltmp29:
	##DEBUG_VALUE: main:vertexbuffer <- R15
	.loc	1 95 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:95:0
	movq	%rdi, -216(%rbp)        ## 8-byte Spill
	movl	%r9d, %edi
	movq	%rsi, -224(%rbp)        ## 8-byte Spill
	movq	%r15, %rsi
	movss	%xmm0, -228(%rbp)       ## 4-byte Spill
	movss	%xmm1, -232(%rbp)       ## 4-byte Spill
	movl	%ecx, -236(%rbp)        ## 4-byte Spill
	movq	%rbx, -248(%rbp)        ## 8-byte Spill
	movq	%rax, -256(%rbp)        ## 8-byte Spill
	movl	%edx, -260(%rbp)        ## 4-byte Spill
	movq	%r14, -272(%rbp)        ## 8-byte Spill
	movq	%r8, -280(%rbp)         ## 8-byte Spill
	movl	%r9d, -284(%rbp)        ## 4-byte Spill
	movq	%r10, -296(%rbp)        ## 8-byte Spill
	movq	%r11, -304(%rbp)        ## 8-byte Spill
	callq	*(%r11)
	.loc	1 96 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:96:0
	movq	-280(%rbp), %rax        ## 8-byte Reload
	movq	(%rax), %rsi
	movl	-68(%rbp), %ecx
	movl	-236(%rbp), %edi        ## 4-byte Reload
	movq	%rsi, -312(%rbp)        ## 8-byte Spill
	movl	%ecx, %esi
	movq	-312(%rbp), %r8         ## 8-byte Reload
	callq	*%r8
	.loc	1 97 0                  ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:97:0
	movl	-236(%rbp), %edi        ## 4-byte Reload
	movq	-248(%rbp), %rsi        ## 8-byte Reload
	movq	-272(%rbp), %rdx        ## 8-byte Reload
	movl	-260(%rbp), %ecx        ## 4-byte Reload
	movq	-216(%rbp), %rax        ## 8-byte Reload
	callq	*(%rax)
Ltmp30:
	##DEBUG_VALUE: main:colorbuffer <- [RBP+-296]
	.loc	1 100 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:100:0
	movl	-284(%rbp), %edi        ## 4-byte Reload
	movq	-296(%rbp), %rsi        ## 8-byte Reload
	movq	-304(%rbp), %rax        ## 8-byte Reload
	callq	*(%rax)
	.loc	1 101 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:101:0
	movq	-280(%rbp), %rax        ## 8-byte Reload
	movq	(%rax), %rdx
	movl	-72(%rbp), %esi
	movl	-236(%rbp), %edi        ## 4-byte Reload
	callq	*%rdx
	.loc	1 102 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:102:0
	movl	-236(%rbp), %edi        ## 4-byte Reload
	movq	-224(%rbp), %rsi        ## 8-byte Reload
	movq	-256(%rbp), %rdx        ## 8-byte Reload
	movl	-260(%rbp), %ecx        ## 4-byte Reload
	movq	-216(%rbp), %rax        ## 8-byte Reload
	callq	*(%rax)
	.loc	1 105 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:105:0
	movss	-232(%rbp), %xmm0       ## 4-byte Reload
	movss	%xmm0, -76(%rbp)
	.loc	1 107 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:107:0
	movss	-228(%rbp), %xmm1       ## 4-byte Reload
	movss	%xmm1, -80(%rbp)
Ltmp31:
LBB1_11:                                ## =>This Inner Loop Header: Depth=1
	movl	$16384, %edi            ## imm = 0x4000
	.loc	1 112 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:112:0
Ltmp32:
	callq	_glClear
	movq	___glewUseProgram@GOTPCREL(%rip), %rax
	.loc	1 115 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:115:0
	movq	(%rax), %rax
	movl	-32(%rbp), %edi
	callq	*%rax
	.loc	1 118 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:118:0
Ltmp33:
	movl	_width(%rip), %edi
	cmpl	_height(%rip), %edi
	jle	LBB1_13
## BB#12:                               ##   in Loop: Header=BB1_11 Depth=1
	movabsq	$1, %rax
	cvtsi2ssq	%rax, %xmm1
	movq	___glewUniform2f@GOTPCREL(%rip), %rax
	.loc	1 119 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:119:0
Ltmp34:
	movq	(%rax), %rax
	movl	-44(%rbp), %edi
	cvtsi2ssl	_height(%rip), %xmm0
	cvtsi2ssl	_width(%rip), %xmm2
	divss	%xmm2, %xmm0
	callq	*%rax
	.loc	1 120 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:120:0
	jmp	LBB1_14
Ltmp35:
LBB1_13:                                ##   in Loop: Header=BB1_11 Depth=1
	movabsq	$1, %rax
	cvtsi2ssq	%rax, %xmm0
	movq	___glewUniform2f@GOTPCREL(%rip), %rax
	.loc	1 122 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:122:0
Ltmp36:
	movq	(%rax), %rax
	movl	-44(%rbp), %edi
	cvtsi2ssl	_width(%rip), %xmm1
	cvtsi2ssl	_height(%rip), %xmm2
	divss	%xmm2, %xmm1
	callq	*%rax
Ltmp37:
LBB1_14:                                ##   in Loop: Header=BB1_11 Depth=1
	movabsq	$2, %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	LCPI1_0(%rip), %xmm1
	cvtsi2ssq	%rax, %xmm2
	movq	___glewUniform1f@GOTPCREL(%rip), %rax
	movss	LCPI1_1(%rip), %xmm3
	movq	___glewUniform2f@GOTPCREL(%rip), %rcx
	.loc	1 124 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:124:0
	movq	(%rcx), %rcx
	movl	-48(%rbp), %edi
	cvtsi2ssl	_width(%rip), %xmm4
	divss	%xmm2, %xmm4
	cvtsi2ssl	_height(%rip), %xmm5
	divss	%xmm2, %xmm5
	movsd	%xmm0, -320(%rbp)       ## 8-byte Spill
	movaps	%xmm4, %xmm0
	movsd	%xmm1, -328(%rbp)       ## 8-byte Spill
	movaps	%xmm5, %xmm1
	movss	%xmm3, -332(%rbp)       ## 4-byte Spill
	movq	%rax, -344(%rbp)        ## 8-byte Spill
	movss	%xmm2, -348(%rbp)       ## 4-byte Spill
	callq	*%rcx
	.loc	1 125 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:125:0
	movq	-344(%rbp), %rax        ## 8-byte Reload
	movq	(%rax), %rcx
	movl	-56(%rbp), %edi
	movss	-332(%rbp), %xmm0       ## 4-byte Reload
	callq	*%rcx
	.loc	1 128 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:128:0
	movq	-344(%rbp), %rax        ## 8-byte Reload
	movq	(%rax), %rcx
	movl	-52(%rbp), %edi
	movss	-76(%rbp), %xmm0
	movss	-348(%rbp), %xmm1       ## 4-byte Reload
	divss	%xmm1, %xmm0
	callq	*%rcx
	.loc	1 129 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:129:0
Ltmp38:
	cvtss2sd	-76(%rbp), %xmm0
	movsd	-328(%rbp), %xmm1       ## 8-byte Reload
	addsd	%xmm1, %xmm0
	movsd	-320(%rbp), %xmm2       ## 8-byte Reload
	ucomisd	%xmm0, %xmm2
	jbe	LBB1_16
## BB#15:                               ##   in Loop: Header=BB1_11 Depth=1
	movsd	LCPI1_0(%rip), %xmm0
	.loc	1 130 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:130:0
Ltmp39:
	cvtss2sd	-76(%rbp), %xmm1
	addsd	%xmm0, %xmm1
	cvtsd2ss	%xmm1, %xmm0
	movss	%xmm0, -76(%rbp)
	.loc	1 131 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:131:0
	jmp	LBB1_17
Ltmp40:
LBB1_16:                                ##   in Loop: Header=BB1_11 Depth=1
	movabsq	$2, %rax
	cvtsi2ssq	%rax, %xmm0
	.loc	1 133 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:133:0
Ltmp41:
	movss	%xmm0, -76(%rbp)
Ltmp42:
LBB1_17:                                ##   in Loop: Header=BB1_11 Depth=1
	movl	$0, %eax
	movl	$80, %edx
	movl	$3, %ecx
	movl	$5126, %esi             ## imm = 0x1406
	movabsq	$0, %rdi
	movq	___glewVertexAttribPointer@GOTPCREL(%rip), %r8
	movl	$34962, %r9d            ## imm = 0x8892
	movq	___glewBindBuffer@GOTPCREL(%rip), %r10
	movq	___glewEnableVertexAttribArray@GOTPCREL(%rip), %r11
	.loc	1 138 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:138:0
	movq	(%r11), %rbx
	movl	-36(%rbp), %r14d
	movq	%rdi, -360(%rbp)        ## 8-byte Spill
	movl	%r14d, %edi
	movl	%eax, -364(%rbp)        ## 4-byte Spill
	movl	%edx, -368(%rbp)        ## 4-byte Spill
	movl	%ecx, -372(%rbp)        ## 4-byte Spill
	movl	%esi, -376(%rbp)        ## 4-byte Spill
	movq	%r11, -384(%rbp)        ## 8-byte Spill
	movq	%r8, -392(%rbp)         ## 8-byte Spill
	movl	%r9d, -396(%rbp)        ## 4-byte Spill
	movq	%r10, -408(%rbp)        ## 8-byte Spill
	callq	*%rbx
	.loc	1 139 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:139:0
	movq	-408(%rbp), %r8         ## 8-byte Reload
	movq	(%r8), %r10
	movl	-68(%rbp), %esi
	movl	-396(%rbp), %edi        ## 4-byte Reload
	callq	*%r10
	.loc	1 140 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:140:0
	movq	-392(%rbp), %r8         ## 8-byte Reload
	movq	(%r8), %r10
	movl	-36(%rbp), %edi
	movl	-372(%rbp), %esi        ## 4-byte Reload
	movl	-376(%rbp), %edx        ## 4-byte Reload
	movl	-364(%rbp), %ecx        ## 4-byte Reload
	movl	-364(%rbp), %r8d        ## 4-byte Reload
	movq	-360(%rbp), %r9         ## 8-byte Reload
	callq	*%r10
	.loc	1 150 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:150:0
	movq	-384(%rbp), %r9         ## 8-byte Reload
	movq	(%r9), %r10
	movl	-40(%rbp), %edi
	callq	*%r10
	.loc	1 151 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:151:0
	movq	-408(%rbp), %r9         ## 8-byte Reload
	movq	(%r9), %r10
	movl	-72(%rbp), %esi
	movl	-396(%rbp), %edi        ## 4-byte Reload
	callq	*%r10
	.loc	1 152 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:152:0
	movq	-392(%rbp), %r9         ## 8-byte Reload
	movq	(%r9), %r10
	movl	-40(%rbp), %edi
	movl	-372(%rbp), %esi        ## 4-byte Reload
	movl	-376(%rbp), %edx        ## 4-byte Reload
	movl	-364(%rbp), %ecx        ## 4-byte Reload
	movl	-364(%rbp), %r8d        ## 4-byte Reload
	movq	-360(%rbp), %r9         ## 8-byte Reload
	callq	*%r10
	.loc	1 162 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:162:0
	movl	-364(%rbp), %edi        ## 4-byte Reload
	movl	-364(%rbp), %esi        ## 4-byte Reload
	movl	-368(%rbp), %edx        ## 4-byte Reload
	callq	_glDrawArrays
	movq	___glewDisableVertexAttribArray@GOTPCREL(%rip), %r9
	.loc	1 164 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:164:0
	movq	(%r9), %r9
	movl	-36(%rbp), %edi
	callq	*%r9
	.loc	1 167 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:167:0
	movq	_window(%rip), %rdi
	callq	_glfwSwapBuffers
	.loc	1 168 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:168:0
	callq	_glfwPollEvents
Ltmp43:
## BB#18:                               ##   in Loop: Header=BB1_11 Depth=1
	movl	$256, %esi              ## imm = 0x100
	.loc	1 171 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:171:0
	movq	_window(%rip), %rdi
	callq	_glfwGetKey
	movb	$0, %cl
	cmpl	$1, %eax
	movb	%cl, -409(%rbp)         ## 1-byte Spill
	je	LBB1_20
## BB#19:                               ##   in Loop: Header=BB1_11 Depth=1
	.loc	1 172 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:172:0
	movq	_window(%rip), %rdi
	callq	_glfwWindowShouldClose
	cmpl	$0, %eax
	sete	%cl
	movb	%cl, -409(%rbp)         ## 1-byte Spill
LBB1_20:                                ##   in Loop: Header=BB1_11 Depth=1
	movb	-409(%rbp), %al         ## 1-byte Reload
	testb	$1, %al
	jne	LBB1_11
## BB#21:
	movq	___glewDeleteProgram@GOTPCREL(%rip), %rax
	movl	$1, %edi
	leaq	-68(%rbp), %rsi
	movq	___glewDeleteBuffers@GOTPCREL(%rip), %rcx
	.loc	1 176 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:176:0
	movq	%rax, -424(%rbp)        ## 8-byte Spill
	callq	*(%rcx)
	.loc	1 177 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:177:0
	movq	-424(%rbp), %rax        ## 8-byte Reload
	movq	(%rax), %rcx
	movl	-32(%rbp), %edi
	callq	*%rcx
	.loc	1 180 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:180:0
	callq	_glfwTerminate
	.loc	1 182 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:182:0
	movl	$0, -28(%rbp)
LBB1_22:
	.loc	1 183 0                 ## /Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp:183:0
	movl	-28(%rbp), %eax
	addq	$408, %rsp              ## imm = 0x198
	popq	%rbx
	popq	%r14
	popq	%r15
	popq	%rbp
Ltmp44:
	retq
Ltmp45:
Lfunc_end1:
	.cfi_endproc

	.globl	_window                 ## @window
.zerofill __DATA,__common,_window,8,3
	.globl	_width                  ## @width
.zerofill __DATA,__common,_width,4,2
	.globl	_height                 ## @height
.zerofill __DATA,__common,_height,4,2
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Width: %d, Height: %d\n"

L_.str1:                                ## @.str1
	.asciz	"Failed to initialize GLFW\n"

L_.str2:                                ## @.str2
	.asciz	"Program 2A - fun with points"

L_.str3:                                ## @.str3
	.asciz	"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n"

L_.str4:                                ## @.str4
	.asciz	"Failed to initialize GLEW\n"

L_.str5:                                ## @.str5
	.asciz	"SimpleVertexShader.vertexshader"

L_.str6:                                ## @.str6
	.asciz	"SimpleFragmentShader.fragmentshader"

L_.str7:                                ## @.str7
	.asciz	"vertexPosition_modelspace"

L_.str8:                                ## @.str8
	.asciz	"vertexColor"

L_.str9:                                ## @.str9
	.asciz	"uWinScale"

L_.str10:                               ## @.str10
	.asciz	"uWinCenter"

L_.str11:                               ## @.str11
	.asciz	"uTime"

L_.str12:                               ## @.str12
	.asciz	"uTargetDist"

.zerofill __DATA,__bss,__ZZ4mainE19g_point_buffer_data,320,4 ## @_ZZ4mainE19g_point_buffer_data
	.section	__TEXT,__const
	.align	4                       ## @_ZZ4mainE19g_color_buffer_data
__ZZ4mainE19g_color_buffer_data:
	.long	1065353216              ## float 1.000000e+00
	.long	1065353216              ## float 1.000000e+00
	.long	1065353216              ## float 1.000000e+00
	.long	1065353216              ## float 1.000000e+00
	.long	1065353216              ## float 1.000000e+00
	.long	1065353216              ## float 1.000000e+00

	.section	__DATA,__bss
Ldebug_end0:
	.section	__DATA,__common
Ldebug_end1:
	.section	__TEXT,__const
Ldebug_end2:
	.section	__TEXT,__text,regular,pure_instructions
Ldebug_end3:
	.section	__DWARF,__debug_str,regular,debug
Linfo_string0:
	.asciz	"Apple LLVM version 6.0 (clang-600.0.56) (based on LLVM 3.5svn)"
Linfo_string1:
	.asciz	"/Users/elliotfiske/471/OpenGL-tutorial_v0014_21/lab4/prog2A.cpp"
Linfo_string2:
	.asciz	"/Users/elliotfiske/471/OpenGL-tutorial_v0014_21"
Linfo_string3:
	.asciz	"window"
Linfo_string4:
	.asciz	"GLFWwindow"
Linfo_string5:
	.asciz	"width"
Linfo_string6:
	.asciz	"int"
Linfo_string7:
	.asciz	"height"
Linfo_string8:
	.asciz	"main"
Linfo_string9:
	.asciz	"g_point_buffer_data"
Linfo_string10:
	.asciz	"float"
Linfo_string11:
	.asciz	"GLfloat"
Linfo_string12:
	.asciz	"g_color_buffer_data"
Linfo_string13:
	.asciz	"targetTime"
Linfo_string14:
	.asciz	"_Z14window_resizedP10GLFWwindowii"
Linfo_string15:
	.asciz	"window_resized"
Linfo_string16:
	.asciz	"glm"
Linfo_string17:
	.asciz	"width_"
Linfo_string18:
	.asciz	"height_"
Linfo_string19:
	.asciz	"programID"
Linfo_string20:
	.asciz	"unsigned int"
Linfo_string21:
	.asciz	"GLuint"
Linfo_string22:
	.asciz	"vertexPosition_modelspaceID"
Linfo_string23:
	.asciz	"vertexColorID"
Linfo_string24:
	.asciz	"winScaleID"
Linfo_string25:
	.asciz	"winCenterID"
Linfo_string26:
	.asciz	"timeID"
Linfo_string27:
	.asciz	"targetDistID"
Linfo_string28:
	.asciz	"vertexbuffer"
Linfo_string29:
	.asciz	"colorbuffer"
Linfo_string30:
	.asciz	"l_time"
Linfo_string31:
	.asciz	"i"
Linfo_string32:
	.asciz	"newPointCoord"
	.section	__DWARF,__debug_info,regular,debug
L__DWARF__debug_info_begin0:
	.long	605                     ## Length of Unit
	.short	2                       ## DWARF version number
Lset0 = Lsection_abbrev-Lsection_abbrev ## Offset Into Abbrev. Section
	.long	Lset0
	.byte	8                       ## Address Size (in bytes)
	.byte	1                       ## Abbrev [1] 0xb:0x256 DW_TAG_compile_unit
Lset1 = Linfo_string0-Linfo_string      ## DW_AT_producer
	.long	Lset1
	.short	4                       ## DW_AT_language
Lset2 = Linfo_string1-Linfo_string      ## DW_AT_name
	.long	Lset2
	.long	0                       ## DW_AT_stmt_list
Lset3 = Linfo_string2-Linfo_string      ## DW_AT_comp_dir
	.long	Lset3
	.quad	0                       ## DW_AT_low_pc
	.byte	2                       ## Abbrev [2] 0x26:0x16 DW_TAG_variable
Lset4 = Linfo_string3-Linfo_string      ## DW_AT_name
	.long	Lset4
	.long	60                      ## DW_AT_type
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_decl_file
	.byte	11                      ## DW_AT_decl_line
	.byte	9                       ## DW_AT_location
	.byte	3
	.quad	_window
	.byte	3                       ## Abbrev [3] 0x3c:0x5 DW_TAG_pointer_type
	.long	65                      ## DW_AT_type
	.byte	4                       ## Abbrev [4] 0x41:0xc DW_TAG_typedef
	.long	77                      ## DW_AT_type
Lset5 = Linfo_string4-Linfo_string      ## DW_AT_name
	.long	Lset5
	.byte	2                       ## DW_AT_decl_file
	.short	574                     ## DW_AT_decl_line
	.byte	5                       ## Abbrev [5] 0x4d:0x6 DW_TAG_structure_type
Lset6 = Linfo_string4-Linfo_string      ## DW_AT_name
	.long	Lset6
	.byte	1                       ## DW_AT_declaration
	.byte	2                       ## Abbrev [2] 0x53:0x16 DW_TAG_variable
Lset7 = Linfo_string5-Linfo_string      ## DW_AT_name
	.long	Lset7
	.long	105                     ## DW_AT_type
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_decl_file
	.byte	19                      ## DW_AT_decl_line
	.byte	9                       ## DW_AT_location
	.byte	3
	.quad	_width
	.byte	6                       ## Abbrev [6] 0x69:0x7 DW_TAG_base_type
Lset8 = Linfo_string6-Linfo_string      ## DW_AT_name
	.long	Lset8
	.byte	5                       ## DW_AT_encoding
	.byte	4                       ## DW_AT_byte_size
	.byte	2                       ## Abbrev [2] 0x70:0x16 DW_TAG_variable
Lset9 = Linfo_string7-Linfo_string      ## DW_AT_name
	.long	Lset9
	.long	105                     ## DW_AT_type
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_decl_file
	.byte	19                      ## DW_AT_decl_line
	.byte	9                       ## DW_AT_location
	.byte	3
	.quad	_height
	.byte	7                       ## Abbrev [7] 0x86:0x128 DW_TAG_subprogram
Lset10 = Linfo_string8-Linfo_string     ## DW_AT_name
	.long	Lset10
	.byte	1                       ## DW_AT_decl_file
	.byte	29                      ## DW_AT_decl_line
	.long	105                     ## DW_AT_type
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_accessibility
                                        ## DW_ACCESS_public
	.quad	Lfunc_begin1            ## DW_AT_low_pc
	.quad	Lfunc_end1              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.byte	8                       ## Abbrev [8] 0xa5:0x15 DW_TAG_variable
Lset11 = Linfo_string9-Linfo_string     ## DW_AT_name
	.long	Lset11
	.long	430                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	80                      ## DW_AT_decl_line
	.byte	9                       ## DW_AT_location
	.byte	3
	.quad	__ZZ4mainE19g_point_buffer_data
	.byte	8                       ## Abbrev [8] 0xba:0x15 DW_TAG_variable
Lset12 = Linfo_string12-Linfo_string    ## DW_AT_name
	.long	Lset12
	.long	468                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	89                      ## DW_AT_decl_line
	.byte	9                       ## DW_AT_location
	.byte	3
	.quad	__ZZ4mainE19g_color_buffer_data
	.byte	9                       ## Abbrev [9] 0xcf:0xe DW_TAG_variable
Lset13 = Linfo_string19-Linfo_string    ## DW_AT_name
	.long	Lset13
	.byte	1                       ## DW_AT_decl_file
	.byte	70                      ## DW_AT_decl_line
	.long	589                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	96
	.byte	9                       ## Abbrev [9] 0xdd:0xe DW_TAG_variable
Lset14 = Linfo_string22-Linfo_string    ## DW_AT_name
	.long	Lset14
	.byte	1                       ## DW_AT_decl_file
	.byte	73                      ## DW_AT_decl_line
	.long	589                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	92
	.byte	9                       ## Abbrev [9] 0xeb:0xe DW_TAG_variable
Lset15 = Linfo_string23-Linfo_string    ## DW_AT_name
	.long	Lset15
	.byte	1                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.long	589                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	88
	.byte	9                       ## Abbrev [9] 0xf9:0xe DW_TAG_variable
Lset16 = Linfo_string24-Linfo_string    ## DW_AT_name
	.long	Lset16
	.byte	1                       ## DW_AT_decl_file
	.byte	75                      ## DW_AT_decl_line
	.long	589                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	84
	.byte	9                       ## Abbrev [9] 0x107:0xe DW_TAG_variable
Lset17 = Linfo_string25-Linfo_string    ## DW_AT_name
	.long	Lset17
	.byte	1                       ## DW_AT_decl_file
	.byte	76                      ## DW_AT_decl_line
	.long	589                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	80
	.byte	9                       ## Abbrev [9] 0x115:0xe DW_TAG_variable
Lset18 = Linfo_string26-Linfo_string    ## DW_AT_name
	.long	Lset18
	.byte	1                       ## DW_AT_decl_file
	.byte	77                      ## DW_AT_decl_line
	.long	589                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	76
	.byte	9                       ## Abbrev [9] 0x123:0xe DW_TAG_variable
Lset19 = Linfo_string27-Linfo_string    ## DW_AT_name
	.long	Lset19
	.byte	1                       ## DW_AT_decl_file
	.byte	78                      ## DW_AT_decl_line
	.long	589                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	72
	.byte	9                       ## Abbrev [9] 0x131:0xf DW_TAG_variable
Lset20 = Linfo_string28-Linfo_string    ## DW_AT_name
	.long	Lset20
	.byte	1                       ## DW_AT_decl_file
	.byte	94                      ## DW_AT_decl_line
	.long	589                     ## DW_AT_type
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\274\177"
	.byte	9                       ## Abbrev [9] 0x140:0xf DW_TAG_variable
Lset21 = Linfo_string29-Linfo_string    ## DW_AT_name
	.long	Lset21
	.byte	1                       ## DW_AT_decl_file
	.byte	99                      ## DW_AT_decl_line
	.long	589                     ## DW_AT_type
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\270\177"
	.byte	9                       ## Abbrev [9] 0x14f:0xf DW_TAG_variable
Lset22 = Linfo_string30-Linfo_string    ## DW_AT_name
	.long	Lset22
	.byte	1                       ## DW_AT_decl_file
	.byte	105                     ## DW_AT_decl_line
	.long	454                     ## DW_AT_type
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\264\177"
	.byte	9                       ## Abbrev [9] 0x15e:0xf DW_TAG_variable
Lset23 = Linfo_string13-Linfo_string    ## DW_AT_name
	.long	Lset23
	.byte	1                       ## DW_AT_decl_file
	.byte	107                     ## DW_AT_decl_line
	.long	496                     ## DW_AT_type
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\260\177"
	.byte	10                      ## Abbrev [10] 0x16d:0x40 DW_TAG_lexical_block
	.quad	Ltmp25                  ## DW_AT_low_pc
	.quad	Ltmp28                  ## DW_AT_high_pc
	.byte	9                       ## Abbrev [9] 0x17e:0xe DW_TAG_variable
Lset24 = Linfo_string31-Linfo_string    ## DW_AT_name
	.long	Lset24
	.byte	1                       ## DW_AT_decl_file
	.byte	82                      ## DW_AT_decl_line
	.long	105                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	68
	.byte	10                      ## Abbrev [10] 0x18c:0x20 DW_TAG_lexical_block
	.quad	Ltmp26                  ## DW_AT_low_pc
	.quad	Ltmp27                  ## DW_AT_high_pc
	.byte	9                       ## Abbrev [9] 0x19d:0xe DW_TAG_variable
Lset25 = Linfo_string32-Linfo_string    ## DW_AT_name
	.long	Lset25
	.byte	1                       ## DW_AT_decl_file
	.byte	83                      ## DW_AT_decl_line
	.long	454                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	64
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	11                      ## Abbrev [11] 0x1ae:0xc DW_TAG_array_type
	.long	442                     ## DW_AT_type
	.byte	12                      ## Abbrev [12] 0x1b3:0x6 DW_TAG_subrange_type
	.long	461                     ## DW_AT_type
	.byte	79                      ## DW_AT_upper_bound
	.byte	0                       ## End Of Children Mark
	.byte	4                       ## Abbrev [4] 0x1ba:0xc DW_TAG_typedef
	.long	454                     ## DW_AT_type
Lset26 = Linfo_string11-Linfo_string    ## DW_AT_name
	.long	Lset26
	.byte	3                       ## DW_AT_decl_file
	.short	273                     ## DW_AT_decl_line
	.byte	6                       ## Abbrev [6] 0x1c6:0x7 DW_TAG_base_type
Lset27 = Linfo_string10-Linfo_string    ## DW_AT_name
	.long	Lset27
	.byte	4                       ## DW_AT_encoding
	.byte	4                       ## DW_AT_byte_size
	.byte	13                      ## Abbrev [13] 0x1cd:0x7 DW_TAG_base_type
Lset28 = Linfo_string6-Linfo_string     ## DW_AT_name
	.long	Lset28
	.byte	4                       ## DW_AT_byte_size
	.byte	5                       ## DW_AT_encoding
	.byte	11                      ## Abbrev [11] 0x1d4:0xc DW_TAG_array_type
	.long	480                     ## DW_AT_type
	.byte	12                      ## Abbrev [12] 0x1d9:0x6 DW_TAG_subrange_type
	.long	461                     ## DW_AT_type
	.byte	5                       ## DW_AT_upper_bound
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0x1e0:0x5 DW_TAG_const_type
	.long	442                     ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0x1e5:0xb DW_TAG_variable
Lset29 = Linfo_string13-Linfo_string    ## DW_AT_name
	.long	Lset29
	.long	496                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	107                     ## DW_AT_decl_line
	.byte	14                      ## Abbrev [14] 0x1f0:0x5 DW_TAG_const_type
	.long	454                     ## DW_AT_type
	.byte	16                      ## Abbrev [16] 0x1f5:0x4a DW_TAG_subprogram
Lset30 = Linfo_string14-Linfo_string    ## DW_AT_MIPS_linkage_name
	.long	Lset30
Lset31 = Linfo_string15-Linfo_string    ## DW_AT_name
	.long	Lset31
	.byte	1                       ## DW_AT_decl_file
	.byte	22                      ## DW_AT_decl_line
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_accessibility
                                        ## DW_ACCESS_public
	.quad	Lfunc_begin0            ## DW_AT_low_pc
	.quad	Lfunc_end0              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.byte	17                      ## Abbrev [17] 0x214:0xe DW_TAG_formal_parameter
Lset32 = Linfo_string3-Linfo_string     ## DW_AT_name
	.long	Lset32
	.byte	1                       ## DW_AT_decl_file
	.byte	22                      ## DW_AT_decl_line
	.long	60                      ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	120
	.byte	17                      ## Abbrev [17] 0x222:0xe DW_TAG_formal_parameter
Lset33 = Linfo_string17-Linfo_string    ## DW_AT_name
	.long	Lset33
	.byte	1                       ## DW_AT_decl_file
	.byte	22                      ## DW_AT_decl_line
	.long	105                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	116
	.byte	17                      ## Abbrev [17] 0x230:0xe DW_TAG_formal_parameter
Lset34 = Linfo_string18-Linfo_string    ## DW_AT_name
	.long	Lset34
	.byte	1                       ## DW_AT_decl_file
	.byte	22                      ## DW_AT_decl_line
	.long	105                     ## DW_AT_type
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	112
	.byte	0                       ## End Of Children Mark
	.byte	18                      ## Abbrev [18] 0x23f:0x7 DW_TAG_namespace
Lset35 = Linfo_string16-Linfo_string    ## DW_AT_name
	.long	Lset35
	.byte	4                       ## DW_AT_decl_file
	.byte	38                      ## DW_AT_decl_line
	.byte	19                      ## Abbrev [19] 0x246:0x7 DW_TAG_imported_module
	.byte	1                       ## DW_AT_decl_file
	.byte	15                      ## DW_AT_decl_line
	.long	575                     ## DW_AT_import
	.byte	4                       ## Abbrev [4] 0x24d:0xc DW_TAG_typedef
	.long	601                     ## DW_AT_type
Lset36 = Linfo_string21-Linfo_string    ## DW_AT_name
	.long	Lset36
	.byte	3                       ## DW_AT_decl_file
	.short	264                     ## DW_AT_decl_line
	.byte	6                       ## Abbrev [6] 0x259:0x7 DW_TAG_base_type
Lset37 = Linfo_string20-Linfo_string    ## DW_AT_name
	.long	Lset37
	.byte	7                       ## DW_AT_encoding
	.byte	4                       ## DW_AT_byte_size
	.byte	0                       ## End Of Children Mark
L__DWARF__debug_info_end0:
	.section	__DWARF,__debug_abbrev,regular,debug
	.byte	1                       ## Abbreviation Code
	.byte	17                      ## DW_TAG_compile_unit
	.byte	1                       ## DW_CHILDREN_yes
	.byte	37                      ## DW_AT_producer
	.byte	14                      ## DW_FORM_strp
	.byte	19                      ## DW_AT_language
	.byte	5                       ## DW_FORM_data2
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	16                      ## DW_AT_stmt_list
	.byte	6                       ## DW_FORM_data4
	.byte	27                      ## DW_AT_comp_dir
	.byte	14                      ## DW_FORM_strp
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	2                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	63                      ## DW_AT_external
	.byte	12                      ## DW_FORM_flag
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	3                       ## Abbreviation Code
	.byte	15                      ## DW_TAG_pointer_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	4                       ## Abbreviation Code
	.byte	22                      ## DW_TAG_typedef
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	5                       ## Abbreviation Code
	.byte	19                      ## DW_TAG_structure_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	60                      ## DW_AT_declaration
	.byte	12                      ## DW_FORM_flag
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	6                       ## Abbreviation Code
	.byte	36                      ## DW_TAG_base_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	62                      ## DW_AT_encoding
	.byte	11                      ## DW_FORM_data1
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	7                       ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	63                      ## DW_AT_external
	.byte	12                      ## DW_FORM_flag
	.byte	50                      ## DW_AT_accessibility
	.byte	11                      ## DW_FORM_data1
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	64                      ## DW_AT_frame_base
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	8                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	9                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	10                      ## Abbreviation Code
	.byte	11                      ## DW_TAG_lexical_block
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	11                      ## Abbreviation Code
	.byte	1                       ## DW_TAG_array_type
	.byte	1                       ## DW_CHILDREN_yes
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	12                      ## Abbreviation Code
	.byte	33                      ## DW_TAG_subrange_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	47                      ## DW_AT_upper_bound
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	13                      ## Abbreviation Code
	.byte	36                      ## DW_TAG_base_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	62                      ## DW_AT_encoding
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	14                      ## Abbreviation Code
	.byte	38                      ## DW_TAG_const_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	15                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	16                      ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.ascii	"\207@"                 ## DW_AT_MIPS_linkage_name
	.byte	14                      ## DW_FORM_strp
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	63                      ## DW_AT_external
	.byte	12                      ## DW_FORM_flag
	.byte	50                      ## DW_AT_accessibility
	.byte	11                      ## DW_FORM_data1
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	64                      ## DW_AT_frame_base
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	17                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	18                      ## Abbreviation Code
	.byte	57                      ## DW_TAG_namespace
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	19                      ## Abbreviation Code
	.byte	58                      ## DW_TAG_imported_module
	.byte	0                       ## DW_CHILDREN_no
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	24                      ## DW_AT_import
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	0                       ## EOM(3)
	.section	__DWARF,__debug_aranges,regular,debug
	.long	92                      ## Length of ARange Set
	.short	2                       ## DWARF Arange version number
Lset38 = L__DWARF__debug_info_begin0-Lsection_info ## Offset Into Debug Info Section
	.long	Lset38
	.byte	8                       ## Address Size (in bytes)
	.byte	0                       ## Segment Size (in bytes)
	.space	4,255
	.quad	__ZZ4mainE19g_point_buffer_data
Lset39 = Ldebug_end0-__ZZ4mainE19g_point_buffer_data
	.quad	Lset39
	.quad	_window
Lset40 = Ldebug_end1-_window
	.quad	Lset40
	.quad	__ZZ4mainE19g_color_buffer_data
Lset41 = Ldebug_end2-__ZZ4mainE19g_color_buffer_data
	.quad	Lset41
	.quad	Lfunc_begin0
Lset42 = Ldebug_end3-Lfunc_begin0
	.quad	Lset42
	.quad	0                       ## ARange terminator
	.quad	0
	.section	__DWARF,__debug_ranges,regular,debug
Lgnu_ranges0:
	.section	__DWARF,__apple_names,regular,debug
Lnames_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	8                       ## Header Bucket Count
	.long	8                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.long	-1                      ## Bucket 1
	.long	0                       ## Bucket 2
	.long	2                       ## Bucket 3
	.long	3                       ## Bucket 4
	.long	4                       ## Bucket 5
	.long	6                       ## Bucket 6
	.long	7                       ## Bucket 7
	.long	2090499946              ## Hash in Bucket 2
	.long	340052594               ## Hash in Bucket 2
	.long	1911851579              ## Hash in Bucket 3
	.long	-1035345028             ## Hash in Bucket 4
	.long	279163045               ## Hash in Bucket 5
	.long	622788189               ## Hash in Bucket 5
	.long	30836958                ## Hash in Bucket 6
	.long	-1325273689             ## Hash in Bucket 7
	.long	LNames2-Lnames_begin    ## Offset in Bucket 2
	.long	LNames7-Lnames_begin    ## Offset in Bucket 2
	.long	LNames3-Lnames_begin    ## Offset in Bucket 3
	.long	LNames4-Lnames_begin    ## Offset in Bucket 4
	.long	LNames0-Lnames_begin    ## Offset in Bucket 5
	.long	LNames5-Lnames_begin    ## Offset in Bucket 5
	.long	LNames6-Lnames_begin    ## Offset in Bucket 6
	.long	LNames1-Lnames_begin    ## Offset in Bucket 7
LNames2:
Lset43 = Linfo_string8-Linfo_string     ## main
	.long	Lset43
	.long	1                       ## Num DIEs
	.long	134
	.long	0
LNames7:
Lset44 = Linfo_string15-Linfo_string    ## window_resized
	.long	Lset44
	.long	1                       ## Num DIEs
	.long	501
	.long	0
LNames3:
Lset45 = Linfo_string14-Linfo_string    ## _Z14window_resizedP10GLFWwindowii
	.long	Lset45
	.long	1                       ## Num DIEs
	.long	501
	.long	0
LNames4:
Lset46 = Linfo_string12-Linfo_string    ## g_color_buffer_data
	.long	Lset46
	.long	1                       ## Num DIEs
	.long	186
	.long	0
LNames0:
Lset47 = Linfo_string5-Linfo_string     ## width
	.long	Lset47
	.long	1                       ## Num DIEs
	.long	83
	.long	0
LNames5:
Lset48 = Linfo_string3-Linfo_string     ## window
	.long	Lset48
	.long	1                       ## Num DIEs
	.long	38
	.long	0
LNames6:
Lset49 = Linfo_string7-Linfo_string     ## height
	.long	Lset49
	.long	1                       ## Num DIEs
	.long	112
	.long	0
LNames1:
Lset50 = Linfo_string9-Linfo_string     ## g_point_buffer_data
	.long	Lset50
	.long	1                       ## Num DIEs
	.long	165
	.long	0
	.section	__DWARF,__apple_objc,regular,debug
Lobjc_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.section	__DWARF,__apple_namespac,regular,debug
Lnamespac_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	1                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	0                       ## Bucket 0
	.long	193492837               ## Hash in Bucket 0
	.long	Lnamespac0-Lnamespac_begin ## Offset in Bucket 0
Lnamespac0:
Lset51 = Linfo_string16-Linfo_string    ## glm
	.long	Lset51
	.long	1                       ## Num DIEs
	.long	575
	.long	0
	.section	__DWARF,__apple_types,regular,debug
Ltypes_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	6                       ## Header Bucket Count
	.long	6                       ## Header Hash Count
	.long	20                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	3                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.short	3                       ## DW_ATOM_die_tag
	.short	5                       ## DW_FORM_data2
	.short	4                       ## DW_ATOM_type_flags
	.short	11                      ## DW_FORM_data1
	.long	0                       ## Bucket 0
	.long	1                       ## Bucket 1
	.long	2                       ## Bucket 2
	.long	3                       ## Bucket 3
	.long	4                       ## Bucket 4
	.long	5                       ## Bucket 5
	.long	367093806               ## Hash in Bucket 0
	.long	259121563               ## Hash in Bucket 1
	.long	193495088               ## Hash in Bucket 2
	.long	-908558227              ## Hash in Bucket 3
	.long	-1289845416             ## Hash in Bucket 4
	.long	-1304652851             ## Hash in Bucket 5
	.long	Ltypes3-Ltypes_begin    ## Offset in Bucket 0
	.long	Ltypes1-Ltypes_begin    ## Offset in Bucket 1
	.long	Ltypes4-Ltypes_begin    ## Offset in Bucket 2
	.long	Ltypes2-Ltypes_begin    ## Offset in Bucket 3
	.long	Ltypes0-Ltypes_begin    ## Offset in Bucket 4
	.long	Ltypes5-Ltypes_begin    ## Offset in Bucket 5
Ltypes3:
Lset52 = Linfo_string11-Linfo_string    ## GLfloat
	.long	Lset52
	.long	1                       ## Num DIEs
	.long	442
	.short	22
	.byte	0
	.long	0
Ltypes1:
Lset53 = Linfo_string10-Linfo_string    ## float
	.long	Lset53
	.long	1                       ## Num DIEs
	.long	454
	.short	36
	.byte	0
	.long	0
Ltypes4:
Lset54 = Linfo_string6-Linfo_string     ## int
	.long	Lset54
	.long	1                       ## Num DIEs
	.long	105
	.short	36
	.byte	0
	.long	0
Ltypes2:
Lset55 = Linfo_string4-Linfo_string     ## GLFWwindow
	.long	Lset55
	.long	1                       ## Num DIEs
	.long	65
	.short	22
	.byte	0
	.long	0
Ltypes0:
Lset56 = Linfo_string21-Linfo_string    ## GLuint
	.long	Lset56
	.long	1                       ## Num DIEs
	.long	589
	.short	22
	.byte	0
	.long	0
Ltypes5:
Lset57 = Linfo_string20-Linfo_string    ## unsigned int
	.long	Lset57
	.long	1                       ## Num DIEs
	.long	601
	.short	36
	.byte	0
	.long	0

.subsections_via_symbols
