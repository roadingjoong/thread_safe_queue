//제출용, 기능구현파일

#include <iostream>
#include "queue.h"


Queue* init(void) {
	Queue* queue = new Queue;
	queue->head = nullptr;
	queue->tail = nullptr;
	return queue;
}


void release(Queue* queue) {
	return;
}


Node* nalloc(Item item) {
	//Node 생성, item으로 초기화
	Node* node = new Node;
	node->item = item;
	node->next = nullptr;
	return node;
}


void nfree(Node* node) {
	return;
}


Node* nclone(Node* node) {
	return NULL;
}


Reply enqueue(Queue* queue, Item item) {
	lock_guard<mutex> lock(queue->mtx);

	Node* node = nalloc(item);

	if(queue->tail == nullptr){
		queue->tail = node;
		queue->head = queue->tail;
	}else{
		queue->tail->next = node;
		queue->tail = node;
	}

	return {true, item};
}

Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };
	return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
