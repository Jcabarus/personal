#include <iostream>
#include "CSC718/pthread/pthread/pthread_barrier_compat.h"

using std::string;

class queue_transaction
{

};

struct transaction
{
    int transaction_id;

    string user_name;
    int amount_deposited;
    int amount_withdrawn;
    int amount_transfer;
};

class user
{
    public:
        void deposit(int x);
        void withdraw(int x);
        void transfer(int x, string s);
        void create_account(string name);
        // check_balance();
        void delete_account(string, int num);

    private:
        void p_deposit(int x);
        void p_withdraw(int x);
        void p_transfer(int x, string s);
        void p_transaction(transaction user_transaction);
        void p_create_account(string name);
        void p_delete_account(string, int num);

        int checking_account_amount;
        int savings_account_amount;
        int account_id;
        string account_name;
};
