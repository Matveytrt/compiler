default abs
extern print
extern printchar
extern my_scanf
global main

section .text
main
call Main
mov RAX, 60
xor RDI, RDI
syscall

;==========================================================================
jmp end_func_Main
; / FUNC Main /
;==========================================================================
Main:
push RBP
mov RBP, RSP
sub RSP, 0
mov RAX, 0
push RAX
jmp exit_Main
exit_Main:
pop RAX
add RSP, 0
pop RBP
ret
;==========================================================================
end_func_Main:
;==========================================================================

section .data
