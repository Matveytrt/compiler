extern print
extern printchar
extern my_scanf
global main

section .text
main:
nop
call Main
mov RAX, 60
xor RDI, RDI
syscall
;OP - _END_STATEMENT_
;OP - _FUNC_DECLARE_

;==========================================================================
jmp end_func_Main
; / FUNC Main /
;==========================================================================
Main:
push RBP
mov RBP, RSP
sub RSP, 16
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 0
mov RAX, 0
mov rcx, -8
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _SCAN_
call my_scanf
mov rcx, -8
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;FUNC - Fact st_idx = 2, end_idx = 3

;VAR - n table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
push RAX
call Fact
add RSP, 8
mov rcx, -16
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _PRINT_
;VAR - res table_idx [1]
mov rcx, -16
mov RAX, [rbp + rcx]
call print
;OP - _END_STATEMENT_
;OP - _RETURN_
;VAR - res table_idx [1]
mov rcx, -16
mov RAX, [rbp + rcx]
jmp exit_Main
exit_Main:
add RSP, 16
pop RBP
ret
;==========================================================================
end_func_Main:
;==========================================================================

;OP - _END_STATEMENT_
;OP - _FUNC_DECLARE_

;==========================================================================
jmp end_func_Fact
; / FUNC Fact /
;==========================================================================
Fact:
push RBP
mov RBP, RSP
sub RSP, 8
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_EQ_
;VAR - n table_idx [2]
mov rcx, 16
mov RAX, [rbp + rcx]
push RAX
;NUM = 0
mov RAX, 0
mov RBX, RAX
pop RAX
cmp RAX, RBX
sete al
movzx RAX, AL
test AL, AL
jz end_IF_0x7c2d5d5e0710
;OP - _END_STATEMENT_
;OP - _RETURN_
;NUM = 1
mov RAX, 1
jmp exit_Fact
end_IF_0x7c2d5d5e0710:
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 1
mov RAX, 1
mov rcx, -8
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_MUL_
;VAR - n table_idx [2]
mov rcx, 16
mov RAX, [rbp + rcx]
push RAX
;FUNC - Fact st_idx = 2, end_idx = 3

;OP - _MATH_SUB_
;VAR - n table_idx [2]
mov rcx, 16
mov RAX, [rbp + rcx]
push RAX
;NUM = 1
mov RAX, 1
mov RBX, RAX
pop RAX
sub RAX, RBX
push RAX
call Fact
add RSP, 8
mov RBX, RAX
pop RAX
imul RAX, RBX
mov rcx, -8
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _RETURN_
;VAR - f table_idx [3]
mov rcx, -8
mov RAX, [rbp + rcx]
jmp exit_Fact
exit_Fact:
add RSP, 8
pop RBP
ret
;==========================================================================
end_func_Fact:
;==========================================================================

section .data
