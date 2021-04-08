#ifndef clox_value_h
#define clox_value_h

#include "common.h"

// forward declare some structs
// for cyclical dependencies
typedef struct Obj Obj;
typedef struct ObjString ObjString;

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
    VAL_OBJ
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
        Obj* obj;
    } as;
} Value;

#define IS_BOOL(value)      ((value).type == VAL_BOOL)
#define IS_NIL(value)       ((value).type == VAL_NIL)
#define IS_NUMBER(value)    ((value).type == VAL_NUMBER)
#define IS_OBJ(value)       ((value).type == VAL_OBJ)

#define AS_BOOL(value)      ((value).as.boolean)
#define AS_NUMBER(value)    ((value).as.number)
#define AS_OBJ(value)       ((value).as.obj)

#define BOOL_VAL(value)     ((Value){VAL_BOOL, { .boolean = value }})
#define NIL_VAL             ((Value){VAL_NIL, { .number = 0 }})
#define NUMBER_VAL(value)   ((Value){VAL_NUMBER, { .number = value }})
#define OBJ_VAL(value)      ((Value){VAL_OBJ, { .obj = (Obj*)value }})

#define OBJ_TYPE(value)     (AS_OBJ(value)->type)
#define IS_STRING(value)    (is_obj_type(value, OBJ_STRING))

#define AS_STRING(value)    ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)   (((ObjString*)AS_OBJ(value))->chars)

typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

bool values_equal(Value a, Value b);
void init_value_array(ValueArray* array);
void write_value_array(ValueArray* array, Value value);
void free_value_array(ValueArray* array);
void print_value(Value value);

#endif