tos	equ	bx
endstr	equ	32

COLDD	equ	100h
celll		equ	2		;size of a cell

RSP		EQU	0FFF0H		;start of return stack
DSP		EQU	RSP-128*celll		;start of data stack

_link  =  0

macro	$code	name,label
{
	dw _link
	_link = $
	db name,endstr
	label:
}

macro	$colon	name,label
{
	$code name,label
	 jmp di
;t      jmp doList@
}

macro	$next
{
	lodsw
;       mov ax,[si]
;       add si,celll
	jmp ax
}


macro	$rsto	       where
{
	mov where,[bp]
	add bp,celll
}

macro	$rsfrom        where
{
	sub bp,celll
	mov [bp],where
}