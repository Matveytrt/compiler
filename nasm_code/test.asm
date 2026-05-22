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
sub RSP, 8
;OP - _END_STATEMENT_
;OP - _ASSIGNMENT_
;OP - _MATH_ADD_
;NUM = 5
mov RAX, 5
push RAX
;NUM = 3
mov RAX, 3
mov RBX, RAX
pop RAX
add RAX, RBX
mov rcx, -8
mov [rbp + rcx], RAX
;OP - _END_STATEMENT_
;OP - _RETURN_
;NUM = 0
mov RAX, 0
jmp exit_Main
exit_Main:
add RSP, 8
pop RBP
ret
;==========================================================================
end_func_Main:
;==========================================================================

section .data
