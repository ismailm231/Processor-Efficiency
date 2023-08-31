//
//  jobCreation.cpp
//  Project2cis200
//
//  Created by Ismail Mohamud on 12/8/22.
//

#include <string>
#include <fstream>
#include "Processor.h"
#include "jobStack.h"
using namespace std;

const int JOBSIZE = sizeof(job);

/*helper function that takes in the middle value and the range and returns a random number*/
static int random(int target, int range) {
    int min = target - range;
    int max = target + range;
    return min + (rand() % (max - min + 1));
}

/*prototypes*/
static job* combine(job* lft, job* rgt);
static void split(job* source, job** lft, job** rgt);

/*recursive function that splits a list until its small enough to sort*/
static void mergeSort(job** head) {
    job* curr = *head;
    job* lft; job* rgt; //used to point to the heads of the two split lists

    //cout << curr->value << endl;
    if (curr == NULL || curr->next == NULL) { //when the list is small enough
        return;                               //return and collapse recursion
    }

    split(curr, &lft, &rgt); //uses reference to split the list
    //printAll(lft); printAll(rgt);

    mergeSort(&lft); //sorts left half by recursion
    mergeSort(&rgt); //sorts right half by recursion

    *head = combine(lft, rgt); //after lft and rgt are sorted combine them
}

/*helper function that actually does the sorting*/
static job* combine(job* lft, job* rgt) {
    job* merged = new job(); //blank head to combine the lft and rgt

    if (!lft) { //if lft is null then the 'combined' list is just the rgt
        return rgt;
    }
    else if (!rgt) { //if rgt is null then the 'combined' list is just the lft
        return lft;
    }

    //D has priority
    if (lft->arvTime <= rgt->arvTime || (lft->arvTime == rgt->arvTime && lft->type == 'D')) { //if lft value is less then add it before rgt
        merged = lft;
        merged->next = combine(lft->next, rgt); //recursively sorts all values in list
    }

    else {
        merged = rgt;
        merged->next = combine(lft, rgt->next); //recursively sorts all values in list
    }

    return merged;
}

/*function that splits the list into two halves using a slow and fast ptr trick*/
static void split(job* head, job** lft, job** rgt) {
    job* hare; job* turtle;
    turtle = head;
    hare = head->next;

    while (hare != NULL) {
        hare = hare->next;

        if (hare != NULL) {
            turtle = turtle->next;
            hare = hare->next;
        }
    }

    *lft = head;
    *rgt = turtle->next;
    turtle->next = NULL; //breaks connection off
}

/*Creates all the jobs with their random values*/
static job* instertRandoms() {
    ofstream output;
    output.open("unsortedJobs.txt", ios::out);

    int size = 0;

    cout << "\tD Started" << endl;
    int prevArv = 0;
    job* head = new job();
    job* curr = head;
    for (int i = 0; i < 500; i++) { //D-Jobs
        curr->type = 'D';
        curr->arvTime = random(19, 5) + prevArv;
        prevArv = curr->arvTime;
        curr->procTime = random(12, 5);
        curr->jobNum = i;

        string s = "D " + to_string(curr->arvTime) + " " + to_string(curr->procTime);
        output << s << endl;

        curr->next = new job();
        curr = curr->next;
        size++;
    }


    cout << "\tA Started" << endl;
    prevArv = 0;
    for (int i = 0; i < 2500; i++) { //A-Jobs
        curr->type = 'A';
        curr->arvTime = random(5, 1) + prevArv;
        prevArv = curr->arvTime;
        curr->procTime = random(3, 2);
        curr->jobNum = i + 500;

        string s = "A " + to_string(curr->arvTime) + " " + to_string(curr->procTime);
        output << s << endl;

        curr->next = new job();
        curr = curr->next;
        size++;
    }

    cout << "\tB Started" << endl;
    prevArv = 0;
    for (int i = 0; i < 1670; i++) { //B-Jobs
        curr->type = 'B';
        curr->arvTime = random(7, 1) + prevArv;
        prevArv = curr->arvTime;
        curr->procTime = random(5, 3);
        curr->jobNum = i + 500 + 2500;

        string s = "B " + to_string(curr->arvTime) + " " + to_string(curr->procTime);
        output << s << endl;

        curr->next = new job();
        curr = curr->next;
        size++;
    }

    cout << "\tC Started" << endl;
    prevArv = 0;
    for (int i = 0; i < 1250; i++) { //C-Jobs
        curr->type = 'C';
        curr->arvTime = random(11, 7) + prevArv;
        prevArv = curr->arvTime;
        curr->procTime = random(9, 3);
        curr->jobNum = i + 500 + 2500 + 1670;
        string s = "C " + to_string(curr->arvTime) + " " + to_string(curr->procTime);
        output << s << endl;

        curr->next = new job();
        curr = curr->next;
        size++;
    }
    
    return head;
}

/*Lists all the Jobs in the listand writes them to a file*/
static void listAll(job* head, bool write=false) {
    ofstream jobData;
    jobData.open("sortedJobs.txt", ios::out);
    job* curr = head;
    while (curr != NULL) {
        if (write) {
            if (curr->type == 'D')
                jobData << "D " + to_string(curr->arvTime) + " " + to_string(curr->procTime) << endl;
            else if (curr->type == 'A')
                jobData << "A " + to_string(curr->arvTime) + " " + to_string(curr->procTime) << endl;
            else if (curr->type == 'B')
                jobData << "B " + to_string(curr->arvTime) + " " + to_string(curr->procTime) << endl;
            else if (curr->type == 'C')
                jobData << "C " + to_string(curr->arvTime) + " " + to_string(curr->procTime) << endl;
        }
        else {
            cout << curr->type << " " << to_string(curr->arvTime) << " " << to_string(curr->procTime) << endl;
        }
        curr = curr->next;
    }
}

/*The 'main' of the file that retruns a head to all the random jobs*/
static job* getJobs() {
    srand(100);

    //opens data files
    ofstream messyData;
    messyData.open("unsortedJobs.txt", ios::out);
    ofstream jobData;
    jobData.open("sortedJobs.txt", ios::out);
    
    //makes all the random data
    cout << "Starting Data Creation:" << endl;
    job* head = instertRandoms();
    head = head->next;

    //sorts data
    mergeSort(&head);

    //shows data
    listAll(head, true);
    head = head->next;
    //closes files
    messyData.close();
    jobData.close();
    return head;
}
