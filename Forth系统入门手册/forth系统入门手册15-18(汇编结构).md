##第15章 汇编基础知识

为什么要使用汇编来构建forth？

因为汇编生成的程序小、运行速度快、自由度大，相应的缺点是编写方面的繁琐、以及不方便移植，而forth在很大程度上解决了汇编的这两个缺陷。


这里讲的是在x86系列（Intel和AMD）的CPU上运行的16位forth，但是在32位的操作系统里，16位的汇编程序是运行在16位虚拟机上的，所以也无法体现汇编的速度。如果想在32位的操作系统上写一个32位的汇编程序，似乎又有很多讲究，所以这里就不研究了。

使用工具：fasm

下载地址：http://flatassembler.net/

使用理由：不喜欢masm；nasm好像又没有“=”这个宏指令；fasm的语法也很简洁明了，并且附带汇编源码，可用fasm自身进行编译，有需要还可以自己修改，编译起来也简单，一句“fasm  源代码文件  可执行文件”就够了，而且windows下的版本还附带了一个简单的IDE


构建forth编译器所需的汇编基础知识

汇编语法里分号就是注释一行，回车就代表一行命令的结束。如果文中还有不太了解的地方，请自行在网上查询相关教程（例如王爽的《汇编语言》）


宏：

```ASM
	equ ：	 简单的替换宏 ，意思是等于，是英文equal的缩写，不能重复使用
    =：	类似于equ，主要用于赋值，可重复使用
    $：	当前行地址的数值
    macro：	多行替换宏，还可以带参数
    org：	内存可以看做是一条很长的单格纸条，每一格的大小是1字节（byte）。
    org是个伪指令，org 0100h就是从内存的第（16进制的100）格开始载入之后的程序。
    ORG是Origin的缩写：起始地址,源。在汇编语言源代码的开始，通常都用一条ORG伪指令来实现规定程序的起始地址。
    如果不用ORG规定则汇编得到的目标程序将从0000H开始。
```

标签`label`

```ASM
aaa:
    mov ax,bx
    jmp aaa	
```
    
`label`是以半角的冒号作为结束，标签`aaa`实际上是那一行的地址数值，`jmp`是无条件跳转指令，会跳转到aaa那一行执行`mov ax,bx`

另外还有一些有条件的跳转指令，请自行翻书。如果是`call`这个调用子程序的指令，在子程序里还要用`ret（return）`指令来返回


伪指令`db , dw , dd`

用法：

```ASM
    dw 1,2,aaa
```

这里`dw`把数值格式化到2个字节的长度，并在当前的位置写下这个数值，逗号是分隔符，这里写了3个数据（`aaa`是楼上那个标签地址数值），总长度是6个字节。

```ASM
    db(byte)是写1个字节的数据
    dw(word)是写2个字节的数据
    dd(dword | double word)是写4个字节的数据
```

总之就是`d系列`了

如果用`db`写字符串，可以简化成

```ASM
    db  'myforth',0
```

常用寄存器

`ax,bx,cx,dx`：装数据的小盒子，最多能装2个字节长度的数据，也就是16位的寄存器，而且每一个都可以拆分成两个8位寄存器，例如`ax`可以拆分成高8位的`ah（high）`和低8位的`al（low），bx,cx,dx`以此类推。`ax,bx,cx,dx`另外还有其他特殊用途，暂且不提。

`sp,bp,si`：指针类型的寄存器，长度也是2字节（16位），`push`和`pop`指令默认操作的就是`sp`这个用于控制系统栈的寄存器

汇编指令：

`mov`：复制数据

```ASM
	mov bx,ax		(ax的值复制给bx)
	mov [bx],ax	(把ax的值复制给bx所指向的内存地址)
	mov byte [bx],1	(把1复制到bx所指向的单字节内存地址)
	mov word [bx],1	(把1复制到bx所指向的两字节内存地址)
	(mov [bx],ax不需要指定byte或word,是因为ax已经代表了数据的长度是两字节)
```

`push`：把某个数据压到栈顶

```ASM
    push bx
```

`pop`：弹出栈顶数据到某个装数据的小盒子	

```ASM
    pop bx
```
`add , sub , mul，div`：加减乘除

```ASM
	add bx,ax		(bx=bx+ax)
	sub bx,ax		(bx=bx-ax)
	mul bx		(dx_ax=ax*bx  ax为默认的被乘数)
	div bx		(ax=dx_ax/bx  dx_ax为默认的被除数 ax中是商,dx中是余数)
```

`and , or , xor , shl , shr , rol, ror`：位运算指令

`int`：配合`mov ah,数值`，调用某个内置的DOS功能

标志位：

`ZF`：判断运算的结果是否为0，配合`jz/je（jmp if zero / jmp if equ）`和 `jnz/jne（jmp if not zero / jmp if not equ）`一起使用

`SF`：判断运算的结果是否为负数，配合`js（jmp if sign）`和 `jns（jmp if not sign ）`一起使用

注：`mov、push、pop`不会影响标志位


觉得看起来很多吧？其实也不算多，我从完全不懂汇编到理解这些东西也就花了一个月而已，还是断断续续的。直到现在，我也不算很懂汇编，不过用在forth上也足够了。

##第16章 还是先来个简单的

其实forth是从一种高度模块化的汇编编程风格演变而来的，forth保留了这种风格的子程序列表方式，并增加了以堆栈做为子程序参数传递的公共接口，围绕堆栈，还衍生了一些专门操作堆栈的子程序。在forth中，这种汇编风格被称为STC（子程序串线）编码方式。


下面将花少量篇幅简单的介绍一下forth的STC编码方式

```ASM
;;;;;;;;;;;;;;;;;;forth.asm;;;;;;;;;;;;;;;;;;;;;;;

;设置单元格大小为2字节
    celll equ 2	

    org	0100h
    mov bp, sp-128*celll
;栈指针SP寄存器作为机器默认的返回栈指针，SP默认值是0FFFEH
;设置BP寄存器为数据栈指针，与SP相隔256个字节
;程序代码是从内存的头部开始，stack却是从尾部倒着开始

    call dupp
    call dupp
    call 2dropp
    call byee



;code_words

;dup这个三个字符跟汇编器的关键字重复了
;按照eforth的惯例，把最后一个字符多写了一个，以示区别
dupp:
    mov bx, [bp]
    sub bp,celll
    mov [bp], bx
    ret

dropp:
    add bp,celll
    ret

byee:
    mov	ah,04ch
    int	021h
;退出程序，这个只用写一次，记不记都可以

;colon_words

2dropp:
    call dropp
    call dropp
    ret
;--------------------------------------------------------

```

##第17章 1k forth

forth更常用的是直接串线编码（DTC）,比起STC要麻烦许多，但各方面的性能更好。具体论述参见《moving forth》（中文译名《Forth系统实现》）


```ASM
;------------------------1k_forth.asm--------------------------------

celll	equ	2

COLDD	EQU	0100h
RSP		EQU	0FFF0H		
DSP		EQU	RSP-128*celll

_link  =  0		;链表连接地址

;next前面加上$，是延自eforth的写法习惯，表示这是一个宏
macro  $next
{
	mov ax,[si]	;si作为forth指令指针（forth 的IP），将si指向的内存地址上的forth指令保存到ax中
	add si,celll	;然后si顺序指向下一个forth指令
	jmp ax		;执行之前保存在ax中的forth指令
}

;类似于r>，但是指定了动向
macro	$rsto  where
{
	mov where,[bp]
	add bp,celll
}

;类似于>r，但是指定了来源
macro	$rsfrom        where
{
	sub bp,celll
	mov [bp],where
}


org	COLDD
	mov ax,cs
	mov ds,ax
	mov ss,ax
	mov es,ax
;将16位forth限制在一个段区域内，也就是64K的内存空间

	mov	sp,DSP	;指定sp为数据栈指针，DSP为数据栈底部
	mov bp,RSP	;指定bp为返回栈指针，RSP为返回栈底部


	mov ax, 2dropp	;设置2drop为起始命令
	jmp ax			;跳转到2dropp：



;code_words

; drop   ( n -- )
    dw _link	;0值
    _link=$	;记下当前行地址
    db 'drop',0	;组成字典的字，与命令行输入的单个字符串进行对比，如果符合就执行标签下的指令
dropp:
    add sp,celll
    $next



; doList ( si->rs   ip->ds->si ) 是colon words的入口
    dw _link	;指向 db 'drop',0 这一行
    _link=$	;记下当前行地址
    db 'doList',0
doList:
    $rsfrom si		;保存上一层的地址到rs上
    pop si		;将call来的DS上的地址存入si，然后$next，执行子程序列表中的核心词指令
    $next


; exit          ( rs->si ) 是colon words的出口
    dw _link	;指向 db 'doList',0 这一行
    _link=$	;记下当前地址
    db 'exit',0
exitt:
    $rsto si		;将rs中在保存的上一层地址取回si，使程序回到上一层子程序列表执行
    $next



;colon_words

    dw _link	;指向 db 'exit',0 这一行
    _link=$	;记下当前地址
    db '2drop',0
2dropp:
    call doList		;将CPU的机器指令指针ip寄存器的当前值（也就是接下来的dw dropp,dropp,exitt	这行的地址）压入sp管辖的数据栈DS，并跳转到doList：
    dw dropp,dropp,exitt		;子程序列表




;结尾记下字典的最后一个链接
dw	_link

_coreEnd:	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

```

##第18章 整理和优化

如果每写一个字，就要在开头写上那么一串，我会很烦的。所以，参数宏该出马了。

```ASM
macro	$code	name,label
{
	dw _link
	_link=$
	db name,0
label:
}

macro	$colon	name,label
{
	$code	name,label
	call doList
}
```


例如：

```ASM
;( n -- )
    $code	'drop',dropp
        add sp,celll
    $next

;( n n  -- )
    $colon	'2drop',2dropp
        dw dropp, dropp, exitt

```

再说优化

```ASM
macro	$next
{
	mov ax,[si]
	add si,celll
	jmp ax
}

    在X86汇编里，lodsw指令可以替代这个宏的前两条指令，所以
macro	$next
{
	lodsw
	jmp ax
}
```

每一个code字都把`$next`作为结尾，所以在使用了`lodsw`指令之后，每个code字都节省了一条指令。虽然`lodsw`的执行速度比那两条指令快不了多少，但它减少了程序的尺寸。你的code字越多，减少的就越多。在最后生成的forth编译器里大约减少了几百个字节，约占总大小的5%

colon字是由code字（或code字和colon字）组合而成的，每一个colon字仅仅只是一连串的字列表，真正在机器上执行实际操作的还是code字，colon字不过是把code字排列组合了一下，所以优化code字在速度上得到的提升是明显的。


由于colon字只是把code字的排列组合，在移植到硬件或软件平台的时候，colon字基本上可以原封不动的搬过去，需要重新编码的只是code字。

所以，code字越多，程序的运行速度越快；code字越少，程序越容易移植。事实上，forth是在现有的CPU上虚拟了一个只有forth指令的forthCPU，你可以把这两种情况看做CISC（复杂指令集计算机）和RISC（精简指令集计算机）的对比，这中间的平衡还得你自己把握。

colon字的实现机制，是通过`call doList`的指令，将ip寄存器指向下一个指令的内存地址压进数据栈，然后跳转到子程序doList执行，doList会把`si寄存器`的值存进返回栈，再把刚刚压进数据栈上的值弹出到`si寄存器`，这样就从上层子程序列表转到了下层子程序列表

简单来说就是：

```ASM
    ip->ds
    si->rs
    ds->si
```

其中ip值的最后目标是传到`si`，但是ip的值无法直接提取出来，而这种传值方式需要两次对内存的读取（堆栈是内存的一部分），比起寄存器之间的传值要慢得多。当高级定义字多起来的时候，这个开销也不小。

《moving forth》里给出了一个绝妙的解决方案，省掉了这两次的内存读写：

```ASM
macro	$colon	name,label
{
    $code name,label
    jmp doList
}

$code	'doList',doList
    $rsfrom si		;先保存上层正在读到的子程序列表的位置
    add ax,3		;还记得$next里的jmp ax吗？ax里保存了之前si指向的下一个指令（也就是现在的指令）位置，这个位置在jmp doList这一行，而jmp doList这个指令占据了3个字节，所以ax只需要加3，就能确定当前的子程序列表的首项
    mov si, ax		;然后传递给si寄存器
$next			;再用$next进入当前的子程序列表
```

`TOS`

`TOS`是`top of stack`的缩写，意思就是栈顶单元。本来`TOS`是在内存里的堆栈上，为了提高速度，前人对它也进行了优化，把`TOS`设置在寄存器bx上。

之前用汇编写的几个操作堆栈的code字有`dup,swap,over,drop`，来对比一下优化后的结果

```ASM
tos	equ	bx
;dup
    mov bx,sp
    mov bx, [bx]	;16位汇编不允许直接使用[sp]
    push bx
;tos dup 
    push tos

;swap
    pop bx
    pop ax
    push bx
    push ax
;tos swap
    pop ax
    push tos
    mov tos, ax


;over
    mov bx,sp
    mov bx,[bx+celll]
    push bx
;tos over
    push tos
    mov tos,sp
    mov tos,[tos+celll]
;over没什么变化


;drop
    add sp,celll
;tos drop
    pop tos
;看起来是慢了，但实际上只是一个提前量
```

`TOS`设定的优点还请自行体会。
