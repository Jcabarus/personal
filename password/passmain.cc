#include "password.h"

int main()
{
	bool RUN = true;
	int process;
	char choice;

	string pass = "";
	passwordtool user;
	
	do
	{
		process = user.welcome();
		if(process == 1)
		{
			pass = user.enter();
		}
		else if(process == 2)
		{
			cout<<"2\n";

		}
		else if(process == 3)
		{
			cout<<"3\n";

		}
		else if(process == 4)
		{
			cout<<"4\n";

		}
		else
		{

			cout<<"5\n";
		}
		RUN = run();
	}while(RUN);

	cout<<"The END\n";
}
