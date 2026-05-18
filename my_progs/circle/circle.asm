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
sub rsp, 88
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
mov rax, 30
push rax
pop rax
mov rcx, -32
mov [rbp + rcx], rax
mov rax, 30
push rax
pop rax
mov rcx, -40
mov [rbp + rcx], rax
call my_scanf WRT ..plt
mov rcx, -16
mov [rbp + rcx], rax
call my_scanf WRT ..plt
mov rcx, -24
mov [rbp + rcx], rax
call my_scanf WRT ..plt
mov rcx, -8
mov [rbp + rcx], rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
pop rax
mov rcx, -48
mov [rbp + rcx], rax
mov rcx, -40
mov rax, [rbp + rcx]
push rax
mov rcx, -32
mov rax, [rbp + rcx]
push rax
mov rcx, -48
mov rax, [rbp + rcx]
push rax
mov rcx, -24
mov rax, [rbp + rcx]
push rax
mov rcx, -16
mov rax, [rbp + rcx]
push rax
call MakeCircle
add rsp, 40
mov rax, 0
push rax
pop rax
mov rcx, -56
mov [rbp + rcx], rax
WHILE_0x7b4dd71e0f50:
mov rcx, -56
mov rax, [rbp + rcx]
push rax
mov rcx, -40
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
cmp rax, rcx
setl al
and rax, 1
push rax
pop rax
test al, al
jz end_WHILE_0x7b4dd71e0f50
mov rax, 0
push rax
pop rax
mov rcx, -64
mov [rbp + rcx], rax
WHILE_0x7b4dd71e11d0:
mov rcx, -64
mov rax, [rbp + rcx]
push rax
mov rcx, -32
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
cmp rax, rcx
setl al
and rax, 1
push rax
pop rax
test al, al
jz end_WHILE_0x7b4dd71e11d0
mov rcx, -56
mov rax, [rbp + rcx]
push rax
mov rcx, -32
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
mov rcx, -64
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
add rax, rcx
push rax
pop rax
mov rcx, -72
mov [rbp + rcx], rax
mov rcx, -72
mov rax, [rbp + rcx]
push rax
pop rbx
lea rcx, [vmem_buf]
add rcx, rbx
movzx rax, byte [rcx]
push rax
pop rax
mov rcx, -80
mov [rbp + rcx], rax
mov rcx, -80
mov rax, [rbp + rcx]
push rax
pop rsi
lea rdi, [fmt_char]
xor rax, rax
call printf WRT ..plt
mov rcx, -64
mov rax, [rbp + rcx]
push rax
mov rax, 1
push rax
pop rcx
pop rax
add rax, rcx
push rax
pop rax
mov rcx, -64
mov [rbp + rcx], rax
jmp WHILE_0x7b4dd71e11d0
end_WHILE_0x7b4dd71e11d0:
mov rax, 10
push rax
pop rax
mov rcx, -88
mov [rbp + rcx], rax
mov rcx, -88
mov rax, [rbp + rcx]
push rax
pop rsi
lea rdi, [fmt_char]
xor rax, rax
call printf WRT ..plt
mov rcx, -56
mov rax, [rbp + rcx]
push rax
mov rax, 1
push rax
pop rcx
pop rax
add rax, rcx
push rax
pop rax
mov rcx, -56
mov [rbp + rcx], rax
jmp WHILE_0x7b4dd71e0f50
end_WHILE_0x7b4dd71e0f50:
mov rax, 0
push rax
jmp exit_Main
exit_Main:
pop rax
add rsp, 88
pop rbp
ret
;==========================================================================
end_func_Main:
;==========================================================================


;==========================================================================
jmp end_func_MakeCircle
; / FUNC MakeCircle /
;==========================================================================
MakeCircle:
push rbp
mov rbp, rsp
sub rsp, 40
mov rax, 0
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
mov rcx, 16
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rcx, 24
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rcx, 32
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rcx, 40
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rcx, 48
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rcx, 40
mov rax, [rbp + rcx]
push rax
mov rcx, 48
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
pop rax
mov rcx, -16
mov [rbp + rcx], rax
WHILE_0x7b4dd71e2710:
mov rcx, -8
mov rax, [rbp + rcx]
push rax
mov rcx, -16
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
cmp rax, rcx
setl al
and rax, 1
push rax
pop rax
test al, al
jz end_WHILE_0x7b4dd71e2710
mov rcx, 48
mov rax, [rbp + rcx]
push rax
mov rcx, 40
mov rax, [rbp + rcx]
push rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
call GetX
add rsp, 24
push rax
mov rcx, 16
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
sub rax, rcx
push rax
pop rax
mov rcx, -24
mov [rbp + rcx], rax
mov rcx, 48
mov rax, [rbp + rcx]
push rax
mov rcx, 40
mov rax, [rbp + rcx]
push rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
call GetY
add rsp, 24
push rax
mov rcx, 24
mov rax, [rbp + rcx]
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
mov rcx, -24
mov rax, [rbp + rcx]
push rax
call GetDist
add rsp, 16
push rax
pop rax
mov rcx, -40
mov [rbp + rcx], rax
mov rcx, -40
mov rax, [rbp + rcx]
push rax
mov rcx, 32
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
cmp rax, rcx
setl al
and rax, 1
push rax
pop rax
test al, al
jz end_IF_0x7b4dd71e3050
mov rcx, -8
mov rax, [rbp + rcx]
push rax
mov rax, 35
push rax
pop rax
pop rbx
lea rcx, [vmem_buf]
add rcx, rbx
mov byte [rcx], al
end_IF_0x7b4dd71e3050:
mov rcx, -8
mov rax, [rbp + rcx]
push rax
lea rdi, [fmt_int]
pop rax
mov rsi, rax
xor rax, rax
call printf WRT ..plt
mov rcx, -8
mov rax, [rbp + rcx]
push rax
mov rax, 1
push rax
pop rcx
pop rax
add rax, rcx
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
jmp WHILE_0x7b4dd71e2710
end_WHILE_0x7b4dd71e2710:
mov rax, 0
push rax
jmp exit_MakeCircle
exit_MakeCircle:
pop rax
add rsp, 40
pop rbp
ret
;==========================================================================
end_func_MakeCircle:
;==========================================================================


;==========================================================================
jmp end_func_GetX
; / FUNC GetX /
;==========================================================================
GetX:
push rbp
mov rbp, rsp
sub rsp, 16
mov rcx, 16
mov rax, [rbp + rcx]
push rax
mov rcx, 24
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
cqo
idiv rcx
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
mov rcx, 16
mov rax, [rbp + rcx]
push rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
mov rcx, 24
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
mov rcx, -16
mov [rbp + rcx], rax
mov rcx, -16
mov rax, [rbp + rcx]
push rax
jmp exit_GetX
exit_GetX:
pop rax
add rsp, 16
pop rbp
ret
;==========================================================================
end_func_GetX:
;==========================================================================


;==========================================================================
jmp end_func_GetY
; / FUNC GetY /
;==========================================================================
GetY:
push rbp
mov rbp, rsp
sub rsp, 8
mov rcx, 16
mov rax, [rbp + rcx]
push rax
mov rcx, 24
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
cqo
idiv rcx
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
jmp exit_GetY
exit_GetY:
pop rax
add rsp, 8
pop rbp
ret
;==========================================================================
end_func_GetY:
;==========================================================================


;==========================================================================
jmp end_func_GetDist
; / FUNC GetDist /
;==========================================================================
GetDist:
push rbp
mov rbp, rsp
sub rsp, 8
mov rcx, 16
mov rax, [rbp + rcx]
push rax
mov rcx, 16
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
mov rcx, 24
mov rax, [rbp + rcx]
push rax
mov rcx, 24
mov rax, [rbp + rcx]
push rax
pop rcx
pop rax
imul rax, rcx
push rax
pop rcx
pop rax
add rax, rcx
push rax
pop rax
mov rcx, -8
mov [rbp + rcx], rax
mov rcx, -8
mov rax, [rbp + rcx]
push rax
jmp exit_GetDist
exit_GetDist:
pop rax
add rsp, 8
pop rbp
ret
;==========================================================================
end_func_GetDist:
;==========================================================================

section .data
vmem_buf db 901 dup('*')
fmt_int db "%d", 10, 0
fmt_char db "%c", 0
