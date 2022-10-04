#include "node.h"



int nodeRead(FILE* fIn, struct node* listOfNodes, int* numOfStructs)
{
  int counter = 0;
  int arrStructCounter = 0;
  unsigned int temp;
  unsigned int temp1;
  unsigned int temp2;
  char* stringTemp;
  char readIn;
  char buffer[bufferVal];
  enum nodeStatus currentState = unkn_Node_Status;
  enum nodeError currentError = node_ok;
  
while (!feof(fIn))
    {
      
    memset(buffer, '\0', bufferVal);
    fgets(buffer, bufferVal, fIn);
      stringCharRemover(buffer, bufferVal, COMMENT_MARKER);
      
    
    if( endOfNode(buffer) == true )
      {
        if(endOfNet(buffer) == true)
        {        
          return 0;
        }
        currentState = end_Node_Status;      

      /* need an if statement based on currentState for  errors */
      }
      readIn = buffer[0];
     
  if(isdigit(readIn) && (currentState == end_Node_Status || currentState == unkn_Node_Status))
  {
      
  
    currentState = start_Node_Status;
  
    sscanf(buffer,"%u, %u", &temp1,       &temp2);  
    nodeInit(listOfNodes, arrStructCounter,temp1,temp2);
    if(sscanf(buffer,"%u, %u", &temp, &temp) != 2)
    {
      currentError = node_Missing_ID_OR_CONNECT_COUNT;
      nodeErrorPrint(currentError);
      currentError = (int)currentError;
      return currentError;
    }
    
    currentState = list_Node_Status;

      if(listOfNodes[arrStructCounter].connectCount > 0)
      {

        for(counter = 0; counter <  listOfNodes[arrStructCounter].connectCount; counter++ )
          {
           memset(buffer, '\0', bufferVal);
           fgets(buffer, bufferVal, fIn);
           stringCharRemover(buffer, bufferVal, COMMENT_MARKER);

            if( endOfNode(buffer) == true  )
          {
              if(counter != listOfNodes[arrStructCounter].connectCount)
                {
                  currentError = node_Wrong_Connect_Count;
                  nodeErrorPrint(currentError);
                  currentError = (int) currentError;
                  return currentError;
                }
              if(endOfNet(buffer) == true)
                {   
                 return 0;
                }
                
                currentState = end_Node_Status;     
          }
            
          if(strlen(buffer) == 0)
          {
            counter -= 1;
            continue;
          }
           readIn = buffer[0];

            
            if(isdigit(readIn))
            {
            
 sscanf(buffer,"%u",&listOfNodes[arrStructCounter].listConnect[counter] );

              if(sscanf(buffer, "%u", &temp) != 1 )
                {
                  currentError = node_Missing_Connection;
                  nodeErrorPrint(currentError);
                  currentError = (int) currentError;
                  return currentError;
                }
              }  
         }
      }
    
    if( listOfNodes[arrStructCounter].connectCount == 0)
      {
       currentState = end_Node_Status ;      
      }
    
    arrStructCounter++;
    *numOfStructs +=1;
  }
      
}
  return 0;
}
void nodeDestroy( struct node listOfNodes[], int arrStructCounter)
{
     
              if(listOfNodes[arrStructCounter].connectCount > 0)
                {
                  free(listOfNodes[arrStructCounter].listConnect);
                  listOfNodes[arrStructCounter].listConnect = NULL;
                }
            
  
}

void nodeInit (struct node listOfNodes[], int arrStructCounter, unsigned int temp1, unsigned int temp2)
{
listOfNodes[arrStructCounter].nodeID = temp1;
listOfNodes[arrStructCounter].connectCount = temp2;

    if (listOfNodes[arrStructCounter].connectCount > 0)
  {
  listOfNodes[arrStructCounter].listConnect = (unsigned int*)malloc(sizeof(unsigned int)* listOfNodes[arrStructCounter].connectCount);
 }
 else
 {
 listOfNodes[arrStructCounter].listConnect = NULL;
 }

  
}
bool endOfNode(char buffer[])
{
  
  if( strchr(buffer, endNodeTester) != NULL )
  {
    return true;
  }
  else
    return false;
  }
bool endOfNet(char buffer[])
{

  if(strchr(buffer, endNetTester) != NULL)
        {
          return true;
        }
  else
    return false;
}

void nodePrint(struct node*  listOfNodes, int arrStructCounter)
{
int counter = 0;
    printf("Node Id: %d\nConnection Count: %d\n", listOfNodes[arrStructCounter].nodeID,listOfNodes[arrStructCounter].connectCount  );

    for(counter = 0; counter <  listOfNodes[arrStructCounter].connectCount; counter++ )
      {
        printf("Connection %d:  %d\n", counter, listOfNodes[arrStructCounter].listConnect[counter]);
      }
  
}


void nodeErrorPrint( enum nodeError currentError)
{
  switch(currentError)
  {
    case node_ok: 
    return;
    break;
    case node_Missing_ID_OR_CONNECT_COUNT:
    printf("There is either a missing node or a missing connection count, please check the format of your ntwk file!");
    break;
    case node_Missing_Connection:
    printf("There is a missing ID in the list of Connections, please check the format of your ntwk file!");
    break;
    case node_Wrong_Connect_Count:
    printf("Based on the Connection Count, there are missing Connection IDs. Please check the format of your ntwk file!");
    break;
    
  }
    
  
}

