//
//  jobStack.hpp
//  Pro2cis200
//
//  Created by Ismail Mohamud on 12/1/22.
//

#ifndef jobStack_hpp
#define jobStack_hpp


#pragma once
#include <iostream>

struct job {
char jobType;
int processingTime;
int typeNumber;
int jobNumber;
int arrivalTime;
int waitTime = 0;
};

class jobStack
{
private:
job jobSet[5920];
int jobCount = 0;
public:
jobStack();
void push(job inputJob);
job pop();
bool isEmpty();
bool isFull();
void print();
int peekArrivalTime();
void quickSort(int low, int high);
void swap(job* a, job* b);
int partition(int low, int high);
int getCount() { return jobCount; }
~jobStack();
};


#endif /* jobStack_hpp */
