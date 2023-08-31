//
//  Processor.cpp
//  Pro2cis200
//
//  Created by Ismail Mohamud on 12/1/22.
//

#include "Processor.hpp"

Processor::Processor()
{
}

//Adds an item to the stack
void Processor::push(job inputJob)
{
if (jobCount == 0) {
currentJob = inputJob;
jobCount++;
}
}

//Removes an item from the stack
job Processor::pop()
{
job tempJob = currentJob;
currentJob = {};
jobCount--;
return tempJob;

}

//Returns true when the stack is empty
bool Processor::isEmpty()
{
if (jobCount == 0) {
return true;
}
else {
return false;
}
}

//Returns true when the stack is full(max of 1)
bool Processor::isFull()
{
if (jobCount == 1) {
return true;
}
else {
return false;
}
}

//Returns true when job in the processor has 0 time remaining
bool Processor::isComplete()
{
if (currentJob.processingTime==0) {
return true;
}
else {
return false;
}
}

//Decreases the processing time in an active job in a processor
void Processor::processJobOne(){
currentJob.processingTime--;
}


Processor::~Processor()
{
}
