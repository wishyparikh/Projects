#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0 

 typedef struct StackStruck   	//struckture for creating the stack.
{
	int top;
        char* array;
	int size;
} Stack;

void Freestack(Stack *s)	//function to free the stack.
{
	if(s!=NULL)
	{
		if(s->array)
			free(s->array);
		free(s);
}	}
		
	
void initialize(Stack *s) 	//function to initialize the stack.
{
 	s->size = 2;
	s->array = (char*)malloc(sizeof (char) * s->size);
	s->top = 0;
}

void grow(Stack *s)	//fucntion to grow the stack when full
{
	
	char *temp;
	s->size=s->size+2;
	temp=(char*)malloc(sizeof (char)*s->size);
	int i;
	for (i=0; i<s->size; i++)
		temp[i]=s->array[i];
			
	free(s->array);
	s->array=temp;
}


void push(Stack *s,char num,int debugMode) 	//function to push the values in the stack
{
    if (s->top==s->size)
	grow(s);
    if(s->top<s->size) 
	{
        	s->array[s->top] = num;
		s->top=s->top+1;
	}
if (debugMode==TRUE)
{
	printf("%c was pushed into the stack\n",s->array[s->top-1]);
}
}

char currospond(char num)		//function to check the currospnding symbol on the top of the stack.
{
	if (num=='(')	
		return ')';
	if (num=='{')
		return '}';
	if (num=='[')
		return ']';
	if (num=='<')
		return '>';
	if (num==')')
		return '(';
	if (num=='}')
		return '{';
	if (num==']')
		return '[';
	if (num=='>')
		return '<';
}

char accesstop(Stack *s)		//function to access the top of the stack
{
	return s->array[s->top-1];
}



char pop(Stack *s,char num, int debugMode)		//function to pop the values out od the stack.
{
	if (num==')'&&accesstop(s)=='(')
	{
		s->top=s->top-1;
	}
	else if (num=='}'&&accesstop(s)=='{')
	{
		s->top=s->top-1;
	}
	else if (num==']'&&accesstop(s)=='[')
	{
		s->top=s->top-1;
	}
	else if (num=='>'&&accesstop(s)=='<')
	{
		s->top=s->top-1;
	}
	else if (s->top==0)
	{
	return currospond(num);
	}

	else
	{
		return currospond(s->array[s->top-1]);
	}

	if (debugMode==TRUE)
	{
		printf("\t%c was popped out of the stack\n",s->array[s->top]);
	}
return 0;
}


int Empty(Stack *s) 					//function to check if the stack is empty or not.
{
 	if(s->top == 0)
	{   
		return TRUE;  
	}
	else
 		return currospond(s->array[s->top-1]);
}


int main(int argc, char** argv) 				//main function.
{

int debugMode;
char inputString[300],counter;
int i, length;
Stack st;
	for (i=0;i<argc;i++)					// start the debug mode.
	{
		if (argv[i][0]=='-')
		{
			if (argv[i][1]=='d')
			{
			debugMode=TRUE;
			}
		}
		else
			debugMode=FALSE; 
	} 
gg:while( TRUE ) 
{
	initialize(&st);
	printf("If you want to run in dubug mode type ' -d' after the executable file\n");
	printf("Enter a string of paranthesis you want to check or enter 'q' or 'Q' to exit\n");
	fgets(inputString,300,stdin);
		if(inputString[0]=='q'||inputString[0]=='Q') 
		{
			exit(0);
		}
length = strlen(inputString);
 	for (i = 0; i < length; i++)
	{
        	if (inputString[i] == '{'||inputString[i]=='('||inputString[i]=='<'||inputString[i]=='[')
                	push(&st,inputString[i],debugMode);
        	if (inputString[i] == '}'||inputString[i]==')'||inputString[i]=='>'||inputString[i]==']')
       			counter = pop(&st,inputString[i],debugMode);
       		if(counter == '{'||counter=='('||counter=='<'||counter=='[')
       		{
        		printf("%c was missing\n",counter);
        		printf("InValid Paranthesis Expression\n");
        		Freestack(&st);	
			counter=0;	
			goto gg;
        	}
        
        if(counter == '}'||counter==')'||counter=='>'||counter==']')
        {
        	printf("%c was expected \n",counter);
        	printf("InValid Paranthesis Expression\n");
        	Freestack(&st);  
		goto gg; 	
        }
      
	}

char x = Empty(&st);
     
    if (x==TRUE)
        printf("Valid Paranthesis Expression\n");
    else
    {
    	printf("%c was expected \n",x);
        printf("InValid Paranthesis Expression\n");
    }
	
	
	Freestack(&st);   
}
        return 0;
}