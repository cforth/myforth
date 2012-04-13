

$colon '..',..@
dw  dup@,Jword@,drop@,....@,_deadloop@,exit@

$colon '..1',..1@
dw  JY@
db 'test ',0
dw  exit@

$colon '..2',..2@
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

$colon '...',...@
dw  sameAs@,sameAs@,exit@

$colon '...',...@
dw  ...@,if@,exit@

$colon '....',....@
dw  ...@,if0@,exit@

$colon '..',..@
dw  ...@,else@,exit@

$colon 'bb',bb@
dw  ...@,bye@,exit@

$colon '....',....@
dw  dup@,c@@,exit@

$colon '.str',Jstr@
dw  do@,....@,AAs@,dup@,if0@,drop@,break@,emit@,loop@,exit@

$colon '."',JY@
dw  rL@,Jstr@,Lr@,exit@

$colon 'cr',cr@
dw  push@,13,emit@,push@,10,emit@,exit@

$colon '...',...@
dw  JY@
db '>>>',0
dw  exit@

$colon '.....',.....@
dw  push@,_coreEnd@,exit@

$colon '.....',.....@
dw  .....@,push@,512,A@,exit@

$colon '....',....@
dw  over@,EE@,if@,setT@,else@,FALSE@,exit@

$colon 'CR?',CR?@
dw  push@,13,....@,exit@

$colon 'LF?',LF?@
dw  push@,10,....@,exit@

$colon 'TRUE',TRUE@
dw  push@,0,not@,exit@

$colon 'FALSE',FALSE@
dw  push@,0,exit@

$colon '...?',...?@
dw  CR?@,...@,TRUE@,exit@,LF?@,exit@

$colon '....',....@
dw  over@,c!@,AA@,exit@

$colon '.....',.....@
dw  push@,32,....@,push@,59,....@,push@,0,swap@,c!@,exit@

$colon '....',....@
dw  .....@,cr@,exit@

$colon '...?',...?@
dw  push@,8,....@,exit@

$colon '....?',....?@
dw  .....@,over@,uR@,exit@

$colon 'space',space@
dw  push@,32,emit@,exit@

$colon '..',..@
dw  ....?@,....@,exit@,endif@,push@,8,dup@,emit@,space@,emit@,SS@,exit@

$colon '...?',...?@
dw  push@,34,....@,exit@

$colon '.....',.....@
dw  dup@,dup@,emit@,space@,emit@,exit@

$colon '.....',.....@
dw  Lr@,r@@,....@,push@,32,....@,rL@,....@,exit@

$colon '.....',.....@
dw  push@,34,.....@,.....@,exit@

$colon '....',....@
dw  .....@,do@,key@,...?@,...@,....@,break@,...?@,...@,..@,loop@,...?@,...@,.....@,loop@,dup@,emit@,....@,loop@,exit@

$colon '..?',..?@
dw  push@,32,....@,exit@

$colon 'tab?',tab?@
dw  push@,9,....@,exit@

$colon 'case',case@
dw  r@@,Q@,swap@,if@,execute@,break@,drop@,rL@,cellA@,Lr@,exit@

$colon '....?',....?@
dw  ..?@,case@,TRUE@,tab?@,case@,TRUE@,CR?@,case@,TRUE@,LF?@,exit@

$colon '.....',.....@
dw  push@,32,....@,exit@

$colon '.....',.....@
dw  do@,....@,dup@,if0@,Cdrop@,break@,....?@,...@,.....@,..@,drop@,AA@,loop@,exit@

$colon '...?',...?@
dw  push@,40,EE@,exit@

$colon '...?',...?@
dw  push@,41,EE@,exit@

$colon '....',....@
dw  do@,....@,AAs@,...?@,...@,break@,endif@,loop@,exit@

$colon '......',......@
dw  do@,....@,AAs@,..?@,...@,loop@,endif@,...?@,...@,....@,loop@,SS@,break@,exit@

$colon '..?',..?@
dw  push@,58,EE@,exit@

$colon '....>',....L@
dw  over@,c@@,....@,AAs@,exit@

$colon '....<',....R@
dw  swap@,....L@,swap@,exit@

$colon '....>',....L@
dw  do@,over@,c@@,..?@,...@,....L@,break@,drop@,....L@,loop@,exit@

$colon '....<',....R@
dw  swap@,....L@,swap@

$colon '...+',...A@
dw  push@,2,A@,exit@

$colon '....',....@
dw  push@,....@,Q@,over@,!@,...A@,exit@

$colon '..?',..?@
dw  push@,59,....@,exit@

$colon '.....',.....@
dw  swaps@,over@,!@,cellA@,swap@,exit@

$colon '....',....@
dw  push@,exit@,.....@,drop@,exit@

$colon '.......',.......@
dw  push@,20h,or@,exit@

$colon '.......',.......@
dw  push@,0dfh,and@,exit@

$colon '0-9?',AS9?@
dw  dup@,push@,48,uR@,if@,FALSE@,exit@,dup@,push@,57,uL@,if@,FALSE@,else@,TRUE@,exit@

$colon 'A-F?',ASF?@
dw  dup@,.......@,dup@,push@,65,uR@,if@,setF@,exit@,dup@,push@,70,uL@,if@,setF@,else@,setT@,exit@

$colon '16....?',B6....?@
dw  AS9?@,...@,setT@,exit@,ASF?@,...@,setT@,..@,FALSE@,exit@

$colon '16.....?',B6.....?@
dw  ..?@,....@,setF2@,exit@,drop@,push@,16,TRUE@,exit@

$colon '16..?',B6..?@
dw  AA@,do@,....@,AAs@,B6....?@,....@,B6.....?@,break@,loop@,exit@

$colon '..?',..?@
dw  push@,45,EE@,exit@

$colon '10.....?',B0.....?@
dw  ..?@,....@,setF2@,exit@,drop@,push@,10,TRUE@,exit@

$colon '10..?',B0..?@
dw  ....@,..?@,...@,AA@,endif@,do@,....@,AAs@,AS9?@,....@,B0.....?@,break@,drop@,loop@,exit@

$colon '...?',...?@
dw  push@,36,EE@,exit@

$colon '..?',..?@
dw  ....@,...?@,...@,B6..?@,..@,B0..?@,exit@

$colon '.word',Jword@
dw  do@,....@,AAs@,..?@,....@,emit@,loop@,break@,exit@

$colon '....',....@
dw  JY@
db '[',0
dw  Jword@,JY@
db ']?',0
dw  cr@,_resetStack@,exit@

$colon '.....0-9',.....0S9@
dw  push@,48,S@,exit@

$colon '.....10-15',.....10S15@
dw  .......@,push@,55,S@,exit@

$colon '.......',.......@
dw  AS9?@,case@,.....0S9@,ASF?@,case@,.....10S15@,drop@,push@,0,exit@

$colon '2drops',Cdrops@
dw  drops@,drops@,exit@

$colon '....',....@
dw  push@,0,do@,over@,c@@,..?@,...@,Cdrops@,break@,Lr@,Lr@,over@,rL@,M@,rL@,.......@,A@,AAs@,loop@,exit@

$colon '....',....@
dw  c@@,..?@,...@,negate@,endif@,exit@

$colon '.....',.....@
dw  over@,....@,over@,....@,exit@

$colon '.....',.....@
dw  push@,push@,.....@,dup@,..?@,....@,....@,exit@,.....@,.....@,exit@

$colon '....?',....?@
dw  do@,over@,c@@,over@,c@@,!E@,if@,setF2@,break@,....@,..?@,...@,setT2@,break@,drop@,AA@,AAs@,loop@,exit@

$colon '......',......@
dw  cellS@,Q@,exit@

$colon '........',........@
dw  do@,....@,AAs@,..?@,...@,break@,endif@,drop@,loop@,exit@

$colon '......',......@
dw  ........@,exit@

$colon '....',....@
dw  ......@,.....@,exit@

$colon '....',....@
dw  do@,......@,dup?@,if0@,.....@,break@,Cdup@,....?@,...@,....@,break@,loop@,exit@

$colon '....',....@
dw  ........@,......@,exit@

$colon '.....?',.....?@
dw  ...?@,....@,setF@,exit@,AA@,....@,..?@,...@,TRUE@,exit@,SSs@,setF@,exit@

$colon '.....0',.....0@
dw  push@,0,....@,exit@

$colon '.....',.....@
dw  swap@,.....0@,swap@,......@,exit@

$colon '.....',.....@
dw  AA@,do@,....@,.....?@,...@,.....@,break@,....R@,loop@,exit@

$colon '....',....@
dw  do@,....@,..?@,...@,....@,break@,...?@,...@,.....@,loop@,drop@,.....@,....@,....@,loop@,exit@

$colon '=',E@
dw  r@@,Q@,...A@,cellA@,!@,rL@,cellA@,Lr@,exit@

$colon '.......',.......@
dw  E@,.....@,exit@

$colon '....',....@
dw  .....@,over@,!@,cellA@,.......@,exit@

$colon '.....',.....@
dw  .....@,exit@

$colon '....',....@
dw  AA@,......@,.....@,....L@,....@,swap@,......@,....@,....@,exit@

$colon '.....',.....@
dw  drop@,.....@,execute@,exit@

$colon '....',....@
dw  .....@,....@,swap@,....@,.....@,exit@

$colon '....',....@
dw  .....@,dup@,.....@,......@,....@,..?@,...@,....@,..@,....@,exit@

$colon '...',...@
dw  do@,...@,....@,....@,cr@,loop@,exit@

$colon '....',....@
dw  do@,push@,10,Dmod@,push@,48,A@,swap@,dup@,if0@,drop@,break@,loop@,exit@

$colon '......',......@
dw  do@,dup@,if0@,drop@,break@,emit@,loop@,exit@

$colon '.abs',Jabs@
dw  push@,0,swap@,....@,......@,exit@

$colon '....',....@
dw  dup@,negate?@,....@,exit@,endif@,negate@,push@,45,emit@,exit@

$colon '.',J@
dw  ....@,Jabs@,space@,exit@

$colon '......',......@
dw  sp@@,push@,DSP,cellS@,do@,Cdup@,EE@,if@,Cdrop@,break@,cellS@,dup@,Q@,J@,loop@,exit@

$colon '.s',Js@
dw  ......@,JY@
db ' <TOP]',0
dw  exit@
