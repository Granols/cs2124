#ifndef __Utility_H
#define __Utility_H
#define COMMENT_MARKER '#'
#include <string.h>


void stringCharRemover(char* buffer, int buffSize, char removeTarget)
{
   char * stringTemp;
  stringTemp = strchr(buffer, COMMENT_MARKER);
    
    if(stringTemp != NULL)
      {
      size_t len = strlen(stringTemp);
        /* Ask if there is a specific reason we should cast to size_t 
      memset(stringTemp, '\0', strlen(stringTemp));  */
        memset(stringTemp, '\0', len); 
        
      }
   
};



#endif