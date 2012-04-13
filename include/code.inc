
; doList	( si->rs  ip->si )	colon....
	$code	'doList',doList@
		$rsfrom si		;......
		add ax,2		;...."jmp di"(....2..)
		mov si,ax		;.si............
	$next


; bye	 ( -- )	....
	$code	'bye',bye@
		mov	ah,04ch
		int	021h





;.....
;.............3.......forth...................

; r>            ( --n )
	$code	'r>',rL@
		push tos
		$rsto tos
	$next

; >r            ( n-- )
	$code	'>r',Lr@
		$rsfrom tos
		pop tos
	$next


; r@            ( -- n )
	$code	'r@',r@@
		push tos
		mov tos,[bp]
	$next



; drop  ( n-- )
	$code	'drop',drop@
		pop tos
	$next

;: drops	swap drop ;
; drops  ( n1 n2 -- n2 )	.....
	$code	'drops',drops@
		add sp,celll
	$next

; dropr	( -- )	........................
	$code	'dropr',dropr@
		add bp,celll
	$next



; dup	( n--n n )
	$code	'dup',dup@
		push tos
	$next


;: dups	>r dup r> ;
; dups  ( n1 n2 --n1 n1 n2 )
	$code	'dups',dups@
		pop ax
		sub sp,celll
		push ax
	$next


; dupr	rs:  ( n --n n )
	$code	'dupr',dupr@
		pop ax
		sub sp,celll
		push ax
	$next



; swap  ( n1 n2 --n2 n1 )
	$code	'swap',swap@
		pop ax
		push tos
		mov tos,ax
	$next

;: swaps	>r swap r> ;
; swaps  ( n1 n2 n3--n2 n1 n3 )
	$code	'swaps',swaps@
		pop ax
		pop cx
		push ax
		push cx
	$next

;: over	>r dup r> swap ;
; over  ( n1 n2--n1 n2 n1 )
	$code	'over',over@
		push tos
		mov tos,sp
		mov tos,[tos+celll]
	$next

;: 2dup	over over ;
; 2dup  ( n1 n2--n1 n2 n1 n2 )
	$code	'2dup',Cdup@
		pop ax
		sub sp,celll
		push tos
		push ax
	$next

;: ++	1 + ;
; ++	 ( n -- n+1 )	..+1
	$code	'++',AA@
		inc tos
	$next
;: --	1 - ;
; --	( n -- n-1 )	..-1
	$code	'--',SS@
		dec tos
	$next

;: ++s	swap ++ swap ;
; ++s	( n1 n2 -- n1+1 n2 )	...+1.S..second
	$code	 '++s',AAs@
		mov ax,tos
		mov tos,sp	;.16..........sp.....ax bx cx dx ...bx.............
		inc word [tos]	;word..............................
		mov tos,ax	;
	$next

;: --s	swap -- swap ;
; --s           ( n1 n2 -- n1-1  n2 )	...-1
	$code	 '--s',SSs@
		mov ax,tos
		mov tos,sp
		dec word [tos]
		mov tos,ax
	$next



;........
; and   ( w w --w )
	$code	'and',and@
		pop ax
		and tos,ax
	$next

;1 and 1 = 1
;1 and 0 = 0
;0 and 1 = 0
;0 and 0 = 0
;1010  and 1100 = 1000


; or		( n1 n2 -- n )
	$code	'or',or@
		pop ax
		or tos,ax
	$next

;1 or 1 = 1
;1 or 0 = 1
;0 or 1 = 1
;0 or 0 = 0
;1010  or 1100 = 1110


; not	( n -- n' )
	$code	 'not',not@
		not tos
	$next

;not 1 = 0
;not 0 = 1
;not 1010 = 0101
;not 1100 = 0011


; xor	( n1 n2 -- n )
	$code	 'xor',xor@
		pop ax
		xor tos,ax
	$next

;1 xor 1 = 0
;1 xor 0 = 1
;0 xor 1 = 1
;0 xor 0 = 0
;1010  xor 1100 = 0110



;: setF	dup - ;
;setF	 ( n -- F )
	$code	'setF',setF@
		xor tos,tos	;.......0..
	$next

;: setT	setF not ;
;setT	 ( n -- t )
	$code	'setT',setT@
		xor tos,tos	;.........16......1111 1111 1111 1111
		not tos		;........-1
	$next			;..1 byte....=8 bit...


; key?  (  -- c T   |    0 )
;......................TRUE......0..
	$code	'key',key@
		push tos		;....
		mov ah,8		;..08.DOS...........al
		int 21h		;..DOS.........ZF

		mov bl, al	
		xor bh,bh		;bx...bh.0.....bl...2...........CELL...
	$next


; emit  ( c --  )		....
	$code	'emit',emit@
		mov dx,tos		;.TOS......dx.
		pop tos			;.....
		mov ah,2			;..2.DOS......
		int 21h			;.........DOS.......16.......32.....
	$next



; push  ( -- n )	..................
	$code	'push',push@
		push tos
		mov tos,[si]		;.SI..............bx....bx..........................
		add si,celll		;....forth.
	$next



; execute	( addr -- )	........forth........forth....execute....
	$code	'execute',execute@
		mov ax, tos	;..1..................2.doList..AX........
		pop tos		;.....
		jmp ax		;...........

; exit	( rs->si )	....forth...
	$code	'exit',exit@
		$rsto si		;.................
	$next



; !	( w addr -- )	.............
	$code	'!',!@
		pop ax
		mov [tos],ax
		pop tos
	$next

; @	( addr --w )	.............
	$code	'@',Q@
		mov tos,[tos]
	$next

; c!	( c a-- )	...............
	$code	'c!',c!@
		pop ax
		mov [tos],al	;...............al
		pop tos
	$next

; c@            ( a--c )...............
	$code	'c@',c@@
		mov bl,[tos]	;................bl
		xor bh,bh		;..16.
	$next

; rp@	( -- rp )	.........
	$code	'rp@',rp@@
		push tos
		mov tos,bp
	$next


; sp@   (  -- sp )	.........
	$code	'sp@',sp@@
		push tos
		mov tos,sp
	$next



;: sameAs	 r> @ execute ;
; sameAs	(  )	...
	$code	'sameAs',sameAs@
		mov ax,[si]		;....sameAs....forth.
		$rsto si			;........................
		jmp ax			;..


;...

;............................
; um+	( u u--ul uh )	
	$code	 'um+',umA@
		xor cx,cx		;cx.0
		pop ax		;
		add ax,tos		;..
		rcl cx,1		;rcl..........cx
		push ax		;............cx..1....0
		mov tos,cx	;..................
	$next

; +            ( n1 n2 --n )
	$code	 '+',A@
		pop ax
		add tos,ax
	$next

; -             ( n1 n2 --n ) 
	$code	 '-',S@
		pop ax
		sub ax,tos
		mov tos,ax
	$next

; um*   ( n1 n2 --dl dh )	.....
	$code	 'um*',umM@
		pop ax
		mul tos	;mul....ax........tos..
		push ax		;.....ax....dx
		mov tos,dx	;
	$next

; um/mod        ( udl udh un -- uq um | ff ff ) ...............
	$code	 'um/mod',umDmod@
		pop dx		;div....dx.......ax......
		pop ax		;
		cmp dx,tos	;cmp....dx.tos.............
		jb ummodd1	;jb...if below then jmp .........
		xor tos,tos	;..dx<tos....................ummodd1
		not tos		;...................................
		push tos		;;..........16...0ffh......
		$next		;;..
ummodd1:
		div tos		;dx ax ..tos
		push ax		;ax..
		mov tos,dx	;dx...
	$next


;..........num bit....0
; shl           ( w num -- w' )
	$code	 'shl',shl@
		mov cx,tos
		pop tos
		shl tos,cl
	$next

;..........num bit....0
; shr           ( w num -- w' )
	$code	 'shr',shr@
		mov cx,tos
		pop tos
		shr tos,cl
	$next

;............num bit............bits
; rol           ( w num -- w' )
	$code	 'rol',rol@
		mov cx,tos
		pop tos
		rol tos,cl
	$next

;............num bit............bits
; ror           ( w num -- w' )
	$code	 'ror',ror@
		mov cx,tos
		pop tos
		ror tos,cl
	$next






; 2*           ( n -- n' )	 ....2*
	$code	 '2*',CM@
		shl tos,1	;.....2*..
	$next

; 2/           ( n -- n' )	....2/
	$code	 '2/',CD@
		shr tos,1
	$next




;: !=	 - if true else false ;
;!=             ( w w-- t|0 )	.........TRUE....0
	$code	'!=',!E@
		pop ax
		xor tos,ax		;..tos.ax...xor.....tos.0
		jnz setT@		;......0.....setT
	$next

;: ==	 - if0 true else false ;
;==             ( w w--t|0 )	........TRUE....0
	$code	'==',EE@
		pop ax
		xor tos,ax
		jz setT@		;.....
		xor tos,tos	;.0
	$next




;u<             ( n1 n2 -- t|0 )	...<
	$code	'u<',uR@
		pop ax
uR@1:
		cmp ax,tos
		jb setT@
		xor tos,tos
	$next

;.“0<”
; negate?      ( n -- t | 0 )		.......TRUE...0
	$code	'negate?',negate?@
		or tos,tos
		js setT@		;......1...........setT
		xor tos,tos	;...0
	$next
;.......0.1...............
;..........................
;...[1]000 0000...................-128
;.............“...”...1
;......1.0000 0001......
;not 0000 0001 = 1111 1110
;1111 1110 + 0000 0001 = 1111 1111.-1.

;<              ( n1 n2 -- t|0 )	...<
	$code	'<',R@
		pop ax
		mov cx,tos	;..tos...........
		xor cx,ax		;...............xor..cx.....0.................1....
		jns uR@1		;..xor....................................."u<"....
		mov tos,ax	;.............n1.....
		jmp negate?@	;n1.....n1<n2....TRUE....0




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; if	( n --  )
	$code	'if',if@
		or tos,tos
		pop tos		;mov push pop ........
		jnz if@1		;....0......
		add si,celll*2	;.......
	if@1:
	$next


; if0	( n --  )	.if..
	$code	'if0',if0@
		or tos,tos
		pop tos		;mov push pop ........
		jz if@1		;...0......
		add si,celll*2
	$next

; endif	( n --  )	.........if..
	$code	'endif',endif@
	$next

;else	 ( - )	 ................endif
	$code	'else',else@
		add si,celll
	$next



; next  ( - )	( addr num -RS-        | addr num'  )
	$code	'next',next@
		dec word [bp]	;..
		jz next@0		;...0.....
		mov si,[bp+celll]	;....
		$next
	next@0:
		add bp,celll*2
	$next
