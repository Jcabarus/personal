#include "Final.h"

Queue::Queue()
{
    queue_size = 0;
    is_queue_full = false;
}

void Queue::Enqueue(TNode transaction_packet)
{  
    ENQUEUE(transaction_packet);
}

void Queue::Dequeue()
{
    DEQUEUE();
}

void Queue::ENQUEUE(TNode transaction_packet)
{
    if(queue_size == 0)
    {
        queue_front_ptr == nullptr;
        queue_back_ptr == nullptr;
    }
    
    if(queue_front_ptr == nullptr && queue_size == 0) // Queue empty
    {
        QNode* enqueue_node = INITIALIZE(transaction_packet);
        LINK_NODE(enqueue_node);
    }
    else if(queue_front_ptr != nullptr && queue_size == 0)
    {
        QNode* enqueue_node = INITIALIZE(transaction_packet);
        LINK_NODE(enqueue_node);
    }
}

void Queue::DEQUEUE()
{
    
}

Queue::QNode* Queue::INITIALIZE(TNode transaction_packet)
{
    QNode* initialize_node = new QNode;

    initialize_node->transaction_packet = transaction_packet;
    initialize_node->qnode_link = nullptr;
    queue_size++;

    return initialize_node;
}

void Queue::LINK_NODE(QNode* node_ptr)
{
    if(queue_size == 0)
    {
        queue_back_ptr = node_ptr;
        queue_front_ptr = node_ptr;
    }
    else
    {
        node_ptr->qnode_link = queue_back_ptr;
        queue_back_ptr = node_ptr;
    }
}