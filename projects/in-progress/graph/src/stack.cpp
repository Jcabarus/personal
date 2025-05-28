#include "header.h"

Stack::Stack()
{
    stack_top_ptr = nullptr;
    stack_bottom_ptr = nullptr;
}

Stack::~Stack()
{
    // cout << "~Stack()" << endl;

    while(stack_bottom_ptr != nullptr && stack_top_ptr != nullptr)
    {
        Pop();
    }
}

void Stack::Push(Graph::GNode* node)
{
    SNode* push_node = INITIALIZE(node);

    if(stack_bottom_ptr == nullptr)
    {
        stack_top_ptr = push_node;
        stack_bottom_ptr = push_node;
    }
    else
    {
        SNode* traverse_stack = stack_bottom_ptr;

        while(traverse_stack->stack_link != nullptr)
        {
            traverse_stack = traverse_stack->stack_link;
        }

        traverse_stack->stack_link = push_node;
        stack_top_ptr = push_node;
    }
}

void Stack::Pop()
{
    if(stack_bottom_ptr == nullptr && stack_top_ptr == nullptr)
    {
        cout << "Stack: empty";
    }
    else
    {
        if(stack_bottom_ptr == stack_top_ptr)
        {
            delete stack_top_ptr;
            
            stack_top_ptr = nullptr;
            stack_bottom_ptr = nullptr;
        }
        else
        {
            SNode* pop_node = stack_top_ptr;
            SNode* update_stack_node = stack_bottom_ptr;

            while(update_stack_node->stack_link != stack_top_ptr)
            {
                update_stack_node = update_stack_node->stack_link;
            }
    
            update_stack_node->stack_link = nullptr;
            stack_top_ptr = update_stack_node;
            
            delete pop_node;
            
        }
    }
}

void Stack::Print()
{
    if(Empty())
    {
        cout << "Stack: empty" << endl;
    }
    else
    {
        SNode* print_traversal = stack_bottom_ptr;

        while(print_traversal != nullptr)
        {
            cout << print_traversal << " -> " << print_traversal->node_ptr->node_source << endl;
    
            print_traversal = print_traversal->stack_link;
        }
    }
}

bool Stack::Search(Graph::GNode* &search_node) // returns true if search is found
{
    SNode* search_traversal = stack_bottom_ptr;

    bool node_found = false;

    while(search_traversal != nullptr)
    {
        if(search_node == search_traversal->node_ptr)
        {
            node_found = true;
            return node_found;
        }

        search_traversal = search_traversal->stack_link;
    }

    return node_found;
}

bool Stack::Empty() // returns true if queue is empty
{
    bool queue_empty = false;

    if(stack_bottom_ptr == nullptr && stack_top_ptr == nullptr)
    {
        queue_empty = true;
    }

    return queue_empty; 
}

Stack::SNode* Stack::INITIALIZE(Graph::GNode* node)
{
    SNode* initialize_node = new SNode;
    initialize_node->node_ptr = node;
    initialize_node->stack_link = nullptr;

    return initialize_node;
}