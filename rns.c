#include "rns.h"

unsigned int commandParse( int argc, char* argv[], networkCmdLine* cmdOut)
{
int counter = 1;
  if(cmdOut == NULL)
    {
      return CMD_LINE_MEMORY_ERR;  
    }
    strcpy(cmdOut->nameOfFile, DEFAULT_FILENAME);
    strcpy(cmdOut->nameOfSimFile, DEFAULT_SIMNAME);
    
  /*check index zero */
  
  for(; counter < argc; ++counter)
    { 
      switch(argv[counter][1])
      {
      case 'n':
              strcpy(cmdOut->nameOfFile, argv[counter + 1]);
              ++counter;
              break;
      case 's':
              strcpy(cmdOut->nameOfSimFile, argv[counter +1]);
              ++counter;
              break;
      case 'h':  /* help call */
      default:
        getHelp(argv[0]);
        return CMD_LINE_ERR;
      
      }
    } 
    /* check command line parameters */   
  return 0;
}

unsigned int networkLoad( const char* nameOfFile)
{
return 0;
}


void getHelp(char* nameOfPgm)
{
/* finish later */
printf("\n\nAcceptable parameters: -n or -h \n\n");
printf("-n: \n use as %s -n {filename} to open a specific file. Program does have a default of basic.ntwk for filename.\n", nameOfPgm);
printf("-h: \n use as %s -h to call the help function.\n\n\n", nameOfPgm);
}

void netWorkDestroy( struct node listOfNodes[], int numOfStructs)
{
int counter = 0;

for (; counter < numOfStructs; ++counter)
  {
    nodeDestroy(listOfNodes, counter);
  }
}

void networkPrint(struct node* listOfNodes, int numOfStructs)
{
int counter;
  for (counter = 0; counter < numOfStructs; counter++)
    {
    nodePrint(listOfNodes, counter);
    
    printf("\n");
    }

  }





int main(int argc, char *argv[]) {
  
  struct node listOfNodes[nodeArr];
  struct sim listOfSims[nodeArr];
  networkCmdLine parameters;
  unsigned int fileStatus = commandParse(argc, argv, &parameters);
  int numOfStructs = 0;
  int numOfSims = 0;
  int* ptrNumOStructs = &numOfStructs;
  int* ptrNumOSims = &numOfSims;
  
  if (fileStatus != 0)
    {
      return fileStatus;
    }
  
  FILE *fIn = fopen(parameters.nameOfFile,  "r");
    if (fIn == NULL)
      {
        return errno;
      }
      
  FILE *fInSim = fopen(parameters.nameOfSimFile,  "r");
    if (fInSim == NULL)
      {
        return errno;
      }
      
  printf("\n\n");
  
  nodeRead(fIn, listOfNodes, ptrNumOStructs);
  networkPrint( listOfNodes, numOfStructs);
  
  simRead(fInSim, listOfSims,ptrNumOSims);
  
  
  
  fclose(fIn);
  fclose(fInSim);
  netWorkDestroy(listOfNodes,numOfStructs);
  simDestroy(listOfSims, numOfSims);
  return 0;
}