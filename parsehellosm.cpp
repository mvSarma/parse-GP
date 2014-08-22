#include <iostream>		//cout && cin
#include <cstdlib>		//exit
#include <sys/time.h>	//timevalue
#include <ctime>		//  "
#include <fstream>		//ifstream
#include <csignal>		//signal
#include <sstream>		//stringstream
//#define TIMEIT
#define FILEIN

using namespace std;

class ToBeParsed
{
	private:
	static int aa;				// already available
	static ToBeParsed *tbp;			// Singleton class implementation
	ToBeParsed(ToBeParsed &) {}		// suppressing copy constructor
	
	ToBeParsed& operator=(const ToBeParsed &);	// suppressing assignment operator
	
	public:
	string str;
	
	ToBeParsed(const string s) : str(s)		// Instantiation
	{}
	
	static ToBeParsed* create(string);	// Static Factory Method
	
	bool parse(char);
};

ToBeParsed* ToBeParsed::tbp = NULL;
int ToBeParsed::aa = 0;

inline ToBeParsed* ToBeParsed::create(string s)
{
	if(ToBeParsed::aa == 0)			// Singleton class implementation
	{
		ToBeParsed::tbp = new ToBeParsed(s);
		ToBeParsed::aa = 1;
	}
	return ToBeParsed::tbp;
}

bool ToBeParsed::parse(char c)
{
	static int i, j;	 
	switch(i)
	{
		 case 0:
		 {
			if (c == str.at(0))		// i->to find the first character of the string to be parsed;
			{
				if(str.length() == 1)
					return true;
				i=1;j=1;
				return false;
		 	}
		 	break;
		 }
		 case 1:
		 {
			 if(c == str.at(j))		//j->traverses through all char of the string
			 {
				i=1;j++;
			 	if(j == str.length())
					 return true;
			 }
			 else 
				 i=0;
			return false;
		 	break;
 		}
 		default:
 		{
 			i=0;
 			return false;
 		}
 	}
}

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp ()
{
	struct timeval now;
	gettimeofday (&now, NULL);
	return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

void handlectrl_c(int num)
{
	if(num == 2)
		cout << endl << "Got Ctrl^C!! exiting" << endl;
	exit(num);
}

int main(int argc, char **argv)
{
	timestamp_t t0;
	ToBeParsed *tbp;
	char c;
	signal(SIGINT, handlectrl_c);  	// registering the signal
	ifstream fp("input.txt");
	if(argc == 1)				// In ubuntu 14.04, gcc. 'argc' may be 0 in some compilers or in other operating systems.
		tbp = ToBeParsed::create("hello");
	else
	{
		stringstream ss;
		for(int i=2 ; i<=argc ; i++)
		{
			ss << argv[i-1];
			if(i != argc)
				ss << " ";
		}
		tbp = ToBeParsed::create(ss.str());
	}
	cout << " " << tbp->str << " To be parsed of length " << tbp->str.length() << endl;
	#ifdef TIMEIT
		t0 = get_timestamp();
	#endif
	while(true)
	{
		#ifdef FILEIN
			fp.get(c);
			if(fp.eof())
			{
				cout << endl << tbp->str << " not found" << endl;
				exit(0);
			}
		#else
			c = cin.get();
		#endif
		bool getout = tbp->parse(c);
		if(getout)
			break;
	}
	#ifdef TIMEIT
		timestamp_t t1 = get_timestamp();
		double secs = (t1 - t0) / 1000000.0L;
	#endif
	cout << endl << " " << tbp->str << " detected ";
	#ifdef TIMEIT
		cout << "in " << secs << " seconds";
	#endif
	cout << endl;
	fp.close();
}
