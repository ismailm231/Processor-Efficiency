//
//  Processor.hpp
//  Pro2cis200
//
//  Created by Ismail Mohamud on 12/1/22.
//

#ifndef Processor_hpp
#define Processor_hpp

#include <iostream>
#include "jobStack.hpp"

class Processor
{
private:
job currentJob;
int jobCount = 0;
public:
Processor();
void push(job inputJob);
job pop();
bool isEmpty();
bool isFull();
bool isComplete();

void processJobOne();
job peekJob() { return currentJob; }
~Processor() ;

};


#endif /* Processor_hpp */
