#include <stdio.h>

#include "common.h"
#include "vm.h"
#include "debug.h"
#include "compiler.h"

VM vm;

static void reset_stack() {
    // stack size is constant and only value at pointer
    // can be accessed so no need to clear values
    vm.stack_top = vm.stack;
}

void init_VM() {
    reset_stack();
}

void free_VM() {
    // TODO
}

void push(Value value) {
    *vm.stack_top++ = value;
}

Value pop() {
    return *--vm.stack_top;
}

Value peek() {
    return *(vm.stack_top - 1);
}

void set(Value value) {
    *(vm.stack_top - 1) = value;
}

static InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    // use do-while loop to avoid macro expansion
    // syntax issues (needs to be in a block and have semicolon at end
    // or not without breaking the program)
    // flip a and b to reverse order of stack operands 
    #define BINARY_OP(op) \
        do { \
            double b = pop(); \
            double a = pop(); \
            push(a op b); \
        } while (false)

    for (;;) {
        #ifdef DEBUG_TRACE_EXECUTION
            printf("        ");
            for (Value* slot = vm.stack; slot < vm.stack_top; slot++) {
                printf("[ ");
                print_value(*slot);
                printf(" ]");
            }
            printf("\n");
            disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_NEGATE: set(-peek()); break;
            case OP_ADD:    BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE: BINARY_OP(/); break;
            case OP_RETURN: {
                print_value(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    Chunk chunk;
    init_chunk(&chunk);

    if (!compile(source, &chunk)) {
        free_chunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;

    InterpretResult result = run();

    free_chunk(&chunk);
    return result;
}