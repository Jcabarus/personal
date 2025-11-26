#include <iostream>
#include <fstream>

using namespace std;

enum user_action
{
    sign_in, sign_up, deposit, withdraw
};

struct packet_session
{
    int session_id, session_attempt;

    user_action action;
    string user_name;
    string password;
};

struct transaction_session
{
    string transaction_id;
    packet_session* session_ptr;
};

void sign_in_menu();
void sign_up_menu();