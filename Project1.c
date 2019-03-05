#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>

int *arraysort(int B[],int x)						//basically <BUBBLE SORT>		//function to sort the array.
{
int i,j,temp, q=0; 
int count=x;
	for(i=0;i<=count;i++)							//loop to select the first number and comparing with all the numbers in the array
	{
		for(j=0;j<count;j++)
		{
			if(B[j]>B[j+1])						//if the 1st element is greater than the next then swap the values from both the positions.
			{
				temp=B[j];
				B[j]=B[j+1];
				B[j+1]=temp;
q++;
			}
		}
	}
printf("\t\tswaps %d",q);
return B;										//returning the array B from where it was called.
}

int *arraycopy(int A[],int count)							//function to copy an array.
{
int i;
int j,temp;
int *B=(int*)malloc(count * sizeof(int));						//creating an array of size=total number of elements in the array.
	for(i=0;i<count;i++)									//loop for transfering the values of array A to B.
	{
		B[i]=A[i];
	}
printf("the elements in new array are\n");
	for(i=0;i<count-1;i++)									//printing the elements in array B.
	{
		printf(" %d ",B[i]);
	}
B=arraysort(B,count);									//calling the function to sort the array B.
return B;										//returning the array B "which is now sorted" to the main function.
}

int linearsearch(int A[],int D,int count,int *position,int *compare)			//function of linear search.
{
int i;
int times=0;
int searchvalue=D;
	for(i=0;i<=count;i++)									//comparing the searchvalue with all the elements in the array A.
	{
		if(A[i]==searchvalue)									//if the value is found then the pointers of position and comparisions are 	
		{											 // updated and passed to the main function where the function was called.
			*position=i+1;						
			*compare=i+1;
			times++;
		}
	if((i==count)&&(times==0)) 								//if the searched value is not found then return -1.								
	return -1;
	}
}


int binarysearch(int B[],int D,int count,int *position,int *compare)			//function for binary search.
{
int i=0,j;
int searchvalue=D;
int middle; 
int first = 0;
int last = count;
	if((first+last)%2==0)									//if the values are even then middle value can be found dividing by 2.
	{
		middle = ((first+last)/2);
	}
		else										//if the total umber of elements are odd then add 1 to get middle.
		middle=((first+last)/2)+1; 
			while (first <= last) 							//loop till first becomes greater than last.
			{									//in other words till all the values in the array are checked.
				if (B[middle] < searchvalue)	
				{								//if the searched value is greater than middle then check the part on the right to middle.
					first = middle + 1;  
				} 
			else if (B[middle] == searchvalue) 					//if the searched value is the middle then the number is found and update the postion and comparision pointers.
			{
				*position=middle+1;
				*compare=last/2;
				break;
			}
				else								//if the earched number is less then check the eft part of middle.
				last = middle - 1;
			middle = (first + last)/2;
			}
		if (first > last)								//if afer the end of the loop no value is found then return -1.
		return -1;
}

void main()
{
int position;
int compare;
int size=100;
int y=0;
int *A=(int*)malloc(size*sizeof(int));
int i,n;
int val;
int k=0;
int count=0;
int num;
int times;
int searchpoint=0;								//declaring all the variables.
printf("enter the values in array A and terminate with -999\n");		
	while(val!=-999)							//loop for scanning values till -999 is reached.
	{
		scanf("%d",&val);
		
		A[k]=val;
		
		k++;
		
		
		if(k==size)
							//conditional statement if the size of array defined is reached then increasing the array size by 2.
		{
			
			int *temp;
			
			temp=(int*)malloc(size*2*sizeof(int));
			
			int i;
			
			for(i=0;i<size;i++)
				
			temp[i]=A[i];
			
			free(A);
			
			A=temp;
			
			size=size*2;
		
		}
		count++;							//counting the number of elements inthe array.
	}
printf("total number of numbers are: %d \n",count-1);
printf("the elements in array A are: \n");
	for(i=0;i<count-1;i++)							//printing all the values in the array.
	{
		printf("%d ",A[i]);
	}
printf("\ncopying the values of A to B\n");
int *B=arraycopy(A,count);							//function to copy the contents of array A to array B.(passing array A, and number of elements in array)
printf("\nthe sorted array is: \n");						//printing the values in the sorted array B.
	for(i=1;i<count;i++)
	{
		printf(" %d ",B[i]);
	}
int *search=(int*)malloc(count * sizeof(int));					//creating another array in which values to be searched are stored it has the same size as number of
printf("\nenter the numbers you want to search terminate with -999\n");		 // elements in the array A.
	while(num!=-999)							//searching the values in the file which we want to search from the array.
	{
		scanf("%d",&num);						//scanning till the value reaches -999 and storing them in array search.
		search[searchpoint]=num;
		searchpoint++;
	}
printf("\nnumbers to be serched are: ");					//printing the values to be searched.
	for(i=0;i<searchpoint-1;i++)
	{
		printf(" %d ",search[i]);
	}
printf("\n\n Linear search ");							
	for(i=0;i<searchpoint-1;i++)						//loop to pass all the values in the array search one by one to linear search in the array A
	{
		int foundnotfound=linearsearch(A,search[i],count-1,&position,&compare);		//calling the function of linear search.
		if(foundnotfound!=-1)							//if the function doesnot return -1 then print the value found in position and comparisions done.
		{
			printf("\n %d was found in position %d and comparisions done are %d ", search[i],position,compare);
		}
			if(foundnotfound==-1)						//if the function returns -1 then print the value was not found.
			{
				printf("\n %d was not found in array",search[i]);
			}
	}
printf("\n\n Binary search");
	for(i=0;i<searchpoint-1;i++)							//calling the function of binary search
	{
		int fof=binarysearch(B,search[i],count-1,&position,&compare);
		if(fof!=-1)								//if function doesnot return -1 then value is found.
		{
			printf("\n %d was found in position %d and comparisions done are %d ", search[i],position,compare);
		}
			if(fof==-1)							//if the function reurns -1 then value is not found.
			{
				printf("\n %d was not found in array",search[i]);
			}
	}
}



