extern read
global my_scanf

section .text
my_scanf:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    mov qword [rbp - 8], 0
    mov qword [rbp - 16], 1
    mov qword [rbp - 24], 0
.read_loop:
    mov rax, 0
    mov rdi, 0
    lea rsi, [rbp - 25]
    mov rdx, 1
    call read WRT ..plt
    cmp rax, 0
    je .done_func
    mov cl, [rbp - 25]
    cmp cl, 10
    je .done_func
    cmp cl, 0
    je .done_func
    cmp cl, '-'
    jne .check_digit
    cmp qword [rbp - 24], 0
    jne .done_func
    mov qword [rbp - 16], -1
    jmp .read_loop
.check_digit:
    sub cl, 48
    cmp cl, 9
    ja .done_func
    mov qword [rbp - 24], 1
    movzx rcx, cl
    mov rax, qword [rbp - 8]
    imul rax, 10
    add rax, rcx
    mov qword [rbp - 8], rax
    jmp .read_loop
.done_func:
    mov rax, qword [rbp - 8]
    imul rax, qword [rbp - 16]
    mov rsp, rbp
    pop rbp
    ret