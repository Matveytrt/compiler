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
sub RSP, 80
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 5
mov RAX, 5
mov rcx, -8
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 15
mov RAX, 15
mov rcx, -16
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 15
mov RAX, 15
mov rcx, -24
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 30
mov RAX, 30
mov rcx, -32
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 30
mov RAX, 30
mov rcx, -40
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 0
mov RAX, 0
mov rcx, -48
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _WHILE_
start_WHILE_0x7c2946fe0890:
;OP - _MATH_BELOW_
;VAR - row table_idx [5]
mov rcx, -48
mov RAX, [rbp + rcx]
push RAX
;VAR - hght table_idx [4]
mov rcx, -40
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
cmp RAX, RBX
setl al
movzx RAX, AL
test AL, AL
jz end_WHILE_0x7c2946fe0890
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;NUM = 0
mov RAX, 0
mov rcx, -56
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _WHILE_
start_WHILE_0x7c2946fe0b10:
;OP - _MATH_BELOW_
;VAR - col table_idx [6]
mov rcx, -56
mov RAX, [rbp + rcx]
push RAX
;VAR - wdth table_idx [3]
mov rcx, -32
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
cmp RAX, RBX
setl al
movzx RAX, AL
test AL, AL
jz end_WHILE_0x7c2946fe0b10
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_SUB_
;VAR - col table_idx [6]
mov rcx, -56
mov RAX, [rbp + rcx]
push RAX
;VAR - x0 table_idx [1]
mov rcx, -16
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
sub RAX, RBX
mov rcx, -64
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_SUB_
;VAR - row table_idx [5]
mov rcx, -48
mov RAX, [rbp + rcx]
push RAX
;VAR - y0 table_idx [2]
mov rcx, -24
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
sub RAX, RBX
mov rcx, -72
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_ADD_
;OP - _MATH_MUL_
;VAR - dx table_idx [7]
mov rcx, -64
mov RAX, [rbp + rcx]
push RAX
;VAR - dx table_idx [7]
mov rcx, -64
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
push RAX
;OP - _MATH_MUL_
;VAR - dy table_idx [8]
mov rcx, -72
mov RAX, [rbp + rcx]
push RAX
;VAR - dy table_idx [8]
mov rcx, -72
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
mov RBX, RAX
pop RAX
add RAX, RBX
mov rcx, -80
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_BELOW_
;VAR - dist table_idx [9]
mov rcx, -80
mov RAX, [rbp + rcx]
push RAX
;OP - _MATH_MUL_
;VAR - r table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
push RAX
;VAR - r table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
mov RBX, RAX
pop RAX
cmp RAX, RBX
setl al
movzx RAX, AL
test AL, AL
jz end_IF_0x7c2946fe1290
;OP - _END_STATEMENT_
;OP - _PUTCHAR_
;NUM = 42
mov RAX, 42
call printchar WRT ..plt
end_IF_0x7c2946fe1290:
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_EQ_
;VAR - dist table_idx [9]
mov rcx, -80
mov RAX, [rbp + rcx]
push RAX
;OP - _MATH_MUL_
;VAR - r table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
push RAX
;VAR - r table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
mov RBX, RAX
pop RAX
cmp RAX, RBX
sete al
movzx RAX, AL
test AL, AL
jz end_IF_0x7c2946fe1510
;OP - _END_STATEMENT_
;OP - _PUTCHAR_
;NUM = 35
mov RAX, 35
call printchar WRT ..plt
end_IF_0x7c2946fe1510:
;OP - _END_STATEMENT_
;OP - _IF_
;OP - _MATH_ABOVE_
;VAR - dist table_idx [9]
mov rcx, -80
mov RAX, [rbp + rcx]
push RAX
;OP - _MATH_MUL_
;VAR - r table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
push RAX
;VAR - r table_idx [0]
mov rcx, -8
mov RAX, [rbp + rcx]
mov RBX, RAX
pop RAX
imul RAX, RBX
mov RBX, RAX
pop RAX
cmp RAX, RBX
setg al
movzx RAX, AL
test AL, AL
jz end_IF_0x7c2946fe1790
;OP - _END_STATEMENT_
;OP - _PUTCHAR_
;NUM = 32
mov RAX, 32
call printchar WRT ..plt
end_IF_0x7c2946fe1790:
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_ADD_
;VAR - col table_idx [6]
mov rcx, -56
mov RAX, [rbp + rcx]
push RAX
;NUM = 1
mov RAX, 1
mov RBX, RAX
pop RAX
add RAX, RBX
mov rcx, -56
mov [rbp + rcx], RAX
jmp start_WHILE_0x7c2946fe0b10
end_WHILE_0x7c2946fe0b10:
;OP - _END_STATEMENT_
;OP - _PUTCHAR_
;NUM = 10
mov RAX, 10
call printchar WRT ..plt
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_ADD_
;VAR - row table_idx [5]
mov rcx, -48
mov RAX, [rbp + rcx]
push RAX
;NUM = 1
mov RAX, 1
mov RBX, RAX
pop RAX
add RAX, RBX
mov rcx, -48
mov [rbp + rcx], RAX
jmp start_WHILE_0x7c2946fe0890
end_WHILE_0x7c2946fe0890:
;OP - _END_STATEMENT_
;OP - _RETURN_
;NUM = 0
mov RAX, 0
jmp exit_Main
exit_Main:
add RSP, 80
pop RBP
ret
;==========================================================================
end_func_Main:
;==========================================================================

section .data
vmem_buf db 901 dup(42)
