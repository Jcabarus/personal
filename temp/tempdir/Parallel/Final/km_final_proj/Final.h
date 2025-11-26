#include <iostream>
#include <pthread.h>

using std::string;  

enum request
{
    read_balance, withdraw_balance, deposit_balance, account_creation
};

struct UNode
{
    string user_name;
    string user_action; // read_balance_request, withdraw_balance_request, deposit_balance_request
    int user_balance;

    string user_previous_action;
    int balance_requested_amount;
};

struct TNode
{
    int transaction_id;
    UNode user_request;

    int user_read_balance()
    {
        return user_request.user_balance;
    }
    
    int withdraw_balance()
    {
        return user_request.user_balance - user_request.balance_requested_amount;
    }
    
    int deposit_balance()
    {
        return user_request.user_balance + user_request.balance_requested_amount;
    }
};

class Queue
{
    int queue_size;
    bool is_queue_full;

    public:
        Queue();
        void Enqueue(TNode transaction_packet);
        void Dequeue();

    private:
        struct QNode
        {
            TNode transaction_packet;
            QNode* qnode_link;
        };

        QNode* queue_front_ptr;
        QNode* queue_back_ptr;

        void ENQUEUE(TNode transaction_packet);
        void DEQUEUE();
        QNode* INITIALIZE(TNode transaction_packet);
        void LINK_NODE(QNode* node_ptr);
};

class Transaction
{

};