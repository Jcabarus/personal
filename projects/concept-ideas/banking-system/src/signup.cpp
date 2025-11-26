/*
    [2/3] Must handle account creation
        [] Bug, when being inserted, it overwrites existing user entries
    [x] Must handle whether the account already exist
    [x] Must handle password creation complexity
*/

#include "header.h"

void sign_up_prompt(packet_session& session);
bool valid_username_flag(string& user_name);
bool valid_password_flag(string& password);
void register_account(string& username, string& password);

void sign_up_menu()
{   
    packet_session sign_up_session;
    sign_up_session.session_id = 0;
    sign_up_session.action = sign_up;
    sign_up_session.user_name = "none";
    sign_up_session.password = "none";

    cout << "=====[ MENU/Sign Up ]=====" << endl;
    sign_up_prompt(sign_up_session);

    return;
}

void sign_up_prompt(packet_session& session)
{
    string write_username = "none";
    string write_password = "none";

    while(write_username == "none")
    {
        if(session.user_name == "none")
        {
            cout << "Username: ";
            cin >> session.user_name;
        }
        
        if(valid_username_flag(session.user_name)) // Checks if username is valid, returns false if exists
        {
            write_username = session.user_name;
        }
        else
        {
            cout << "Error: username '" << session.user_name << "' is invalid or already exist" << endl << endl;
            session.user_name = "none";
        }
    }
    
    while(write_password == "none")
    {
        if(session.password == "none")
        {
            cout << "Password: ";
            cin >> session.password;
        }
    
        if(valid_password_flag(session.password)) // Checks if password is valid, returns false if exists
        {
            write_password = session.password;
        }
        else
        {
            cout << "Error: password is weak try adding characters: @, !, #, $, %, ^, &, *" << endl << endl;
            session.password = "none";
        }
    }

    register_account(write_username, write_password);
}

bool valid_username_flag(string& user_name) // Checks if username is vaid, returns false if exists
{
    ifstream check_username;
    bool valid_creation_flag = true;
    
    check_username.open("../database/user_login");
    
    if(check_username.is_open()) // Error check if source file is accessible
    {
        string read_buffer;
        
        while(getline(check_username, read_buffer, '\n') && valid_creation_flag) // Finds if the user's username already exist
        {
            getline(check_username, read_buffer, '\n');

            if(read_buffer == user_name || user_name == "none") // Checks if username exists and valid
            {
                valid_creation_flag = false;
            }
            else
            {
                getline(check_username, read_buffer, '\n');
            }
        }
    }
    else
    {
        cout << "Error: internal error (signup.cpp: 99: bool account_creation_check())" << endl;
    }
    
    check_username.close();
    return valid_creation_flag;
}

bool valid_password_flag(string& password) // Checks if password is valid, returns false if exists
{
    int password_complexity = 0;

    if(password.size() >= 10)
    {
        password_complexity += 10;
    }

    for(int i = 0; i < password.size(); i++)
    {
        if(password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '^' || password[i] == '&' || password[i] == '*')
        {
            password_complexity += 5;
        }
        else if(password[i] == '0' || password[i] == '1' || password[i] == '2' || password[i] == '3' || password[i] == '4' || password[i] == '5' || password[i] == '6' || password[i] == '7' || password[i] == '8' || password[i] == '9')
        {
            password_complexity += 5;
        }
    }  
    
    if(password_complexity >= 15)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void register_account(string& username, string& password)
{
    streampos valid_write_position, write_position_offset = 5;
    ifstream prep_write_user_details;
    bool available_write_position_flag = false;
    string write_buffer;
    
    prep_write_user_details.open("../database/user_login");
    
    while(getline(prep_write_user_details, write_buffer, '\n') && !available_write_position_flag)
    {
        if(write_buffer == "none")
        {
            valid_write_position = prep_write_user_details.tellg();
            available_write_position_flag = true;
        }
    }

    prep_write_user_details.close();

    ofstream write_user_details;

    if(!available_write_position_flag) // No available spots
    {
        write_user_details.open("../database/user_login", ios::app);

        write_user_details << "----" << endl;
        write_user_details << username << endl;
        write_user_details << password << endl;
    }
    else // There is an available spot
    {
        write_user_details.open("../database/user_login", ios::in | ios::out);
        write_user_details.seekp(valid_write_position - write_position_offset);

        write_user_details << username << endl;
        write_user_details << password;
    }

    write_user_details.close();
}