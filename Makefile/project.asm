
./src/main.o:     file format elf64-x86-64
./src/main.o
architecture: i386:x86-64, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x0000000000000000

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         00000015  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  00000055  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  00000055  2**0
                  ALLOC
  3 .debug_info   0000009f  0000000000000000  0000000000000000  00000055  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  4 .debug_abbrev 00000042  0000000000000000  0000000000000000  000000f4  2**0
                  CONTENTS, READONLY, DEBUGGING
  5 .debug_aranges 00000030  0000000000000000  0000000000000000  00000136  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  6 .debug_line   0000003e  0000000000000000  0000000000000000  00000166  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  7 .debug_str    0000011a  0000000000000000  0000000000000000  000001a4  2**0
                  CONTENTS, READONLY, DEBUGGING
  8 .comment      00000035  0000000000000000  0000000000000000  000002be  2**0
                  CONTENTS, READONLY
  9 .note.GNU-stack 00000000  0000000000000000  0000000000000000  000002f3  2**0
                  CONTENTS, READONLY
 10 .eh_frame     00000038  0000000000000000  0000000000000000  000002f8  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000 main.c
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 l    d  .data	0000000000000000 .data
0000000000000000 l    d  .bss	0000000000000000 .bss
0000000000000000 l    d  .debug_info	0000000000000000 .debug_info
0000000000000000 l    d  .debug_abbrev	0000000000000000 .debug_abbrev
0000000000000000 l    d  .debug_aranges	0000000000000000 .debug_aranges
0000000000000000 l    d  .debug_line	0000000000000000 .debug_line
0000000000000000 l    d  .debug_str	0000000000000000 .debug_str
0000000000000000 l    d  .note.GNU-stack	0000000000000000 .note.GNU-stack
0000000000000000 l    d  .eh_frame	0000000000000000 .eh_frame
0000000000000000 l    d  .comment	0000000000000000 .comment
0000000000000000 g     F .text	0000000000000015 main
0000000000000000         *UND*	0000000000000000 project_1_report



Disassembly of section .text:

0000000000000000 <main>:
#include <stdlib.h>
#include <stdint.h>
#include "project_1.h"

int main()
{
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
  project_1_report();
   4:	b8 00 00 00 00       	mov    $0x0,%eax
   9:	e8 00 00 00 00       	callq  e <main+0xe>
			a: R_X86_64_PC32	project_1_report-0x4
   e:	b8 00 00 00 00       	mov    $0x0,%eax
}
  13:	5d                   	pop    %rbp
  14:	c3                   	retq   

./src/data.o:     file format elf64-x86-64
./src/data.o
architecture: i386:x86-64, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x0000000000000000

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         000002cf  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  0000030f  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  0000030f  2**0
                  ALLOC
  3 .rodata       0000003f  0000000000000000  0000000000000000  0000030f  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .debug_info   000002db  0000000000000000  0000000000000000  0000034e  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  5 .debug_abbrev 00000101  0000000000000000  0000000000000000  00000629  2**0
                  CONTENTS, READONLY, DEBUGGING
  6 .debug_aranges 00000030  0000000000000000  0000000000000000  0000072a  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  7 .debug_line   000000c6  0000000000000000  0000000000000000  0000075a  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  8 .debug_str    00000195  0000000000000000  0000000000000000  00000820  2**0
                  CONTENTS, READONLY, DEBUGGING
  9 .comment      00000035  0000000000000000  0000000000000000  000009b5  2**0
                  CONTENTS, READONLY
 10 .note.GNU-stack 00000000  0000000000000000  0000000000000000  000009ea  2**0
                  CONTENTS, READONLY
 11 .eh_frame     000000b8  0000000000000000  0000000000000000  000009f0  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000 data.c
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 l    d  .data	0000000000000000 .data
0000000000000000 l    d  .bss	0000000000000000 .bss
0000000000000000 l    d  .rodata	0000000000000000 .rodata
0000000000000000 l    d  .debug_info	0000000000000000 .debug_info
0000000000000000 l    d  .debug_abbrev	0000000000000000 .debug_abbrev
0000000000000000 l    d  .debug_aranges	0000000000000000 .debug_aranges
0000000000000000 l    d  .debug_line	0000000000000000 .debug_line
0000000000000000 l    d  .debug_str	0000000000000000 .debug_str
0000000000000000 l    d  .note.GNU-stack	0000000000000000 .note.GNU-stack
0000000000000000 l    d  .eh_frame	0000000000000000 .eh_frame
0000000000000000 l    d  .comment	0000000000000000 .comment
0000000000000000 g     F .text	0000000000000088 my_itoa
0000000000000000         *UND*	0000000000000000 strlen
0000000000000000         *UND*	0000000000000000 printf
0000000000000088 g     F .text	00000000000000de my_atoi
0000000000000000         *UND*	0000000000000000 __stack_chk_fail
0000000000000166 g     F .text	000000000000004b dump_memory
00000000000001b1 g     F .text	000000000000008f big_to_little
0000000000000240 g     F .text	000000000000008f little_to_big



Disassembly of section .text:

0000000000000000 <my_itoa>:
#include "data.h"



int8_t * my_itoa(int8_t *str,int32_t data,int32_t base)
{	
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 30          	sub    $0x30,%rsp
   8:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
   c:	89 75 d4             	mov    %esi,-0x2c(%rbp)
   f:	89 55 d0             	mov    %edx,-0x30(%rbp)
   int remainder,n; 
   long binary = 0, i = 1;
  12:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  19:	00 
  1a:	48 c7 45 f0 01 00 00 	movq   $0x1,-0x10(%rbp)
  21:	00 
   int32_t len= strlen(str);
  22:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  26:	48 89 c7             	mov    %rax,%rdi
  29:	e8 00 00 00 00       	callq  2e <my_itoa+0x2e>
			2a: R_X86_64_PC32	strlen-0x4
  2e:	89 45 ec             	mov    %eax,-0x14(%rbp)
   for (i=0; i<len; i++)
  31:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
  38:	00 
  39:	eb 2b                	jmp    66 <my_itoa+0x66>
   {
     char b =(char)*(str+i);
  3b:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  3f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  43:	48 01 d0             	add    %rdx,%rax
  46:	0f b6 00             	movzbl (%rax),%eax
  49:	88 45 eb             	mov    %al,-0x15(%rbp)
     printf("\n%c",b);
  4c:	0f be 45 eb          	movsbl -0x15(%rbp),%eax
  50:	89 c6                	mov    %eax,%esi
  52:	bf 00 00 00 00       	mov    $0x0,%edi
			53: R_X86_64_32	.rodata
  57:	b8 00 00 00 00       	mov    $0x0,%eax
  5c:	e8 00 00 00 00       	callq  61 <my_itoa+0x61>
			5d: R_X86_64_PC32	printf-0x4
int8_t * my_itoa(int8_t *str,int32_t data,int32_t base)
{	
   int remainder,n; 
   long binary = 0, i = 1;
   int32_t len= strlen(str);
   for (i=0; i<len; i++)
  61:	48 83 45 f0 01       	addq   $0x1,-0x10(%rbp)
  66:	8b 45 ec             	mov    -0x14(%rbp),%eax
  69:	48 98                	cltq   
  6b:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  6f:	7f ca                	jg     3b <my_itoa+0x3b>
   {
     char b =(char)*(str+i);
     printf("\n%c",b);
   }
   printf("\ndecimal value%x",data);
  71:	8b 45 d4             	mov    -0x2c(%rbp),%eax
  74:	89 c6                	mov    %eax,%esi
  76:	bf 00 00 00 00       	mov    $0x0,%edi
			77: R_X86_64_32	.rodata+0x4
  7b:	b8 00 00 00 00       	mov    $0x0,%eax
  80:	e8 00 00 00 00       	callq  85 <my_itoa+0x85>
			81: R_X86_64_PC32	printf-0x4
}
  85:	90                   	nop
  86:	c9                   	leaveq 
  87:	c3                   	retq   

0000000000000088 <my_atoi>:

   
int32_t my_atoi(int8_t*src)
{
  88:	55                   	push   %rbp
  89:	48 89 e5             	mov    %rsp,%rbp
  8c:	48 81 ec c0 01 00 00 	sub    $0x1c0,%rsp
  93:	48 89 bd 48 fe ff ff 	mov    %rdi,-0x1b8(%rbp)
  9a:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  a1:	00 00 
  a3:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  a7:	31 c0                	xor    %eax,%eax
  int32_t *dst,x[100];
  dst=x; 
  a9:	48 8d 85 60 fe ff ff 	lea    -0x1a0(%rbp),%rax
  b0:	48 89 85 58 fe ff ff 	mov    %rax,-0x1a8(%rbp)
  int32_t len = strlen(src); 
  b7:	48 8b 85 48 fe ff ff 	mov    -0x1b8(%rbp),%rax
  be:	48 89 c7             	mov    %rax,%rdi
  c1:	e8 00 00 00 00       	callq  c6 <my_atoi+0x3e>
			c2: R_X86_64_PC32	strlen-0x4
  c6:	89 85 54 fe ff ff    	mov    %eax,-0x1ac(%rbp)
  for(int i=0;i<len;i++)
  cc:	c7 85 50 fe ff ff 00 	movl   $0x0,-0x1b0(%rbp)
  d3:	00 00 00 
  d6:	eb 69                	jmp    141 <my_atoi+0xb9>
  {
     *(dst+i)=(int32_t)*(src+i);
  d8:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
  de:	48 98                	cltq   
  e0:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
  e7:	00 
  e8:	48 8b 85 58 fe ff ff 	mov    -0x1a8(%rbp),%rax
  ef:	48 01 c2             	add    %rax,%rdx
  f2:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
  f8:	48 63 c8             	movslq %eax,%rcx
  fb:	48 8b 85 48 fe ff ff 	mov    -0x1b8(%rbp),%rax
 102:	48 01 c8             	add    %rcx,%rax
 105:	0f b6 00             	movzbl (%rax),%eax
 108:	0f be c0             	movsbl %al,%eax
 10b:	89 02                	mov    %eax,(%rdx)
     printf("%d",*(dst+i));
 10d:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
 113:	48 98                	cltq   
 115:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
 11c:	00 
 11d:	48 8b 85 58 fe ff ff 	mov    -0x1a8(%rbp),%rax
 124:	48 01 d0             	add    %rdx,%rax
 127:	8b 00                	mov    (%rax),%eax
 129:	89 c6                	mov    %eax,%esi
 12b:	bf 00 00 00 00       	mov    $0x0,%edi
			12c: R_X86_64_32	.rodata+0x15
 130:	b8 00 00 00 00       	mov    $0x0,%eax
 135:	e8 00 00 00 00       	callq  13a <my_atoi+0xb2>
			136: R_X86_64_PC32	printf-0x4
int32_t my_atoi(int8_t*src)
{
  int32_t *dst,x[100];
  dst=x; 
  int32_t len = strlen(src); 
  for(int i=0;i<len;i++)
 13a:	83 85 50 fe ff ff 01 	addl   $0x1,-0x1b0(%rbp)
 141:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
 147:	3b 85 54 fe ff ff    	cmp    -0x1ac(%rbp),%eax
 14d:	7c 89                	jl     d8 <my_atoi+0x50>
  {
     *(dst+i)=(int32_t)*(src+i);
     printf("%d",*(dst+i));
  }
}
 14f:	90                   	nop
 150:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
 154:	64 48 33 34 25 28 00 	xor    %fs:0x28,%rsi
 15b:	00 00 
 15d:	74 05                	je     164 <my_atoi+0xdc>
 15f:	e8 00 00 00 00       	callq  164 <my_atoi+0xdc>
			160: R_X86_64_PC32	__stack_chk_fail-0x4
 164:	c9                   	leaveq 
 165:	c3                   	retq   

0000000000000166 <dump_memory>:


void dump_memory(uint8_t *start, uint32_t length)
   {
 166:	55                   	push   %rbp
 167:	48 89 e5             	mov    %rsp,%rbp
 16a:	48 83 ec 20          	sub    $0x20,%rsp
 16e:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
 172:	89 75 e4             	mov    %esi,-0x1c(%rbp)
      for(int i=0;i<length;i++)
 175:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
 17c:	eb 28                	jmp    1a6 <dump_memory+0x40>
      printf("The hex output is %x\n", *(start+i));
 17e:	8b 45 fc             	mov    -0x4(%rbp),%eax
 181:	48 63 d0             	movslq %eax,%rdx
 184:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
 188:	48 01 d0             	add    %rdx,%rax
 18b:	0f b6 00             	movzbl (%rax),%eax
 18e:	0f b6 c0             	movzbl %al,%eax
 191:	89 c6                	mov    %eax,%esi
 193:	bf 00 00 00 00       	mov    $0x0,%edi
			194: R_X86_64_32	.rodata+0x18
 198:	b8 00 00 00 00       	mov    $0x0,%eax
 19d:	e8 00 00 00 00       	callq  1a2 <dump_memory+0x3c>
			19e: R_X86_64_PC32	printf-0x4
}


void dump_memory(uint8_t *start, uint32_t length)
   {
      for(int i=0;i<length;i++)
 1a2:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
 1a6:	8b 45 fc             	mov    -0x4(%rbp),%eax
 1a9:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
 1ac:	72 d0                	jb     17e <dump_memory+0x18>
      printf("The hex output is %x\n", *(start+i));
   }
 1ae:	90                   	nop
 1af:	c9                   	leaveq 
 1b0:	c3                   	retq   

00000000000001b1 <big_to_little>:
  

uint32_t big_to_little(uint32_t data)
{
 1b1:	55                   	push   %rbp
 1b2:	48 89 e5             	mov    %rsp,%rbp
 1b5:	48 83 ec 30          	sub    $0x30,%rsp
 1b9:	89 7d dc             	mov    %edi,-0x24(%rbp)
 1bc:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
 1c3:	00 00 
 1c5:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
 1c9:	31 c0                	xor    %eax,%eax
   uint32_t m=100;
 1cb:	c7 45 ec 64 00 00 00 	movl   $0x64,-0x14(%rbp)
   uint32_t *z= NULL;
 1d2:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
 1d9:	00 
   z=&m;
 1da:	48 8d 45 ec          	lea    -0x14(%rbp),%rax
 1de:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
   *z=(data & 0xff)<<24|(data & 0xff00)<<8|(data & 0xff0000)>>8|(data & 0xff000000)>>24;
 1e2:	8b 45 dc             	mov    -0x24(%rbp),%eax
 1e5:	c1 e0 18             	shl    $0x18,%eax
 1e8:	89 c2                	mov    %eax,%edx
 1ea:	8b 45 dc             	mov    -0x24(%rbp),%eax
 1ed:	25 00 ff 00 00       	and    $0xff00,%eax
 1f2:	c1 e0 08             	shl    $0x8,%eax
 1f5:	09 c2                	or     %eax,%edx
 1f7:	8b 45 dc             	mov    -0x24(%rbp),%eax
 1fa:	25 00 00 ff 00       	and    $0xff0000,%eax
 1ff:	c1 e8 08             	shr    $0x8,%eax
 202:	09 c2                	or     %eax,%edx
 204:	8b 45 dc             	mov    -0x24(%rbp),%eax
 207:	c1 e8 18             	shr    $0x18,%eax
 20a:	09 c2                	or     %eax,%edx
 20c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 210:	89 10                	mov    %edx,(%rax)
   printf("CONVERSION IS %x",*z);
 212:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 216:	8b 00                	mov    (%rax),%eax
 218:	89 c6                	mov    %eax,%esi
 21a:	bf 00 00 00 00       	mov    $0x0,%edi
			21b: R_X86_64_32	.rodata+0x2e
 21f:	b8 00 00 00 00       	mov    $0x0,%eax
 224:	e8 00 00 00 00       	callq  229 <big_to_little+0x78>
			225: R_X86_64_PC32	printf-0x4
   

}
 229:	90                   	nop
 22a:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
 22e:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
 235:	00 00 
 237:	74 05                	je     23e <big_to_little+0x8d>
 239:	e8 00 00 00 00       	callq  23e <big_to_little+0x8d>
			23a: R_X86_64_PC32	__stack_chk_fail-0x4
 23e:	c9                   	leaveq 
 23f:	c3                   	retq   

0000000000000240 <little_to_big>:


uint32_t little_to_big(uint32_t data)
{ 
 240:	55                   	push   %rbp
 241:	48 89 e5             	mov    %rsp,%rbp
 244:	48 83 ec 30          	sub    $0x30,%rsp
 248:	89 7d dc             	mov    %edi,-0x24(%rbp)
 24b:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
 252:	00 00 
 254:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
 258:	31 c0                	xor    %eax,%eax

   int m=100;
 25a:	c7 45 ec 64 00 00 00 	movl   $0x64,-0x14(%rbp)
   uint32_t *y= NULL;
 261:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
 268:	00 
   y=&m;
 269:	48 8d 45 ec          	lea    -0x14(%rbp),%rax
 26d:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
   *y=(data & 0xff)<<24|(data & 0xff00)<<8|(data & 0xff0000)>>8|(data & 0xff000000)>>24;
 271:	8b 45 dc             	mov    -0x24(%rbp),%eax
 274:	c1 e0 18             	shl    $0x18,%eax
 277:	89 c2                	mov    %eax,%edx
 279:	8b 45 dc             	mov    -0x24(%rbp),%eax
 27c:	25 00 ff 00 00       	and    $0xff00,%eax
 281:	c1 e0 08             	shl    $0x8,%eax
 284:	09 c2                	or     %eax,%edx
 286:	8b 45 dc             	mov    -0x24(%rbp),%eax
 289:	25 00 00 ff 00       	and    $0xff0000,%eax
 28e:	c1 e8 08             	shr    $0x8,%eax
 291:	09 c2                	or     %eax,%edx
 293:	8b 45 dc             	mov    -0x24(%rbp),%eax
 296:	c1 e8 18             	shr    $0x18,%eax
 299:	09 c2                	or     %eax,%edx
 29b:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 29f:	89 10                	mov    %edx,(%rax)
   printf("CONVERSION IS %x",*y);
 2a1:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
 2a5:	8b 00                	mov    (%rax),%eax
 2a7:	89 c6                	mov    %eax,%esi
 2a9:	bf 00 00 00 00       	mov    $0x0,%edi
			2aa: R_X86_64_32	.rodata+0x2e
 2ae:	b8 00 00 00 00       	mov    $0x0,%eax
 2b3:	e8 00 00 00 00       	callq  2b8 <little_to_big+0x78>
			2b4: R_X86_64_PC32	printf-0x4


}
 2b8:	90                   	nop
 2b9:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
 2bd:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
 2c4:	00 00 
 2c6:	74 05                	je     2cd <little_to_big+0x8d>
 2c8:	e8 00 00 00 00       	callq  2cd <little_to_big+0x8d>
			2c9: R_X86_64_PC32	__stack_chk_fail-0x4
 2cd:	c9                   	leaveq 
 2ce:	c3                   	retq   

./src/project_1.o:     file format elf64-x86-64
./src/project_1.o
architecture: i386:x86-64, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x0000000000000000

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         000000f9  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  00000139  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  00000139  2**0
                  ALLOC
  3 .rodata       00000004  0000000000000000  0000000000000000  00000139  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .debug_info   00000136  0000000000000000  0000000000000000  0000013d  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  5 .debug_abbrev 0000008d  0000000000000000  0000000000000000  00000273  2**0
                  CONTENTS, READONLY, DEBUGGING
  6 .debug_aranges 00000030  0000000000000000  0000000000000000  00000300  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  7 .debug_line   000000a1  0000000000000000  0000000000000000  00000330  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  8 .debug_str    00000132  0000000000000000  0000000000000000  000003d1  2**0
                  CONTENTS, READONLY, DEBUGGING
  9 .comment      00000035  0000000000000000  0000000000000000  00000503  2**0
                  CONTENTS, READONLY
 10 .note.GNU-stack 00000000  0000000000000000  0000000000000000  00000538  2**0
                  CONTENTS, READONLY
 11 .eh_frame     00000038  0000000000000000  0000000000000000  00000538  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000 project_1.c
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 l    d  .data	0000000000000000 .data
0000000000000000 l    d  .bss	0000000000000000 .bss
0000000000000000 l    d  .rodata	0000000000000000 .rodata
0000000000000000 l    d  .debug_info	0000000000000000 .debug_info
0000000000000000 l    d  .debug_abbrev	0000000000000000 .debug_abbrev
0000000000000000 l    d  .debug_aranges	0000000000000000 .debug_aranges
0000000000000000 l    d  .debug_line	0000000000000000 .debug_line
0000000000000000 l    d  .debug_str	0000000000000000 .debug_str
0000000000000000 l    d  .note.GNU-stack	0000000000000000 .note.GNU-stack
0000000000000000 l    d  .eh_frame	0000000000000000 .eh_frame
0000000000000000 l    d  .comment	0000000000000000 .comment
0000000000000000 g     F .text	00000000000000f9 project_1_report
0000000000000000         *UND*	0000000000000000 my_memzero
0000000000000000         *UND*	0000000000000000 my_memmove
0000000000000000         *UND*	0000000000000000 my_reverse
0000000000000000         *UND*	0000000000000000 printf
0000000000000000         *UND*	0000000000000000 __stack_chk_fail



Disassembly of section .text:

0000000000000000 <project_1_report>:
#include  <string.h>
#include "project_1.h"
#include  "memory.h"

void project_1_report()
{ 
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 50          	sub    $0x50,%rsp
   8:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
   f:	00 00 
  11:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  15:	31 c0                	xor    %eax,%eax
  int8_t a[32];
  int8_t *d;
  int8_t *e;
  int8_t *f;
  d=&a[0];
  17:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
  1b:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  e=&a[8];
  1f:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
  23:	48 83 c0 08          	add    $0x8,%rax
  27:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  f=&a[17];
  2b:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
  2f:	48 83 c0 11          	add    $0x11,%rax
  33:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  for(int i=0;i<16;i++)
  37:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
  3e:	eb 19                	jmp    59 <project_1_report+0x59>
  {
      *(d+i)=31+i;
  40:	8b 45 b0             	mov    -0x50(%rbp),%eax
  43:	48 63 d0             	movslq %eax,%rdx
  46:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  4a:	48 01 d0             	add    %rdx,%rax
  4d:	8b 55 b0             	mov    -0x50(%rbp),%edx
  50:	83 c2 1f             	add    $0x1f,%edx
  53:	88 10                	mov    %dl,(%rax)
  int8_t *e;
  int8_t *f;
  d=&a[0];
  e=&a[8];
  f=&a[17];
  for(int i=0;i<16;i++)
  55:	83 45 b0 01          	addl   $0x1,-0x50(%rbp)
  59:	83 7d b0 0f          	cmpl   $0xf,-0x50(%rbp)
  5d:	7e e1                	jle    40 <project_1_report+0x40>
  {
      *(d+i)=31+i;
 
  }
  my_memzero(e,24);
  5f:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  63:	be 18 00 00 00       	mov    $0x18,%esi
  68:	48 89 c7             	mov    %rax,%rdi
  6b:	e8 00 00 00 00       	callq  70 <project_1_report+0x70>
			6c: R_X86_64_PC32	my_memzero-0x4

  my_memmove(d,f,8);
  70:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  74:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  78:	ba 08 00 00 00       	mov    $0x8,%edx
  7d:	48 89 ce             	mov    %rcx,%rsi
  80:	48 89 c7             	mov    %rax,%rdi
  83:	e8 00 00 00 00       	callq  88 <project_1_report+0x88>
			84: R_X86_64_PC32	my_memmove-0x4
 
  my_memmove(e,d,16);
  88:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  8c:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  90:	ba 10 00 00 00       	mov    $0x10,%edx
  95:	48 89 ce             	mov    %rcx,%rsi
  98:	48 89 c7             	mov    %rax,%rdi
  9b:	e8 00 00 00 00       	callq  a0 <project_1_report+0xa0>
			9c: R_X86_64_PC32	my_memmove-0x4

  my_reverse(d,32);
  a0:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  a4:	be 20 00 00 00       	mov    $0x20,%esi
  a9:	48 89 c7             	mov    %rax,%rdi
  ac:	e8 00 00 00 00       	callq  b1 <project_1_report+0xb1>
			ad: R_X86_64_PC32	my_reverse-0x4
  for(int i=0;i<32;i++)
  b1:	c7 45 b4 00 00 00 00 	movl   $0x0,-0x4c(%rbp)
  b8:	eb 22                	jmp    dc <project_1_report+0xdc>
  printf("\n%d",a[i]);
  ba:	8b 45 b4             	mov    -0x4c(%rbp),%eax
  bd:	48 98                	cltq   
  bf:	0f b6 44 05 d0       	movzbl -0x30(%rbp,%rax,1),%eax
  c4:	0f be c0             	movsbl %al,%eax
  c7:	89 c6                	mov    %eax,%esi
  c9:	bf 00 00 00 00       	mov    $0x0,%edi
			ca: R_X86_64_32	.rodata
  ce:	b8 00 00 00 00       	mov    $0x0,%eax
  d3:	e8 00 00 00 00       	callq  d8 <project_1_report+0xd8>
			d4: R_X86_64_PC32	printf-0x4
  my_memmove(d,f,8);
 
  my_memmove(e,d,16);

  my_reverse(d,32);
  for(int i=0;i<32;i++)
  d8:	83 45 b4 01          	addl   $0x1,-0x4c(%rbp)
  dc:	83 7d b4 1f          	cmpl   $0x1f,-0x4c(%rbp)
  e0:	7e d8                	jle    ba <project_1_report+0xba>
  printf("\n%d",a[i]);
  }
  e2:	90                   	nop
  e3:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  e7:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  ee:	00 00 
  f0:	74 05                	je     f7 <project_1_report+0xf7>
  f2:	e8 00 00 00 00       	callq  f7 <project_1_report+0xf7>
			f3: R_X86_64_PC32	__stack_chk_fail-0x4
  f7:	c9                   	leaveq 
  f8:	c3                   	retq   

./src/memory.o:     file format elf64-x86-64
./src/memory.o
architecture: i386:x86-64, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x0000000000000000

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         00000257  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  00000297  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  00000297  2**0
                  ALLOC
  3 .rodata       00000018  0000000000000000  0000000000000000  00000297  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .debug_info   0000027a  0000000000000000  0000000000000000  000002af  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  5 .debug_abbrev 000000d8  0000000000000000  0000000000000000  00000529  2**0
                  CONTENTS, READONLY, DEBUGGING
  6 .debug_aranges 00000030  0000000000000000  0000000000000000  00000601  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  7 .debug_line   0000010e  0000000000000000  0000000000000000  00000631  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  8 .debug_str    00000164  0000000000000000  0000000000000000  0000073f  2**0
                  CONTENTS, READONLY, DEBUGGING
  9 .comment      00000035  0000000000000000  0000000000000000  000008a3  2**0
                  CONTENTS, READONLY
 10 .note.GNU-stack 00000000  0000000000000000  0000000000000000  000008d8  2**0
                  CONTENTS, READONLY
 11 .eh_frame     00000078  0000000000000000  0000000000000000  000008d8  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000 memory.c
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 l    d  .data	0000000000000000 .data
0000000000000000 l    d  .bss	0000000000000000 .bss
0000000000000000 l    d  .rodata	0000000000000000 .rodata
0000000000000000 l    d  .debug_info	0000000000000000 .debug_info
0000000000000000 l    d  .debug_abbrev	0000000000000000 .debug_abbrev
0000000000000000 l    d  .debug_aranges	0000000000000000 .debug_aranges
0000000000000000 l    d  .debug_line	0000000000000000 .debug_line
0000000000000000 l    d  .debug_str	0000000000000000 .debug_str
0000000000000000 l    d  .note.GNU-stack	0000000000000000 .note.GNU-stack
0000000000000000 l    d  .eh_frame	0000000000000000 .eh_frame
0000000000000000 l    d  .comment	0000000000000000 .comment
0000000000000000 g     F .text	00000000000000b6 my_memmove
0000000000000000         *UND*	0000000000000000 puts
00000000000000b6 g     F .text	000000000000006d my_memzero
0000000000000123 g     F .text	0000000000000134 my_reverse
0000000000000000         *UND*	0000000000000000 __stack_chk_fail



Disassembly of section .text:

0000000000000000 <my_memmove>:
#include <stdint.h>
#include <stdlib.h>
#include "memory.h"

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{ 
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 30          	sub    $0x30,%rsp
   8:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
   c:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
  10:	89 55 dc             	mov    %edx,-0x24(%rbp)
  int8_t ret_val =-1;
  13:	c6 45 f3 ff          	movb   $0xff,-0xd(%rbp)
  
    for (int j=0;j<length;j++)
  17:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
  1e:	e9 81 00 00 00       	jmpq   a4 <my_memmove+0xa4>
    {
        for (int k=0;k<length;k++)
  23:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
  2a:	eb 6c                	jmp    98 <my_memmove+0x98>
	{
	    if((src+j) == (dst+k))
  2c:	8b 45 f4             	mov    -0xc(%rbp),%eax
  2f:	48 63 d0             	movslq %eax,%rdx
  32:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  36:	48 8d 0c 02          	lea    (%rdx,%rax,1),%rcx
  3a:	8b 45 f8             	mov    -0x8(%rbp),%eax
  3d:	48 63 d0             	movslq %eax,%rdx
  40:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  44:	48 01 d0             	add    %rdx,%rax
  47:	48 39 c1             	cmp    %rax,%rcx
  4a:	75 10                	jne    5c <my_memmove+0x5c>
	    {
	       	printf("ERROR:OVERLAPPED MEMORY\n");
  4c:	bf 00 00 00 00       	mov    $0x0,%edi
			4d: R_X86_64_32	.rodata
  51:	e8 00 00 00 00       	callq  56 <my_memmove+0x56>
			52: R_X86_64_PC32	puts-0x4

		ret_val=-1;
  56:	c6 45 f3 ff          	movb   $0xff,-0xd(%rbp)
  5a:	eb 38                	jmp    94 <my_memmove+0x94>
	    }
	    else
	    {
                for (int i=0;i<length;i++)
  5c:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  63:	eb 27                	jmp    8c <my_memmove+0x8c>
		{
		    *(dst+i)=*(src+i);
  65:	8b 45 fc             	mov    -0x4(%rbp),%eax
  68:	48 63 d0             	movslq %eax,%rdx
  6b:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  6f:	48 01 c2             	add    %rax,%rdx
  72:	8b 45 fc             	mov    -0x4(%rbp),%eax
  75:	48 63 c8             	movslq %eax,%rcx
  78:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  7c:	48 01 c8             	add    %rcx,%rax
  7f:	0f b6 00             	movzbl (%rax),%eax
  82:	88 02                	mov    %al,(%rdx)
		   ret_val=0;
  84:	c6 45 f3 00          	movb   $0x0,-0xd(%rbp)

		ret_val=-1;
	    }
	    else
	    {
                for (int i=0;i<length;i++)
  88:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
  8c:	8b 45 fc             	mov    -0x4(%rbp),%eax
  8f:	3b 45 dc             	cmp    -0x24(%rbp),%eax
  92:	72 d1                	jb     65 <my_memmove+0x65>
{ 
  int8_t ret_val =-1;
  
    for (int j=0;j<length;j++)
    {
        for (int k=0;k<length;k++)
  94:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
  98:	8b 45 f8             	mov    -0x8(%rbp),%eax
  9b:	3b 45 dc             	cmp    -0x24(%rbp),%eax
  9e:	72 8c                	jb     2c <my_memmove+0x2c>

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{ 
  int8_t ret_val =-1;
  
    for (int j=0;j<length;j++)
  a0:	83 45 f4 01          	addl   $0x1,-0xc(%rbp)
  a4:	8b 45 f4             	mov    -0xc(%rbp),%eax
  a7:	3b 45 dc             	cmp    -0x24(%rbp),%eax
  aa:	0f 82 73 ff ff ff    	jb     23 <my_memmove+0x23>
		   ret_val=0;
		}
	    }
	 }
    }	
	return ret_val;	
  b0:	0f b6 45 f3          	movzbl -0xd(%rbp),%eax
}
  b4:	c9                   	leaveq 
  b5:	c3                   	retq   

00000000000000b6 <my_memzero>:

int8_t my_memzero(uint8_t *src, uint32_t length)
{
  b6:	55                   	push   %rbp
  b7:	48 89 e5             	mov    %rsp,%rbp
  ba:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  be:	89 75 e4             	mov    %esi,-0x1c(%rbp)
    int8_t ret_val =-1;
  c1:	c6 45 f7 ff          	movb   $0xff,-0x9(%rbp)
    for (int i=0; i<length;i++)
  c5:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
  cc:	eb 14                	jmp    e2 <my_memzero+0x2c>
    {
        *(src+i)=0;
  ce:	8b 45 f8             	mov    -0x8(%rbp),%eax
  d1:	48 63 d0             	movslq %eax,%rdx
  d4:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  d8:	48 01 d0             	add    %rdx,%rax
  db:	c6 00 00             	movb   $0x0,(%rax)
}

int8_t my_memzero(uint8_t *src, uint32_t length)
{
    int8_t ret_val =-1;
    for (int i=0; i<length;i++)
  de:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
  e2:	8b 45 f8             	mov    -0x8(%rbp),%eax
  e5:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
  e8:	72 e4                	jb     ce <my_memzero+0x18>
    {
        *(src+i)=0;
    }
    	
    for(int j=0;j<length;j++)
  ea:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  f1:	eb 22                	jmp    115 <my_memzero+0x5f>
    {
        if((*(src+j))!=0) 
  f3:	8b 45 fc             	mov    -0x4(%rbp),%eax
  f6:	48 63 d0             	movslq %eax,%rdx
  f9:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  fd:	48 01 d0             	add    %rdx,%rax
 100:	0f b6 00             	movzbl (%rax),%eax
 103:	84 c0                	test   %al,%al
 105:	74 06                	je     10d <my_memzero+0x57>
        {
	    ret_val=-1;
 107:	c6 45 f7 ff          	movb   $0xff,-0x9(%rbp)
            break;
 10b:	eb 10                	jmp    11d <my_memzero+0x67>
        } 
	else
	    ret_val=0;
 10d:	c6 45 f7 00          	movb   $0x0,-0x9(%rbp)
    for (int i=0; i<length;i++)
    {
        *(src+i)=0;
    }
    	
    for(int j=0;j<length;j++)
 111:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
 115:	8b 45 fc             	mov    -0x4(%rbp),%eax
 118:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
 11b:	72 d6                	jb     f3 <my_memzero+0x3d>
        } 
	else
	    ret_val=0;
    }
    
    return ret_val;
 11d:	0f b6 45 f7          	movzbl -0x9(%rbp),%eax
}
 121:	5d                   	pop    %rbp
 122:	c3                   	retq   

0000000000000123 <my_reverse>:

int8_t my_reverse(uint8_t *src, uint32_t length)
{  
 123:	55                   	push   %rbp
 124:	48 89 e5             	mov    %rsp,%rbp
 127:	48 81 ec a0 00 00 00 	sub    $0xa0,%rsp
 12e:	48 89 bd 68 ff ff ff 	mov    %rdi,-0x98(%rbp)
 135:	89 b5 64 ff ff ff    	mov    %esi,-0x9c(%rbp)
 13b:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
 142:	00 00 
 144:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
 148:	31 c0                	xor    %eax,%eax
    int8_t ret_val = -1;
 14a:	c6 85 7f ff ff ff ff 	movb   $0xff,-0x81(%rbp)
    uint8_t *dest = NULL;
 151:	48 c7 45 88 00 00 00 	movq   $0x0,-0x78(%rbp)
 158:	00 
    uint8_t r[100];
    dest=r;
 159:	48 8d 45 90          	lea    -0x70(%rbp),%rax
 15d:	48 89 45 88          	mov    %rax,-0x78(%rbp)
    int i;    
    int k=0;
 161:	c7 45 84 00 00 00 00 	movl   $0x0,-0x7c(%rbp)
    
    
    
    for ( i=length-1;i>=0;i--)
 168:	8b 85 64 ff ff ff    	mov    -0x9c(%rbp),%eax
 16e:	83 e8 01             	sub    $0x1,%eax
 171:	89 45 80             	mov    %eax,-0x80(%rbp)
 174:	eb 2a                	jmp    1a0 <my_reverse+0x7d>
    {
       *(dest+k)=*(src+i);
 176:	8b 45 84             	mov    -0x7c(%rbp),%eax
 179:	48 63 d0             	movslq %eax,%rdx
 17c:	48 8b 45 88          	mov    -0x78(%rbp),%rax
 180:	48 01 c2             	add    %rax,%rdx
 183:	8b 45 80             	mov    -0x80(%rbp),%eax
 186:	48 63 c8             	movslq %eax,%rcx
 189:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
 190:	48 01 c8             	add    %rcx,%rax
 193:	0f b6 00             	movzbl (%rax),%eax
 196:	88 02                	mov    %al,(%rdx)
	k++;
 198:	83 45 84 01          	addl   $0x1,-0x7c(%rbp)
    int i;    
    int k=0;
    
    
    
    for ( i=length-1;i>=0;i--)
 19c:	83 6d 80 01          	subl   $0x1,-0x80(%rbp)
 1a0:	83 7d 80 00          	cmpl   $0x0,-0x80(%rbp)
 1a4:	79 d0                	jns    176 <my_reverse+0x53>
    {
       *(dest+k)=*(src+i);
	k++;
    }
    
    for(i=0;i<length;i++)
 1a6:	c7 45 80 00 00 00 00 	movl   $0x0,-0x80(%rbp)
 1ad:	eb 26                	jmp    1d5 <my_reverse+0xb2>
    { 
       *(src+i)=*(dest+i);
 1af:	8b 45 80             	mov    -0x80(%rbp),%eax
 1b2:	48 63 d0             	movslq %eax,%rdx
 1b5:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
 1bc:	48 01 c2             	add    %rax,%rdx
 1bf:	8b 45 80             	mov    -0x80(%rbp),%eax
 1c2:	48 63 c8             	movslq %eax,%rcx
 1c5:	48 8b 45 88          	mov    -0x78(%rbp),%rax
 1c9:	48 01 c8             	add    %rcx,%rax
 1cc:	0f b6 00             	movzbl (%rax),%eax
 1cf:	88 02                	mov    %al,(%rdx)
    {
       *(dest+k)=*(src+i);
	k++;
    }
    
    for(i=0;i<length;i++)
 1d1:	83 45 80 01          	addl   $0x1,-0x80(%rbp)
 1d5:	8b 45 80             	mov    -0x80(%rbp),%eax
 1d8:	3b 85 64 ff ff ff    	cmp    -0x9c(%rbp),%eax
 1de:	72 cf                	jb     1af <my_reverse+0x8c>
    { 
       *(src+i)=*(dest+i);
    }		
    
    for(i=1;i<=length;i++)
 1e0:	c7 45 80 01 00 00 00 	movl   $0x1,-0x80(%rbp)
 1e7:	eb 46                	jmp    22f <my_reverse+0x10c>
    {
       if((*(src+i))!=(*(src+length-i)))
 1e9:	8b 45 80             	mov    -0x80(%rbp),%eax
 1ec:	48 63 d0             	movslq %eax,%rdx
 1ef:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
 1f6:	48 01 d0             	add    %rdx,%rax
 1f9:	0f b6 10             	movzbl (%rax),%edx
 1fc:	8b 8d 64 ff ff ff    	mov    -0x9c(%rbp),%ecx
 202:	8b 45 80             	mov    -0x80(%rbp),%eax
 205:	48 98                	cltq   
 207:	48 29 c1             	sub    %rax,%rcx
 20a:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
 211:	48 01 c8             	add    %rcx,%rax
 214:	0f b6 00             	movzbl (%rax),%eax
 217:	38 c2                	cmp    %al,%dl
 219:	74 09                	je     224 <my_reverse+0x101>
	   ret_val=-1;
 21b:	c6 85 7f ff ff ff ff 	movb   $0xff,-0x81(%rbp)
 222:	eb 07                	jmp    22b <my_reverse+0x108>
       else
           ret_val=0;
 224:	c6 85 7f ff ff ff 00 	movb   $0x0,-0x81(%rbp)
    for(i=0;i<length;i++)
    { 
       *(src+i)=*(dest+i);
    }		
    
    for(i=1;i<=length;i++)
 22b:	83 45 80 01          	addl   $0x1,-0x80(%rbp)
 22f:	8b 45 80             	mov    -0x80(%rbp),%eax
 232:	3b 85 64 ff ff ff    	cmp    -0x9c(%rbp),%eax
 238:	76 af                	jbe    1e9 <my_reverse+0xc6>
           ret_val=0;
    }
    
   

    return ret_val;
 23a:	0f b6 85 7f ff ff ff 	movzbl -0x81(%rbp),%eax
}		
 241:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
 245:	64 48 33 34 25 28 00 	xor    %fs:0x28,%rsi
 24c:	00 00 
 24e:	74 05                	je     255 <my_reverse+0x132>
 250:	e8 00 00 00 00       	callq  255 <my_reverse+0x132>
			251: R_X86_64_PC32	__stack_chk_fail-0x4
 255:	c9                   	leaveq 
 256:	c3                   	retq   
