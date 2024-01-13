movl $5, -4(%rbp)
movl $7, -8(%rbp)
movl -4(%rbp), %edx
movl -8(%rbp), %eax
addl %edx, %eax
movl %eax, -12(%rbp)
nop
addq $48, %rsp
popq %rbp
ret