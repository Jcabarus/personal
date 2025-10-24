/*
    Must handle account creation
    Must handle wether the account already exist
    Must handle password creation complexity
*/

#include "header.h"

void sign_up_prompt(packet_session& session);
bool account_creation(packet_session& session);

void sign_up_menu()
{   
    packet_session sign_up_session;
    sign_up_session.session_id = 0;
    sign_up_session.action = sign_up;


    cout << "=====[ MENU/Sign Up ]=====" << endl;
    sign_up_prompt(sign_up_session);

    return;
}

void sign_up_prompt(packet_session& session)
{
    cout << "Username: ";
    cin >> session.user_name;
    cout << "Password: ";
    cin >> session.password;

    if(account_creation(session))
    {
        return;
    }
    else
    {
        cout << "Error: account already exist" << endl;
        return;
    }
}

bool account_creation(packet_session& session)
{
    return false;
}