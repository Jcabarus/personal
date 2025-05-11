#include "header.h"

Queue::Queue()
{
    queue_front_ptr = nullptr;
    queue_back_ptr = nullptr;
}

Queue::~Queue()
{
    cout << "~Queue()" << endl;

    while(queue_front_ptr != nullptr && queue_back_ptr != nullptr)
    {
        Deq();
    }
}

void Queue::Enq(Graph::GNode* node)
{
    QNode* enq_node = INITIALIZE(node);

    if(queue_back_ptr == nullptr)
    {
        queue_front_ptr = enq_node;
        queue_back_ptr = enq_node;
    }
    else
    {
        enq_node->queue_link = queue_back_ptr;
        queue_back_ptr = enq_node;
    }
}

void Queue::Deq()
{
    if(queue_front_ptr == nullptr && queue_back_ptr == nullptr)
    {   
        cout << "Stack: empty" << endl;
    }
    else
    {
        if(queue_back_ptr == queue_front_ptr)
        {
            delete queue_front_ptr;
            queue_front_ptr = nullptr;  
            queue_back_ptr = nullptr;           
        }
        else
        {
            QNode* deq_node = queue_front_ptr;
            QNode* update_queue_node = queue_back_ptr;

            while(update_queue_node->queue_link != queue_front_ptr)
            {
                update_queue_node = update_queue_node->queue_link;
            }

            update_queue_node->queue_link = nullptr;
            
            delete deq_node;

            queue_front_ptr = update_queue_node;
        }
    }
}

Queue::QNode* Queue::INITIALIZE(Graph::GNode* node)
{
    QNode* initialize_node = new QNode;
    initialize_node->node_ptr = node;
    initialize_node->queue_link = nullptr;

    return initialize_node;
}