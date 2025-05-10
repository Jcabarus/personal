#include "header.h"

Stack::Stack()
{
    stack_top_ptr = nullptr;
    stack_bottom_ptr = nullptr;
}

Stack::~Stack()
{
    cout << "~Stack()" << endl;

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

Stack::SNode* Stack::INITIALIZE(Graph::GNode* node)
{
    SNode* initialize_node = new SNode;
    initialize_node->node_ptr = node;
    initialize_node->stack_link = nullptr;

    return initialize_node;
}