//제출안함

#include <iostream>
#include <thread>
#include <atomic>
#include "queue.h"
#include <cstdint>

using namespace std;

#define REQUEST_PER_CLINET	10000

atomic<int> sum_key{0};
atomic<int> sum_value{0};

typedef enum {
	GET,
	SET,
	GETRANGE
} Operation;

typedef struct {
	Operation op;
	Item item;
} Request;

bool check = false;
Queue* newqueue;

void client_func(Queue* queue, Request requests[], int n_request) {
	Reply reply = { false, 0 };

	for (int i = 0; i < n_request; i++) {
		if (requests[i].op == GET) {
			reply = dequeue(queue);
		}
		else {
			reply = enqueue(queue, requests[i].item);
		}

		if (reply.success) {
			sum_key += reply.item.key;
			sum_value += reinterpret_cast<intptr_t>(reply.item.value);
		}
		else {
			// noop
		}

		if(requests[i].op == GET && check == false){
			newqueue = range(queue, 1000, 1010);
			check = true;
		}
	}

	// elapsed_time = finish_time - start_time;
	// finish_time = ....
	// average_response_time = elapsed_time / REQUEST_PER_CLIENT;
	// printf(...average_response_time of client1 = .....);
	// response_time_tot += finish_time - start_time;
}

//-----------------------------------------------------------------------

int main(void) {
	srand((unsigned int)time(NULL));

	//워크로드 생성(GETRANGE는 패스)
	Request requests[REQUEST_PER_CLINET];

	for (int i = 0; i < REQUEST_PER_CLINET / 2; i++) {
		requests[i].op = SET;
		requests[i].item.key = i;
		requests[i].item.value = reinterpret_cast<void*>(static_cast<intptr_t>(rand() % 1000000));
	} //0~4999

	for (int i = REQUEST_PER_CLINET / 2; i < REQUEST_PER_CLINET; i++) {
		requests[i].op = GET;
	} //5000~9999

//-----
	Queue* queue = init();

	//if (queue == NULL) return 0;
	//일단 한 개 뿐인데, 그래도 multi client라고 가정하기
	thread client = thread(client_func, queue, requests, REQUEST_PER_CLINET);
	client.join();

	cout << "-----------" << endl;
	Node* node = newqueue->head;
    while(node != nullptr){
        cout << node->item.key << endl;
        node = node->next;
    }
	cout << "---------" << endl;

	release(queue);
	release(newqueue);
//--------

	// 의미 없는 작업
	cout << "sum of returned keys = " << sum_key << endl;
	cout << "sum of returned values = " << sum_value << endl;

	// total_average_response_time = total_response_time / n_cleint;
	// printf("total average response time = ....
	return 0;
}



//------Test Code------
/* 
	//enqueue, dequeue TEST
	
	Item test1 = {1, (void*)1111};
	Item test2 = {2, (void*)2222};
	Item test3 = {3, (void*)3333};
	Item test4 = {4, (void*)3333};

	cout<<"enqueue 1, 2"<<endl;
	enqueue(queue, test1);
	enqueue(queue, test2);
	cout<<queue->head->item.key<<", "<<queue->tail->item.key<<endl;
	cout<<"next:"<<queue->head->next->item.key<<endl;

	cout<<"dequeue"<<endl;
	dequeue(queue);
	cout<<queue->head->item.key<<", "<<queue->tail->item.key<<endl;

	cout<<"enqueue 3"<<endl;
	enqueue(queue, test3);
	cout<<queue->head->item.key<<", "<<queue->tail->item.key<<endl;

	cout<<"enqueue 4"<<endl;
	enqueue(queue, test4);
	cout<<queue->head->item.key<<", "<<queue->tail->item.key<<endl;

	cout<<"dequeue"<<endl;
	dequeue(queue);
	cout<<queue->head->item.key<<", "<<queue->tail->item.key<<endl;
*/