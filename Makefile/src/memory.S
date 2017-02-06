	.file	"memory.c"
	.section	.rodata
.LC0:
	.string	"ERROR:OVERLAPPED MEMORY"
	.text
	.globl	my_memmove
	.type	my_memmove, @function
my_memmove:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movb	$-1, -13(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L2
.L9:
	movl	$0, -8(%rbp)
	jmp	.L3
.L8:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	cmpq	%rax, %rcx
	jne	.L4
	movl	$.LC0, %edi
	call	puts
	movb	$-1, -13(%rbp)
	jmp	.L5
.L4:
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	movb	$0, -13(%rbp)
	addl	$1, -4(%rbp)
.L6:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jb	.L7
.L5:
	addl	$1, -8(%rbp)
.L3:
	movl	-8(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jb	.L8
	addl	$1, -12(%rbp)
.L2:
	movl	-12(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jb	.L9
	movzbl	-13(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	my_memmove, .-my_memmove
	.globl	my_memzero
	.type	my_memzero, @function
my_memzero:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movb	$-1, -9(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L12
.L13:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	addl	$1, -8(%rbp)
.L12:
	movl	-8(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jb	.L13
	movl	$0, -4(%rbp)
	jmp	.L14
.L17:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L15
	movb	$-1, -9(%rbp)
	jmp	.L16
.L15:
	movb	$0, -9(%rbp)
	addl	$1, -4(%rbp)
.L14:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jb	.L17
.L16:
	movzbl	-9(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	my_memzero, .-my_memzero
	.globl	my_reverse
	.type	my_reverse, @function
my_reverse:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$160, %rsp
	movq	%rdi, -152(%rbp)
	movl	%esi, -156(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movb	$-1, -129(%rbp)
	movq	$0, -120(%rbp)
	leaq	-112(%rbp), %rax
	movq	%rax, -120(%rbp)
	movl	$0, -124(%rbp)
	movl	-156(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -128(%rbp)
	jmp	.L20
.L21:
	movl	-124(%rbp), %eax
	movslq	%eax, %rdx
	movq	-120(%rbp), %rax
	addq	%rax, %rdx
	movl	-128(%rbp), %eax
	movslq	%eax, %rcx
	movq	-152(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -124(%rbp)
	subl	$1, -128(%rbp)
.L20:
	cmpl	$0, -128(%rbp)
	jns	.L21
	movl	$0, -128(%rbp)
	jmp	.L22
.L23:
	movl	-128(%rbp), %eax
	movslq	%eax, %rdx
	movq	-152(%rbp), %rax
	addq	%rax, %rdx
	movl	-128(%rbp), %eax
	movslq	%eax, %rcx
	movq	-120(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, -128(%rbp)
.L22:
	movl	-128(%rbp), %eax
	cmpl	-156(%rbp), %eax
	jb	.L23
	movl	$1, -128(%rbp)
	jmp	.L24
.L27:
	movl	-128(%rbp), %eax
	movslq	%eax, %rdx
	movq	-152(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movl	-156(%rbp), %ecx
	movl	-128(%rbp), %eax
	cltq
	subq	%rax, %rcx
	movq	-152(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	je	.L25
	movb	$-1, -129(%rbp)
	jmp	.L26
.L25:
	movb	$0, -129(%rbp)
.L26:
	addl	$1, -128(%rbp)
.L24:
	movl	-128(%rbp), %eax
	cmpl	-156(%rbp), %eax
	jbe	.L27
	movzbl	-129(%rbp), %eax
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L29
	call	__stack_chk_fail
.L29:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	my_reverse, .-my_reverse
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
