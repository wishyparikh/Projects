
#include "GWInterface.h"

#include <vector>
#include <iostream>
#define nullptr NULL

using std::vector;
using std::cout;
using std::cin;



/*
  
  
  I removed classes and created structures, I had some functions in my class 
  you have to make those functions
  and make the code work. The other code is working 
  fine all you have to do is make your own functions and link 
  the front and back and return perfect elements.
  
  
  
  
  */











  class GridWorld : public GWInterface
{

  public:
  GridWorld() {}
 
  GridWorld(unsigned nrows, unsigned ncols)   {
		rows=nrows;
		cols=ncols;
     popul=0;
	 secNum=0;
	
	 
	 list=new MyList *[nrows];
	 for( int i = 0; i < nrows; i++ ) 
	 {
        list[i] = new MyList[ncols];
    }
	
}





    ~GridWorld(){
      
    }





    bool birth(int row, int col, int &id){
	
	
		
		if((row>rows || col>cols)||(row<0 || col<0))
		{
			
			return false;
		}
		if(deadpool.getfront()==NULL)
		{
			
		id=secNum;
		secNum++;
		}
		else
		{
			id=deadpool.returnfirst();
			
		}
		
		MyLNode * temp;
		temp=list[row][col].insert(secNum);
		
		Human hum;
		hum.roww=row;
		hum.column=col;
		hum.life='A';
		hum.ptr=temp;
		world1.humans.push_back(hum);
		
		
		
		popul=world1.humans.size();
		
		
	
		
		
		
		
		
      return true;
    }

    bool death(int personID){
		if(secNum<personID)
		{
			return false;
		}
		
		if(world1.humans[personID].life=='D')
		{
			return false;
		}
		
		list[world1.humans[personID].roww][world1.humans[personID].column].deleteNode(world1.humans[personID].ptr);
		world1.humans[personID].life='D';
		
		deadpool.insert(personID);
		

      return true;
    }

    bool whereis(int id, int &row, int &col)const{
		
		row=world1.humans[id].roww;
		col=world1.humans[id].column;
		
      return true;
    }

    bool move(int id, int targetRow, int targetCol)
	{
		MyLNode * temp;
		if((targetRow>rows || targetCol>cols)||(targetRow<0 || targetCol<0))
		{
				return false;
			
		}
		
		if(world1.humans[id].life=='D')
		{
			
			return false;
		}
		
		
		list[world1.humans[id].roww][world1.humans[id].column].deleteNode(world1.humans[id].ptr);
		
		world1.humans[id].roww=targetRow;
		world1.humans[id].column=targetCol;
		temp=list[world1.humans[id].roww][world1.humans[id].column].insert(id);
		world1.humans[id].ptr=temp;
		
      return true;
    }

    std::vector<int> * members(int row, int col)const{
		
		vector<int>* temp;
		
		MyLNode *tempo; 
		tempo= list[row][col].show();
		
		while(tempo!=NULL)
		{
		//temp->emplace_back(tempo->getElem());
		cout<<" "<<tempo->getElem();
			tempo=tempo->getNext();
			
		}

      return temp;
    }

    int population()const{
		return popul;
     
    }
    
    int population(int row, int col)const{
      
	 int pp;
     pp = list[row][col].getpopul();
	 return pp;
    }

    int num_rows()const {
      return rows;
    }
    int num_cols()const {
      return cols;
    }


  private:
  int popul;
  int rows,cols;
  int secNum;
  
  
  
  
  
  
  
  
  
  
  struct MyLNode{
  
  int ID;
  MyLNode *next;
  MyLNode *prev;
  
  
  };
  
  
  
  
  struct MyList
  {
	  MyLNode *front;
	  MyLNode *back;
	  
	  
  };
 
  struct Human
{
	int roww;
	int column;
	char life;
	MyLNode *ptr;
	
};
 typedef struct Human Human; 

 
 struct World
 {
	 vector<Human> humans;
	 
	 
 };
  typedef struct World World;
  
 World world1;
  
MyList **list;
MyList deadpool;
  
  
   
};
