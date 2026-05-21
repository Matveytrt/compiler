
binary/test.bin:     file format binary


Disassembly of section .data:

00400078 <.data+0x78>:
  400078:	e8 0f 00 00 00       	call   0x40008c
  40007d:	48                   	dec    eax
  40007e:	b8 3c 00 00 00       	mov    eax,0x3c
  400083:	00 00                	add    BYTE PTR [eax],al
  400085:	00 00                	add    BYTE PTR [eax],al
  400087:	48                   	dec    eax
  400088:	31 ff                	xor    edi,edi
  40008a:	0f 05                	syscall
  40008c:	55                   	push   ebp
  40008d:	48                   	dec    eax
  40008e:	89 e5                	mov    ebp,esp
  400090:	48                   	dec    eax
  400091:	83 ec 10             	sub    esp,0x10
  400094:	48                   	dec    eax
  400095:	b8 05 00 00 00       	mov    eax,0x5
  40009a:	00 00                	add    BYTE PTR [eax],al
  40009c:	00 00                	add    BYTE PTR [eax],al
  40009e:	50                   	push   eax
  40009f:	58                   	pop    eax
  4000a0:	48                   	dec    eax
  4000a1:	b9 f8 ff ff ff       	mov    ecx,0xfffffff8
  4000a6:	ff                   	(bad)
  4000a7:	ff                   	(bad)
  4000a8:	ff                   	(bad)
  4000a9:	ff 48 89             	dec    DWORD PTR [eax-0x77]
  4000ac:	45                   	inc    ebp
  4000ad:	f8                   	clc
  4000ae:	48                   	dec    eax
  4000af:	b9 f8 ff ff ff       	mov    ecx,0xfffffff8
  4000b4:	ff                   	(bad)
  4000b5:	ff                   	(bad)
  4000b6:	ff                   	(bad)
  4000b7:	ff 48 8b             	dec    DWORD PTR [eax-0x75]
  4000ba:	45                   	inc    ebp
  4000bb:	f8                   	clc
  4000bc:	50                   	push   eax
  4000bd:	e8 2a 00 00 00       	call   0x4000ec
  4000c2:	48                   	dec    eax
  4000c3:	83 c4 08             	add    esp,0x8
  4000c6:	50                   	push   eax
  4000c7:	58                   	pop    eax
  4000c8:	48                   	dec    eax
  4000c9:	b9 f0 ff ff ff       	mov    ecx,0xfffffff0
  4000ce:	ff                   	(bad)
  4000cf:	ff                   	(bad)
  4000d0:	ff                   	(bad)
  4000d1:	ff 48 89             	dec    DWORD PTR [eax-0x77]
  4000d4:	45                   	inc    ebp
  4000d5:	f0 48                	lock dec eax
  4000d7:	b9 f0 ff ff ff       	mov    ecx,0xfffffff0
  4000dc:	ff                   	(bad)
  4000dd:	ff                   	(bad)
  4000de:	ff                   	(bad)
  4000df:	ff 48 8b             	dec    DWORD PTR [eax-0x75]
  4000e2:	45                   	inc    ebp
  4000e3:	f0 50                	lock push eax
  4000e5:	58                   	pop    eax
  4000e6:	48                   	dec    eax
  4000e7:	83 c4 10             	add    esp,0x10
  4000ea:	5d                   	pop    ebp
  4000eb:	c3                   	ret
  4000ec:	55                   	push   ebp
  4000ed:	48                   	dec    eax
  4000ee:	89 e5                	mov    ebp,esp
  4000f0:	48                   	dec    eax
  4000f1:	83 ec 08             	sub    esp,0x8
  4000f4:	48                   	dec    eax
  4000f5:	b9 10 00 00 00       	mov    ecx,0x10
  4000fa:	00 00                	add    BYTE PTR [eax],al
  4000fc:	00 00                	add    BYTE PTR [eax],al
  4000fe:	48                   	dec    eax
  4000ff:	8b 45 10             	mov    eax,DWORD PTR [ebp+0x10]
  400102:	50                   	push   eax
  400103:	48                   	dec    eax
  400104:	b8 0a 00 00 00       	mov    eax,0xa
  400109:	00 00                	add    BYTE PTR [eax],al
  40010b:	00 00                	add    BYTE PTR [eax],al
  40010d:	50                   	push   eax
  40010e:	48                   	dec    eax
  40010f:	b8 0a 00 00 00       	mov    eax,0xa
  400114:	00 00                	add    BYTE PTR [eax],al
  400116:	00 00                	add    BYTE PTR [eax],al
  400118:	50                   	push   eax
  400119:	59                   	pop    ecx
  40011a:	58                   	pop    eax
  40011b:	48                   	dec    eax
  40011c:	01 c1                	add    ecx,eax
  40011e:	50                   	push   eax
  40011f:	59                   	pop    ecx
  400120:	58                   	pop    eax
  400121:	48                   	dec    eax
  400122:	39 c1                	cmp    ecx,eax
  400124:	0f 94 c0             	sete   al
  400127:	0f b6 c0             	movzx  eax,al
  40012a:	50                   	push   eax
  40012b:	58                   	pop    eax
  40012c:	48                   	dec    eax
  40012d:	85 c0                	test   eax,eax
  40012f:	0f 84 1c 00 00 00    	je     0x400151
  400135:	48                   	dec    eax
  400136:	b8 14 00 00 00       	mov    eax,0x14
  40013b:	00 00                	add    BYTE PTR [eax],al
  40013d:	00 00                	add    BYTE PTR [eax],al
  40013f:	50                   	push   eax
  400140:	48                   	dec    eax
  400141:	b8 13 00 00 00       	mov    eax,0x13
  400146:	00 00                	add    BYTE PTR [eax],al
  400148:	00 00                	add    BYTE PTR [eax],al
  40014a:	50                   	push   eax
  40014b:	59                   	pop    ecx
  40014c:	58                   	pop    eax
  40014d:	48                   	dec    eax
  40014e:	01 c1                	add    ecx,eax
  400150:	50                   	push   eax
  400151:	48                   	dec    eax
  400152:	b8 1e 00 00 00       	mov    eax,0x1e
  400157:	00 00                	add    BYTE PTR [eax],al
  400159:	00 00                	add    BYTE PTR [eax],al
  40015b:	50                   	push   eax
  40015c:	48                   	dec    eax
  40015d:	b8 1d 00 00 00       	mov    eax,0x1d
  400162:	00 00                	add    BYTE PTR [eax],al
  400164:	00 00                	add    BYTE PTR [eax],al
  400166:	50                   	push   eax
  400167:	59                   	pop    ecx
  400168:	58                   	pop    eax
  400169:	48                   	dec    eax
  40016a:	01 c1                	add    ecx,eax
  40016c:	50                   	push   eax
  40016d:	58                   	pop    eax
  40016e:	48                   	dec    eax
  40016f:	b9 f8 ff ff ff       	mov    ecx,0xfffffff8
  400174:	ff                   	(bad)
  400175:	ff                   	(bad)
  400176:	ff                   	(bad)
  400177:	ff 48 89             	dec    DWORD PTR [eax-0x77]
  40017a:	45                   	inc    ebp
  40017b:	f8                   	clc
  40017c:	48                   	dec    eax
  40017d:	b9 10 00 00 00       	mov    ecx,0x10
  400182:	00 00                	add    BYTE PTR [eax],al
  400184:	00 00                	add    BYTE PTR [eax],al
  400186:	48                   	dec    eax
  400187:	8b 45 10             	mov    eax,DWORD PTR [ebp+0x10]
  40018a:	50                   	push   eax
  40018b:	48                   	dec    eax
  40018c:	b8 01 00 00 00       	mov    eax,0x1
  400191:	00 00                	add    BYTE PTR [eax],al
  400193:	00 00                	add    BYTE PTR [eax],al
  400195:	50                   	push   eax
  400196:	48                   	dec    eax
  400197:	b9 10 00 00 00       	mov    ecx,0x10
  40019c:	00 00                	add    BYTE PTR [eax],al
  40019e:	00 00                	add    BYTE PTR [eax],al
  4001a0:	48                   	dec    eax
  4001a1:	8b 45 10             	mov    eax,DWORD PTR [ebp+0x10]
  4001a4:	50                   	push   eax
  4001a5:	e8 aa aa aa aa       	call   0xaaeaac54
  4001aa:	48                   	dec    eax
  4001ab:	83 c4 08             	add    esp,0x8
  4001ae:	50                   	push   eax
  4001af:	59                   	pop    ecx
  4001b0:	58                   	pop    eax
  4001b1:	48                   	dec    eax
  4001b2:	01 c1                	add    ecx,eax
  4001b4:	50                   	push   eax
  4001b5:	58                   	pop    eax
  4001b6:	48                   	dec    eax
  4001b7:	b9 f8 ff ff ff       	mov    ecx,0xfffffff8
  4001bc:	ff                   	(bad)
  4001bd:	ff                   	(bad)
  4001be:	ff                   	(bad)
  4001bf:	ff 48 89             	dec    DWORD PTR [eax-0x77]
  4001c2:	45                   	inc    ebp
  4001c3:	f8                   	clc
  4001c4:	48                   	dec    eax
  4001c5:	b9 f8 ff ff ff       	mov    ecx,0xfffffff8
  4001ca:	ff                   	(bad)
  4001cb:	ff                   	(bad)
  4001cc:	ff                   	(bad)
  4001cd:	ff 48 8b             	dec    DWORD PTR [eax-0x75]
  4001d0:	45                   	inc    ebp
  4001d1:	f8                   	clc
  4001d2:	50                   	push   eax
  4001d3:	58                   	pop    eax
  4001d4:	48                   	dec    eax
  4001d5:	83 c4 08             	add    esp,0x8
  4001d8:	5d                   	pop    ebp
  4001d9:	c3                   	ret
