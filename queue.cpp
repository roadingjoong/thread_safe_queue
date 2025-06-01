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
	Node* node = queue->head;
	while(node != nullptr){
		Node* nextnode = node->next;
		nfree(node);
		node = nextnode;
	}
	delete(queue);
}


Node* nalloc(Item item) {
	//Node 생성, item으로 초기화
	Node* node = new Node;
	node->item = item;
	node->next = nullptr;
	return node;
}


void nfree(Node* node) {
	delete(node);
}


Node* nclone(Node* node) {
	if(node == nullptr){
		return nullptr;
	}
	
	Node* newnode = new Node;
	newnode->item = node->item;
	newnode->next = nullptr;

	return newnode;
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
	lock_guard<mutex> lock(queue->mtx);

	if(queue->head == nullptr){
		return {false, {0, NULL}};
	}

	Node* node = queue->head;
	Item item = node->item;

	queue->head = node->next;

	if(queue->head == nullptr){
		queue->tail = nullptr;
	}

	nfree(node);

	return {true, item};
}

Queue* range(Queue* queue, Key start, Key end) {
	Queue* newqueue = init();
	lock_guard<mutex> lock(queue->mtx);

	Node* node = queue->head;

	while(node!=nullptr){
		if(node->item.key >= start && node->item.key <= end){
			Node* newnode = nclone(node);

			if(newnode != nullptr){
				enqueue(newqueue, newnode->item);
			}
		}
		node = node->next;
	}

	return newqueue;
}
