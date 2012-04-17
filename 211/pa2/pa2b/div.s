	.file	"div.c"
	.text
.globl div
	.type	div, @function
div:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	imull	$1431655766, %eax, %eax
	movl	$32, %ecx
	sarl	%cl, %eax
	popl	%ebp
	ret
	.size	div, .-div
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-51)"
	.section	.note.GNU-stack,"",@progbits
