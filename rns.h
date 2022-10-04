#ifndef __rns_h
#define __rns_h

#include "node.h"
#include "utility.h"
#include "sim.h"

#define MAX_LEN_NAME_OF_FILE 512
#define NO_ERR 0
#define CMD_LINE_ERR 1
#define CMD_LOAD_NET 2
#define CMD_LINE_MEMORY_ERR 3
 
#define DEFAULT_FILENAME "basic.ntwk" 


typedef struct __CMD_LINE_PARAMETERS networkCmdLine;
struct __CMD_LINE_PARAMETERS 
{
  char nameOfFile[MAX_LEN_NAME_OF_FILE];
  char nameOfSimFile[MAX_LEN_NAME_OF_FILE];
};

void netWorkPrint(struct node* listOfNodes, int numOfStructs);
void netWorkDestroy( struct node listOfNodes[], int numOfStructs);
unsigned int commandParse( int argc, char* argv[], networkCmdLine* cmdOut);
unsigned int networkLoad( const char* nameOfFile);
void getHelp(char *nameOfPgm);

#endif