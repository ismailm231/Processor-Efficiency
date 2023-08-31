/*
*  Project 2; CIS 200 
*  jobStack.cpp
*  Created by Ismail Mohamud on 12/1/22.
*/

#include "jobStack.h"

jobStack::jobStack(){
}

//Adds a job to the end of the stack
void jobStack::push(job inputJob){
	jobCount++;
	jobSet[jobCount - 1] = inputJob;
}

//Removes and returns 
job jobStack::pop(){
	job tempJob;
	tempJob = jobSet[jobCount - 1];
	jobSet[jobCount - 1] = job();
	jobCount--;
	return tempJob;
}

//Returns true if stack is empty
bool jobStack::isEmpty() {
	if (jobCount == 0) {
		return true;
	}

	return false;
}

//Returns true if stack is full
bool jobStack::isFull() {
	if (jobCount == 5920) {
		return true;
	}

	return false;
}

void jobStack::print() {
	for (int arr_i = jobCount - 1; arr_i >= 0; arr_i--) {
		std::cout << "Type " << jobSet[arr_i].type << " "
			<< "Arrival Time " << jobSet[arr_i].arvTime << " "
			<< "Processing Time " << jobSet[arr_i].procTime << std::endl;
	}
}

int jobStack::peekArrivalTime() {
	return jobSet[jobCount - 1].arvTime;
}

void jobStack::quickSort(int low, int high) {
	if (low < high){

		int pi = partition(low, high);

		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}


void jobStack::swap(job* a, job* b) {
	job t = *a;
	*a = *b;
	*b = t;
}


int jobStack::partition(int low, int high) {

	job pivot = jobSet[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (jobSet[j].arvTime >= pivot.arvTime)
		{
			i++;
			swap(&jobSet[i], &jobSet[j]);
		}
	}
	swap(&jobSet[i + 1], &jobSet[high]);
	return (i + 1);
}

jobStack::~jobStack() {
}
