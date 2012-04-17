	.file	"square.c"
	.text
.globl square
	.type	square, @function
square:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	imull	8(%ebp), %eax
	popl	%ebp
	ret
	.size	square, .-square
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-48)"
	.section	.note.GNU-stack,"",@progbits
