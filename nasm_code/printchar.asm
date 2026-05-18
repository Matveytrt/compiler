global printchar

section .text
printchar:
    push rbp
    mov rbp, rsp
    sub rsp, 8
    
    mov [rbp - 1], al
    
    mov rax, 1
    mov rdi, 1
    lea rsi, [rbp - 1]
    mov rdx, 1
    syscall
    
    mov rsp, rbp
    pop rbp
    ret