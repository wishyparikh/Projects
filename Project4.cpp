/*main.cpp*/

//
// Grade Analysis program in modern C++.
//
// << Wishy Parikh >>
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 01
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;


class Course     //this class contains all the information for different courses
{

public:
string Department;
int coursenum;
string title;
int grades[10];
string instructor;






public:

Course(string Department, int coursenum, string title, int grades[10], string instructor)
{
  this->Department = Department;                 //constructor for initializing the variables for courses
  this->coursenum = coursenum;
  this->title = title;
  for(int i=0;i<10;i++)
  {
    this->grades[i]=grades[i];
  }
  this->instructor = instructor;
  
}

int totalgrades()            // returns total number of grades in a specific course.
{
  int total=0;
  for(int i=0; i<5;i++)
  {
    total=grades[i]+total;
    
  }
  
  return total;
}

int requestnumgrade(int i)    //getter function for getting number of grades
{
  return grades[i];
}

string requestdept()  // getter function for department
{
  return Department;
}

string requestinst()   // getter function for instructor name
{
  return instructor;
}


void print()    //function for printing the Distribution of courses.
{
   

  
  int numA = grades[0];
  int numB = grades[1]; 
  int numC = grades[2];
  int numD = grades[3];
  int numF = grades[4];
  
  int totalstuds=numA+numB+numC+numD+numF+grades[5]+grades[6]+grades[7]+grades[8]+grades[9];
 float num=numA+numB+numC+numD+numF;
 float dfw= numA+numB+numC+numD+numF+grades[9];
  float rate = numD+numF+grades[9];
  
 if((numA==0)&&(numB==0)&&(numC==0)&&(numD==0)&&(numF==0)&&(grades[6]<100))
 {
   cout << Department << " " << coursenum << " " << "(" << instructor << "): " << endl;
			cout << "Num students: " << totalstuds << endl;
			cout << "  Distribution: no report" << endl;
			cout << "DFW rate: 0.00%"  << endl;
			return;
}

if(grades[6]>100)
 {
   cout << Department << " " << coursenum << " " << "(" << instructor << "): " << endl;
			cout << "Num students: " << totalstuds << endl;
			cout << "  Distribution: no report" << endl;
			cout << "DFW rate: 100.00%"  << endl;
			return;
}
 
 cout << Department << " " << coursenum << " " << "(" << instructor << "): " << endl;
  cout << "Num students: " << totalstuds << endl;
  cout<<" Distribution: "<<(numA/num)*100<<"%, ";
cout<<(numB/num)*100<<"%, ";
cout<<(numC/num)*100<<"%, ";
cout<<(numD/num)*100<<"%, ";
cout<<(numF/num)*100<<"%"<<endl;
cout << "DFW rate: " <<(rate/dfw)*100<<"%"<< endl;
  
}










};


class Parts       //this class contains the parts of projects. part 1 and part 2
{
  public:
  void part1(vector<Course> &tempcourses)     //part 1 
  {
    
    	int totalgrade = 0;
	for(auto i: tempcourses)
	{
	 totalgrade=i.totalgrades() + totalgrade;
	  
	}
float numA = 0;
float numB = 0;
float numC = 0;
float numD = 0;
float numF = 0;
for(int i=0;i<tempcourses.size();i++)
{
  numA = tempcourses[i].requestnumgrade(0) + numA;
  numB = tempcourses[i].requestnumgrade(1) + numB;
  numC = tempcourses[i].requestnumgrade(2) + numC;
  numD = tempcourses[i].requestnumgrade(3) + numD;
  numF = tempcourses[i].requestnumgrade(4) + numF;
}
cout<<"College of Engineering:"<<endl;
cout<<" Num courses: "<<tempcourses.size()<<endl;
cout<<" Num grades: "<<totalgrade<<endl;
cout<<" Distribution: "<<(numA/totalgrade)*100<<"%, ";
cout<<(numB/totalgrade)*100<<"%, ";
cout<<(numC/totalgrade)*100<<"%, ";
cout<<(numD/totalgrade)*100<<"%, ";
cout<<(numF/totalgrade)*100<<"%"<<endl;
}

void part2(vector<Course>& tempcourses)   //part 2 of project
{
  string fields[11] = { "BIOE", "CHE", "CME", "CS", "ECE", "ENER", "ENGR", "IE","IT", "ME", "MENG" };
  
    int counter = 0;
  for(auto j: fields)
  {
  int num=0;
  float numA = 0;
  float numB = 0;
  float numC = 0;
  float numD = 0;
  float numF = 0;
  
     while(j == tempcourses[counter].requestdept())
    {
      num++;
      numA = tempcourses[counter].requestnumgrade(0) + numA;
      numB = tempcourses[counter].requestnumgrade(1) + numB;
      numC = tempcourses[counter].requestnumgrade(2) + numC;
      numD = tempcourses[counter].requestnumgrade(3) + numD;
      numF = tempcourses[counter].requestnumgrade(4) + numF;
      counter++;
      
      if(counter==tempcourses.size())
      {
        break;
      }
    }
    
  
  int numgrade = numA+numB+numC+numD+numF; 
  cout<<j<<":"<<endl;
cout<<" Num courses: "<<num<<endl;
cout<<" Num grades: "<<numgrade<<endl;
cout<<" Distribution: "<<(numA/numgrade)*100<<"%, ";
cout<<(numB/numgrade)*100<<"%, ";
cout<<(numC/numgrade)*100<<"%, ";
cout<<(numD/numgrade)*100<<"%, ";
cout<<(numF/numgrade)*100<<"%"<<endl;
  
  }
}

};



auto Find_Course( vector < Course> &tempcourses, string inst)   //this is a function for finding course in the vector of courses.
{ 
	auto cc = std::find_if ( tempcourses.begin (), tempcourses.end(), 
		[=](  Course& c)    
	{
	  
	if ((inst.length() == 2)&&(c.requestinst()[0] == inst[0])&&(c.requestinst()[1] == inst[1]))
		{
			return true;
		}
	  
	
	else if ((inst.length() == 3)&&(c.requestinst()[0] == inst[0])&&(c.requestinst()[1] == inst[1])&&(c.requestinst()[2] == inst[2]))
		{
			return true;
		}
		else if ((inst.length() == 4)&&(c.requestinst()[0] == inst[0])&&(c.requestinst()[1] == inst[1])&&(c.requestinst()[2] == inst[2])&&(c.requestinst()[3] == inst[3]))
		{
			return true;
		}
		else if(c.requestinst() == inst)
		{
		  return true;
		}
			
		else
			return false;
	}
	);

	
	return cc;
}








int main()   // the main function that actually runs the code.
{

  string  filename;

 LOOP:cin >> filename;
      cout<<filename<<endl;
      cout<<endl;

  cout << std::fixed;
  cout << std::setprecision(2);

ifstream file;
file.open(filename);     //opening the file
if (!file.good())
	{
		cout << "cannot  open  file!" << endl;
		goto LOOP;
	}
	vector<Course> courses;  //vector of courses to store different types of courses.
	string line, department, number, title, grade, instructor;
	int g[10];
	getline(file, line);
	
	while(getline(file,line))
	{
	  stringstream parts(line);
	  getline(parts,department,',');
	  getline(parts,number,',');
	  getline(parts,title,',');
	  
	  for (int i = 0; i < 10; i++)
		{
			getline(parts, grade, ',');
			g[i] = stoi(grade);
		}
	  
	  getline(parts,instructor);
	  
	  Course c(department, stoi(number), title, g, instructor);
	  
	  courses.push_back(c);
	}
	
Parts p1;
p1.part1(courses);
cout<<endl;
p1.part2(courses);

cout<<endl;

 string inst;

while(inst != "#")       //loop for part 3 where user enters the instructors name 
{
	AGAIN : cout << "Please enter instructor's name (or prefix or #)>  " << endl;
	        cin >> inst;
  
  
 
  
 
  
  
  
  
 /*  for (int i = 0; i < courses.size(); i++)
	{
		if (courses[i].requestinst() == inst)
		{
			break;
		}
		
		if (i == courses.size()-1)
		{
			goto AGAIN;
		}
			
	}*/
	
	auto printer = Find_Course(courses, inst);
 
 while (printer != courses.end())
	{
	  	printer->print();
	  	printer->instructor = "null";
		printer = Find_Course(courses, inst);

		if (printer == courses.end())
			break;
		
	

		

}

}



  cout << endl;
  return 0;
}
