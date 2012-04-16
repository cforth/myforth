;;;;;下面所有的标签后面都加上一个“@”（“@”不是fasm的关键字），以示与fasm的关键字区别，例如bye@。另外对于一些特殊符号如+-*/<>，则变更为大写的ASMDRL，便于之后colon词的格式转换。记不住也没关系，我会提供一个小程序来转化格式，在code.txt文本文件里写下你需要的核心词名字，然后在正式开始敲代码之前先运行一下这个小程序

; doList	( si->rs  ip->si )	colon字的入口
	$code	'doList',doList@
		$rsfrom si		;保存上层地址
		add ax,2		;越过词头"jmp di"(内存上占2字节)
		mov si,ax		;让si指向冒号字里接下来的地址
	$next


; bye	 ( -- )	退出程序
	$code	'bye',bye@
		mov	ah,04ch
		int	021h





;堆栈操作词
;这里面有些词涉及到栈顶的前3个单元，是传统forth标准中没有的，只是为了提高效率才增加的

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
; drops  ( n1 n2 -- n2 )	丢弃次栈顶
	$code	'drops',drops@
		add sp,celll
	$next

; dropr	( -- )	丢弃返回栈栈顶（反正就一条指令，多你一个也不多）
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
; ++	 ( n -- n+1 )	栈顶+1
	$code	'++',AA@
		inc tos
	$next
;: --	1 - ;
; --	( n -- n-1 )	栈顶-1
	$code	'--',SS@
		dec tos
	$next

;: ++s	swap ++ swap ;
; ++s	( n1 n2 -- n1+1 n2 )	次栈顶+1，S代表second
	$code	 '++s',AAs@
		mov ax,tos
		mov tos,sp	;在16位汇编里，不能直接用sp读取内存，ax bx cx dx 中只有bx可以读取指定的内存地址内容
		inc word [tos]	;word是指定了两个字节，否则汇编器不可能知道你要操作的是多大的区域
		mov tos,ax	;
	$next

;: --s	swap -- swap ;
; --s           ( n1 n2 -- n1-1  n2 )	次栈顶-1
	$code	 '--s',SSs@
		mov ax,tos
		mov tos,sp
		dec word [tos]
		mov tos,ax
	$next



;二进制逻辑位运算
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
		xor tos,tos	;汇编里常用的置0方式
	$next

;: setT	setF not ;
;setT	 ( n -- t )
	$code	'setT',setT@
		xor tos,tos	;实际上最后的结果是16位的二进制数1111 1111 1111 1111
		not tos		;也就是有符号数的-1
	$next			;注：1 byte（字节）=8 bit（位）


; key?  (  -- c T   |    0 )
;基本输入，如果有键盘动作，就按顺序放上字符和TRUE，否则放一个0上去
	$code	'key',key@
		push tos		;空出栈顶
		mov ah,8		;调用08号DOS功能，接收输入的字符到al
		int 21h		;这个DOS功能会影响到标志位ZF

		mov bl, al	
		xor bh,bh		;bx的高位bh置0，配合低位bl，凑成2字节长度的数值，以符合CELL的长度
	$next


; emit  ( c --  )		基本输出
	$code	'emit',emit@
		mov dx,tos		;把TOS上的字符移到dx上
		pop tos			;消去原栈顶
		mov ah,2			;调用2号DOS功能打印字符
		int 21h			;需要说明的一点是，DOS调用功能只能在16位汇编里使用，32位并不支持
	$next



; push  ( -- n )	将后面紧跟的一个字当做数字放入数据栈
	$code	'push',push@
		push tos
		mov tos,[si]		;将SI指向的内存地址上的数据复制到bx上，由于bx是两个字节的长度，所以复制的数据也自动匹配为两个字节
		add si,celll		;越过一个forth字
	$next



; execute	( addr -- )	执行一个地址上的forth词，相当于把这个forth词放置在execute的位置上
	$code	'execute',execute@
		mov ax, tos	;理由1：直接跳转会导致无法消去原栈顶，理由2：doList需要AX，记住要保持统一
		pop tos		;消去原栈顶
		jmp ax		;跳转之后不再回到这里来

; exit	( rs->si )	返回上层forth词列表
	$code	'exit',exit@
		$rsto si		;返回栈的主要意义就是存放返回的地址
	$next



; !	( w addr -- )	把数据存入到指定的内存地址
	$code	'!',!@
		pop ax
		mov [tos],ax
		pop tos
	$next

; @	( addr --w )	从指定的内存地址中取出数据
	$code	'@',Q@
		mov tos,[tos]
	$next

; c!	( c a-- )	把单个字符存入到指定的内存地址
	$code	'c!',c!@
		pop ax
		mov [tos],al	;字符只有一个字节，所以这里用了al
		pop tos
	$next

; c@            ( a--c )从指定的内存地址中取出单个字符
	$code	'c@',c@@
		mov bl,[tos]	;从指定的内存地址上读取一个字节到bl
		xor bh,bh		;凑足16位
	$next

; rp@	( -- rp )	取出返回栈指针的值
	$code	'rp@',rp@@
		push tos
		mov tos,bp
	$next


; sp@   (  -- sp )	取出数据栈指针的值
	$code	'sp@',sp@@
		push tos
		mov tos,sp
	$next



;: sameAs	 r> @ execute ;
; sameAs	(  )	同义词
	$code	'sameAs',sameAs@
		mov ax,[si]		;准备执行sameAs接下来的forth词
		$rsto si			;恢复原来的现场，相当于在使用同义词的地方嵌入原词
		jmp ax			;执行


;计算词

;无符号加法，两个单精度无符号数相加得出一个双精度无符号数
; um+	( u u--ul uh )	
	$code	 'um+',umA@
		xor cx,cx		;cx清0
		pop ax		;
		add ax,tos		;相加
		rcl cx,1		;rcl指令会把进位标志移入cx
		push ax		;如果相加的结果进位了，则cx就是1，否则为0
		mov tos,cx	;计算的结果，高位在栈顶，低位在次栈顶
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

; um*   ( n1 n2 --dl dh )	无符号乘法
	$code	 'um*',umM@
		pop ax
		mul tos	;mul指令默认ax中为乘数，这里与tos相乘
		push ax		;得数低位在ax，高位在dx
		mov tos,dx	;
	$next

; um/mod        ( udl udh un -- uq um | ff ff ) 双精度无符号除法，得出商和余数
	$code	 'um/mod',umDmod@
		pop dx		;div指令默认dx为被除数高位，ax为被除数低位
		pop ax		;
		cmp dx,tos	;cmp指令比较dx和tos的大小，不会改变它们的数值
		jb ummodd1	;jb指令（if below then jmp ）如果小于就跳转，
		xor tos,tos	;如果dx<tos，则说明可以正常进行除法，然后跳转到标签ummodd1
		not tos		;否则被除数除以除数得到的结果仍然是一个双精度数，而不是预定的单精度结果
		push tos		;;异常的结果会给出两个16进制数0ffh作为错误标志
		$next		;;结束
ummodd1:
		div tos		;dx ax 除以tos
		push ax		;ax为商
		mov tos,dx	;dx为余数
	$next


;左移位指令，向左移动num bit，右边补0
; shl           ( w num -- w' )
	$code	 'shl',shl@
		mov cx,tos
		pop tos
		shl tos,cl
	$next

;右移位指令，向右移动num bit，左边补0
; shr           ( w num -- w' )
	$code	 'shr',shr@
		mov cx,tos
		pop tos
		shr tos,cl
	$next

;左回环移位指令，向左移动num bit，右边补上从左边移出去的bits
; rol           ( w num -- w' )
	$code	 'rol',rol@
		mov cx,tos
		pop tos
		rol tos,cl
	$next

;右回环移位指令，向右移动num bit，左边补上从右边移出去的bits
; ror           ( w num -- w' )
	$code	 'ror',ror@
		mov cx,tos
		pop tos
		ror tos,cl
	$next






; 2*           ( n -- n' )	 无符号的2*
	$code	 '2*',CM@
		shl tos,1	;左移一位的2*更快
	$next

; 2/           ( n -- n' )	无符号的2/
	$code	 '2/',CD@
		shr tos,1
	$next




;: !=	 - if true else false ;
;!=             ( w w-- t|0 )	如果不等于，则留下TRUE，否则是0
	$code	'!=',!E@
		pop ax
		xor tos,ax		;如果tos和ax相等，xor的结果就是tos清0
		jnz setT@		;如果得数不为0，就跳转到setT
	$next

;: ==	 - if0 true else false ;
;==             ( w w--t|0 )	如果等于，则留下TRUE，否则是0
	$code	'==',EE@
		pop ax
		xor tos,ax
		jz setT@		;与上面相反
		xor tos,tos	;清0
	$next




;u<             ( n1 n2 -- t|0 )	无符号<
	$code	'u<',uR@
		pop ax
uR@1:
		cmp ax,tos
		jb setT@
		xor tos,tos
	$next

;原“0<”
; negate?      ( n -- t | 0 )		如果是负数，则TRUE，否则0
	$code	'negate?',negate?@
		or tos,tos
		js setT@		;如果符号位是1，则是负数，然后跳转到setT
		xor tos,tos	;否则清0
	$next
;计算机本身只有0和1这种二进制数，并没有负数的概念
;由于需要负数这个东西，就规定二进制数的最高位为符号位
;例如：[1]000 0000，方括号里的就是符号位，这个有符号数是-128
;正数转变成负数，需要先进行“非运算”，再加1
;例如有符号的1是0000 0001，转变成负数
;not 0000 0001 = 1111 1110
;1111 1110 + 0000 0001 = 1111 1111（-1）

;<              ( n1 n2 -- t|0 )	有符号<
	$code	'<',R@
		pop ax
		mov cx,tos	;保留tos的原值，方便下面的跳转
		xor cx,ax		;比较符号位，如果符号位相同，则xor之后cx的符号位为0（表示正数）。如果不同，则符号位为1（负数）
		jns uR@1		;如果xor运算的结果不是负数（也就是两数的符号位相同），就当做是两个无符号数，跳转到"u<"进行比较
		mov tos,ax	;如果两数的符号不同，则看看n1是否为负数
		jmp negate?@	;n1是负数，则n1<n2，栈顶置TRUE，否则置0




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; if	( n --  )
	$code	'if',if@
		or tos,tos
		pop tos		;mov push pop 不会影响到标志位
		jnz if@1		;如果不是0，就顺序执行
		add si,celll*2	;否则跳过两个词
	if@1:
	$next


; if0	( n --  )	与if相反
	$code	'if0',if0@
		or tos,tos
		pop tos		;mov push pop 不会影响到标志位
		jz if@1		;如果是0，就顺序执行
		add si,celll*2
	$next

; endif	( n --  )	空指令，只是用来填if的缺
	$code	'endif',endif@
	$next

;else	 ( - )	 直接跳过一个词，后面也无需跟一个endif
	$code	'else',else@
		add si,celll
	$next



; next  ( - )	( addr num -RS-        | addr num'  )
	$code	'next',next@
		dec word [bp]	;计数
		jz next@0		;如果为0则退出循环
		mov si,[bp+celll]	;否则循环
		$next
	next@0:
		add bp,celll*2
	$next