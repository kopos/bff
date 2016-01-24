/**
 * Usage
 * =====
 * ./compiler ../examples/mandelbrot.bf >mandelbrot.s
 * as mandelbrot.s -o mandelbrot.o
 * ld -lc -macosx_version_min 10.8.5 mandelbrot.o -o mandelbrot; ./mandelbrot
 */
#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"
#include "stack.h"

void print_prologue() {
    const char* const prologue =
      ".text\n"
      ".globl _main\n"
      "_main:\n"
      "  pushq %rbp\n"
      "  movq %rsp, %rbp\n"
      "  pushq %r12\n"        // store callee saved register
      "  subq $30008, %rsp\n" // allocate 30,008 B on stack, and realign
      "  leaq (%rsp), %rdi\n" // address of beginning of tape
      "  movl $0, %esi\n"     // fill with 0's
      "  movq $30000, %rdx\n" // length 30,000 B
      "  call _memset\n"      // memset
      "  movq %rsp, %r12";
    puts(prologue);
}

void print_epilogue() {
    const char* const epilogue =
      "  addq $30008, %rsp\n" // clean up tape from stack.
      "  popq %r12\n" // restore callee saved register
      "  popq %rbp\n"
      "  ret\n";
    puts(epilogue);
}

void compile(char * code) {
    char * code_ptr = code;
    struct stack stack = { .size=0, .items={0} };
    int num_brackets = 0, matching_bracket = 0;

    print_prologue();

    while ((*code_ptr) != '\0') {
        switch(*code_ptr) {
            case '>':
                puts("  inc %r12");
                break;
            case '<':
                puts("  dec %r12");
                break;
            case '+':
                puts("  incb (%r12)");
                break;
            case '-':
                puts("  decb (%r12)");
                break;
            case '.':
                puts("  movzbl (%r12), %edi");
                puts("  call _putchar");
                break;
            case ',':
                puts("  call _getchar");
                puts("  movb %al, (%r12)");
                break;
            case '[':
                stack_push(&stack, num_brackets);
                puts("  cmpb $0, (%r12)");
                printf("  je bracket_%d_end\n", num_brackets);
                printf("bracket_%d_start:\n", num_brackets++);
                break;
            case ']':
                stack_pop(&stack, &matching_bracket);
                puts("  cmpb $0, (%r12)");
                printf("  jne bracket_%d_start\n", matching_bracket);
                printf("bracket_%d_end:\n", matching_bracket);
                break;
        };

        ++code_ptr;
    }

    print_epilogue();
}

int main(int argc, char **argv) {
    if (argc != 2) err("Usage: compile inputfile");
    char * code = read_file(argv[1]);
    if (code == NULL) err("Couldn't open file");

    compile(code);
    free(code);

    return 0;
}
