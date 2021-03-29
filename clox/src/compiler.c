#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char* source, Chunk* chunk) {
    init_scanner(source);
    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");
}