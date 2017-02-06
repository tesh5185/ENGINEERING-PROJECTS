	.file	"data.c"
	.section	.rodata
.LC0:
	.string	"\n%c"
.LC1:
	.string	"\ndecimal value%x"
	.text
	.globl	my_itoa
	.type	my_itoa, @function
my_itoa:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	%edx, -48(%rbp)
	movq	$0, -8(%rbp)
	movq	$1, -16(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movl	%eax, -20(%rbp)
	movq	$0, -16(%rbp)
	jmp	.L2
.L3:
	movq	-16(%rbp), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -21(%rbp)
	movsbl	-21(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addq	$1, -16(%rbp)
.L2:
	movl	-20(%rbp), %eax
	cltq
	cmpq	-16(%rbp), %rax
	jg	.L3
	movl	-44(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	my_itoa, .-my_itoa
	.section	.rodata
.LC2:
	.string	"%d"
	.text
	.globl	my_atoi
	.type	my_atoi, @function
my_atoi:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$448, %rsp
	movq	%rdi, -440(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-416(%rbp), %rax
	movq	%rax, -424(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movl	%eax, -428(%rbp)
	movl	$0, -432(%rbp)
	jmp	.L5
.L6:
	movl	-432(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-424(%rbp), %rax
	addq	%rax, %rdx
	movl	-432(%rbp), %eax
	movslq	%eax, %rcx
	movq	-440(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, (%rdx)
	movl	-432(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-424(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -432(%rbp)
.L5:
	movl	-432(%rbp), %eax
	cmpl	-428(%rbp), %eax
	jl	.L6
	nop
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L7
	call	__stack_chk_fail
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	my_atoi, .-my_atoi
	.section	.rodata
.LC3:
	.string	"The hex output is %x\n"
	.text
	.globl	dump_memory
	.type	dump_memory, @function
dump_memory:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L9
.L10:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -4(%rbp)
.L9:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jb	.L10
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	dump_memory, .-dump_memory
	.section	.rodata
.LC4:
	.string	"CONVERSION IS %x"
	.text
	.globl	big_to_little
	.type	big_to_little, @function
big_to_little:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$100, -20(%rbp)
	movq	$0, -16(%rbp)
	leaq	-20(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-36(%rbp), %eax
	sall	$24, %eax
	movl	%eax, %edx
	movl	-36(%rbp), %eax
	andl	$65280, %eax
	sall	$8, %eax
	orl	%eax, %edx
	movl	-36(%rbp), %eax
	andl	$16711680, %eax
	shrl	$8, %eax
	orl	%eax, %edx
	movl	-36(%rbp), %eax
	shrl	$24, %eax
	orl	%eax, %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	nop
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L12
	call	__stack_chk_fail
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	big_to_little, .-big_to_little
	.globl	little_to_big
	.type	little_to_big, @function
little_to_big:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$100, -20(%rbp)
	movq	$0, -16(%rbp)
	leaq	-20(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	-36(%rbp), %eax
	sall	$24, %eax
	movl	%eax, %edx
	movl	-36(%rbp), %eax
	andl	$65280, %eax
	sall	$8, %eax
	orl	%eax, %edx
	movl	-36(%rbp), %eax
	andl	$16711680, %eax
	shrl	$8, %eax
	orl	%eax, %edx
	movl	-36(%rbp), %eax
	shrl	$24, %eax
	orl	%eax, %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	nop
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L14
	call	__stack_chk_fail
.L14:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	little_to_big, .-little_to_big
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
