default rel
global Main
section .text
mov rax, End_Prog
push rax
;OP - _END_STATEMENT_

;OP - _FUNC_DECLARE_

:Main
push rbp
mov rbp, rsp

sub rsp, 8
;OP - _END_STATEMENT_

;OP - _ASSIGNMENT_

;OP - _MATH_SUB_

;NUM = 2

mov rax, 2
push rax
;NUM = 3

mov rax, 3
push rax

pop rcx
pop rax

sub rax, rcx
push rax

pop rax
mov [rbp + -8], rax
;OP - _END_STATEMENT_

;OP - _RETURN_

;VAR - res table_idx [0]

mov rax, [rbp + -8]
push rax
pop rax

add rsp, 8

pop rbp
ret

:End_Prog
mov rax, 60
xor rdi, rdi
syscall
section .data
