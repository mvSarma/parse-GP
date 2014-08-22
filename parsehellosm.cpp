#include <iostream>
#include <vector>
#include <sys/time.h>
#include <ctime>
#include <ctime>
#include <fstream>

using namespace std;

class ToBeParsed
{
	private:
	static int aa;				// already available
	static ToBeParsed *tbp;			// Singleton class implementation
	vector<char> v;
	ToBeParsed(ToBeParsed &) {}		// suppressing copy constructor
	
	ToBeParsed& operator=(const ToBeParsed &);	// suppressing assignment operator
	
	public:
	string str;
	
	ToBeParsed(const string s) : str(s)		// Instantiation
	{}
	
	static ToBeParsed* create(string);	// Static Factory Method
	
	bool parse(char);
	
	~ToBeParsed()
	{
		cout << "Destructing the object";
		delete(tbp);
		cout << endl << "success" << endl;
	}
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
			if (c == str.at(0))
			{
				 i=1;j=1;
				 return false;
		 	}
		 	break;
		 }
		 case 1:
		 {
			 if(c == str.at(j))
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

int main(int argc, char **argv)
{
	int abcd = 0;
	timestamp_t t0;
	ToBeParsed *tbp;
	char c;
	ifstream fp("input.txt");
	if(argc == 1)				// In ubuntu 14.04, gcc. 'argc' may be 0 in some compilers or in other operating systems.
		tbp = ToBeParsed::create("hello");
	else
		tbp = ToBeParsed::create(argv[1]);
	t0 = get_timestamp();
	while(true)
	{
		//c = cin.get();
		fp.get(c);
		bool getout = tbp->parse(c);
		if(getout)
			break;
	}
	timestamp_t t1 = get_timestamp();
	double secs = (t1 - t0) / 1000000.0L;
	cout << endl << endl << "Thank You for your Participation !! " << tbp->str << " detected in " << secs << endl;
	fp.close();
}
