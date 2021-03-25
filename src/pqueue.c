#include <stdio.h>

#include "./pqueue.h"

// create an empty priority queue
Pqueue *empty_pqueue(){
    Pqueue *temp = (Pqueue *)malloc(sizeof(Pqueue));
    temp->head = NULL;
    temp->length = 0;
}


// create a new node
Node* new_node(void *data){
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
 
    return temp;
}

// return the data at head
void* head(Pqueue *pqueue){
    return pqueue->head->data;
}

// remove the element with the highest priority from the list
void pop(Pqueue *pqueue){
    Node* temp = pqueue->head;
    pqueue->head = pqueue->head->next;
    (pqueue->length)--;
    free(temp);
}

/**push a node into priority queue
 * a function of how to compare the data is required
 * return -1 if data1 is smaller, 0 if equal, 1 if is bigger
*/
void push_node(Pqueue *pqueue, Node *temp, int *compare(void *data1, void *data2)){

    //start from head
    Node *curr_node = pqueue->head;

    //add new node at head
    if(compare(temp->data,pqueue->head->data)==-1){
        temp->next = pqueue->head;
        pqueue->head = temp;
    }
    else{
        //find the place to insert new node
        while(curr_node->next != NULL &&
            compare(temp->data,curr_node->next->data)!=-1){
            curr_node = curr_node->next;
        }

        //insert the new node
        temp->next = curr_node->next;
        curr_node->next = temp;

    }

    //increment the length of priority queue
    (pqueue->length)++;
}


/**push data into priority queue
 * a function of how to compare the data is required
 * return -1 if data1 is smaller, 0 if equal, 1 if is bigger
*/
void push_data(Pqueue *pqueue, void *data, int *compare(void *data1, void *data2)){

    // Create new Node
    Node *temp = newNode(data);
    //push it into priority queue
    push_node(pqueue,temp,compare);
}


// return whether the priority queue is empty
int isEmpty(Pqueue *pqueue){
    return pqueue->length==0;
}

// return  the length of priority queue
int pqueue_length(Pqueue *pqueue){
    return pqueue->length;
}

