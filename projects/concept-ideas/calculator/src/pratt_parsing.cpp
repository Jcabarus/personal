#include "header.h"

Pratt::Pratt(vector<Token*> &tokenized_expression_vector)
{
    PARSE(tokenized_expression_vector);
    // OPERATION();
    // Result   ();
}

Pratt::~Pratt()
{

}

void Pratt::Result()
{
    while(!order_of_operation.empty())
    {
        cout << order_of_operation.front() << " ";
        order_of_operation.pop();
    }

    cout << endl;
}

void Pratt::PARSE(vector<Token*> &tokenized_expression_vector) // Assigns affinity based on the token, and forms a tree based on its affinity
{
    int priority_precedence_index;
    vector<int> operand_index_position, operator_index_position, operation_index_position;

    for(int i = 0; i < tokenized_expression_vector.size(); i++) // Affinity assignment
    {
        if(tokenized_expression_vector[i]->token_attribute == "operand") // If it's an operand, its affinity is 0
        {
            PNode* insert_node = INITIALIZE(tokenized_expression_vector[i]);

            binary_parse_tree.push_back(insert_node);
        }
        else if(tokenized_expression_vector[i]->token_attribute == "operator") // If it's an operator, for simplicity the affinities are in tens plaace
        {
            PNode* insert_node = INITIALIZE(tokenized_expression_vector[i]);

            if(tokenized_expression_vector[i]->token_identificator == "+")
            {
                insert_node->precedence_left = 10;
                insert_node->precedence_right = 11;
            }
            else if(tokenized_expression_vector[i]->token_identificator == "-")
            {
                insert_node->precedence_left = 10;
                insert_node->precedence_right = 11;
                
            }
            else if(tokenized_expression_vector[i]->token_identificator == "*")
            {
                insert_node->precedence_left = 20;
                insert_node->precedence_right = 21;
                
            }
            else if(tokenized_expression_vector[i]->token_identificator == "/")
            {
                insert_node->precedence_left = 20;
                insert_node->precedence_right = 21;
            }
            
            binary_parse_tree.push_back(insert_node);
        }
    }

    for(int i = 0; i < binary_parse_tree.size(); i++)
    {
        if(binary_parse_tree[i]->token->token_attribute == "operator")
        {
            operator_index_position.push_back(i);
        }
        else if(binary_parse_tree[i]->token->token_attribute == "operand")
        {
            operand_index_position.push_back(i);
        }
    }

    priority_precedence_index = operator_index_position[0];

    for(int i = 0; i < operator_index_position.size(); i++)
    {
        if(binary_parse_tree[priority_precedence_index]->precedence_left == binary_parse_tree[operator_index_position[i]]->precedence_left)
        {
            operation_index_position.push_back(operator_index_position[i]);
        }
        else if(binary_parse_tree[priority_precedence_index]->precedence_left < binary_parse_tree[operator_index_position[i]]->precedence_left)
        {
            operation_index_position.clear();
            operation_index_position.push_back(operator_index_position[i]);
            priority_precedence_index = operator_index_position[i];
        }
    }

    // For debugging purposes, delete later
    // cout << "  operand_index_position(" << operand_index_position.size() << "): ";
    // for(int i = 0; i < operand_index_position.size(); i++)
    // {
    //     cout << binary_parse_tree[operand_index_position[i]]->token->token_identificator << " ";
    // }
    // cout << endl;
    
    // cout << " operator_index_position(" << operator_index_position.size() << "): ";
    // for(int i = 0; i < operator_index_position.size(); i++)
    // {
    //     cout << binary_parse_tree[operator_index_position[i]]->token->token_identificator << " ";
    // }
    // cout << endl;

    // cout << "operation_index_position(" << operation_index_position.size() << "): ";
    // for(int i = 0; i < operation_index_position.size(); i++)
    // {
    //     cout << binary_parse_tree[operation_index_position[i]]->token->token_identificator << " ";
    // }
    // cout << endl;
    // For debugging purposes, delete later

        // For debugging purposes, delete later
        // cout << "=============================" << endl << endl;
        // for(int j = 1; j < binary_parse_tree.size(); j = j + 2)
        // {
        //         cout << "    PNode: " << binary_parse_tree[j] << endl;
        //     // cout << "    |   |---token: " << binary_parse_tree[j]->token << endl;
        //     cout << "    |   |---token_identificator: " << binary_parse_tree[j]->token->token_identificator << endl;
        //     cout << "    |   |---token_attribute: " << binary_parse_tree[j]->token->token_attribute << endl;
        //     // cout << "    |---precedence_left: " << binary_parse_tree[j]->precedence_left << endl;
        //     // cout << "    |---precedence_right: " << binary_parse_tree[j]->precedence_right << endl;
        //     if(binary_parse_tree[j]->pnode_left_link != nullptr)
        //     {
        //         cout << "    |---pnode_left_link: " << binary_parse_tree[j]->pnode_left_link->token->token_identificator << endl;
        //     }

        //     if(binary_parse_tree[j]->pnode_right_link != nullptr)
        //     {
        //         cout << "    |---pnode_right_link: " << binary_parse_tree[j]->pnode_right_link->token->token_identificator << endl;
        //     }
        //     cout << endl;
        // }
        // cout << "=============================" << endl << endl;
        // For debugging purposes, delete later
    // }
}

void Pratt::OPERATION()
{
    INORDER(binary_parse_tree_root);
}

void Pratt::INORDER(PNode* pnode_pointer)
{
    if(pnode_pointer == nullptr)
    {
        return;
    }
    else
    {
        INORDER(pnode_pointer->pnode_left_link);
        order_of_operation.push(pnode_pointer->token->token_identificator);
        INORDER(pnode_pointer->pnode_right_link);
    }
}

Pratt::PNode* Pratt::INITIALIZE(Token *token)
{
    PNode* initialize_pnode = new PNode;

    initialize_pnode->token = token;
    initialize_pnode->precedence_left = 0;
    initialize_pnode->precedence_right = 0;
    initialize_pnode->pnode_left_link = nullptr;
    initialize_pnode->pnode_right_link = nullptr;

    return initialize_pnode;
}