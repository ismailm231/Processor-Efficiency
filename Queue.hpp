//
//  Queue.hpp
//  Project2cis200
//
//  Created by Ismail Mohamud on 12/8/22.
//

#ifndef Queue_hpp
#define Queue_hpp


#include <iostream>
#include "jobStack.h"
using namespace std;

class QueType {
private:
    int front;
    int rear;
    int maxQue;
    job* jobs;

public:
    QueType(int max);
    ~QueType();
    bool IsEmpty() const;
    bool IsFull() const;
    void Enqueue(job jobs);
    void Dequeue(job& jobs);
    void addHighPriority(job high);
    job peek();
};
#endif /* Queue_hpp */
