##第12章 一个最简单的forth

能看到这一章，相信你应该是对forth有了那么点兴趣了吧？学forth的最好途径就是自己做一个forth。那么，你有没有想过自己做一个forth呢？

这一部分就是简单的介绍forth的整体结构，用C语言的形式。声明一下，我用的是VC（至今还没脱离windows）


首先，建一个空白的模板。

```C++
//-----------------------cforth.cpp---------------------

#include <stdio.h>

void main()
{
        
}
///////////////////////////////////////////////////////
```

然后，要有堆栈。

```C++
//-----------------------cforth.cpp---------------------

#include <stdio.h>

//堆栈和堆栈指针
int ds[256],rs[256];
int *dsp=ds,*rsp=rs;
......
///////////////////////////////////////////////////////
```


在这里我用数组来申请一段连续空间充当堆栈。因为堆栈是公共的，所以放在外面作为全局变量，堆栈指针指向数组开头，也就是栈底。

接着，建立核心词文件code_words.h和扩展词文件colon_words.h

```C++
//堆栈和堆栈指针
int ds[256],rs[256];
int *dsp=ds, *rsp=rs;

#include "code_words.h"
#include "colon_words.h"
```

```C++
//-----------------------code_words.h-----------------------

//输入数字到DS
//push是forth里极少见的带参数的字，目的是为了输入数字到数据栈。
void push(int a){ dsp++; *dsp=a; }

//>r
void tor(){ rsp++; *rsp=*dsp; dsp--; }

//r>
void rto(){ dsp++; *dsp=*rsp; rsp--; }

void drop(){ dsp--; }

void dup(){ dsp++; *dsp=*(dsp-1); }

void swap(){ int tmp; tmp=*dsp,*dsp=*(dsp-1),*(dsp-1)=tmp; }

//+
void add(){ *(dsp-1)=*(dsp-1) + *dsp;  dsp--; }
......

//////////////////////////////////////////////////////////
```

```C++
//-----------------------colon_words.h-----------------------
//2drop
void drop2(){ drop(); drop();  };

//over
void over(){ tor(); dup(); rto();  swap(); };

//2dup
void dup2(){ over(); over();  };
...........
///////////////////////////////////////////////////////////////
```


这就是一个编译型的forth了。如果你还想继续往下做，那就扩充这两个头文件。如果不想写那么多();，可以先用forth的语法写在一个文本文件上，然后再写一个把这个文件转换成colon_words.h的小程序，避免不必要的重复劳动。（最好是用这种方式写，因为除了forth语法的文件，其他的都会有变动）

现在来测试一下某个字能否正常使用吧

```C++
//code_words.h
.......
//显示DS
void showDS()
{
        int * tmp=&ds[1];
        while(tmp<=dsp)
        {
                printf("%d ",*tmp); 
                tmp++;
        }
        printf("<DS]\n");
}

//显示RS
void showRS()
{
        int * tmp=&rs[1];
        while(tmp<=rsp)
        {
                printf("%d ",*tmp); 
                tmp++;
        }
        printf("<RS]\n");
}
```

```C++
//cforth.cpp
void main()
{
        push(6);
        push(2);


        showDS();
        showRS();


        dup2();

        printf("\n");

        showDS();
        showRS();

}
```


##第13章 判断和循环

现在做一个判断和循环的模拟

```
( n1 n2 -- n )
: max        2dup < if swap drop else drop then ;

void max(){ dup2(); less();    dsp--;if(*(dsp+1)){        swap(); drop();      }else{     drop();       }       }



: xx        5 for ." sdfsdf" next ;

void xx(){ push(5);       tor(); while(*rsp){      printf("sdfsdf");    *rsp--;}rsp--;      }
```

if和for...next在用完栈顶单元之后就丢掉栈顶单元。
    

##第14章 字的执行

Is that all?当然不是，别忘了在forth里是可以直接运行forth语句的，而上面这个程序做不到。

现在的目标是，在运行起来的程序里输入一个命令，并且得以执行。


```C++
#include <stdio.h>
#include <string.h>

//字符串输入缓冲区1k
char strBuff[1024];
.......
void main()
{
        push(6);
        push(2);
        while(1)
        {
                showDS();
                showRS();

                gets(strBuff);
                if( !strcmp("dup",strBuff) )        dup();
                

                printf("\n");
        }
}
```

现在DUP这个字可以起作用了，然后有样学样，添上其他字

```C++
        else if( !strcmp(">r",strBuff) )        tor();
        else if( !strcmp("r>",strBuff) )        rto();
        else if( !strcmp("drop",strBuff) )        drop();

    //退出程序
        else if( !strcmp("bye",strBuff) )        return;
    //输入数字
        else if( isNum() )        chgNum();
    //如果输入的命令错误，还可以加个提示
        else printf("\n[%s]?\n",strBuff);
```

别忘了添上这两个函数

```C++
int isNum()
{
        char * str=strBuff;
        while(*str)
        {
                if(*str<'0' || *str>'9')         return 0;
                str++;
        }return 1;
}

void chgNum()
{
        char * str=strBuff;
        int sum=0;
        while(*str)
        {
                sum=10*sum+(int)(*str-'0');
                str++;
        }
        push(sum);
}
```

嫌输入命令不够连贯？嗯，自己写个分解字符串的函数吧

C的示范到此为止
