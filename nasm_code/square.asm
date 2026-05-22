extern print
extern printchar
extern my_scanf
global main

section .text
main:
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
sub RSP, 56
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 0
mov RAX, 0
mov rcx, -8
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 0
mov RAX, 0
mov rcx, -16
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 0
mov RAX, 0
mov rcx, -24
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 0
mov RAX, 0
mov rcx, -32
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 0
mov RAX, 0
mov rcx, -40
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 0
mov RAX, 0
mov rcx, -48
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _SCAN_
call my_scanf
;OP - _END_STATEMENT_
;OP - _SCAN_
call my_scanf
;OP - _END_STATEMENT_
;OP - _SCAN_
call my_scanf
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_EQ_
;VAR - a table_idx [0]
mov rcx, -8
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
jz end_IF_0x7ba2f67e0ad0
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_EQ_
;VAR - b table_idx [1]
mov rcx, -16
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
jz end_IF_0x7ba2f67e0c10
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_EQ_
;VAR - c table_idx [2]
mov rcx, -24
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
jz end_IF_0x7ba2f67e0d50
;OP - _END_STATEMENT_
;OP - _PUTCHAR_
;NUM = 38
mov RAX, 38
call printchar
;OP - _END_STATEMENT_
;OP - _RETURN_
;NUM = 0
mov RAX, 0
jmp exit_Main
end_IF_0x7ba2f67e0d50:
;OP - _END_STATEMENT_
;OP - _PUTCHAR_
;NUM = 63
mov RAX, 63
call printchar
;OP - _END_STATEMENT_
;OP - _RETURN_
;NUM = 0
mov RAX, 0
jmp exit_Main
end_IF_0x7ba2f67e0c10:
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_DIV_
;OP - _MATH_SUB_
;NUM = 0
mov RAX, 0
push RAX
;VAR - c table_idx [2]
mov rcx, -24
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
sub RAX, RBX
push RAX
;VAR - b table_idx [1]
mov rcx, -16
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
cqo
idiv RBX
mov rcx, -40
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _PRINT_
;VAR - x1 table_idx [4]
mov rcx, -40
mov RAX, [rbp + rcx]
call print
;OP - _END_STATEMENT_
;OP - _RETURN_
;NUM = 0
mov RAX, 0
jmp exit_Main
end_IF_0x7ba2f67e0ad0:
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_SUB_
;OP - _MATH_MUL_
;VAR - b table_idx [1]
mov rcx, -16
mov RAX, [rbp + rcx]
push RAX
;VAR - b table_idx [1]
mov rcx, -16
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
push RAX
;OP - _MATH_MUL_
;OP - _MATH_MUL_
;NUM = 4
mov RAX, 4
push RAX
;VAR - a table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
push RAX
;VAR - c table_idx [2]
mov rcx, -24
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
mov RBX, RAX
pop RAX
sub RAX, RBX
mov rcx, -32
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_BELOW_
;VAR - d table_idx [3]
mov rcx, -32
mov RAX, [rbp + rcx]
push RAX
;NUM = 0
mov RAX, 0
mov RBX, RAX
pop RAX
cmp RAX, RBX
setl al
movzx RAX, AL
test AL, AL
jz end_IF_0x7ba2f67e1890
;OP - _END_STATEMENT_
;OP - _PUTCHAR_
;NUM = 105
mov RAX, 105
call printchar
;OP - _END_STATEMENT_
;OP - _RETURN_
;NUM = 0
mov RAX, 0
jmp exit_Main
end_IF_0x7ba2f67e1890:
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_EQ_
;VAR - d table_idx [3]
mov rcx, -32
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
jz end_IF_0x7ba2f67e1b50
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_DIV_
;OP - _MATH_SUB_
;NUM = 0
mov RAX, 0
push RAX
;VAR - b table_idx [1]
mov rcx, -16
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
sub RAX, RBX
push RAX
;OP - _MATH_MUL_
;NUM = 2
mov RAX, 2
push RAX
;VAR - a table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
mov RBX, RAX
pop RAX
cqo
idiv RBX
mov rcx, -40
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _PRINT_
;VAR - x1 table_idx [4]
mov rcx, -40
mov RAX, [rbp + rcx]
call print
;OP - _END_STATEMENT_
;OP - _RETURN_
;NUM = 0
mov RAX, 0
jmp exit_Main
end_IF_0x7ba2f67e1b50:
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_SQRT_
;VAR - d table_idx [3]
mov rcx, -32
mov RAX, [rbp + rcx]
cvtsi2sd xmm0, rax
sqrtsd xmm0, xmm0
cvttsd2si rax, xmm0
mov rcx, -56
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_DIV_
;OP - _MATH_SUB_
;OP - _MATH_SUB_
;NUM = 0
mov RAX, 0
push RAX
;VAR - b table_idx [1]
mov rcx, -16
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
sub RAX, RBX
push RAX
;VAR - sqrtd table_idx [6]
mov rcx, -56
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
sub RAX, RBX
push RAX
;OP - _MATH_MUL_
;NUM = 2
mov RAX, 2
push RAX
;VAR - a table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
mov RBX, RAX
pop RAX
cqo
idiv RBX
mov rcx, -40
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_DIV_
;OP - _MATH_ADD_
;OP - _MATH_SUB_
;NUM = 0
mov RAX, 0
push RAX
;VAR - b table_idx [1]
mov rcx, -16
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
sub RAX, RBX
push RAX
;VAR - sqrtd table_idx [6]
mov rcx, -56
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
add RAX, RBX
push RAX
;OP - _MATH_MUL_
;NUM = 2
mov RAX, 2
push RAX
;VAR - a table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
mov RBX, RAX
pop RAX
cqo
idiv RBX
mov rcx, -48
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _PRINT_
;VAR - x1 table_idx [4]
mov rcx, -40
mov RAX, [rbp + rcx]
call print
;OP - _END_STATEMENT_
;OP - _PUTCHAR_
;NUM = 32
mov RAX, 32
call printchar
;OP - _END_STATEMENT_
;OP - _PRINT_
;VAR - x2 table_idx [5]
mov rcx, -48
mov RAX, [rbp + rcx]
call print
;OP - _END_STATEMENT_
;OP - _RETURN_
;NUM = 0
mov RAX, 0
jmp exit_Main
exit_Main:
add RSP, 56
pop RBP
ret
;==========================================================================
end_func_Main:
;==========================================================================

section .data
