//제출용, 수정가능

#ifndef _QTYPE_H  // header guard
#define _QTYPE_H

typedef unsigned int Key;
typedef void* Value;

typedef struct {
    Key key;
    Value value;
} Item;

typedef struct {
    bool success;
    Item item;
    // 필드 추가 기능
} Reply;

typedef struct node_t {
    Item item;
    struct node_t* next;
    // 필드 추가 기능
} Node;

typedef struct {
    Node* head, tail;
    // 필드 추가 기능
} Queue;

#endif
