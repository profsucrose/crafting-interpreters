#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

typedef enum {
    OBJ_STRING
} ObjType;

struct Obj {
    ObjType type;
    struct Obj* next;
};

// A struct stores memory in the way in it's defined
// so an Obj* could be a generic object or an ObjString
// which enables inheritance and type pruning
struct ObjString {
    Obj obj;
    int length;
    char* chars;
    uint32_t hash;
};

ObjString* take_string(char* chars, int length);
ObjString* copy_string(const char* chars, int length);
void print_object(Value value);

static inline bool is_obj_type(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif