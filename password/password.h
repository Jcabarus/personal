#include <iostream>
#include <cctype>
#include <fstream>
#include <regex>
#include <algorithm>
#include <limits>
using namespace std;

bool run();

class passwordtool
{
	public:
		passwordtool();
		void password(int);
		void passphrase(int);
		void check();
		string enter();
		int welcome();
	private:
		//password variables
		int passlen;
		int passspecial;
		int passnum;
		string userpassword;
		string passbig;
		string passalt;
		string passsmall;
		int passup;
		int passlow;
		int genflag;
		//create
		void passwordc(int);
		void passphrasec(int);
		//check
		void CHECK();
		bool repeat(string);
		bool exposed(string);
		void calculation(string);
		//regex
		regex specsearch;
		//changes user's password
		void trans();

};


