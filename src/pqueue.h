#ifndef _PQUEUE_H
#define _PQUEUE_H


/** a Priority Queue which can reuse by change the data
 * 
*/


// Node
typedef struct node{
    void *data;
    struct node *next;
}Node;

// Priority Queue
typedef struct pqueue{
    Node *head;
    int length;
}Pqueue;

// create an empty priority queue
Pqueue *empty_pqueue();
// create a new node
Node* new_node(void *data);
// return the data at head
void* head(Pqueue *pqueue);
// remove the element with the highest priority from the list
void pop(Pqueue *pqueue);
/**push a node into priority queue
 * a function of how to compare the data is required
 * return -1 if data1 is smaller, 0 if equal, 1 if is bigger
*/
void push_node(Pqueue *pqueue, Node *temp, int *compare(void *data1, void *data2));
/**push data into priority queue
 * a function of how to compare the data is required
 * return -1 if data1 is smaller, 0 if equal, 1 if is bigger
*/
void push_data(Pqueue *pqueue, void *data, int *compare(void *data1, void *data2));
// return whether the priority queue is empty
int isEmpty(Pqueue *pqueue);
// return  the length of priority queue
int pqueue_length(Pqueue *pqueue);

#endif