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
 - Enqueue: Add an element to the buffer.
 - Dequeue: Remove an element from the buffer.
 - Peek   : View the front element without removing it.

 The buffer is implemented as a struct with a fixed size. It uses:
 - buffer[]: The array that holds the data.
 - head    : Points to the element to be removed (dequeue).
 - tail    : Points to the position to insert the next element (enqueue).
 - count   : Keeps track of the number of elements in the buffer.

 Wrap-around behavior is handled using: (index + 1) % capacity.

 The code also includes functions to:
 - Check if the buffer is empty or full.
 - Get the current size of the buffer.

 Note:
 This buffer is designed to hold elements of type `int`, but you can modify
 the type in the struct definition to store other types of data.

 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Buffer Size Definition
#define BUFFER_SIZE 5

// Circular Buffer Structure
typedef struct {
    int buffer[BUFFER_SIZE];  // Array to store buffer data
    int head;                  // Points to the element to be removed (dequeue)
    int tail;                  // Points to the position to insert the next element (enqueue)
    int count;                 // Keeps track of the number of elements in the buffer
} CBUF;

// Function Declarations
void initBuffer(CBUF *cb);
bool isFull(CBUF *cb);
bool isEmpty(CBUF *cb);
bool enqueue(CBUF *cb, int data);
bool dequeue(CBUF *cb, int *data);
bool peek(CBUF *cb, int *data);

// Initialization Function
void initBuffer(CBUF *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// Check if the buffer is full
bool isFull(CBUF *cb) {
    return (cb->count == BUFFER_SIZE);
}

// Check if the buffer is empty
bool isEmpty(CBUF *cb) {
    return (cb->count == 0);
}

// Enqueue: Add an element to the buffer
bool enqueue(CBUF *cb, int data) {
    if (isFull(cb)) {
        printf("Buffer is Full. Cannot Enqueue %d\n", data);
        return false;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count++;
    printf("Enqueued %d\n", data);
    return true;
}

// Dequeue: Remove an element from the buffer
bool dequeue(CBUF *cb, int *data) {
    if (isEmpty(cb)) {
        printf("Buffer is Empty. Cannot Dequeue\n");
        return false;
    }
    *data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count--;
    printf("Dequeued %d\n", *data);
    return true;
}

// Peek: View the front element without removing it
bool peek(CBUF *cb, int *data) {
    if (isEmpty(cb)) {
        return false;
    }
    *data = cb->buffer[cb->head];
    printf("Peeked %d\n", *data);
    return true;
}

// Main function to demonstrate the buffer operations
int main() {
    CBUF cb;
    initBuffer(&cb); // Initialize buffer
    int data;

    // Enqueue some elements into the buffer
    enqueue(&cb, 1);
    enqueue(&cb, 2);
    enqueue(&cb, 3);
    enqueue(&cb, 4);
    enqueue(&cb, 5);

    // Try to enqueue an element when the buffer is full
    enqueue(&cb, 6);  // This should fail

    // Dequeue some elements from the buffer
    dequeue(&cb, &data);
    dequeue(&cb, &data);

    // Enqueue after some dequeues
    enqueue(&cb, 6);
    enqueue(&cb, 7);

    // Dequeue more elements
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    dequeue(&cb, &data);

    // Try to dequeue when the buffer is empty
    dequeue(&cb, &data); // This should fail

    // Enqueue more elements
    enqueue(&cb, 8);
    enqueue(&cb, 9);
    enqueue(&cb, 10);

    // Try to enqueue an element when the buffer is full
    enqueue(&cb, 11);  // This should fail

    // Peek at the front element
    peek(&cb, &data);

    // Dequeue all remaining elements
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    dequeue(&cb, &data);
    dequeue(&cb, &data);

    // Try to dequeue when the buffer is empty
    dequeue(&cb, &data); // This should fail

    // Enqueue new elements after the buffer is empty
    enqueue(&cb, 12);
    enqueue(&cb, 13);
    enqueue(&cb, 14);

    return 0;
}
