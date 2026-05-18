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


;==========================================================================
jmp end_func_Main
; / FUNC Main /
;==========================================================================
Main:
push rbp
mov rbp, rsp
sub rsp, 56
mov rax, 0
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
mov rax, 0
push rax
pop rax
mov rcx, -16
mov [rbp + rcx], rax
mov rax, 0
push rax
pop rax
mov rcx, -24
mov [rbp + rcx], rax
mov rax, 0
push rax
pop rax
mov rcx, -32
mov [rbp + rcx], rax
mov rax, 0
push rax
pop rax
mov rcx, -40
mov [rbp + rcx], rax
mov rax, 0
push rax
pop rax
mov rcx, -48
mov [rbp + rcx], rax
call my_scanf WRT ..plt
mov rcx, -8
mov [rbp + rcx], rax
call my_scanf WRT ..plt
mov rcx, -16
mov [rbp + rcx], rax
call my_scanf WRT ..plt
mov rcx, -24
mov [rbp + rcx], rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
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
jz end_IF_0x7b52aefe0ad0
mov rcx, -16
mov rax, [rbp + rcx]
push rax
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
jz end_IF_0x7b52aefe0c10
mov rcx, -24
mov rax, [rbp + rcx]
push rax
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
jz end_IF_0x7b52aefe0d50
mov rax, 8
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rax, 0
push rax
jmp exit_Main
end_IF_0x7b52aefe0d50:
mov rax, -1
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rax, 0
push rax
jmp exit_Main
end_IF_0x7b52aefe0c10:
mov rax, 0
push rax
mov rcx, -24
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
sub rax, rcx
push rax
mov rcx, -16
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
cqo
idiv rcx
push rax
pop rax
mov rcx, -40
mov [rbp + rcx], rax
mov rcx, -40
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rax, 0
push rax
jmp exit_Main
end_IF_0x7b52aefe0ad0:
mov rcx, -16
mov rax, [rbp + rcx]
push rax
mov rcx, -16
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
mov rax, 4
push rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
mov rcx, -24
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
mov rcx, -32
mov [rbp + rcx], rax
mov rcx, -32
mov rax, [rbp + rcx]
push rax
mov rax, 0
push rax
pop rcx
pop rax
cmp rax, rcx
setl al
and rax, 1
push rax
pop rax
test al, al
jz end_IF_0x7b52aefe1890
mov rax, -1
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rax, 0
push rax
jmp exit_Main
end_IF_0x7b52aefe1890:
mov rcx, -32
mov rax, [rbp + rcx]
push rax
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
jz end_IF_0x7b52aefe1b50
mov rax, 0
push rax
mov rcx, -16
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
sub rax, rcx
push rax
mov rax, 2
push rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
pop rcx
pop rax
cqo
idiv rcx
push rax
pop rax
mov rcx, -40
mov [rbp + rcx], rax
mov rcx, -40
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rax, 0
push rax
jmp exit_Main
end_IF_0x7b52aefe1b50:
mov rcx, -32
mov rax, [rbp + rcx]
push rax
pop rax
cvtsi2sd xmm0, rax
sqrtsd xmm0, xmm0
cvttsd2si rax, xmm0
push rax
pop rax
mov rcx, -56
mov [rbp + rcx], rax
mov rax, 0
push rax
mov rcx, -16
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
sub rax, rcx
push rax
mov rcx, -56
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
sub rax, rcx
push rax
mov rax, 2
push rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
pop rcx
pop rax
cqo
idiv rcx
push rax
pop rax
mov rcx, -40
mov [rbp + rcx], rax
mov rax, 0
push rax
mov rcx, -16
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
sub rax, rcx
push rax
mov rcx, -56
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
add rax, rcx
push rax
mov rax, 2
push rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
pop rcx
pop rax
cqo
idiv rcx
push rax
pop rax
mov rcx, -48
mov [rbp + rcx], rax
mov rcx, -40
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rcx, -48
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rax, 0
push rax
jmp exit_Main
exit_Main:
pop rax
add rsp, 56
pop rbp
ret
;==========================================================================
end_func_Main:
;==========================================================================

section .data
vmem_buf db 901 dup('*')
fmt_int db "%d", 10, 0
fmt_char db "%c", 0
