#include "header.h"

Pratt::Pratt(vector<string> &insert_parsed_expression)
{
    parsed_expression = insert_parsed_expression;
    counter = 0;

    PARSE();
}

Pratt::~Pratt()
{

}

void Pratt::OPERATION()
{

}

void Pratt::PARSE()
{
    for(int i = 0; i < parsed_expression.size(); i++) // Initalizes all the pointers NULL
    {
        pnode.push_back(nullptr);
    }

    for(int i = 0; i < pnode.size(); i++) // Inserts all nodes for parsing
    {
        pnode[i] = INSERT(pnode[i], parsed_expression[i]);
    }

    for(int i = 0; i < pnode.size(); i++) // Parses all the operators
    {
        if(pnode[i]->expression == "+" || pnode[i]->expression == "-" || pnode[i]->expression == "/" || pnode[i]->expression == "*")
        {
            binary_parse_tree.push_back(pnode[i]);
        }
    }
    
    int parse_tree_index = 0;

    for(int i = 0; i < pnode.size(); i += 2) // Parses all the operators
    {
        if(i == 0) // Beginning
        {
            // binary_parse_tree[parse_tree_index]->pnode_left_link = pnode[i];
            parse_tree_index++;
        }
        else if(i < pnode.size() - 1) // 0 < i < pnode_size()
        {
            if(binary_parse_tree[parse_tree_index - 1]->precendence_right < binary_parse_tree[parse_tree_index + 1]->precendence_left)
            {
                // binary_parse_tree[parse_tree_index - 1]->pnode_right_link = pnode[parse_tree_index];
            }
            else
            {
                // binary_parse_tree[parse_tree_index + 1]->pnode_left_link = pnode[parse_tree_index];
            }

            parse_tree_index++;
        }
        else // End
        {
            // binary_parse_tree[parse_tree_index - 1]->pnode_right_link = pnode[parse_tree_index];
        }
    }

    // Debuggin, delete later
    // cout << pnode.size() << endl;
    // for(int i = 0; i < pnode.size(); i++)
    // {
    //     cout << pnode[i] << " -> " << pnode[i]->expression << endl;
    //     cout << "   unique_id: " << pnode[i]->unique_id << endl;
    //     cout << "   precendence left: " << pnode[i]->precendence_left << endl;
    //     cout << "   precendence right: " << pnode[i]->precendence_right << endl;
    //     cout << endl;
    // }

    // Debuggin, delete later
    // cout << binary_parse_tree.size() << endl;
    // for(int i = 0; i < binary_parse_tree.size(); i++)
    // {
    //     cout << binary_parse_tree[i] << " -> " << binary_parse_tree[i]->expression << endl;
    //     cout << "   unique_id: " << binary_parse_tree[i]->unique_id << endl;
    //     cout << "   precendence left: " << binary_parse_tree[i]->precendence_left << endl;
    //     cout << "   precendence right: " << binary_parse_tree[i]->precendence_right << endl;
    //     cout << endl;
    // }
}

Pratt::PNode* Pratt::INSERT(PNode* &pnode_ptr, string string_arg)
{
    PNode* insert_node = INITIALIZE(string_arg);

    if(pnode_ptr == nullptr)
    {
        if(insert_node->expression == "+")
        {
            insert_node->precendence_left = 10;
            insert_node->precendence_right = 11;
        }
        else if(insert_node->expression == "-")
        {
            insert_node->precendence_left = 10;
            insert_node->precendence_right = 11;
        }
        else if(insert_node->expression == "*")
        {
            insert_node->precendence_left = 20;
            insert_node->precendence_right = 21;
        }
        else if(insert_node->expression == "/")
        {
            insert_node->precendence_left = 20;
            insert_node->precendence_right = 21;
        }
        
        pnode_ptr = insert_node;
    }

    return pnode_ptr;
}

Pratt::PNode* Pratt::INITIALIZE(string string_arg)
{
    PNode* initialize_node = new PNode;

    initialize_node->expression = string_arg;
    
    initialize_node->unique_id = counter++;
    initialize_node->precendence_left = 0;
    initialize_node->precendence_left = 0;

    initialize_node->pnode_left_link = nullptr;
    initialize_node->pnode_right_link = nullptr;

    return initialize_node;
}