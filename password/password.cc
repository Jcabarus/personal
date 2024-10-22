#include "password.h"

//Welcome message function
int passwordtool::welcome()
{
	int choice = 0;

	cout<<"Welcome to the password tool"<<endl;
	cout<<"Which option would you like to use"<<endl;
  	cout<<"(1) Password Check"<<endl;
	cout<<"(2) Password Generator"<<endl;
  	cout<<"(3) Passphrase Generator"<<endl;
  	cout<<"(4) View Password File"<<endl;
 	cout<<"(5) Rewrite Password"<<endl;

	do
	{
		cout<<"What choice would you like to use: ";
		cin>>choice;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			choice=0;
		}
	}while(choice<1||choice>5);

	if(choice==2||choice==3)
	{
		genflag=1;
	}

	return choice;
}

bool run()
{
	char choice;
	cout<<"Would you like to run the program again (y/n): ";
	do
	{
		cin>>choice;
	}while(choice!='y'&&choice!='Y'&&choice!='n'&&choice!='N');

	if(choice=='y'||choice=='Y')
	{
		return true;
	}
	else
	{
		return false;
	}

}

//Start of class functions
passwordtool::passwordtool()
{
	regex specsearch("[!@#$%^&*()_+-={}|\\;:,./<>?`~'\"\\[\\] ]");
	passlen = 0;
	passspecial = 0;
	passnum = 0;
	passup = 0;
	passlow = 0;
	userpassword = "";
	genflag = 0;
	//password changes for testing
	passbig = "";
	passsmall = "";
	passalt = "";
}

string passwordtool::enter()
{
	char eat;
	string p;
	cout<<"Please enter the password you want to use"<<endl;
	getline(cin, p);
	userpassword = p;
	cin>>eat;
	return p;
}

void passwordtool::password(int x)
{
	 passwordc(x);
}

void passwordtool::passwordc(int len)
{
	string word="";

	userpassword=word;
}

void passwordtool::passphrase(int x)
{
	passphrasec(x);
}

void passwordtool::passphrasec(int len)
{
	string phrase="";

	userpassword=phrase;
}


void passwordtool::check()
{
	CHECK();
}

void passwordtool::CHECK()
{
	bool FAIL = false;

	do
	{
		FAIL = exposed(userpassword);
		FAIL = repeat(userpassword);

		if(FAIL)
		{
			enter();
		}
		else if(FAIL && genflag == 1)
		{

		}
	}while(FAIL);

	calculation(userpassword);
}

bool passwordtool::exposed(string pass)
{
	string rock;
	trans();

	ifstream passlist("rockyou.txt");
	if(passlist.is_open())
	{
		do
		{
			getline(passlist, rock);
			if(rock == pass)
			{
				return true;
			}
			else if(rock == passbig)
			{
				return true;
			}	
			else if(rock == passsmall)
			{
				return true;
			}
			else if(rock == passalt)
			{
				return true;
			}
		}while(!passlist.eof());

	}

	return false;

}

bool passwordtool::repeat(string pass)
{
	for(int k = 0;k < pass.size();k++)
	{
		if(k >= 2 && pass[k] == pass[k-1] && pass[k] == pass[k-2])
			return true;
		if(k >= 3 && pass[k] == pass[k-2] && pass[k-1] == pass[k-3])
			return true;
		if(k>=5&&pass[k]==pass[k-3]&&pass[k-1]==pass[k-4]&&pass[k-2]==pass[k-5])
			return false;
	}
	return false;
}


void passwordtool::calculation(string p)
{
	int up=0,low=0,special=0,num=0;
	passlen=p.length();
	for(int k=0;k<p.size();k++)
	{
		if(isdigit(p[k]))
			num++;
		if(isupper(p[k]))
			up++;
		if(islower(p[k]))
			low++;
		if(regex_match(string(1, p[k]), specsearch))
			special++;
	}
	passlow=low;
	passup=up;
	passspecial=special;
	passnum=num;
}

void passwordtool::trans()
{
	passbig=userpassword;
	passsmall=userpassword;
	passalt=userpassword;

	transform(passbig.begin(), passbig.end(), passbig.begin(), ::toupper);
	transform(passbig.begin(), passbig.end(), passbig.begin(), ::tolower);
	for(int k=0;k<passalt.size();k++)
	{
		if(isupper(passalt[k]))
			passalt[k]=::tolower(passalt[k]);
		else if(islower(passalt[k]))
			passalt[k]=::toupper(passalt[k]);
	}

}
