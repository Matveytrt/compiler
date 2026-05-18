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
sub rsp, 0
mov rax, 0
push rax
mov rax, 10
push rax
pop rax
pop rbx
lea r8, [vmem_buf]
mov [r8 + rbx], rax
mov rax, 0
push rax
pop r13
lea rbx, [vmem_buf]
add rbx, r13
movzx rsi, byte [rbx]
mov [char_buf], sil
mov rax, 1
mov rdi, 1
lea rsi, [char_buf]
mov rdx, 1
syscall
mov rax, 42
push rax
pop r13
lea rbx, [vmem_buf]
add rbx, r13
movzx rsi, byte [rbx]
mov [char_buf], sil
mov rax, 1
mov rdi, 1
lea rsi, [char_buf]
mov rdx, 1
syscall
mov rax, 0
push rax
jmp exit_Main
exit_Main:
pop rax
add rsp, 0
pop rbp
ret
;==========================================================================
end_func_Main:
;==========================================================================

section .data
vmem_buf db 901 dup('*')
fmt_int db "%d", 10, 0
char_buf db 0
