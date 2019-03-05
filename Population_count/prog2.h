

#include "GWInterface.h"
#include <vector>
#include <iostream>
using namespace std;

using std::vector;

class GridWorld : public GWInterface 
{
public:
	GridWorld(unsigned nrows, unsigned ncols) 
	{
       // Assigning Gridworld. dimensions
	   numPeople = 0;
	   rs = nrows;
	   cs = ncols;

		// 2D ARRAY OF DISTRICTS    District grid 5*5
		 district = new District*[nrows];
		for (int i = 0; i < nrows; i++)
		{
			district[i] = new District[ncols];
		}    
		peopleInfo people[100];
	}
	~GridWorld() 
	{
        // DEALLOCATION PROBLEM FOR DELETING ALL LISTS.---------------FIX ME.
		for (int i = 0; i <rs; i++)
		{
			for (int j = 0; i < cs; j++)
			{
				delete district[rs][cs].list;
			}
			
		}
	
		// DEALLOCATIONG THE N*N GRID.
		for (int i = 0; i <rs; i++)
		{
			delete[] district[i];
		}
		delete[] district;	  

		// DEALLOCATING THE PEOPLE'S ARRAY.
		delete[] people;
		// your destructor code here.

		// STILL LEFT TO DEALLOCATE THE DEADPOOL.....................FIX ME.
		delete deadpool;
	}

	bool birth(int row, int col, int &id) 
	{
		// REALLOCATION OF PEOPLE'S ARRAY IF IT IS FULL.
		//cout << " People's array: " << numPeople << endl;

		//IF sizeOfpeople is same as numPeople then resize by double.
		if ( numPeople == sizeOfpeople)
		{
			//cout << " enter" << endl;
			resize();
		}  

		// ERROR CHECKING.
		if (row < 0 || row > (rs-1))
		{
		//	cout << " Not valid row";
			return false;
		}

		if (col < 0 || col > (cs-1))
		{
		//	cout << " Not valid coloumn";
			return false;
		} 


		// CHECK IF THE DEADPOOl IS NON EMPTY-----------------------------------------------------------------------
		// IF THE DEADPOOL IS NON EMPTY RESUSE THE LAST ID, AND GARBAJE THAT.
		if (deadpool->getfront() != nullptr)
		{
			// DEBUGGING.
			deadpool->print();

			int idd = 0;
			idd = deadpool->getTop();

			// Assign ID. Pass by reference.
			id = idd;

			// NOW POP THE TOP VALUE OF THE LIST.
			deadpool->pop_front();
			deadpool->print();


			// PEOPLE'S INFO UPDATED.    PEOPLE ARRAY UPDATED.
			people[idd].roww = row;
			people[idd].coloumn = col;
			people[idd].alive = true;

			// DEBUGGING
			check_death(idd);


			// INCREMENT THE POPULATION OF THAT PARTICULAR DISTRICT.
			district[row][col].pop_district++;

			//	ADD THE ID THE LIST OF THAT PARTICULAR DISTRICT.      DISTRICT UPDATION LIST
			people[idd].id_ptr = district[row][col].list->push_back(idd);

			// DEBUGGING
			cout << " Value in id-pointer for district:  (" << row << "," << col << " ) are: " << people[idd].id_ptr->ID << endl;
			cout << " Values in the district (" << row << "," << col << " ) are: " << endl;

			district[row][col].list->print();
			district[row][col].list->r_print();

			cout << endl << endl;

			// INCREMENT THE NUMBER OF PEOPLE LIVING.
			curr_numPeople++;
			return true;
		}

		else
		{ 
			// Assign ID.-----------1
			id = numPeople;      // People's array track.

			// INCREMENT THE POPULATION OF THAT PARTICULAR DISTRICT.------------2
			district[row][col].pop_district++;

			//	ADD THE ID THE LIST OF THAT PARTICULAR DISTRICT.--------DISTRICT UPDATION LIST------------3
			people[id].id_ptr = district[row][col].list->push_back(id);

			// DEBUGGING.
			cout << " Value in id-pointer for district:  (" << row << "," << col << " ) are: " << people[id].id_ptr->ID << endl;
			cout << " Values in the district (" << row << "," << col << " ) are: " << endl;
			district[row][col].list->print();
			district[row][col].list->r_print();
			cout << endl << endl;


			// SET THE INFORMATION OF NEW CHILD BORN ,, PEOPLE ARRAY UPDATED.---------------------------------4
			people[numPeople].roww = row;
			people[numPeople].coloumn = col;
			people[numPeople].alive = true;
			people[numPeople].id = numPeople;

			// DEBUGGING
			check();

			// Incremement the population because of birth.-----------------------------------5
			numPeople++;
			curr_numPeople++;
			return true;
		}
		
	}

	



	// ---------------------DEATH!!!!!!!!!!------------------------------------------------------------------------------------------
	bool death(int personID) 
	{
		// Error checking   ----------1
		if ( (personID <0 )  || (personID > numPeople))
		{
			//cout << " Not a valid person ID" << endl;
			return false;
		}

		// POP FROM THE DISTRICT.                DISTRICT LIST UPDATION.-------------2
		if (people[personID].alive == true)
		{
			district[people[personID].roww][people[personID].coloumn].list->pop_personID(people[personID].id_ptr);
			district[people[personID].roww][people[personID].coloumn].list->print();
		}

		else
		{
		//	cout << " Don't try to kill person who is already dead.";
			return false;
		}

		//cout << endl << endl;

		// Update People's info.  Set the flag to be false for that index of ID.---- PEOPLE ARRAY UPDATION-------------3
		people[personID].alive = false;
		
		// DEBUGGGING
		cout << "People's infos are: " << endl;
		check_death( personID); 

		
		// Create a DeadPool. Push the id to the back of the deadpool list. -------     DEADPOOL UPDATION---- ----------4
		 deadpool->push_back(personID);

		 // DEBUGGGING
		cout << " DEEAAAAAD POOOLLLLLL are: " << endl;
		deadpool->print();
		cout << endl;

		// deCREMENT THE POPULATION OF THAT PARTICULAR DISTRICT.------------2
		district[people[personID].roww][people[personID].coloumn].pop_district--;

		// Decrement the population because of death.-------------------------5
		curr_numPeople--;
		return true;
		
	}


	bool move(int id, int targetRow, int targetCol)
	{
		// ERROR CHECKING.--------------------------------------------------------------1
		// NOT VALID ID....OR TRYING TO MOVE A PERSON WHO IS DEAD.
		if (  id < 0   || id > numPeople || people[id].alive == 0)
		{
			// DEBUGGGING
			cout << " Either not valid or you are trying to move a person who is dead.";
			return false;
		}

		else
		{
			//----------UPDATE DISTRICT PROCEDURE..................................

			// POP THE ELEMENT FROM THE GIVEN DISTRICT.--------------------------------2

			// DEBUGGG
			cout << " THE DISTRICT: (" << people[id].roww << "  " << people[id].coloumn << " )  has given list values: " << endl;
			district[people[id].roww][people[id].coloumn].list->print();

			district[people[id].roww][people[id].coloumn].list->pop_personID(people[id].id_ptr);

			// UPDATE DISTRICT POPULATION.
			district[people[id].roww][people[id].coloumn].pop_district--;

			// DEBUGGG
			cout << " THE DISTRICT: (" << people[id].roww << "  " << people[id].coloumn << " )  has given list values: " << endl;
			district[people[id].roww][people[id].coloumn].list->print();



			// PUSH THAT ID TO THE TARGET DISTRICT.---------------------------------3
			// HERE WE ARE REALLOCATING THE ID TO DIFFERENT DISTRICT.

			// DEBUGG
			cout << " THE DISTRICT: (" << targetRow << "  " << targetCol << " )  has given list values: " << endl;
			district[targetRow][targetCol].list->print();

			people[id].id_ptr= district[targetRow][targetCol].list->push_back(id);

			// UPDATE DISTRICT POPULATION.
			district[targetRow][targetCol].pop_district++;

			// DEBUGG
			cout << " THE DISTRICT: (" << targetRow << "  " << targetCol << " )  has given list values: " << endl;
			district[targetRow][targetCol].list->print();


			// ---------------------UPDATE PEOPLE'S ARRAY PROCEDURE.------------------------------   4

			people[id].roww = targetRow;
			people[id].coloumn = targetCol;
			check_death(id);


			return true;
		}
		
	}

	std::vector<int> * members(int row, int col)const
	{
		// ERROR CHECKING.

		if (row<0 || row >(rs - 1) || col <0 || col >(cs - 1))
		{
			cout << " Not a valid row and col";
			return nullptr;
		}


		std::vector <int> *snapshot = new std::vector <int>();
	
		Node* temp = nullptr;
		temp = district[row][col].list->getfront();	
		if (temp == nullptr)
		{	
			return snapshot;
		}

		while (temp!= nullptr)
		{
			snapshot->push_back(temp->ID);
			temp = temp->next;	
		}
		return snapshot;
	}

	bool whereis(int id, int &row, int &col)const 
	{
		if (id <0 && id >numPeople)
		{
			return false;
		}

		row = people[id].roww;
		col = people[id].coloumn;	
	}

	int population()const 
	{
		return curr_numPeople;
	}

	int population(int row, int col)const 
	{
		return district[row][col].pop_district;
	}

	int num_rows()const 
	{
		return rs;
	}
	int num_cols()const 
	{
		return cs;
	}


	//---------------------------------- DEBUGGING-------------------------------
	void check()
	{

		cout << " ID for Person Number:   " << numPeople << endl;
		cout << " Person is in this row:   " << people[numPeople].roww << endl;
		cout << " Person is in this coloumn:  " << people[numPeople].coloumn << endl;

		if (people[numPeople].alive == 1)
		{
			cout << " Life status: ALIVE " << endl;
		}
		else
		{
			cout << " Life status: DEATH " << endl;
		}
		//cout << " Life status:  " << people[numPeople].alive << endl;
		//cout << " ID of person: " << people[numPeople].id << endl;

	}


	//---------------------------------- DEBUGGING-------------------------------
	void check_death(int personID)
	{
		cout << " ID for Person Number:   " << personID << endl;
		cout << " Person is in this row:   " << people[personID].roww << endl;
		cout << " Person is in this coloumn:  " << people[personID].coloumn << endl;

		if (people[personID].alive == 1)
		{
			cout << " Life status: ALIVE " << endl;
		}
		else
		{
			cout << " Life status: DEATH " << endl;
		}
	}

	// -----------------------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------------------------
	


private:

	// Helper functions for linked list.
	struct Node
	{
		Node*next = nullptr;
		Node*prev= nullptr;
		int ID = 0;      // ID OF PEOPLE.	
		Node(const int & d = int{}, Node * n = nullptr, Node * p = nullptr)
			: ID{ d }, next{ n }, prev{ p } { }
	};

  // LIST CLASS...........................
	class List
	{
	private:
		Node * front;
		Node* back;

		void init()
		{
			front = nullptr;
			back = nullptr;
		}
		

	public:

		// constructors
		List() 
		{
			init();
		}

		~List() 
		{
			clear();
		}

		void setfront()
		{
			front = front->next;
		}

		Node* getfront()
		{
			return front;
		}

		Node* getback()
		{
			return back;
		}

		void clear() 
		{
			Node * p = front;
			Node *pnext;

			while (p != nullptr) 
			{
				pnext = p->next;
				delete p;
				p = pnext;
			}
			front = back = nullptr;
		}


		void push_front(int ID)
		{

			front = new Node(ID, front);

			if (back == nullptr)
				back = front;
		}

		void pop_personID(Node* id)
		{

			// EMPTY LIST.
			if (front == nullptr)
			{
				return;
			}

			// SINGELETON LIST.
			if (front->next == nullptr)
			{
				//id->next = nullptr;
				//id -> prev = nullptr;

				front = nullptr;
				back = nullptr;
				delete id;
				return;

			}

			// PREVIOUS OF FRONT IS EMPTY. FIRST NODE TO BE DELETED IN ENTIRE LIST.
			if (id->prev == nullptr)
			{ 
				front = id->next;
				id->next->prev = id->prev;
				delete id;
				return;

			}

			// NEXT OF BACK IS EMPTY. LAST NODE TO BE DELETED IN ENTIRE LIST.
			if (id-> next == nullptr)
			{
				back = id->prev;
				id->prev->next = id->next;
				delete id;
				return;

			}

			// List is non empty and list contain more than one element.

			id->prev->next = id->next;
			id->next->prev = id->prev;
			delete id;
				
		}

		//  ------------POP THE TOP--------------------------------------
		void pop_front() 
		{
			Node *tmp;

			if (front == nullptr)
				return ;
			
			tmp = front;
			front = front->next;
			delete tmp;

			if (front == nullptr)
				back = nullptr;
			//numElements--;
			return;
		}


		Node* push_back(int &ID)
		{
			//numElements++;
			Node *tmp = new Node(ID, nullptr, back);

			

			if (this->front == nullptr) 
			{
				front = back = tmp;
			}
			else 
			{

				back->next = tmp;
				back = tmp;
			}

		  return tmp;


		}

		void print() const
		{
			Node *p = front;

			cout << "[ ";
			while (p != nullptr) {
				cout << p->ID << " ";
				p = p->next;
			}
			cout << "]\n";
		}

		// Display reverse.
		void r_print() const
		{
			Node *p = back;

			cout << "[ ";
			while (p != nullptr) {
				cout << p->ID << " ";
				p = p->prev;
			}
			cout << "]\n";
		}

		// Get the top value or front value of the list.

		int getTop()
		{
			return front->ID;
		}


	};

	// DISTRICT ARRAY UPDATION.
	struct District
	{
		int pop_district = 0;   //Population of district
		List* list = new List; // LIST OF EVERY DISTRICT.
		// Node for members.
	};

    //  STRUCT FOR PEOPLE'S ARRAY INFORMATION.
	struct peopleInfo
	{
		int roww = 0;
		int coloumn = 0;
		bool alive = false;
		int id = 0;
		Node* id_ptr;    // Points to current ID.
	};

	int rs;          // Grid row size
	int cs;          // Grid col size
	int numPeople = 0;                 // Total trace of the population including birth and death.
	int curr_numPeople = 0;            // Total number of current population in world. 
	//District **district = new District*[rows];
	District **district;
	int sizeOfpeople = 2;

	// List for the dead ids.
	List* deadpool = new List;

	peopleInfo* people = new peopleInfo[sizeOfpeople];

	// DYNAMIC ARRAY ALLOCATION FUNCTION.
	void resize() 
	{
		peopleInfo* temp;
		int double_capacity = 2 *sizeOfpeople;
		temp = new peopleInfo[double_capacity];

		for (int i = 0; i < sizeOfpeople; i++)
		{
			temp[i].roww = people[i].roww;
			temp[i].coloumn = people[i].coloumn;
			temp[i].id = people[i].id;
			temp[i].alive = people[i].alive;
			temp[i].id_ptr = people[i].id_ptr;
			
		}
		delete people;
		sizeOfpeople = double_capacity;
     	people = temp;
	}     
	// private stuff goes here!
	//   typedefs
	//   data members
	//   private helper functions
	//   etc.

};
