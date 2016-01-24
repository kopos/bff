# Brainfuck compiler / repl / interpreter / jits

## About

Teaching myself about the low-level stuff going on with a programming language.
Compilers, interpreters, JITs for a programming language. Have sailed the high
seas for far too long that the land is a distant memory.

Teaching myself using the code at [https://github.com/nickdesaulniers/bf_interpreter_jit_compile]

## About Brainfuck

Brainfuck is an interesting, if hard to read, language. It only has eight
operations it can perform > < + - . , [ ], yet is Turing complete. There’s
nothing really to lex; each character is a token, and if the token is not one
of the eight operators, it’s ignored.

## 8 language commands

+---+------------------------------------------------------------------------+
| > | increment the data pointer (to point to the next cell to the right).   |
+---+------------------------------------------------------------------------+
| < | decrement the data pointer (to point to the next cell to the left).    |
+---+------------------------------------------------------------------------+
| + | increment (increase by one) the byte at the data pointer.              |
+---+------------------------------------------------------------------------+
| - | decrement (decrease by one) the byte at the data pointer.              |
+---+------------------------------------------------------------------------+
| . | output the byte at the data pointer.                                   |
+---+------------------------------------------------------------------------+
| , | accept one byte of input, storing its value in the byte at the data    |
|   | pointer.                                                               |
+---+------------------------------------------------------------------------+
| [ | if the byte at the data pointer is zero, then instead of moving the    |
|   | instruction pointer forward to the next command, jump it forward to    |
|   | the command after the matching ] command.                              |
+---+------------------------------------------------------------------------+
| ] | if the byte at the data pointer is nonzero, then instead of moving the |
|   | instruction pointer forward to the next command, jump it back to the   |
|   | command after the matching [ command.                                  |
+---+------------------------------------------------------------------------+

## References

1. http://nickdesaulniers.github.io/blog/2015/05/25/interpreter-compiler-jit/
2. http://en.wikipedia.org/wiki/Brainfuck
