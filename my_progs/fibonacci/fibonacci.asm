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
;NUM = 0
mov rax, 0
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
;OP - _END_STATEMENT_
;OP - _SCAN_
call my_scanf WRT ..plt
mov rcx, -8
mov [rbp + rcx], rax
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;FUNC - Fibonacci st_idx = 2, end_idx = 3

;VAR - n table_idx [0]
mov rcx, -8
mov rax, [rbp + rcx]
push rax
call Fibonacci
add rsp, 8
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
imul rax, 100
call printf WRT ..plt
;OP - _END_STATEMENT_
;OP - _RETURN_
;VAR - x table_idx [1]
mov rcx, -16
mov rax, [rbp + rcx]
push rax
jmp exit_Main
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
jmp end_func_Fibonacci
; / FUNC Fibonacci /
;==========================================================================
Fibonacci:
push rbp
mov rbp, rsp
sub rsp, 8
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_EQ_
;VAR - n table_idx [2]
mov rcx, 16
mov rax, [rbp + rcx]
push rax
;NUM = 0
mov rax, 0
push rax
pop rcx
pop rax
cmp rax, rcx
sete al
and rax, 1
push rax
pop rax
test al, al
jz end_IF_0x7c0602be0710
;OP - _END_STATEMENT_
;OP - _RETURN_
;VAR - n table_idx [2]
mov rcx, 16
mov rax, [rbp + rcx]
push rax
jmp exit_Fibonacci
end_IF_0x7c0602be0710:
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_EQ_
;VAR - n table_idx [2]
mov rcx, 16
mov rax, [rbp + rcx]
push rax
;NUM = 1
mov rax, 1
push rax
pop rcx
pop rax
cmp rax, rcx
sete al
and rax, 1
push rax
pop rax
test al, al
jz end_IF_0x7c0602be0910
;OP - _END_STATEMENT_
;OP - _RETURN_
;VAR - n table_idx [2]
mov rcx, 16
mov rax, [rbp + rcx]
push rax
jmp exit_Fibonacci
end_IF_0x7c0602be0910:
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_ADD_
;FUNC - Fibonacci st_idx = 2, end_idx = 3

;OP - _MATH_SUB_
;VAR - n table_idx [2]
mov rcx, 16
mov rax, [rbp + rcx]
push rax
;NUM = 1
mov rax, 1
push rax
pop rcx
pop rax
sub rax, rcx
push rax
call Fibonacci
add rsp, 8
push rax
;FUNC - Fibonacci st_idx = 2, end_idx = 3

;OP - _MATH_SUB_
;VAR - n table_idx [2]
mov rcx, 16
mov rax, [rbp + rcx]
push rax
;NUM = 2
mov rax, 2
push rax
pop rcx
pop rax
sub rax, rcx
push rax
call Fibonacci
add rsp, 8
push rax
pop rcx
pop rax
add rax, rcx
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
;OP - _END_STATEMENT_
;OP - _RETURN_
;VAR - val table_idx [3]
mov rcx, -8
mov rax, [rbp + rcx]
push rax
jmp exit_Fibonacci
exit_Fibonacci:
pop rax
add rsp, 8
pop rbp
ret
;==========================================================================
end_func_Fibonacci:
;==========================================================================

section .data
fmt_int db "%d", 10, 0
fmt_char db "%c", 10, 0
