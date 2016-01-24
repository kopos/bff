# AT&T syntax
#
# as nothing.asm -o nothing.o
# ld -lc -macosx_version_min 10.8.5 nothing.o -o nothing
.text
.globl _main
_main:
  subq $8, %rsp
  movq $0, %rdi
  call _exit
