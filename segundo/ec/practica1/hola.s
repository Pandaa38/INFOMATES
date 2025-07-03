.data
msg:	.string "¡hola, mundo!\n"
tam:	.quad	. - msg

.text
_start: .global _start
	call	write
	call	exit

write:  mov	$1,	%rax
	mov 	$1,	%rdi
	mov	$msg,	%rsi
	mov	tam,	%rdx
	syscall
	ret

exit:	mov	$60,	%rax
	xor	%rdi,	%rdi
	syscall
	ret
	

