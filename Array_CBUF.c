/*
 ============================================================================
 Name           : circular_buffer.c
 Author         : SathwikPb
 Time Complexity: O(1) for all operations

 Description    :

 Circular Buffer Implementation:
 This code implements a circular buffer (also known as a ring buffer) in C.
 A circular buffer is a data structure that uses a single, fixed-size buffer
 as if it were connected end-to-end.

 It is useful for buffering data streams, such as audio or video data,
 where the producer and consumer operate at different rates.

 Operations:
 - Enqueue: Add an element to the buffer
 - Dequeue: Remove an element from the buffer
 - Peek   : View the front element without removing it

 The buffer is implemented as a struct with a fixed size. It uses:
 - buffer[]: The array that holds the data
 - head    : Points to the element to be removed (dequeue)
 - tail    : Points to the position to insert the next element (enqueue)
 - count   : Keeps track of the number of elements in the buffer

 Wrap-around behavior is handled using: (index + 1) % capacity

 The code also includes functions to:
 - Check if the buffer is empty or full
 - Get the current size of the buffer

 Note:
 This buffer is designed to hold elements of type `int`, but you can modify
 the type in the struct definition to store other types of data.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Buffer Size 
#define BUFFER_SIZE 5

// Cricular Buffer Structure
typedef struct
{
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
}CBUF;

// Initialization Function
void initBuffer(CBUF *cb)
{
    cb->head=0;
    cb->tail=0;
    cb->count=0;
}

bool isFull(CBUF *cb)
{
    return (cb->count==BUFFER_SIZE);
}

bool isEmpty(CBUF *cb)
{
    return (cb->count==0);

}

bool enqueue(CBUF *cb, int data)

{
    if(isFull(cb))
    {
        printf("Buffer is FUll. Cannot Enqueue %d\n",data);
        return false;
    }
    cb->buffer[cb->tail]=data;
    cb->tail=(cb->tail+1)%BUFFER_SIZE;
    cb->count++;
    printf("Enqueued %d\n",data);
    return true;

}

bool dequeue(CBUF *cb , int *data)
{
    if(isEmpty(cb))
{
    printf("Buffer is Empty. Cannot Dequeue\n");
    return false;

}
    *data=cb->buffer[cb->head];
    cb->head=(cb->head+1)%BUFFER_SIZE;
    cb->count--;
    printf("Dequeued %d\n",*data);
    return true;
}

bool peek(CBUF *cb, int *data)
{
    if(isEmpty(cb))return false;
    *data=cb->buffer[cb->head];
    printf("Peeked %d\n",*data);
    return true;

}


int main()

{
    CBUF cb;
    initBuffer(&cb);
    int data;
    enqueue(&cb, 1);
    enqueue(&cb, 2);
    enqueue(&cb, 3);
    enqueue(&cb, 4);
    enqueue(&cb, 5);
    enqueue(&cb, 6); // This should fail as the buffer is full
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    enqueue(&cb, 6);
    enqueue(&cb, 7);
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    dequeue(&cb, &data); // This should fail as the buffer is empty
    enqueue(&cb, 8);
    enqueue(&cb, 9);
    enqueue(&cb, 10);       
    enqueue(&cb, 11); // This should fail as the buffer is full
    peek(&cb, &data); // Peek the front element
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    dequeue(&cb, &data);

    dequeue(&cb, &data); // This should fail as the buffer is empty
    enqueue(&cb, 12);
    enqueue(&cb, 13);
    enqueue(&cb, 14);

    return 0;
    
}