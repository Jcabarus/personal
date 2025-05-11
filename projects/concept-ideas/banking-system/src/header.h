#include <iostream>
#include <fstream>

using namespace std;

enum action
{
    login, sigup, transaction
};

class SignIn
{
    public:
        SignIn();  
        bool Exist();
        bool Invalid();
        
    private:
        string username, password;
};
    
class SignUp
{
    public:
        SignUp();
        bool Exist();
        
    private:
        string username, password;

};
    
class Session
{
    public:
        // Session();    
        
    private:
};