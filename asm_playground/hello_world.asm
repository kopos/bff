# hello_world.s
# as hello_world.s -o hello_world.o
# ld hello_world.o -e _main -lc -o hello_world
.section __DATA,__data
str:
  .asciz "Hello, %s!\n"
name:
  .asciz "John Doe"

.section __TEXT,__text
.globl _main
_main:
  pushq %rbp
  movq %rsp, %rbp
  movq str@GOTPCREL(%rip), %rdi
  movq name@GOTPCREL(%rip), %rsi
  movb $0, %al
  callq _printf
  popq %rbp
  movl $0x2000001, %eax
  syscall
