/*
*  Project 2; CIS 200
*  Queue.cpp
*  Created by Ismail Mohamud on 12/1/22.
*/
#include "Queue.hpp"

/*constuctor to set up the algorithm*/
QueType::QueType(int max) {
    maxQue = max + 1;
    front = maxQue - 1;
    rear = maxQue - 1;
    jobs = new job[maxQue];
}

/*if the rear and front are same the queue is empty*/
bool QueType::IsEmpty() const {
    return (rear == front);
}

/*equation below returns true if the queue is full*/
bool QueType::IsFull() const {
    return ((rear + 1) % maxQue == front);
}

/*Adds the job to the end of the queue*/
void QueType::Enqueue(job newJob) {
    rear = (rear + 1) % maxQue;
    jobs[rear] = newJob;
}

/*Removes first element from queue and assigns it to param*/
void QueType::Dequeue(job& newJob) {
    front = (front + 1) % maxQue;
    newJob = jobs[front];
}

/*Method to add a value to the front of the queue*/
void QueType::addHighPriority(job high) {
    //make temp queue with all old values
    QueType tempQue = QueType(maxQue);
    while (!this->IsEmpty()) {
        job temp;
        this->Dequeue(temp);
        tempQue.Enqueue(temp);
    }
    this->Enqueue(high); //add value to start
    while (!tempQue.IsEmpty()) { //add all old values back
        job temp;
        tempQue.Dequeue(temp);
        this->Enqueue(temp);
    }
}

/*Returns the top value*/
job QueType::peek() {
    return jobs[rear];
}

/*Simple Destructor*/
QueType::~QueType() {
    delete[] jobs;
}
