include 'include\macro.inc'

org	COLDD
	mov ax,cs
	mov ds,ax
	mov ss,ax
	mov es,ax

_resetStack@:
	mov	sp,DSP
	mov bp,RSP
	mov di,doList@
	
;       mov ax , 测试@
	mov ax , 命令行@

	jmp ax



_showstack@:
	call print
	pop bx
	cmp bx,0
	je _deadloop@
	jmp _showstack@


_deadloop@:
	jmp $

print:
	mov cx,4
	loopp:
		rol bx,4
		call print1
	dec cx
	jnz loopp
	ret

print1:
	mov dl,bl
	and dl,0fh
	add dl,48
	cmp dl,58
	jb num
		add dl,7
	num:
		mov ah,2
		int 21h
		ret

include 'include\code.inc'
include 'include\colon.inc'

dw	_link

_coreEnd@: