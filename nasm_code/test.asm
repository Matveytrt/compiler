default rel
extern printf
extern my_scanf
global main

section .text
main:
call Main
mov rax, 60
xor rdi, rdi
syscall

;OP - _END_STATEMENT_
;OP - _FUNC_DECLARE_

;==========================================================================
jmp end_func_Main
; / FUNC Main /
;==========================================================================
Main:
push rbp
mov rbp, rsp
sub rsp, 16
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 100
mov rax, 100
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
;OP - _END_STATEMENT_
;OP - MEMSET
;OP - _COMMA_
;NUM = 2
mov rax, 2
push rax
;NUM = 100
mov rax, 100
push rax
pop rax
pop rbx
lea r8, [vmem_buf]
mov [r8 + rbx], rax
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - MEMGET
;NUM = 1
mov rax, 1
push rax
pop rbx
lea r8, [vmem_buf]
mov rax, [r8 + rbx]
push rax
pop rax
mov rcx, -16
mov [rbp + rcx], rax
;OP - _END_STATEMENT_
;OP - _PRINT_
;VAR - x table_idx [1]
mov rcx, -16
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
exit_Main:
pop rax
add rsp, 16
pop rbp
ret
;==========================================================================
end_func_Main:
;==========================================================================

;OP - _END_STATEMENT_
;OP - _FUNC_DECLARE_

;==========================================================================
jmp end_func_Myaufunc
; / FUNC Myaufunc /
;==========================================================================
Myaufunc:
push rbp
mov rbp, rsp
sub rsp, 8
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_SUB_
;OP - _MATH_ADD_
;VAR - a table_idx [2]
mov rcx, 16
mov rax, [rbp + rcx]
push rax
;VAR - b table_idx [3]
mov rcx, 24
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
add rax, rcx
push rax
;OP - _MATH_MUL_
;VAR - c table_idx [4]
mov rcx, 32
mov rax, [rbp + rcx]
push rax
;VAR - d table_idx [5]
mov rcx, 40
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
pop rcx
pop rax
sub rax, rcx
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
;OP - _END_STATEMENT_
;OP - _RETURN_
;VAR - f table_idx [6]
mov rcx, -8
mov rax, [rbp + rcx]
push rax
jmp exit_Myaufunc
exit_Myaufunc:
pop rax
add rsp, 8
pop rbp
ret
;==========================================================================
end_func_Myaufunc:
;==========================================================================

section .data
vmem_buf db 900 dup(0)
fmt_int db "%d", 10, 0
fmt_char db "%c", 10, 0
