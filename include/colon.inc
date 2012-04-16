

$colon '测试',测试@
dw  dup@,Jword@,drop@,下个单词@,_deadloop@,exit@

$colon '测试1',测试1@
dw  JY@
db 'test ',0
dw  exit@

$colon '测试2',测试2@
dw  JY@
db 'notfind ',0
dw  exit@

$colon 'u>',uL@
dw  swap@,uR@,exit@

$colon '>',L@
dw  swap@,R@,exit@

$colon 'negate',negate@
dw  not@,AA@,exit@

$colon 'dnegate',dnegate@
dw  not@,Lr@,not@,push@,1,umA@,rL@,A@,exit@

$colon 'isDifSign',isDifSign@
dw  xor@,negate?@,exit@

$colon 'abs',abs@
dw  dup@,negate?@,if@,negate@,endif@,exit@

$colon 'dabs',dabs@
dw  dup@,negate?@,if@,dnegate@,endif@,exit@

$colon 'm*',mM@
dw  Cdup@,isDifSign@,Lr@,abs@,swap@,abs@,umM@,rL@,if@,dnegate@,endif@,exit@

$colon '*',M@
dw  mM@,drop@,exit@

$colon 'm/mod',mDmod@
dw  Cdup@,isDifSign@,Lr@,abs@,Lr@,dabs@,rL@,umDmod@,rL@,if0@,exit@,endif@,Lr@,negate@,rL@,exit@

$colon '/mod',Dmod@
dw  over@,negate?@,swap@,mDmod@,exit@

$colon 'mod',mod@
dw  Dmod@,drops@,exit@

$colon '/',D@
dw  Dmod@,drop@,exit@

$colon 'cell',cell@
dw  push@,2,exit@

$colon 'cell+',cellA@
dw  cell@,A@,exit@

$colon 'cell-',cellS@
dw  cell@,S@,exit@

$colon '2drop',Cdrop@
dw  drops@,drop@,exit@

$colon 'setT2',setT2@
dw  drops@,setT@,exit@

$colon 'setF2',setF2@
dw  drops@,setF@,exit@

$colon 'do',do@
dw  r@@,Lr@,exit@

$colon 'loop',loop@
dw  dropr@,r@@,Lr@,exit@

$colon 'break',break@
dw  dropr@,dropr@,exit@

$colon 'dup?',dup?@
dw  dup@,if@,dup@,endif@,exit@

$colon 'for',for@
dw  dup?@,if0@,dropr@,exit@,r@@,swap@,Lr@,Lr@,exit@

$colon '同义词',同义词@
dw  sameAs@,sameAs@,exit@

$colon '如果是',如果是@
dw  同义词@,if@,exit@

$colon '如果不是',如果不是@
dw  同义词@,if0@,exit@

$colon '否则',否则@
dw  同义词@,else@,exit@

$colon 'bb',bb@
dw  同义词@,bye@,exit@

$colon '读取字符',读取字符@
dw  dup@,c@@,exit@

$colon '.str',Jstr@
dw  do@,读取字符@,AAs@,dup@,if0@,drop@,break@,emit@,loop@,exit@

$colon '."',JY@
dw  rL@,Jstr@,Lr@,exit@

$colon 'cr',cr@
dw  push@,13,emit@,push@,10,emit@,exit@

$colon '提示符',提示符@
dw  JY@
db '>>>',0
dw  exit@

$colon '词典目录尾',词典目录尾@
dw  push@,_coreEnd@,exit@

$colon '缓冲区定位',缓冲区定位@
dw  词典目录尾@,push@,512,A@,exit@

$colon '对比字符',对比字符@
dw  over@,EE@,if@,setT@,else@,FALSE@,exit@

$colon 'CR?',CR?@
dw  push@,13,对比字符@,exit@

$colon 'LF?',LF?@
dw  push@,10,对比字符@,exit@

$colon 'TRUE',TRUE@
dw  push@,0,not@,exit@

$colon 'FALSE',FALSE@
dw  push@,0,exit@

$colon '换行符?',换行符?@
dw  CR?@,如果是@,TRUE@,exit@,LF?@,exit@

$colon '储存字符',储存字符@
dw  over@,c!@,AA@,exit@

$colon '标记词条尾',标记词条尾@
dw  push@,32,储存字符@,push@,59,储存字符@,push@,0,swap@,c!@,exit@

$colon '结束输入',结束输入@
dw  标记词条尾@,cr@,exit@

$colon '退格符?',退格符?@
dw  push@,8,对比字符@,exit@

$colon '缓冲区内?',缓冲区内?@
dw  缓冲区定位@,over@,uR@,exit@

$colon 'space',space@
dw  push@,32,emit@,exit@

$colon '退格',退格@
dw  缓冲区内?@,如果不是@,exit@,endif@,push@,8,dup@,emit@,space@,emit@,SS@,exit@

$colon '双引号?',双引号?@
dw  push@,34,对比字符@,exit@

$colon '显示双引号',显示双引号@
dw  dup@,dup@,emit@,space@,emit@,exit@

$colon '储存双引号',储存双引号@
dw  Lr@,r@@,储存字符@,push@,32,储存字符@,rL@,储存字符@,exit@

$colon '双引号匹配',双引号匹配@
dw  push@,34,显示双引号@,储存双引号@,exit@

$colon '输入命令',输入命令@
dw  缓冲区定位@,do@,key@,换行符?@,如果是@,结束输入@,break@,退格符?@,如果是@,退格@,loop@,双引号?@,如果是@,双引号匹配@,loop@,dup@,emit@,储存字符@,loop@,exit@

$colon '空格?',空格?@
dw  push@,32,对比字符@,exit@

$colon 'tab?',tab?@
dw  push@,9,对比字符@,exit@

$colon 'case',case@
dw  r@@,Q@,swap@,if@,execute@,break@,drop@,rL@,cellA@,Lr@,exit@

$colon '空白字符?',空白字符?@
dw  空格?@,case@,TRUE@,tab?@,case@,TRUE@,CR?@,case@,TRUE@,LF?@,exit@

$colon '替换成空格',替换成空格@
dw  push@,32,储存字符@,exit@

$colon '文本预处理',文本预处理@
dw  do@,读取字符@,dup@,if0@,Cdrop@,break@,空白字符?@,如果是@,替换成空格@,否则@,drop@,AA@,loop@,exit@

$colon '左括号?',左括号?@
dw  push@,40,EE@,exit@

$colon '右括号?',右括号?@
dw  push@,41,EE@,exit@

$colon '忽略注释',忽略注释@
dw  do@,读取字符@,AAs@,右括号?@,如果是@,break@,endif@,loop@,exit@

$colon '忽略空白字符',忽略空白字符@
dw  do@,读取字符@,AAs@,空格?@,如果是@,loop@,endif@,左括号?@,如果是@,忽略注释@,loop@,SS@,break@,exit@

$colon '冒号?',冒号?@
dw  push@,58,EE@,exit@

$colon '复制字符>',复制字符L@
dw  over@,c@@,储存字符@,AAs@,exit@

$colon '复制字符<',复制字符R@
dw  swap@,复制字符L@,swap@,exit@

$colon '复制词名>',复制词名L@
dw  do@,over@,c@@,空格?@,如果是@,复制字符L@,break@,drop@,复制字符L@,loop@,exit@

$colon '复制词名<',复制词名R@
dw  swap@,复制词名L@,swap@

$colon '词头长+',词头长A@
dw  push@,2,A@,exit@

$colon '连接词头',连接词头@
dw  push@,连接词头@,Q@,over@,!@,词头长A@,exit@

$colon '分号?',分号?@
dw  push@,59,对比字符@,exit@

$colon '编入新词条',编入新词条@
dw  swaps@,over@,!@,cellA@,swap@,exit@

$colon '结束分解',结束分解@
dw  push@,exit@,编入新词条@,drop@,exit@

$colon '转换成小写字母',转换成小写字母@
dw  push@,20h,or@,exit@

$colon '转换成大写字母',转换成大写字母@
dw  push@,0dfh,and@,exit@

$colon '0-9?',AS9?@
dw  dup@,push@,48,uR@,if@,FALSE@,exit@,dup@,push@,57,uL@,if@,FALSE@,else@,TRUE@,exit@

$colon 'A-F?',ASF?@
dw  dup@,转换成大写字母@,dup@,push@,65,uR@,if@,setF@,exit@,dup@,push@,70,uL@,if@,setF@,else@,setT@,exit@

$colon '16进制数字?',B6进制数字?@
dw  AS9?@,如果是@,setT@,exit@,ASF?@,如果是@,setT@,否则@,FALSE@,exit@

$colon '16进制尾标记?',B6进制尾标记?@
dw  空格?@,如果不是@,setF2@,exit@,drop@,push@,16,TRUE@,exit@

$colon '16进制?',B6进制?@
dw  AA@,do@,读取字符@,AAs@,B6进制数字?@,如果不是@,B6进制尾标记?@,break@,loop@,exit@

$colon '负号?',负号?@
dw  push@,45,EE@,exit@

$colon '10进制尾标记?',B0进制尾标记?@
dw  空格?@,如果不是@,setF2@,exit@,drop@,push@,10,TRUE@,exit@

$colon '10进制?',B0进制?@
dw  读取字符@,负号?@,如果是@,AA@,endif@,do@,读取字符@,AAs@,AS9?@,如果不是@,B0进制尾标记?@,break@,drop@,loop@,exit@

$colon '美元号?',美元号?@
dw  push@,36,EE@,exit@

$colon '数值?',数值?@
dw  读取字符@,美元号?@,如果是@,B6进制?@,否则@,B0进制?@,exit@

$colon '.word',Jword@
dw  do@,读取字符@,AAs@,空格?@,如果不是@,emit@,loop@,break@,exit@

$colon '编译错误',编译错误@
dw  JY@
db '[',0
dw  Jword@,JY@
db ']?',0
dw  cr@,_resetStack@,exit@

$colon '转换成数字0-9',转换成数字0S9@
dw  push@,48,S@,exit@

$colon '转换成数字10-15',转换成数字10S15@
dw  转换成大写字母@,push@,55,S@,exit@

$colon '字符转换成数值',字符转换成数值@
dw  AS9?@,case@,转换成数字0S9@,ASF?@,case@,转换成数字10S15@,drop@,push@,0,exit@

$colon '2drops',Cdrops@
dw  drops@,drops@,exit@

$colon '进制转换',进制转换@
dw  push@,0,do@,over@,c@@,空格?@,如果是@,Cdrops@,break@,Lr@,Lr@,over@,rL@,M@,rL@,字符转换成数值@,A@,AAs@,loop@,exit@

$colon '负号处理',负号处理@
dw  c@@,负号?@,如果是@,negate@,endif@,exit@

$colon '转换成数值',转换成数值@
dw  over@,进制转换@,over@,负号处理@,exit@

$colon '没找到该词',没找到该词@
dw  push@,push@,编入新词条@,dup@,数值?@,如果不是@,编译错误@,exit@,转换成数值@,编入新词条@,exit@

$colon '词名相同?',词名相同?@
dw  do@,over@,c@@,over@,c@@,!E@,if@,setF2@,break@,读取字符@,空格?@,如果是@,setT2@,break@,drop@,AA@,AAs@,loop@,exit@

$colon '词典下一词目',词典下一词目@
dw  cellS@,Q@,exit@

$colon '移到单词尾空格外',移到单词尾空格外@
dw  do@,读取字符@,AAs@,空格?@,如果是@,break@,endif@,drop@,loop@,exit@

$colon '该词执行地址',该词执行地址@
dw  移到单词尾空格外@,exit@

$colon '编译该词',编译该词@
dw  该词执行地址@,编入新词条@,exit@

$colon '查找单词',查找单词@
dw  do@,词典下一词目@,dup?@,if0@,没找到该词@,break@,Cdup@,词名相同?@,如果是@,编译该词@,break@,loop@,exit@

$colon '下个单词',下个单词@
dw  移到单词尾空格外@,忽略空白字符@,exit@

$colon '字串尾标记?',字串尾标记?@
dw  双引号?@,如果不是@,setF@,exit@,AA@,读取字符@,空格?@,如果是@,TRUE@,exit@,SSs@,setF@,exit@

$colon '标记字串尾0',标记字串尾0@
dw  push@,0,储存字符@,exit@

$colon '标记字串尾',标记字串尾@
dw  swap@,标记字串尾0@,swap@,忽略空白字符@,exit@

$colon '编译成字串',编译成字串@
dw  AA@,do@,读取字符@,字串尾标记?@,如果是@,标记字串尾@,break@,复制字符R@,loop@,exit@

$colon '分解语句',分解语句@
dw  do@,读取字符@,分号?@,如果是@,结束分解@,break@,双引号?@,如果是@,编译成字串@,loop@,drop@,词典目录尾@,查找单词@,下个单词@,loop@,exit@

$colon '=',E@
dw  r@@,Q@,词头长A@,cellA@,!@,rL@,cellA@,Lr@,exit@

$colon '更新词典目录尾',更新词典目录尾@
dw  E@,词典目录尾@,exit@

$colon '词典扩充',词典扩充@
dw  词典目录尾@,over@,!@,cellA@,更新词典目录尾@,exit@

$colon '新词条位置',新词条位置@
dw  词典目录尾@,exit@

$colon '编译模式',编译模式@
dw  AA@,忽略空白字符@,新词条位置@,复制词名L@,连接词头@,swap@,忽略空白字符@,分解语句@,词典扩充@,exit@

$colon '执行临时词',执行临时词@
dw  drop@,新词条位置@,execute@,exit@

$colon '解释模式',解释模式@
dw  新词条位置@,连接词头@,swap@,分解语句@,执行临时词@,exit@

$colon '编译执行',编译执行@
dw  缓冲区定位@,dup@,文本预处理@,忽略空白字符@,读取字符@,冒号?@,如果是@,编译模式@,否则@,解释模式@,exit@

$colon '命令行',命令行@
dw  do@,提示符@,输入命令@,编译执行@,cr@,loop@,exit@

$colon '余数分解',余数分解@
dw  do@,push@,10,Dmod@,push@,48,A@,swap@,dup@,if0@,drop@,break@,loop@,exit@

$colon '打印堆栈字串',打印堆栈字串@
dw  do@,dup@,if0@,drop@,break@,emit@,loop@,exit@

$colon '.abs',Jabs@
dw  push@,0,swap@,余数分解@,打印堆栈字串@,exit@

$colon '负数处理',负数处理@
dw  dup@,negate?@,如果不是@,exit@,endif@,negate@,push@,45,emit@,exit@

$colon '.',J@
dw  负数处理@,Jabs@,space@,exit@

$colon '显示堆栈单元',显示堆栈单元@
dw  sp@@,push@,DSP,cellS@,do@,Cdup@,EE@,if@,Cdrop@,break@,cellS@,dup@,Q@,J@,loop@,exit@

$colon '.s',Js@
dw  显示堆栈单元@,JY@
db ' <TOP]',0
dw  exit@