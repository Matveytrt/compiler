global print
default abs

section .text
print:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    
    mov r12, rax
    
    test r12, r12
    jns .positive
    
    mov rax, 1
    mov rdi, 1
    mov rsi, minus
    mov rdx, 1
    syscall
    neg r12
    
.positive:
    lea rsi, [rbp - 32]
    mov rbx, 10
    mov rcx, 0
    
.convert:
    mov rdx, 0
    mov rax, r12
    div rbx
    add dl, '0'
    dec rsi
    mov [rsi], dl
    inc rcx
    mov r12, rax
    test r12, r12
    jnz .convert
    
    mov rax, 1
    mov rdi, 1
    mov rdx, rcx
    syscall
    
    mov rsp, rbp
    pop rbp
    ret

section .data
    minus db '-'