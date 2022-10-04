#ifndef __Sim_C
#define __Sim_C
#include <stdio.h>
#include <string.h>

#define bufferVal 1024
#define COMMENT_MARKER '#'
#define DEFAULT_SIMNAME "simple.sim"
#define SIM_TEST_REP_ID "rep,"
#define SIM_TEST_REP "rep"
#define SIM_TEST_MSG "msg"
#define SIM_TEST_END "endSim"



struct sim {
      unsigned int timeStamp;
      unsigned int msgID;
      unsigned int IDofNode;
      unsigned int IDofEndNode;
      unsigned int currentNode;
      unsigned int timeStampEnd;
      char* keyWord;

};

int simRead( FILE* fInSim, struct sim* listOfSims, int* ptrNumOSims);
void simInit(struct sim* listOfSims, int SimNum, unsigned int temp, unsigned int temp1, unsigned int temp2, unsigned int temp3, char* tempBuffer);
void printAllSim (struct sim* listOfSims, int numOfSims, unsigned int timeOfRep);
void printSingleSim( struct sim* listOfSims, int SimNum, int arrSimCount, unsigned int timeOfRep);
void simDestroy(struct sim* listOfSims, int numOfSims);


#endif