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
sub RSP, 16
mov RAX, 0
push RAX
pop RAX
mov rcx, -8
mov [rbp + rcx], RAX
call my_scanf WRT ..plt
mov rcx, -8
mov [rbp + rcx], RAX
mov rcx, -8
mov RAX, [rbp + rcx]
push RAX
call Fact
add RSP, 8
push RAX
pop RAX
mov rcx, -16
mov [rbp + rcx], RAX
mov rcx, -16
mov RAX, [rbp + rcx]
push RAX
pop RAX
call print WRT ..plt
mov rcx, -16
mov RAX, [rbp + rcx]
push RAX
jmp exit_Main
exit_Main:
pop RAX
add RSP, 16
pop RBP
ret
;==========================================================================
end_func_Main:
;==========================================================================


;==========================================================================
jmp end_func_Fact
; / FUNC Fact /
;==========================================================================
Fact:
push RBP
mov RBP, RSP
sub RSP, 8
mov rcx, 16
mov RAX, [rbp + rcx]
push RAX
mov RAX, 10
push RAX
mov RAX, 10
push RAX
pop RCX
pop RAX
add RAX, RCX
push RAX
pop RCX
pop RAX
cmp RAX, RCX
sete al
movzx RAX, AL
push RAX
pop RAX
test AL, AL
jz end_IF_0x7bbad15e0710
mov RAX, 20
push RAX
mov RAX, 19
push RAX
pop RCX
pop RAX
add RAX, RCX
push RAX
jmp exit_Fact
end_IF_0x7bbad15e0710:
mov RAX, 30
push RAX
mov RAX, 29
push RAX
pop RCX
pop RAX
add RAX, RCX
push RAX
pop RAX
mov rcx, -8
mov [rbp + rcx], RAX
mov rcx, 16
mov RAX, [rbp + rcx]
push RAX
mov RAX, 1
push RAX
mov rcx, 16
mov RAX, [rbp + rcx]
push RAX
call Fact
add RSP, 8
push RAX
pop RCX
pop RAX
add RAX, RCX
push RAX
pop RAX
mov rcx, -8
mov [rbp + rcx], RAX
mov rcx, -8
mov RAX, [rbp + rcx]
push RAX
jmp exit_Fact
exit_Fact:
pop RAX
add RSP, 8
pop RBP
ret
;==========================================================================
end_func_Fact:
;==========================================================================

section .data
