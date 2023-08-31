//
//  main.cpp
//  Project2cis200
//
//  Created by Ismail Mohamud on 12/8/22.
//

#include "Processor.h"
#include "Queue.hpp"
#include "jobCreation.cpp"
#include "jobStack.h"
#include <vector>

const int PROCSIZE =4;

struct statistics {
    int procList = PROCSIZE;
    int currSize;
    int countSize;
    double sumSize;
    double avgSize;
    int maxQue;
    double totalTime;
    int totalQue;
    double avgTime;
    int aTotal;
    int aComp;
    int bTotal;
    int bComp;
    int cTotal;
    int cComp;
    int dTotal;
    int dComp;
    int jobComp;
    int procTime;
    int idleTime;
    int total;
};

/*Method that prints all the stats of the simulation*/
void metrics(statistics& stats){
    cout << "Number of processor(s) being used: " << stats.procList << endl;
    cout << "Current queue size: " << stats.currSize << endl;
    cout << "Average queue size: " << stats.avgSize << endl;
    cout << "Maximum jobs in queue: " << stats.maxQue << endl;
    cout << "Total time jobs are in queue: " << stats.totalTime << " time units" << endl;
    cout << "Average time jobs are in queue: " <<  stats.avgTime << " time units" << endl;
    cout << "Total number of A jobs arrived: " << stats.aTotal << endl;
    cout << "Total number of A jobs completed: " << stats.aComp << endl;
    cout << "Total number of B jobs arrived: " << stats.bTotal << endl;
    cout << "Total number of B jobs completed: " << stats.bComp << endl;
    cout << "Total number of C jobs arrived: " << stats.cTotal << endl;
    cout << "Total number of C jobs completed: " << stats.cComp << endl;
    cout << "Total number of D jobs arrived: " << stats.dTotal << endl;
    cout << "Total number of D jobs completed: " << stats.dComp << endl;
    cout << "Total jobs completed: " << stats.jobComp << endl;
    cout << "Total time CPU(s) were processing: " << stats.procTime << " time units" << endl;
    cout << "Total time CPU(s) were idle: " << stats.idleTime << " time units\n\n" << endl;

}

//Loops through all processors and works the job one unit
void procAll(vector<Processor>& procList, statistics& stats, int time, ofstream& log) {
    for (Processor& proc : procList) {
        proc.processJob();

        //stats for proc
        if (proc.isEmpty()) {
            stats.idleTime++;
        }
        else {
            stats.procTime++;
        }

        if (proc.isComplete() && proc.peekJob().arvTime != 0) {
            job completed = proc.pop();
            proc.reset();

            //stats for completion
            string type;
            if (completed.type == 'A') {
                stats.aComp++;
                type = "A";
            }
            else if (completed.type == 'B') {
                stats.bComp++;
                type = "B";
            }
            else if (completed.type == 'C') {
                stats.cComp++;
                type = "C";
            }
            else if (completed.type == 'D') {
                stats.dComp++;
                type = "D";
            }
            stats.jobComp++;

            //adding completion to log file
            log << "Time" << to_string(time) << ":-  Complete Processing Job:" << completed.jobNum << ", Job " << type << completed.arvTime << endl;

        }
    }
}

//returns a list of all the arrivals at the current time
job* getArrivals(int time, job* head, statistics& stats) {
    job* curr = head;
    job* arrivals = new job();
    job* arvTemp = arrivals;
    while (curr != NULL) {
        if (curr->arvTime == time) { //if the curr job arrives at the time then add it to list
            arvTemp->type = curr->type;
            arvTemp->arvTime = curr->arvTime;
            arvTemp->procTime = curr->procTime;

            arvTemp->next = new job();
            arvTemp = arvTemp->next;

            //stats for arrival
            if (curr->type == 'A')
                stats.aTotal++;
            else if (curr->type == 'B')
                stats.bTotal++;
            else if (curr->type == 'C')
                stats.cTotal++;
            else if (curr->type == 'D')
                stats.dTotal++;
            stats.total++;

        }

        else if (curr->arvTime > time) {
            break; //ensures loop won't run longer than it has to
        }

        curr = curr->next;
    }

    return arrivals;
}

//if the proc is empty add the arrivals
void fillProc(vector<Processor>& procList, job** arrivals, int time, ofstream& log) {
    int x = 1;
    for (Processor& proc : procList) {
        if (proc.isEmpty() && (*arrivals)->arvTime != 0) {
            proc.push(**arrivals);
            //cout << "->>>>>>" << proc.peekJob().type << proc.peekJob().arvTime << " @ " << x << endl;
            job* temp = *arrivals;
                
            //add to log
            string type;
            if ((*arrivals)->type == 'A')
                type = "A";
            else if ((*arrivals)->type == 'B')
                type = "B";
            else if ((*arrivals)->type == 'C')
                type = "C";
            else if ((*arrivals)->type == 'D')
                type = "D";
            log << "Time" << to_string(time) << ":-  Begin Processing Job:" << (*arrivals)->jobNum << ", Job " << type << (*arrivals)->arvTime << " in CPU " << x << endl;
            *arrivals = (*arrivals)->next;
            delete temp;
        }

        x++;
    }
}

//if the proccesors were full check arrivals for a high priority
void fillHighPri(vector<Processor>& procList, job* arrivals, int time, QueType& queue) {
    job* curr = arrivals;
    while (curr != NULL) {
        if (curr->type == 'D') { //if job is high priority
            for (Processor& proc : procList) { //check all proc
                if (proc.peekJob().type != 'D') { //and proc has lower priority
                    job lowPri = proc.pop(); //kick out low priority
                    proc.push(*curr);
                    lowPri.arvTime = time;
                    queue.addHighPriority(lowPri);
                    break;
                }
            }
        }
        curr = curr->next;
    }
}

//after going through the arrivals and high priority, check the queue to enter a proc
void checkQueue(vector<Processor>& procList, QueType& queue, statistics& stats) {
    if (!queue.IsEmpty()) {
        int x = 1;
        for (Processor& proc : procList) { //check all proc
            if (proc.isEmpty()) { //if theres a free proc
                job lucky;
                queue.Dequeue(lucky); //remove from queue
                if (lucky.arvTime != 0) {
                    proc.push(lucky); //add to proc
                    //cout << "Q~~~~~~>" << lucky.type << lucky.arvTime << " @ " << x << endl;

                    //stats for current queue size
                    stats.currSize--;
                }
            }
            x++;
        }
    }
}

//adds the arrivals not at a proc to the queue
void addQueue(job* arrivals, QueType& queue, statistics& stats) {
    while (arrivals->arvTime != 0) {
        //cout << "Q<+++++++" << arrivals->type << arrivals->arvTime << endl;
        queue.Enqueue(*arrivals);
        arrivals = arrivals->next;

        //final stat calculations
        stats.currSize++;
        stats.totalQue++;
        if (stats.currSize > stats.maxQue)
            stats.maxQue = stats.currSize;
        stats.totalTime += stats.currSize;
        stats.countSize++;
        stats.sumSize += stats.currSize;
        stats.avgSize = stats.sumSize / stats.countSize;
        stats.avgTime = stats.totalTime / stats.countSize;

    }
}

void createLog(vector<Processor>& procList, statistics& stats, int time, job* head, QueType& queue, int state, job* arrivals, ofstream& log, int CPU=0) {
    //overall state of cpus
    if (state == 0) {
        string empty = "empty; ";
        if (!queue.IsEmpty())
            empty = to_string(stats.currSize) + " Jobs; ";
        string CPUS = "";
        int i = 0;
        for (Processor proc : procList) {
            i++;
            string idle = " Idle Time:" + to_string(proc.getIT());
            if (proc.isFull())
                idle = " Run Time:" + to_string(proc.getPT());

            CPUS += "CPU " + to_string(i) + idle + "; ";
        }

        log << "Time" << to_string(time) << ":   Queue:" << empty << CPUS << endl;
    }
    //arrival of new job
    else if (state == 1 ) {
        job* curr = arrivals;
        curr = arrivals;
        while (curr != NULL && curr->arvTime != 0) {
            string type;
            if (curr->type == 'A')
                type = "A";
            else if (curr->type == 'B')
                type = "B";
            else if (curr->type == 'C')
                type = "C";
            else if (curr->type == 'D')
                type = "D";
            log << "Time" << to_string(time) << ":-  Arrival: Overall Job:" << to_string(stats.total) << ", Job " << type << to_string(curr->arvTime) << ", Processing Time " << to_string(curr->procTime) << endl;
            curr->jobNum = stats.total;
            curr = curr->next;
        }
    }

}

void generation(vector<Processor>& procList, statistics& stats, int time, job* head, QueType& queue, ofstream& log) {
    createLog(procList, stats, time, head, queue, 0, NULL, log);
    procAll(procList, stats, time, log);
    job* arrivals = getArrivals(time, head, stats);
    createLog(procList, stats, time, head, queue, 1, arrivals, log);
    fillProc(procList, &arrivals, time, log);
    fillHighPri(procList, arrivals, time, queue);
    checkQueue(procList, queue, stats);
    addQueue(arrivals, queue, stats);
    //createLog(procList, stats, time, head, queue, 0);
}
    

int main() {
    ofstream log;
    log.open("log.txt", ios::out);
    //Create and get head for sorted data
    job* head = getJobs();

    //listAll(head);

    //make proc list
    vector<Processor> procList;
    for (int i = 0; i < PROCSIZE; i++) {
        procList.push_back(Processor());
    }

    //make initial queue & stats
    QueType queue = QueType(5920);
    statistics stats = statistics();
    
    for (int i = 1; i < 501; i++) {  //generation should run for 500 times
        generation(procList, stats, i, head, queue, log); //before first initial report metrics
    }

    metrics(stats);

    for (int i = 0; i < 9500; i++) {
        generation(procList, stats, i+500, head, queue, log); //add 500 since 500 units have already passed
    }

    metrics(stats);

    log.close();
    return 0;
}
