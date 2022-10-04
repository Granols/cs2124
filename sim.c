#include "sim.h"
#include <stdlib.h>


int simRead( FILE* fInSim, struct sim* listOfSims, int* ptrNumOSims)
{

    int arrSimCount = 0;
    int counter = 0;
    char buffer[bufferVal];
    char tempBuffer[bufferVal];
    unsigned int temp;
    unsigned int temp1;
    unsigned int temp2;
    unsigned int temp3;
    char testBuffMsg[] = SIM_TEST_MSG;
    char testBuffRepID[] = SIM_TEST_REP_ID;
    char testBuffRep[] = SIM_TEST_REP;
    char testBuffEnd[] = SIM_TEST_END;
    char* testbuffResult;
    
     
    while(!feof(fInSim))
    {
      memset(buffer, '\0', bufferVal);
      fgets(buffer, bufferVal, fInSim);
      stringCharRemover(buffer, bufferVal, COMMENT_MARKER);
      char* testbuffBackup = strstr(buffer,testBuffRepID);
      
      if (strlen(buffer) == 0)
      {
      continue;
      }

      
      testbuffResult = strstr(buffer, testBuffMsg);
      
      if(testbuffResult != NULL)
      {
       
       sscanf(buffer, "%u,msg,%u,%u,%u", &temp, &temp1, &temp2,&temp3);
       strncpy(tempBuffer, testBuffMsg,3);
       
       
       
       simInit(listOfSims, arrSimCount, temp,temp1,temp2,temp3,tempBuffer);
    
      }
      
      testbuffResult = strstr(buffer, testBuffRepID);
      
      if(testbuffResult != NULL)
      {
      
          
          /*get the value and rep that specific message ID */
          sscanf(buffer,"%u,rep,%u", &temp, &temp1);
          strncpy(tempBuffer, testBuffRepID,3);
          listOfSims[arrSimCount].timeStamp = temp;
          listOfSims[arrSimCount].keyWord = (char *)malloc(sizeof(char)* strlen(tempBuffer));
          strncpy(listOfSims[arrSimCount].keyWord, tempBuffer,3);
          listOfSims[arrSimCount].msgID = temp1;
          
          
          printSingleSim(listOfSims,temp1, arrSimCount, listOfSims[arrSimCount].timeStamp );
          
          
          /* now print the message info for the node ID received, should be in listOfSims[arrSimCount].IDofNode now */
          
          /* something like printSimAt( listOfSims, specific message id) */
          
      }
      
      
      testbuffResult = strstr(buffer, testBuffRep);
      
      if(testbuffResult != NULL && testbuffBackup == NULL)
      
          {
          sscanf(buffer, "%u", &temp);
          strncpy(tempBuffer, testBuffRep,3);
          listOfSims[arrSimCount].timeStamp = temp;
          listOfSims[arrSimCount].keyWord = (char *)malloc(sizeof(char)* strlen(tempBuffer));
          strncpy(listOfSims[arrSimCount].keyWord, tempBuffer,3);
          
          /* now print all message info */ 
          /* something like printAllSim(listOfSims, arrSimCount); to print all */
          
          printAllSim(listOfSims, arrSimCount,listOfSims[arrSimCount].timeStamp );
         
          }
          
      
    
      testbuffResult = strstr(buffer,testBuffEnd);
      
      if(testbuffResult != NULL)
      {
      sscanf(buffer,"%u", &temp);
      listOfSims[arrSimCount].timeStamp = temp;
      strncpy(tempBuffer, testBuffEnd, 6);
      listOfSims[arrSimCount].keyWord = (char *)malloc(sizeof(char)* strlen(tempBuffer));
      strncpy(listOfSims[arrSimCount].keyWord,tempBuffer,6);
      
        /* end of simulation, return */ 
        return 0;
      }
    
      arrSimCount++;
      *ptrNumOSims += 1;
    }
    return 0;
}
void simInit(struct sim* listOfSims, int SimNum, unsigned int temp, unsigned int temp1, unsigned int temp2, unsigned int temp3, char* tempBuffer)
{
listOfSims[SimNum].timeStamp = temp;
listOfSims[SimNum].msgID = temp1;
listOfSims[SimNum].IDofNode = temp2;
listOfSims[SimNum].IDofEndNode = temp3;

listOfSims[SimNum].keyWord = (char*)malloc(sizeof(char)* strlen(tempBuffer));
strcpy(listOfSims[SimNum].keyWord, tempBuffer);
}


void printSingleSim( struct sim* listOfSims, int SimNum, int arrSimCount, unsigned int timeOfRep)
{
int counter = 0;
/* using for loop in case the msgIDs are not in order */
for(; counter < arrSimCount; ++counter)
  {
    if (listOfSims[counter].msgID == SimNum && listOfSims[counter].timeStamp < timeOfRep && strncmp(listOfSims[counter].keyWord, SIM_TEST_REP,3) != 0)
    {

  printf( "Time Start: %u \n Start Node: %u \n End Node: %u \n Cur Node: \n Time End: \n", listOfSims[counter].timeStamp, listOfSims[counter].IDofNode, listOfSims[counter].IDofEndNode);
  }
  }
  return;
}

void printAllSim (struct sim* listOfSims, int numOfSims, unsigned int timeOfRep)
{
int counter = 0;

    for(; counter < numOfSims; ++counter)

      {
      if(listOfSims[counter].timeStamp < timeOfRep && strncmp(listOfSims[counter].keyWord, SIM_TEST_REP,3) != 0)
        printf( "Time Start: %u \n Start Node: %u \n End Node: %u \n Cur Node: \n Time End: \n\n", listOfSims[counter].timeStamp, listOfSims[counter].IDofNode, listOfSims[counter].IDofEndNode);
      
      }
      return;
}


void simDestroy(struct sim* listOfSims, int numOfSims)
{
int counter = 0;

    for(; counter < numOfSims; ++counter)
    {
   
       if( listOfSims[counter].keyWord != NULL)
       {
        free(listOfSims[counter].keyWord);
        listOfSims[counter].keyWord = NULL;
        }
    }

}