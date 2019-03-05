
#include "GWInterface.h"

#include <vector>
#include <iostream>
#define nullptr NULL

using std::vector;
using std::cout;
using std::cin;

class MyLNode
{
 public:
  int elem;
  
  MyLNode* next;
  MyLNode* prev;
  
 public:
  MyLNode (int v1)
  {
	  elem = v1;
  next = NULL;
  prev = NULL;
  }

  
  void setElem (int e)
  {
	  elem = e;
  }
  int getElem ()
  {
	  return elem;
  }
  void setNext (MyLNode* n)
  {
	  next = n;
  }
  void setprev (MyLNode* p)
  {
	  prev = p;
	  
  }
  MyLNode* getNext()
  {
	  
	  return next;
  }
   
  MyLNode* getprev()
  {
	  
	  return prev;
  }
  
};



class MyList
{
 public:
  MyLNode* front;
  MyLNode* back;
  int pop;
  

  
 public:
  MyList()
  {
	  front = NULL;
	  back=NULL;
	  pop=0;
  }
  

   void deadpush(int v1)
   {
	   MyLNode* tmp = new MyLNode (v1);
  
  
  if(front == nullptr) 
  {
        front = back = tmp;
		
		
      }
      else 
	  {
        back->setNext(tmp);
		tmp->setprev(back);
        back = tmp;
		
		
      }
	   
	   
	   
   }
  
  MyLNode* insert(int v1)
  {
	 
	MyLNode* tmp = new MyLNode (v1);
  pop++;
  
  if(front == nullptr) 
  {
        front = back = tmp;
		return tmp;
		
      }
      else 
	  {
        back->setNext(tmp);
		tmp->setprev(back);
        back = tmp;
		tmp->setNext(NULL);
		return tmp;
		
      }  
  }
  
  int getpopul()
  {
	  return pop;
	  
	  
  }
  MyLNode* show()
  {
	  MyLNode * temp;
	  temp=front;
	return temp;
	
  } 
  
 
	  
	void deleteNode(MyLNode *del)
{
	
 
			if (front == NULL)
			{
				return;
			}

			
			if (front->getNext() == NULL)
			{
				

				front = NULL;
				back = NULL;
				delete del;
				pop--;
				return;

			}

			
			if (del->getprev() == NULL)
			{ 
				front = del->getNext();
				del->getNext()->setprev(del->getprev());
				delete del;
				pop--;
				return;

			}

		
			if (del-> getNext() == NULL)
			{
				back = del->getprev();
				del->getprev()->setNext(del->getNext());
				delete del;
				pop--;
				return;

			}

			del->getprev()->setNext( del->getNext());
			del->getNext()->setprev( del->getprev());
			delete del;
			pop--;
  }     
	  
	int returnfirst()
	{
		MyLNode* temp;
		
		temp=front;
		front=front->getNext();
		
		return temp->getElem();
		
	}	
  
  MyLNode* getfront()
  {
	  return front;
	  
  }
  
  


};


class GridWorld : public GWInterface, public MyList
{

  public:
  GridWorld() {}
 
  GridWorld(unsigned nrows, unsigned ncols)   {
		rows=nrows;
		cols=ncols;
     popul=0;
	 secNum=0;
	
	 deadpool = new MyList;
	
	 
	 list=new MyList *[nrows];
	 for( int i = 0; i < nrows; i++ ) 
	 {
        list[i] = new MyList[ncols];
    }
	
}




    ~GridWorld(){
		
		for( int i = 0; i < rows; i++ ) 
	 {
        delete[] list[i];
    }
	delete list;
		
		
		
	}



    bool birth(int row, int col, int &id)
	{
	
		if((row>rows || col>cols)||(row<0 || col<0))
		{
			
			return false;
		}
		if(deadpool->getfront()==NULL)
		{
			
		id=secNum;
		secNum++;
		}
		else if(deadpool->show()!=NULL)
		{
			MyLNode * templ;
			
			id=deadpool->returnfirst();
			templ=list[row][col].insert(id);
			world1.humans[id].roww=row;
			world1.humans[id].column=col;
			world1.humans[id].life='A';
			world1.humans[id].ptr=templ;
			popul++;
			return true;
			
			
		}
		
		MyLNode * temp;
		temp=list[row][col].insert(id);
		
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
		popul--;
		
		deadpool->insert(personID);
		

      return true;
    }

    bool whereis(int id, int &row, int &col)const{
		
		if(world1.humans[id].life=='D')
		{
			return false;
		}
		
		
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
		
		vector <int> *temp=new vector <int>();
		
		if (row<0 || row > rows || col <0 || col >cols)
		{
			return temp;
		}


		 
	
		MyLNode* tempo;
		tempo= list[row][col].show();
		if (tempo == nullptr)
		{	
			return temp;
		}

		while (tempo!= NULL)
		{
			
			temp->push_back(tempo->getElem());
			tempo = tempo->getNext();	
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
MyList *deadpool;

  
  
   
};
