#include "common.h"
#include "chunk.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
    Chunk chunk;
    init_chunk(&chunk);
    write_chunk(&chunk, OP_RETURN);
    free_chunk(&chunk);
    printf("Successfully created and freed chunk\n");
    printf("Hello World!\n");
    return 0;
}