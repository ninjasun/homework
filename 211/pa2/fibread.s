	.file	"fib.c"
	.text
.globl fib
	.type	fib, @function
fib:
	pushl %ebp
	movl %esp, %ebp

	pushl %ebx
	pushl %ecx
	pushl %edx
	movl 8(%ebp), %ecx
	cmpl $1, %ecx
	jle identical
	movl $1, %eax
	movl $0, %ebx
	decl %ecx
	jmp repeat

identical:
	movl %ecx, %eax
	jmp done

over:
	movl $-1, %eax
	jmp done

repeat:
	movl %eax, %edx
	addl %ebx, %eax
	jo over
	movl %edx, %ebx
	loop repeat

done:
	popl %ebx
	popl %ecx
	popl %edx
	movl %ebp, %esp
	popl %ebp
	ret
