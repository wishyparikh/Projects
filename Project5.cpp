/*main.cpp*/

//
// Netflix movie search with reviews.
//
// << Wishy Parikh >>
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 02
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <chrono>
using namespace std;

class Reviews           //class reviews to store content of reviews 
{
	private:
	int reviewID;
	int movieID;
	int userID;
	int rating;
	string date;
	
	public:
	Reviews(int reviewID, int movieID, int userID, int rating, string date)          //constructor to initialize the values
	{
		this->reviewID = reviewID;
		this->movieID = movieID;
		this->userID = userID;
		this->rating = rating;
		this->date = date;
	}
	int getreviewID()                      //all the getter functions to access the private data.
	{
		return reviewID;
	}
	int getrating()
	{
		return rating;
	}
	int getmovieID()
	{
		return movieID;
	}
	int getuserID()
	{
		return userID;
	}
	string getdate()
	{
		return date;
	}
	
	
};

class Movies                                    //class movies to store the data of movies
{
	private:
	int movieID;
	string moviename;
	int pubyear;
	float avgrates;
	float avgrate;
	int numreviews;
	int onestar;
	int twostar;
	int threestar;
	int fourstar;
	int fivestar;
	
	
	
	public:
	
	Movies(int movieID, string moviename, int pubyear)                //constructor to initialize the variables
	{
		this->movieID = movieID;
		this->moviename = moviename;
		this->pubyear = pubyear;
		 onestar = 0;
		 twostar = 0;
		 threestar = 0;
		 fourstar = 0;
		 fivestar = 0;
		avgrates = 0;
		avgrate = 0;
		numreviews = 0;
		
		
		
	}                                             
	int getmovieID()                          //all the getter functions to access the private data outside the class.
	{
		return movieID;
	}
	int getpubyear()
	{
		return pubyear;
	}
	string getmoviename()
	{
		return moviename;
	}
	
	
	int getnumberratings()
	{
		return numreviews;
	}
	int get1star()
	{
		return onestar;
	}
	int get2star()
	{
		return twostar;
	}
	int get3star()
	{
		return threestar;
	}
	int get4star()
	{
		return fourstar;
	}
	int get5star()
	{
		return fivestar;
	}
	
	
	
	
	void setavgrating(float rate)                                 //setter function to set the number of reviews and stars for each movie.
	{ 
		if(rate == 1)
			onestar++;
		if(rate == 2)
			twostar++;
		if(rate == 3)
			threestar++;
		if(rate == 4)
			fourstar++;
		if(rate == 5)
			fivestar++;
		
		numreviews++;
		avgrates = ((onestar*1) + (twostar*2) + (threestar*3) + (fourstar*4) + (fivestar*5));
	}
	
	
	float getavgrating()                                      //getter function to calculate average rating for each movie.
	{
		if(numreviews == 0)
			return 0;
		
		
				avgrate = avgrates/numreviews;
		return avgrates/numreviews;
	}
	float returnavgrate()                                   //return the calculated average rating.
	{
		return avgrate;
	}
	
};

int readFilemovie(string filename, map<int, Movies>& M)             //user defined function to accessthe movie file and store the data in the movie class
{
	int i = 0;
	string movieID;
	string moviename;
	string pubyear;
	string line;
		
		ifstream file(filename);                                //ifstream to open file and access it.
		
		if (!file.good())
	{
		cout << "cannot  open  file!" << endl;
		return 0;
	}
	
	getline(file, line);
	while(getline(file, line))
	{
		stringstream ss(line);
		getline(ss,movieID,',');
		getline(ss,moviename,',');
		getline(ss,pubyear);
		Movies mov(stoi(movieID),moviename,stoi(pubyear));
		M.insert(pair<int,Movies>(stoi(movieID), mov));
		i++;
	}
			
	file.close();
	return i;

}


int readFilereviews(string filename, map<int, Reviews> &R, map<int, Movies> &M)        //function for reading reviews file and storing data in reviews class
{
	int i = 0;
	string reviewID;
	string movieID;
	string userID;
	string rating;
	string date;
	string line;
		
		ifstream file(filename);
		
		if (!file.good())
	{
		cout << "cannot  open  file!" << endl;
		return 0;
	}
	
	getline(file, line);
	
	while(getline(file, line))
	{

		stringstream ss(line);
		getline(ss,reviewID,',');
		getline(ss,movieID,',');
		getline(ss,userID,',');
		getline(ss,rating,',');
		getline(ss,date);
		
		M.find(stoi(movieID))->second.setavgrating(stoi(rating));         //this is the important step, after reading each line in reviews file it stores the rating                                                                      values in the movie class. (one by one).
		
		Reviews rev(stoi(reviewID),stoi(movieID),stoi(userID), stoi(rating),date);
		R.emplace( stoi(reviewID), rev );
		i++;
	}
		
	file.close();
	return i;
}
void find(map<int, Reviews> &R, map<int, Movies> &M)
{
	long ID;
	while(true)
	{
	cout<<endl;
	LOOP:cout<<"Please enter a movie ID (<100,000), a review ID (>=100,000), 0 top stop> ";   //searching the movie and review manually.
	cin>>ID;
	cout<<endl;
	if(ID == 0)
	{
		cout<<"** Done! **"<<endl;
		break;
	}
	else if(ID<0)
	{
		cout<<"**invalid id"<<endl;
	}
	else if(ID < 100000)                       //less than 100000 are movies and greater than that are reviews
	{
		if(M.find(ID) == M.end())
		{
			cout<<"movie not found"<<endl;
			goto LOOP;
		}
		else
		{
			Movies mm = M.find(ID)->second;
			
		cout<<"Movie:\t"<<mm.getmoviename()<<endl;
		cout<<"Year:\t"<<mm.getpubyear()<<endl;
		cout<<"Avg rating:\t"<<mm.returnavgrate()<<endl;
		cout<<"Num reviews:\t"<<mm.getnumberratings()<<endl;
		cout<<" 1 star:\t"<<mm.get1star()<<endl;
		cout<<" 2 star:\t"<<mm.get2star()<<endl;
		cout<<" 3 star:\t"<<mm.get3star()<<endl;
		cout<<" 4 star:\t"<<mm.get4star()<<endl;
		cout<<" 5 star:\t"<<mm.get5star()<<endl;
		}
	}
	 if(ID >= 100000)
	{
		
		if(R.find(ID) == R.end())
		{
			cout<<"review not found"<<endl;
			goto LOOP;
		}
		else
		{
			Reviews rr = R.find(ID)->second;
		Movies m = M.find(rr.getmovieID())->second;
		cout<<"Movie: "<<rr.getmovieID()<<"("<<m.getmoviename()<<")"<<endl;
		cout<<"Num stars: "<<rr.getrating()<<endl;
		cout<<"User id:\t"<<rr.getuserID()<<endl;
		cout<<"Date:\t"<<rr.getdate()<<endl;
		}
		
	}
	}
}



int main()                   //main fnction to run the code
{ 
	int num = 0;
	string  filename;
	string filename2;
	
	cout<<"** Netflix Movie Review Analysis **"<<endl;
	
	cin >> filename;
	cin>>filename2;
	cout<<filename<<endl;
	cout<<filename2<<endl;
	cout<<endl;
	
	auto  beginTime  =  std::chrono::steady_clock::now();
	
	
	map<int, Movies> M;                    //map of movie objects 
	num = readFilemovie(filename, M);
	cout<<">> Reading movies... "<<num<<endl;
	cout<<endl;
	auto  endTime  =  std::chrono::steady_clock::now();
	auto diff  =  endTime-beginTime;
	cout  <<  "  [  time:  "<<  std::chrono::duration<double,  std::milli>(diff).count()<<  "  ms  ]"  <<  endl;
	
	
beginTime  =  std::chrono::steady_clock::now();
	map<int,Reviews> R;                            //map of review objects
	num = readFilereviews(filename2, R, M);
	cout<<">> Reading reviews... "<<num<<endl;
	cout<<endl;
	
	endTime  =  std::chrono::steady_clock::now();
	diff  =  endTime-beginTime;
	cout  <<  "  [  time:  "<<  std::chrono::duration<double,  std::milli>(diff).count()<<  "  ms  ]"  <<  endl;
	
	beginTime  =  std::chrono::steady_clock::now();
	
	multimap<float, Movies> m2;                       //created a multimap so that average rating can be stored in sorted order then printed the bottom 10 values(as                                                     they are sorted in ascending order) to get top 10 values. 
	map<int, Movies>::iterator p;
    for (p = M.begin(); p!=M.end(); ++p)
        m2.insert(make_pair(p->second.getavgrating(), p->second));
	int i = 1;
	
	cout<<">> Top 10 Movies <<"<<endl;
	cout<<endl;
	cout<<"rank"<<"\t"<<"ID"<<"\t"<<"reviews"<<"\t"<<"Avg"<<"\t"<<"Name"<<endl;
	
	
	multimap<float, Movies>::reverse_iterator a;              //reverse iterator to print bottom 10 values as they will be the top 10 movies.
    for (a = m2.rbegin(); a!=m2.rend(); ++a)
	{
		cout<<i<<"\t"<<a->second.getmovieID()<<"\t"<<a->second.getnumberratings()<<"\t"<<a->first<<"\t"<<a->second.getmoviename()<<endl;
		
	if(i==10)
		break;
		
		i++;
	}
	
	 endTime  =  std::chrono::steady_clock::now();
	diff  =  endTime-beginTime;
	cout  <<  "  [  time:  "<<  std::chrono::duration<double,  std::milli>(diff).count()<<  "  ms  ]"  <<  endl;
	
	cout<<endl;
	cout<<">> Movie and Review Information <<"<<endl;
	
	find(R,M);
	
	
	return 0;
	
	
}