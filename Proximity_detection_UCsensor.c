/*
 ============================================================================
 Name           : circular_buffer_arduino_sensor_operations_continuous.ino
 Author         : SathwikPb
 Description    : Continuous Data Collection with Circular Buffer
 ============================================================================
*/


#include <stdlib.h>
#include <stdbool.h>
// Define buffer size and sensor pins
#define BUFFER_SIZE 5  // Define the size of the circular buffer
#define TRIG_PIN 9     // Trigger pin for HC-SR04
#define ECHO_PIN 10    // Echo pin for HC-SR04
#define LED_PIN 13     // Pin for LED (for visual feedback)

// Define the Circular Buffer Structure
typedef struct {
    int buffer[BUFFER_SIZE];  // Array to hold the buffer elements
    int head;                  // Points to the element to be removed (dequeue)
    int tail;                  // Points to the position to insert the next element (enqueue)
    int count;                 // Keeps track of the number of elements in the buffer
} CBUF;

// Declare the circular buffer
CBUF cb;

// Function Declarations
void initBuffer(CBUF *cb);
bool isFull(CBUF *cb);
bool isEmpty(CBUF *cb);
bool enqueue(CBUF *cb, int data);
bool dequeue(CBUF *cb, int *data);
long getDistance();
float calculateAverageDistance(CBUF *cb);
void performAction(float avgDistance);

// Initialization Function: Sets buffer values to initial state
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
        // If buffer is full, dequeue one element before enqueueing new data
        dequeue(cb, &data);  // Remove the oldest element
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;  // Move tail to the next position (wrap-around if needed)
    cb->count++;
    Serial.print("Enqueued Distance: ");
    Serial.println(data);
    return true;
}

// Dequeue: Remove an element from the buffer
bool dequeue(CBUF *cb, int *data) {
    if (isEmpty(cb)) {
        Serial.println("Buffer is Empty. Cannot Dequeue");
        return false;
    }
    *data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE;  // Move head to the next position (wrap-around if needed)
    cb->count--;
    return true;
}

// Function to get distance from the ultrasonic sensor
long getDistance() {
    // Send a pulse to the trigger pin
    digitalWrite(TRIG_PIN, LOW);  
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);  
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read the time for the pulse to return
    long duration = pulseIn(ECHO_PIN, HIGH);

    // Calculate the distance (speed of sound = 34300 cm/s)
    long distance = duration * 0.0344 / 2;  // distance in cm
    return distance;
}

// Calculate the average distance from the buffer
float calculateAverageDistance(CBUF *cb) {
    if (cb->count == 0) return 0.0;  // Avoid division by zero

    int total = 0;
    for (int i = 0; i < cb->count; i++) {
        total += cb->buffer[(cb->head + i) % BUFFER_SIZE];
    }
    return total / (float)cb->count;
}

// Perform an action based on the average distance
void performAction(float avgDistance) {
    // Example action: if the average distance is less than 10 cm, turn on an LED
    if (avgDistance < 10) {
        digitalWrite(LED_PIN, HIGH);  // Turn on the LED
        Serial.println("Warning: Object is too close!");
    } else {
        digitalWrite(LED_PIN, LOW);   // Turn off the LED
    }
}

// Setup function: Runs once when the Arduino starts
void setup() {
    // Start serial communication
    Serial.begin(9600);
    
    // Set ultrasonic sensor pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    // Initialize the circular buffer
    initBuffer(&cb);

    Serial.println("Starting Continuous Data Collection");
}

// Loop function: Runs continuously
void loop() {
    // Continuously read data from the ultrasonic sensor
    long distance = getDistance();  // Get the distance from the sensor

    // Enqueue the distance to the circular buffer
    enqueue(&cb, distance);

    // Calculate the average distance from the buffer
    float avgDistance = calculateAverageDistance(&cb);

    // Perform an action based on the average distance
    performAction(avgDistance);

    // Print the buffer state for debugging (optional)
    Serial.print("Buffer contents: ");
    for (int i = 0; i < cb.count; i++) {
        Serial.print(cb.buffer[(cb.head + i) % BUFFER_SIZE]);
        Serial.print(" ");
    }
    Serial.println();

    // Wait for a short delay before the next reading
    delay(1000);  // Adjust the delay as needed
}
