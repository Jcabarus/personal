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
    INORDER(binary_parse_tree_root);

    while(!order_of_operation.empty())
    {
        cout << order_of_operation.front() << " ";
        order_of_operation.pop();
    }

    cout << endl;
}

void Pratt::PARSE(vector<Token*> &tokenized_expression_vector) // Assigns affinity based on the token, and forms a tree based on its affinity
{
    vector<Token*> *tokenized_expression_vector_ptr = &tokenized_expression_vector;

    AFFINITY_ASSIGNMENT(1, tokenized_expression_vector_ptr);
    VECTOR_INITIALIZATION();

    while(!operation_index_position.empty())
    {
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

    priority_precedence_index = 0;

    for(int i = 0; i < operator_index_position.size(); i++) // operation_index_position initialization
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
        if(i == 0)
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
        else if(i == operation_index_position.size() - 1)
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
        else
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
        case(1):
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

                    if((*tokenized_expression_vector_ptr)[i]->token_identificator == "+")
                    {
                        insert_node->precedence_left = 10;
                        insert_node->precedence_right = 11;
                    }
                    else if((*tokenized_expression_vector_ptr)[i]->token_identificator == "-")
                    {
                        insert_node->precedence_left = 10;
                        insert_node->precedence_right = 11;
                        
                    }
                    else if((*tokenized_expression_vector_ptr)[i]->token_identificator == "*")
                    {
                        insert_node->precedence_left = 20;
                        insert_node->precedence_right = 21;
                        
                    }
                    else if((*tokenized_expression_vector_ptr)[i]->token_identificator == "/")
                    {
                        insert_node->precedence_left = 20;
                        insert_node->precedence_right = 21;
                    }
                    
                    binary_parse_tree.push_back(insert_node);
                }
            }
            
            break;
        }
        case(2):
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

void Pratt::INORDER(PNode* pnode_ptr)
{
    if(pnode_ptr == nullptr)
    {
        return;
    }
    else
    {
        INORDER(pnode_ptr->pnode_left_link);
        order_of_operation.push(pnode_ptr->token->token_identificator);
        INORDER(pnode_ptr->pnode_right_link);
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

void Pratt::DEBUG() // For debugging purposes, delete later
{
    // For debugging purposes, delete later
    cout << "      binary_parse_tree(" << binary_parse_tree.size() << "): ";
    for(int i = 0; i < binary_parse_tree.size(); i++)
    {
        cout << binary_parse_tree[i]->token->token_identificator << " ";
    }
    cout << endl;

    cout << "  operand_index_position(" << operand_index_position.size() << "): ";
    for(int i = 0; i < operand_index_position.size(); i++)
    {
        cout << binary_parse_tree[operand_index_position[i]]->token->token_identificator << " ";
    }
    cout << endl;
    
    cout << " operator_index_position(" << operator_index_position.size() << "): ";
    for(int i = 0; i < operator_index_position.size(); i++)
    {
        cout << binary_parse_tree[operator_index_position[i]]->token->token_identificator << " ";
    }
    cout << endl;
    
    cout << "operation_index_position(" << operation_index_position.size() << "): ";
    for(int i = 0; i < operation_index_position.size(); i++)
    {
        cout << binary_parse_tree[operator_index_position[operation_index_position[i]]]->token->token_identificator << " ";
    }
    cout << endl;

    cout << endl;

    cout << "      binary_parse_tree(" << binary_parse_tree.size() << "): ";
    for(int i = 0; i < binary_parse_tree.size(); i++)
    {
        cout << binary_parse_tree[i]->token->token_identificator << " ";
    }
    cout << endl;

    cout << "  operand_index_position(" << operand_index_position.size() << "): ";
    for(int i = 0; i < operand_index_position.size(); i++)
    {
        cout << operand_index_position[i] << " ";
    }
    cout << endl;
    
    cout << " operator_index_position(" << operator_index_position.size() << "): ";
    for(int i = 0; i < operator_index_position.size(); i++)
    {
        cout << operator_index_position[i] << " ";
    }
    cout << endl;

    cout << "operation_index_position(" << operation_index_position.size() << "): ";
    for(int i = 0; i < operation_index_position.size(); i++)
    {
        cout << operator_index_position[operation_index_position[i]] << " ";
    }
    cout << endl;
    // For debugging purposes, delete later

    // For debugging purposes, delete later
    cout << "=============================" << endl << endl;
    for(int j = 1; j < binary_parse_tree.size(); j = j + 2)
    {
            cout << "    PNode: " << binary_parse_tree[j] << endl;
        // cout << "    |   |---token: " << binary_parse_tree[j]->token << endl;
        cout << "    |   |---token_identificator: " << binary_parse_tree[j]->token->token_identificator << endl;
        cout << "    |   |---token_attribute: " << binary_parse_tree[j]->token->token_attribute << endl;
        // cout << "    |---precedence_left: " << binary_parse_tree[j]->precedence_left << endl;
        // cout << "    |---precedence_right: " << binary_parse_tree[j]->precedence_right << endl;
        if(binary_parse_tree[j]->pnode_left_link != nullptr)
        {
            cout << "    |---pnode_left_link: " << binary_parse_tree[j]->pnode_left_link->token->token_identificator << endl;
        }

        if(binary_parse_tree[j]->pnode_right_link != nullptr)
        {
            cout << "    |---pnode_right_link: " << binary_parse_tree[j]->pnode_right_link->token->token_identificator << endl;
        }
        cout << endl;
    }
    cout << "=============================" << endl << endl;
    // For debugging purposes, delete later
}