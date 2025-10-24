/*
    Handles user sign in
    Must take account of number of attempts, if too many attemps deny access
    Must handle forgot account recovery
*/

#include "header.h"

bool authentication(packet_session& session);
void sign_in_prompt(packet_session& session);

void sign_in_menu()
{
    packet_session sign_in_session;
    sign_in_session.session_id = 0;
    sign_in_session.session_attempt = 0;
    sign_in_session.action = sign_in;

    cout << "=====[ MENU/Sign In ]=====" << endl;
    sign_in_prompt(sign_in_session);
} 

void sign_in_prompt(packet_session& session)
{   
    cout << "Username: ";
    cin >> session.user_name;
    cout << "Password: ";
    cin >> session.password;

    if(authentication(session))
    {
        return;
    }
    else if(session.session_attempt < 4)
    {
        cout << "Error: Incorrect username or password" << endl << endl;
        sign_in_prompt(session);
    }
    else
    {
        cout << "Access denied: Too many attemps" << endl;
    }
}

bool authentication(packet_session& session)
{
    session.session_attempt++;
    return false;
}