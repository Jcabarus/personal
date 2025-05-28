#include "header.h"

Queue::Queue()
{
    queue_front_ptr = nullptr;
    queue_back_ptr = nullptr;
}

Queue::~Queue()
{
    // cout << "~Queue()" << endl;

    while(queue_front_ptr != nullptr && queue_back_ptr != nullptr)
    {
        Deq();
    }
}

void Queue::Enq(Graph::GNode* node) // Enqeues from the back
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

void Queue::Deq() // Dequeues from the front
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

void Queue::Print()
{
    if(Empty())
    {
        cout << "Queue: empty" << endl;
    }
    else
    {
        QNode* print_traversal = queue_back_ptr;

        while(print_traversal != nullptr)
        {
            cout << print_traversal << " -> " << print_traversal->node_ptr->node_source << endl;
    
            print_traversal = print_traversal->queue_link;
        }
    }
}

bool Queue::Search(Graph::GNode* &search_node) // returns true if search is found
{
    QNode* search_traversal = queue_back_ptr;

    bool node_found = false;

    while(search_traversal != nullptr)
    {
        if(search_node == search_traversal->node_ptr)
        {
            node_found = true;
            return node_found;
        }

        search_traversal = search_traversal->queue_link;
    }

    return node_found;
}

bool Queue::Empty() // returns true if queue is empty
{
    bool queue_empty = false;

    if(queue_back_ptr == nullptr && queue_front_ptr == nullptr)
    {
        queue_empty = true;
    }

    return queue_empty; 
}

Queue::QNode* Queue::INITIALIZE(Graph::GNode* node)
{
    QNode* initialize_node = new QNode;
    initialize_node->node_ptr = node;
    initialize_node->queue_link = nullptr;

    return initialize_node;
}