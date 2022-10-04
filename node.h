#ifndef __Node_H
#define __Node_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define bufferVal 1024
#define nodeArr 20
#define COMMENT_MARKER '#'
#define endNetTester 't'
#define endNodeTester 'e'

struct node {
  unsigned int nodeID;
  unsigned int connectCount;
  unsigned int *listConnect;
};


enum nodeStatus
{
unkn_Node_Status,
start_Node_Status,
list_Node_Status,
end_Node_Status

};
enum nodeError
{
node_ok = 0,
node_Missing_ID_OR_CONNECT_COUNT,
node_Missing_Connection,
node_Wrong_Connect_Count

};
int nodeRead(FILE* fIn, struct node* listOfNodes,int* numOfStructs);
void nodeGet( struct node listOfNodes[]);
void nodeDestroy( struct node listOfNodes[], int arrStructCounter);
void nodeInit (struct node Node[], int arrStructCounter, unsigned int temp, unsigned int temp2);
bool endOfNode(char buffer[]);
bool endOfNet(char buffer[]);
void nodePrint(struct node listOfNodes[], int arrStructCounter);
void nodeErrorPrint( enum nodeError currentError);






#endif