/*Guzel Noori - Lab 5
Could not do the scheduling, only reading processes and printing the total memory allocated*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

//enum STYPE {PRIORITY, SHORTEST, ROUNDROBIN};

struct Processor {
    char processName[16];
    int processID;
    unsigned char processActivity;
    int CPUBurstTime;
    int baseRegister;
    long limitRegister;
    unsigned char priority;

};

/*struct process {
    int id;
    int CPU_time;
    Processor pr;
    int totalP;
    int readyP;
    int finishP;
    int currentP;
    pthread_t t;
    pthread_mutex_t m;
    enum STYPE stype;
};*/

Processor p;
int processors = 0;
int processes = 0;
//ifstream binaryFile = NULL;
pthread_mutex_t tLock = PTHREAD_MUTEX_INITIALIZER;
int temp = -1;

void readProcessor(string fileName){
    Processor p;
    ifstream binaryFile;
    int size = 0;
    int totalMemory = 0;

    binaryFile.open(fileName, ios::in | ios::binary);
    binaryFile.seekg(0, ios::end);
    size = (int) binaryFile.tellg();
    binaryFile.seekg(0, ios::beg);
    cout << "Number of processes in the binary file  is: " << size << endl;
    
    //read the entire binary file
    while(binaryFile.tellg()<size){
        binaryFile.read((char*)&p.processName, sizeof(p.processName));
        binaryFile.read((char*)&p.processID, sizeof(p.processID));
        binaryFile.read((char*)&p.processActivity, sizeof(p.processActivity));
        binaryFile.read((char*)&p.CPUBurstTime, sizeof(p.CPUBurstTime));
        binaryFile.read((char*)&p.baseRegister, sizeof(p.baseRegister));
        binaryFile.read((char*)&p.limitRegister, sizeof(p.limitRegister));
        binaryFile.read((char*)&p.priority, sizeof(p.priority));

        totalMemory += (p.limitRegister - p.baseRegister);

        
        cout << "Process Name: " << p.processName <<endl;
        cout << "Process ID: " << p.processID << endl;
        cout << "Activity Status: " << p.processActivity << endl;
        cout << "CPU Burst TIme: " << p.CPUBurstTime << endl;
        cout << "Base Register: " << p.baseRegister << endl;
        cout << "Limit Register: " << p.limitRegister << endl;
        cout << "Priority: " << p.priority << endl;
        cout << endl;
    }
    cout << "Total memory allocated by the processor(s) is: " << totalMemory<< endl;
    binaryFile.close();

}
int main(int argc, char *argv[]){
    if (argc<4){
        cout << "Invalid entry. Please run the program as follows: "<< endl;
        cout << "./nameOfTheCompiledFile <process1> <load> ... bineFile.bin. " <<endl;
    }
    else if(argc == 8){
        readProcessor(argv[7]);
    }
    else if (argc == 6){
        readProcessor(argv[5]);
    }
    else if(argc == 4){
        readProcessor(argv[3]);
    }
    else {
        cout << "Invalid entry. Please run the program as follows: "<< endl;
        cout << "./nameOfTheCompiledFile <process1> <load> ... bineFile.bin. " <<endl;
    }
}