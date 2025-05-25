//제춡X, 수정불가

#ifndef _QUEUE_H // header guard
#define _QUEUE_H 

#include "qtype.h"

Queue* init(void); //큐 초기화
void release(Queue* queue); //큐 해제


// ==========concurrent operations==========

Node* nalloc(Item item); //노드 생성, 초기화
void nfree(Node* node); //노드 해제
Node* nclone(Node* node); //노드 복제

Reply enqueue(Queue* queue, Item item); //삽입

Reply dequeue(Queue* queue); //해제

Queue* range(Queue* queue, Key start, Key end);

#endif
