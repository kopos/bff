#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

#define TAPE_SIZE 30000

char * jump_fwd(unsigned char * data_ptr, char * inst_ptr) {
    int level = 1;
    if (!(*data_ptr)) {
        while (level > 0) {
            inst_ptr++;
            if ((*inst_ptr) == ']') {
                level--;
            } else if ((*inst_ptr) == '[') {
                level++;
            }
        }
    }

    return inst_ptr;
}

char * jump_bck(unsigned char * data_ptr, char * inst_ptr) {
    int level = 1;
    if (*data_ptr) {
        while (level > 0) {
            inst_ptr--;
            if ((*inst_ptr) == ']') {
                level++;
            } else if ((*inst_ptr) == '[') {
                level--;
            }
        }
    }

    return inst_ptr;
}

void interpret(char * code) {
    char * inst_ptr = code;

    unsigned char data[TAPE_SIZE] = {0};
    unsigned char * data_ptr = data;

    while ((*inst_ptr) != '\0') {
        switch(* inst_ptr) {
            case '>': ++data_ptr; break;
            case '<': --data_ptr; break;
            case '+': ++(*data_ptr); break;
            case '-': --(*data_ptr); break;
            case '.': putchar(*data_ptr); break;
            case ',': *data_ptr = getchar(); break;
            case '[': inst_ptr = jump_fwd(data_ptr, inst_ptr); break;
            case ']': inst_ptr = jump_bck(data_ptr, inst_ptr); break;
        };
        ++inst_ptr;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) err("Usage: interpret inputfile");
    char * code = read_file(argv[1]);
    if (code == NULL) err("Couldn't open file");
    interpret(code);
    free(code);

    return 0;
}
