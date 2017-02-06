	.file	"project_1.c"
	.section	.rodata
.LC0:
	.string	"\n%d"
	.text
	.globl	project_1_report
	.type	project_1_report, @function
project_1_report:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-48(%rbp), %rax
	movq	%rax, -72(%rbp)
	leaq	-48(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -64(%rbp)
	leaq	-48(%rbp), %rax
	addq	$17, %rax
	movq	%rax, -56(%rbp)
	movl	$0, -80(%rbp)
	jmp	.L2
.L3:
	movl	-80(%rbp), %eax
	movslq	%eax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movl	-80(%rbp), %edx
	addl	$31, %edx
	movb	%dl, (%rax)
	addl	$1, -80(%rbp)
.L2:
	cmpl	$15, -80(%rbp)
	jle	.L3
	movq	-64(%rbp), %rax
	movl	$24, %esi
	movq	%rax, %rdi
	call	my_memzero
	movq	-56(%rbp), %rcx
	movq	-72(%rbp), %rax
	movl	$8, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	my_memmove
	movq	-72(%rbp), %rcx
	movq	-64(%rbp), %rax
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	my_memmove
	movq	-72(%rbp), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	my_reverse
	movl	$0, -76(%rbp)
	jmp	.L4
.L5:
	movl	-76(%rbp), %eax
	cltq
	movzbl	-48(%rbp,%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -76(%rbp)
.L4:
	cmpl	$31, -76(%rbp)
	jle	.L5
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L6
	call	__stack_chk_fail
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	project_1_report, .-project_1_report
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
