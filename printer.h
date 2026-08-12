#ifndef PRINTER_QUEUE_H
#define PRINTER_QUEUE_H
#include <iostream>
#include <stdexcept>
#include "jobPrinter.h"

template <typename T>
class queueArr {
private:
    T* q_array;
    size_t q_capacity;
    size_t q_size;
    int q_front;
    int q_back;

public:
    queueArr(size_t capacity = 10);
    queueArr(const queueArr& other);
    queueArr& operator=(const queueArr& other);
    ~queueArr();

    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    void Clear();

    T& Front();
    T& Back();

    void Enqueue(const T& value);
    T Dequeue();
};


// Constructor
template <typename T>
queueArr<T>::queueArr(size_t capacity) : q_array(nullptr),
      q_capacity(capacity),
      q_size(0),
      q_front(0),
      q_back(-1) {

    if (capacity > 0) {
        q_array = new T[capacity];
    }
}

// Copy constructor
template <typename T>
queueArr<T>::queueArr(const queueArr& other) : q_array(nullptr),
      q_capacity(other.q_capacity),
      q_size(other.q_size),
      q_front(other.q_front),
      q_back(other.q_back) {

    if (q_capacity > 0) {
        q_array = new T[q_capacity];

        for (size_t i = 0; i < q_capacity; i++) {
            q_array[i] = other.q_array[i];
        }
    }
}

// Assignment operator
template <typename T>
queueArr<T>& queueArr<T>::operator=(const queueArr& other) {

    if (this == &other) {
        return *this;
    }

    T* new_array = nullptr;

    if (other.q_capacity > 0) {
        new_array = new T[other.q_capacity];

        for (size_t i = 0; i < other.q_capacity; i++) {
            new_array[i] = other.q_array[i];
        }
    }

    delete[] q_array;

    q_array = new_array;
    q_capacity = other.q_capacity;
    q_size = other.q_size;
    q_front = other.q_front;
    q_back = other.q_back;

    return *this;
}

// Destructor
template <typename T>
queueArr<T>::~queueArr() {
    delete[] q_array;
}

// Empty
template <typename T>
bool queueArr<T>::Empty() const {
    return q_size == 0;
}

// Full
template <typename T>
bool queueArr<T>::Full() const {
    return q_size == q_capacity;
}

// Size
template <typename T>
size_t queueArr<T>::Size() const {
    return q_size;
}

// Front
template <typename T>
T& queueArr<T>::Front() {

    if (Empty()) {
        throw std::runtime_error("Queue is empty");
    }

    return q_array[q_front];
}

// Back
template <typename T>
T& queueArr<T>::Back() {
    if (Empty()) {
        throw std::runtime_error("Queue is empty");
    }

    return q_array[q_back];
}

// Clear
template <typename T>
void queueArr<T>::Clear() {
    q_size = 0;
    q_front = 0;
    q_back = -1;
}

// Enqueue
template <typename T>
void queueArr<T>::Enqueue(const T& value) {

    if (Full()) {
        std::cout << "Queue is full." << std::endl;
        return;
    }

    q_back = (q_back + 1) % q_capacity;
    q_array[q_back] = value;

    ++q_size;
}

// Dequeue
template <typename T>
T queueArr<T>::Dequeue() {

    if (Empty()) {
        throw std::runtime_error("Queue is empty");
    }

    T temp = q_array[q_front];

    q_front = (q_front + 1) % q_capacity;
    --q_size;

    if (Empty()) {
        q_front = 0;
        q_back = -1;
    }

    return temp;
}

class Printer {
private:
    queueArr<Job> job_queue;

public:

    Printer(size_t capacity = 10)
        : job_queue(capacity) {
    }

    // Add a job to the printer queue
    void aJob(const Job& job) {

        if (job_queue.Full()) {
            std::cout << "Cannot add Job #"
                      << job.getId()
                      << " - printer queue is full."
                      << std::endl;
            return;
        }

        std::cout << "Submitted print: ";

        job.print();

        std::cout << std::endl;

        job_queue.Enqueue(job);
    }

    // Process all jobs
    void pJob() {

        while (!job_queue.Empty()) {

            Job current = job_queue.Dequeue();

            std::cout << "Printing ";

            current.print();

            std::cout << std::endl;
        }
    }

    // Check if queue is empty
    bool Empty() const {
        return job_queue.Empty();
    }
    
    // Get queue size
    size_t Size() const {
        return job_queue.Size();
    }
};

#endif // PRINTER_QUEUE_H