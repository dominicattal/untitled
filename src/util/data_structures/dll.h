#ifndef DLL_H
#define DLL_H

#include "../type.h"
#include "../vec.h"

struct DLLNode;

typedef struct Data {
    void* val;
    u32 length, offset;
    struct DLLNode* node;
} Data;

typedef struct DLLNode {
    Data* data;
    struct DLLNode* next;
    struct DLLNode* prev;
} DLLNode;

typedef struct DLL {
    struct DLLNode* head;
    struct DLLNode* tail;
} DLL;

Data* data_create(void* val, u32 length, u32 offset);
void data_destroy(Data* d);

DLLNode* dll_node_create(Data* d);
void dll_node_destroy(DLLNode* n);

DLL dll_create(void);
i2 dll_empty(DLL* dll);
void dll_append(DLL* dll, DLLNode* n);
void dll_remove(DLL* dll, DLLNode* n);
void dll_replace(DLL* dll, DLLNode* n);

#endif