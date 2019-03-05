#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

struct nodeStruct			//structure for 3 variable linked list
{
 char status;	
 int xcord;
 int ycord;
 struct nodeStruct*  next;
};








typedef struct nodeStruct node;

typedef struct mazeStruct				//structure for creating maze
{
 char **arr;  
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

void push(node** head, int xcord, int ycord)     	//fucntion to insert the values in the linked list
{

 node* ptr = (node*) malloc (sizeof(node));
 ptr->xcord = xcord;
 ptr->ycord = ycord;
 ptr->next=*head;
 *head = ptr;  
}

void setstatusU (node* head)				//function to set the positions as "UNVISITED"
{
node* ptr=head;
while(ptr!= NULL)
{
ptr->status='U';
ptr = ptr->next;
}
head=ptr;
} 

void setstatusV (node** head, int x, int y)			//function to set the positions as "VISITED"
{
node* ptr=*head;
	while (ptr!=NULL)
   	{
    	 	if((ptr->xcord==x)&&(ptr->ycord==y))
		{
		ptr->status='V';
		}
		
		ptr = ptr->next;
   	}
}

char ifend(node** head, int x, int y)			//function to determine if the end of the MAZE is found 
{
node* ptr= *head;			
if((ptr->xcord==x)&&(ptr->ycord==y))
{
	printf("end has been found\n");
	return 'E';
} 
return 0;  
}


int gettopx(node** head)				//function to access the top element in the linked list stack
{
node* ptr=*head;

return ptr->xcord;
}



int gettopy(node** head)					//function to access the top element in the linked list stack
{
node* ptr=*head;

return ptr->ycord;

}

char checkstatus(node* head, int xcord, int ycord)		//fucntion to know is the position is VISITED or UNVISITED
{
node* ptr=head;


 while (ptr != NULL)
    {

	
        if ((ptr->xcord == xcord)&&(ptr->ycord==ycord)&&(ptr->status=='U'))
        {
            
            return 'U';
        }
	if ((ptr->xcord == xcord)&&(ptr->ycord==ycord)&&(ptr->status=='V'))
        {
            
            return 'V';
        }
ptr=ptr->next;
    }

return 0;

}


void pop(node** head, int xcord, int ycord)			//function to remove the top element in the linked list stack
{
node* ptr;
node* curr;
ptr=*head;
curr=ptr->next;
free(ptr);
*head=curr;
}

int show(node** head)						//function to print out the linked list of positions in debug mode
{
node* ptr=*head;

while(ptr!=NULL)
{
printf("(%d,%d,%c) ",ptr->xcord,ptr->ycord,ptr->status);
ptr=ptr->next;
}
if(ptr==NULL)
{
return 0;
}
}

void checkifempty(node** head)				//function to know the stack is empty or not
{
node* ptr= *head;

if(ptr==NULL)
{
printf("There is no solution to this maze\n");
exit(0);
}
}

int solution(node* head)				//resurrsive function call to reverse and print stack
{
node* ptr=head;
	
	if (ptr == NULL)
       		return 0;
 
        solution(ptr->next);
 
	printf("(%d,%d) ",ptr->xcord,ptr->ycord);

}



void emptystack(node** head)				//function to empty the stack so that it can be used again
{
node* ptr=*head;
node* curr;
while(ptr!=NULL)
{
curr=ptr->next;
free(ptr);
ptr=curr;
}
*head=ptr;
free(ptr);
}





int main (int argc, char **argv)			//Main function
{
  maze m1;
node* head= NULL;
node* stack= NULL;
  int xpos, ypos;
  int i,j;
int length=0;
char p;
int debugMode;

	for(i=0;i<argc;i++)
	{								// start the debug mode.
	
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

FILE *src;

 								 /* verify the proper number of command line arguments were given */
if(argc == 1) 
{
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
}
   
										 /* Try to open the input file. */
if ( ( src = fopen( argv[1], "r" )) == NULL)
{
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
}

fscanf (src, "%d %d", &m1.xsize, &m1.ysize);			/* read in the size, starting and ending positions in the maze */
while(m1.xsize==0||m1.ysize==0)
{
if(debugMode==TRUE)
printf("%d %d (size cannot be 0)\n",m1.xsize,m1.ysize);
fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
}

printf ("\nsize: %d, %d\n\n", m1.xsize, m1.ysize);

  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
while(m1.xstart>m1.xsize||m1.ystart>m1.ysize)
{
if(debugMode==TRUE)
printf("%d %d (start is out of maze)\n",m1.xstart,m1.ystart);
fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
}

printf ("\nstart: %d, %d\n\n", m1.xstart, m1.ystart);

  fscanf (src, "%d %d", &m1.xend, &m1.yend);
  while(m1.xend>m1.xsize||m1.yend>m1.ysize)
{
if(debugMode==TRUE)
printf("%d %d (end is out of maze)\n",m1.xend,m1.yend);
fscanf (src, "%d %d", &m1.xend, &m1.yend);
}

printf ("\nend: %d, %d\n\n", m1.xend, m1.yend);

m1.arr=(char**)malloc((m1.xsize+2)*sizeof(char*));

for(i=0;i<m1.xsize+2;i++)
{
m1.arr[i]=(char*)malloc((m1.ysize+2)*sizeof(char));
}


for (i = 0; i < m1.xsize+2; i++)			/* initialize the maze to empty */
{
     	for (j = 0; j < m1.ysize+2; j++)
	{ 
	        m1.arr[i][j] = 250;
		push(&head,i,j);
	}
}

setstatusU(head);

if(debugMode==TRUE)
{
	printf("Linked list before the blocked positions\n");
	show(&head);
	printf("\n");
}

  									/* mark the borders of the maze blocked */
for (i=0; i < m1.xsize+2; i++)
{
     m1.arr[i][0] = 254;
     m1.arr[i][m1.ysize+1] = 254;
	setstatusV(&head,i,0);
	setstatusV(&head,i,m1.ysize+1);
}

for (i=0; i < m1.ysize+2; i++)
{
     m1.arr[0][i] = 254;
     m1.arr[m1.xsize+1][i] = 254;
	setstatusV(&head,0,i);
	setstatusV(&head,m1.xsize+1,i);
}


  								/* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 'S';
 push(&stack,m1.xstart,m1.ystart);
 setstatusV(&head,m1.xstart,m1.ystart);
  m1.arr[m1.xend][m1.yend] = 'E';

LOOP: while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)		/* mark the blocked positions visited */
    {

	while(xpos>m1.xsize||ypos>m1.ysize)
	{
	if(debugMode==TRUE)
	printf("%d %d blocking border\n",xpos,ypos);
	goto LOOP;
	
	}

	while(xpos==m1.xstart&&ypos==m1.ystart)
	{
	if(debugMode==TRUE)
	printf("%d %d blocking start\n",xpos,ypos);
	goto LOOP;
	
	}

	while(xpos==m1.xend&&ypos==m1.yend)
	{
	if(debugMode==TRUE)
	printf("%d %d blocking end\n",xpos,ypos);
	
	goto LOOP;
	}
	
	m1.arr[xpos][ypos] = 189;
	setstatusV(&head,xpos,ypos);
}


if(debugMode==TRUE)
{
printf("Linked List after marking all the blocked positions\n");
show(&head);
printf("\n");
}

 											/* print out the initial maze */
  for (i = 0; i < m1.xsize+2; i++)
    {
     for (j = 0; j < m1.ysize+2; j++)
	{
       printf (" %c ", m1.arr[i][j]);
     	}
	printf("\n");
    }


while(ifend(&stack,m1.xend,m1.yend)!= 'E')				//loop to check if the position is visited or unvisited
{									//This is the main loop of the algorithm.
int x= gettopx(&stack);
if(debugMode==TRUE)
printf("the xcord in top of stack is %d\n",x);

int y= gettopy(&stack);
if(debugMode==TRUE)
{
printf("the ycord in top of stack is %d\n",y);
printf("\n");
}

 if(checkstatus(head,x+1,y)=='U')
{

push(&stack,x+1,y);
setstatusV(&head,x+1,y);

}

else if(checkstatus(head,x-1,y)=='U')
{
push(&stack,x-1,y);
setstatusV(&head,x-1,y);

}

else if(checkstatus(head,x,y+1)=='U')
{
push(&stack,x,y+1);
setstatusV(&head,x,y+1);

}

else if(checkstatus(head,x,y-1)=='U')
{
push(&stack,x,y-1);
setstatusV(&head,x,y-1);

}
else
{
pop(&stack,x,y);
if(debugMode==TRUE)
printf("%d %d popped\n",x,y);
checkifempty(&stack);
}
}

printf("\nSolution of the Maze is\n\n");

solution(stack);

emptystack(&stack);						//at the end empty the lists
emptystack(&head);

return 0;
}





























