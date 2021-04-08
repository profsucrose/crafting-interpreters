#ifndef clox_compiler_h
#define clox_compiler_h

#include "object.h"
#include "vm.h"
#include "common.h"
#include "scanner.h"
#include "object.h"

bool compile(const char* source, Chunk* chunk);

#endif