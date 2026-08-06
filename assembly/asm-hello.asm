%define SYS_WRITE 1
%define STDOUT 1

global _start
segment .text
_start :
	;; write 
	mov rax, SYS_WRITE
	mov rdi, STDOUT
	mov rsi, hello
	mov rdx, hello_size
	syscall

;; exit
mov rax, 60
mov rdi, 0
syscall


segment .data
hello: db "hello, world", 10
hello_size: equ $-hello
