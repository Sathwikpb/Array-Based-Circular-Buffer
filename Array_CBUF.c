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

bool isFUll(CBUF *cb)
{
    return (cb->count==BUFFER_SIZE);
}

bool isEmpty(CBUF *cb)
{
    return (cb->count==0);
    
}