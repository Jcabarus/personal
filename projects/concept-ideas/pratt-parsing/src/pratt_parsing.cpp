#include "header.h"

Pratt::Pratt(vector<Token*> &tokenized_expression_vector)
{
    PARSE(tokenized_expression_vector);
}

void Pratt::CLEANUP()
{
    for(int i = 0; i < binary_parse_tree.size(); i++)
    {
        delete binary_parse_tree[i];
        binary_parse_tree[i] = nullptr;
    }
}

float Pratt::Result()
{
    char operator_char;

    vector<float> calculate;

    POSTORDER(binary_parse_tree_root);

    for(int i = 0; i < order_of_operation.size(); i++)
    {
        switch(order_of_operation[i])
        {
            case('+'): 
            {
                int calculate_offset_position = calculate.size() - 1;
                calculate[calculate_offset_position - 1] = calculate[calculate_offset_position - 1] + calculate[calculate_offset_position];
                calculate.pop_back();
                break;
            }
            case('-'):
            {
                int calculate_offset_position = calculate.size() - 1;
                    calculate[calculate_offset_position - 1] = calculate[calculate_offset_position - 1] - calculate[calculate_offset_position];
                    calculate.pop_back();
                break;
            }
            case('/'):
            {
                int calculate_offset_position = calculate.size() - 1;
                calculate[calculate_offset_position - 1] = calculate[calculate_offset_position - 1] / calculate[calculate_offset_position];
                calculate.pop_back();
                break;
            }
            case('*'):
            {
                int calculate_offset_position = calculate.size() - 1;
                calculate[calculate_offset_position - 1] = calculate[calculate_offset_position - 1] * calculate[calculate_offset_position];
                calculate.pop_back();
                break;
            }
            default: calculate.push_back(order_of_operation[i] - 48); break;
        }
    }

    CLEANUP();

    return calculate[0];
}

void Pratt::PARSE(vector<Token*> &tokenized_expression_vector) // Assigns affinity based on the token, and forms a tree based on its affinity
{
    AFFINITY_ASSIGNMENT(1, &tokenized_expression_vector);
    VECTOR_INITIALIZATION();
    
    while(!operation_index_position.empty())
    {
        AFFINITY_ASSIGNMENT(1, &tokenized_expression_vector);
        PARSE_OPERATION();
        AFFINITY_ASSIGNMENT(2);

        operator_index_position.clear();
        operand_index_position.clear();
        operation_index_position.clear();
    
        VECTOR_INITIALIZATION();
    }

    binary_parse_tree_root = binary_parse_tree[operand_index_position[0]];
}

void Pratt::VECTOR_INITIALIZATION()
{
    for(int i = 0; i < binary_parse_tree.size(); i++) // operand_index_position, operand_index_position initialization
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

    int priority_precedence_index = 0; 

    for(int i = 0; i < operator_index_position.size(); i++) // operation_index_position initialization, finds an operator whose precedence is higher compared to other operators
    {
        if(binary_parse_tree[operator_index_position[priority_precedence_index]]->precedence_left == binary_parse_tree[operator_index_position[i]]->precedence_left)
        {
            operation_index_position.push_back(i);
        }
        else if(binary_parse_tree[operator_index_position[priority_precedence_index]]->precedence_left < binary_parse_tree[operator_index_position[i]]->precedence_left)
        {
            operation_index_position.clear();
            operation_index_position.push_back(i);
            priority_precedence_index = i;
        }
    }
}

void Pratt::PARSE_OPERATION()
{
    for(int i = 0; i < operation_index_position.size(); i++) // Operation assignment
    {
        if(i == 0) // Initial position
        {
            if(binary_parse_tree[operand_index_position[operation_index_position[i]]]->token->token_attribute == "operand" &&  binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_left_link == nullptr)
            {
                binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_left_link = binary_parse_tree[operand_index_position[operation_index_position[i]]];
                binary_parse_tree[operand_index_position[operation_index_position[i]]]->token->token_attribute = "N/A";
            }
            
            if( binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_right_link == nullptr)
            {
                binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_right_link = binary_parse_tree[operand_index_position[operation_index_position[i] + 1]];
                binary_parse_tree[operand_index_position[operation_index_position[i] + 1]]->token->token_attribute = "N/A";
            }
        }
        else if(i == operation_index_position.size() - 1) // Last position
        { 
            if(binary_parse_tree[operand_index_position[operation_index_position[i]]]->token->token_attribute == "operand" &&  binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_left_link == nullptr)
            {
                binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_left_link = binary_parse_tree[operand_index_position[operation_index_position[i]]];
                binary_parse_tree[operand_index_position[operation_index_position[i]]]->token->token_attribute = "N/A";
            }

            if( binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_right_link == nullptr)
            {
                binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_right_link = binary_parse_tree[operand_index_position[operation_index_position[i] + 1]];
                binary_parse_tree[operand_index_position[operation_index_position[i] + 1]]->token->token_attribute = "N/A";
            }
        }
        else // 1 < i < operation_index_position.size()
        {
            if(binary_parse_tree[operand_index_position[operation_index_position[i]]]->token->token_attribute == "operand" &&  binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_left_link == nullptr)
            {
                binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_left_link = binary_parse_tree[operand_index_position[operation_index_position[i]]];
                binary_parse_tree[operand_index_position[operation_index_position[i]]]->token->token_attribute = "N/A";
            }
            
            if(binary_parse_tree[operand_index_position[operation_index_position[i] + 1]]->token->token_attribute == "operand" && binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_right_link == nullptr)
            {
                binary_parse_tree[operator_index_position[operation_index_position[i]]]->pnode_right_link = binary_parse_tree[operand_index_position[operation_index_position[i] + 1]];
                binary_parse_tree[operand_index_position[operation_index_position[i] + 1]]->token->token_attribute = "N/A";
            }
        }
    }
}

void Pratt::AFFINITY_ASSIGNMENT(int mode, vector<Token*> *tokenized_expression_vector_ptr)
{
    switch(mode)
    {
        case(1): // Pre initialization
        {
            for(int i = 0; i < (*tokenized_expression_vector_ptr).size(); i++) // Affinity assignment
            {
                if((*tokenized_expression_vector_ptr)[i]->token_attribute == "operand") // If it's an operand, its affinity is 0
                {
                    PNode* insert_node = INITIALIZE((*tokenized_expression_vector_ptr)[i]);

                    binary_parse_tree.push_back(insert_node);
                }
                else if((*tokenized_expression_vector_ptr)[i]->token_attribute == "operator") // If it's an operator, for simplicity the affinities are in tens plaace
                {
                    PNode* insert_node = INITIALIZE((*tokenized_expression_vector_ptr)[i]);

                    if((*tokenized_expression_vector_ptr)[i]->token_identity == "+")
                    {
                        insert_node->precedence_left = 10;
                        insert_node->precedence_right = 11;
                    }
                    else if((*tokenized_expression_vector_ptr)[i]->token_identity == "-")
                    {
                        insert_node->precedence_left = 10;
                        insert_node->precedence_right = 11;
                        
                    }
                    else if((*tokenized_expression_vector_ptr)[i]->token_identity == "*")
                    {
                        insert_node->precedence_left = 22;
                        insert_node->precedence_right = 23;
                        
                    }
                    else if((*tokenized_expression_vector_ptr)[i]->token_identity == "/")
                    {
                        insert_node->precedence_left = 20;
                        insert_node->precedence_right = 21;
                    }
                    // else if((*tokenized_expression_vector_ptr)[i]->token_identity == "pr") // Need more progress
                    // {
                    //     insert_node->precedence_left = 98;
                    //     insert_node->precedence_right = 99;
                    // }
                    
                    binary_parse_tree.push_back(insert_node);
                }
            }
            
            break;
        }
        case(2): // Post initialization
        {
            for(int i = 0; i < operator_index_position.size(); i++) // If an operator is a tree, it becomes an operand, and loses its affinity
            {
                if(binary_parse_tree[operator_index_position[i]]->pnode_left_link != nullptr && binary_parse_tree[operator_index_position[i]]->pnode_right_link != nullptr)
                {
                    binary_parse_tree[operator_index_position[i]]->token->token_attribute = "operand";
                    binary_parse_tree[operator_index_position[i]]->precedence_left = 0;
                    binary_parse_tree[operator_index_position[i]]->precedence_right = 0;
                }
            }

            break;
        }
    }
}

void Pratt::POSTORDER(PNode* pnode_ptr) // Graph traversal
{
    if(pnode_ptr == nullptr)
    {
        return;
    }
    else
    {
        POSTORDER(pnode_ptr->pnode_left_link);
        POSTORDER(pnode_ptr->pnode_right_link);
        order_of_operation.push_back(pnode_ptr->token->token_identity[0]);
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