#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//max number of tokens is 32
#define MAXARGS 32//limits arg vectors
#define LEN 256//limits users entry length

struct PARAM//a struct to hold input data
{
	char *inputRedirect;
	char *outputRedirect;
	int argumentCount;
	char *argumentVector[MAXARGS];
};typedef struct PARAM Param_t;


char* read()//will read input from user 
	{
	int i=0,j=1;//loop counter and value for reallocation
	char *entry, c='\0'; //string will be stored in entry, each character will be placed in array using c
	entry = (char*)malloc(sizeof(char));//allocate memory for user entry
	while (c!='\n')
	{
  		if(i>=LEN)
		{	
			printf("Entry too long\nEverything after the 256th character will not be recorded.\n");
			break; //this limits the length of the string	
		}
	c = getc(stdin);// read the input from keyboard standard input		
	entry = (char*)realloc(entry, j * sizeof(char));// re-allocate memory for character read to be stored
   	entry[i] = c;// store read character by making pointer point to c
 	i++;
    	j++;
	}
	entry[i]='\0';
	printf("You entered: %s",entry);
	return entry;
}


void argCount(char *c, Param_t* p)//this counts the # of args in string so the memory can be allocated
{
   int i = 0;
   while(c[i]!='\0')
   {
      if(c[i]!=' '&&c[i]!='\0')
      {   
         while(c[i]!=' '&&c[i]!='\0')
            i++;
         p->argumentCount++;
      }
      else
      {   
         i++;
         if(c[i]=='<'||c[i]=='>')//checking for redirect so it isn't counted
            while(c[i]!=' '&&c[i]!='\0')
               i++;
      }
   }
}

Param_t* PARAMbuild()//builds a param struct
{
   Param_t* new;
   new = (Param_t*)malloc( sizeof(Param_t));
   new->argumentCount=0;
   new->inputRedirect=NULL;
   new->outputRedirect=NULL;
   return new;
}

int main(void)
{
     printf("Type input and hit ENTER ");
     char *entry;
     entry=read();
     Param_t* param1;
     param1=PARAMbuild();
     argCount(entry,param1);
     free(entry);
     printf("%d", param1->argumentCount);
}


