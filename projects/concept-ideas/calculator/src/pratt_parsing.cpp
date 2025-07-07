#include "header.h"

Pratt::Pratt(vector<Token*> &tokenized_expression_vector)
{
    PARSE(tokenized_expression_vector);
    OPERATION();
    Result();
}

Pratt::~Pratt()
{

}

void Pratt::Result()
{

}

void Pratt::PARSE(vector<Token*> &tokenized_expression_vector) // Assigns affinity based on the token, and forms a tree based on its affinity
{
    vector<int> operator_index, operand_index;

    for(int i = 0; i < tokenized_expression_vector.size(); i++) // Affinity assignment
    {
        if(tokenized_expression_vector[i]->token_attribute == "operand") // If it's an operand, its affinity is 0
        {
            PNode* insert_node = INITIALIZE(tokenized_expression_vector[i]);

            binary_parse_tree.push_back(insert_node);
            operand_index.push_back(i);
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
            operator_index.push_back(i);
        }
    }

    while(!operator_index.empty())
    {
        for(int i = 0; i < operator_index.size(); i++) // Tree formation
        {

            if(i == 0) // Beginning position affinity
            {
                binary_parse_tree[operator_index[i]]->pnode_left_link = binary_parse_tree[operand_index[i]];
                binary_parse_tree[operand_index[i]]->token->token_attribute = "N/A";
    
                if(binary_parse_tree[operator_index[i]]->precedence_right > binary_parse_tree[operator_index[i + 1]]->precedence_left) // Is left has a greater affinity?
                {
                    binary_parse_tree[operator_index[i]]->pnode_right_link = binary_parse_tree[operand_index[i + 1]];
                    binary_parse_tree[operand_index[i + 1]]->token->token_attribute = "N/A";
                }
                else // Right as a greater affinity
                {
                    binary_parse_tree[operator_index[i + 1]]->pnode_left_link = binary_parse_tree[operand_index[i + 1]];
                    binary_parse_tree[operand_index[i + 1]]->token->token_attribute = "N/A";
                }
            }
            else if(i < operator_index.size() - 1)// In between affinity
            {
                if(binary_parse_tree[operator_index[i]]->precedence_right > binary_parse_tree[operator_index[i + 1]]->precedence_left) // Is left has a greater affinity?
                {
                    binary_parse_tree[operator_index[i]]->pnode_right_link = binary_parse_tree[operand_index[i + 1]];
                }
                else // Right as a greater affinity
                {
                    binary_parse_tree[operator_index[i + 1]]->pnode_left_link = binary_parse_tree[operand_index[i + 1]];
                }
    
                binary_parse_tree[operand_index[i + 1]]->token->token_attribute = "N/A";
            }
            else if(i == operator_index.size() - 1) // Last position affinity
            {
                binary_parse_tree[operator_index[i]]->pnode_right_link = binary_parse_tree[operand_index[i + 1]];
                binary_parse_tree[operand_index[i + 1]]->token->token_attribute = "N/A";
            }
        }

        for(int i = 0; i < operator_index.size(); i++) // If an operator is a binary tree, it becomes an operand and loses its affinity
        {
            if(binary_parse_tree[operator_index[i]]->pnode_left_link != nullptr && binary_parse_tree[operator_index[i]]->pnode_right_link != nullptr)
            {
                binary_parse_tree[operator_index[i]]->token->token_attribute = "operand";
                binary_parse_tree[operator_index[i]]->precedence_left = 0;
                binary_parse_tree[operator_index[i]]->precedence_right = 0;
            }            
        }
        
        // For debugging purposes, delete later
        // cout << " operand_index: ";
        // for(int i = 0; i < operand_index.size(); i++)
        // {
        //     cout << binary_parse_tree[operand_index[i]]->token->token_identificator << " ";
        // }
        // cout << endl;
        
        // cout << "operator_index: ";
        // for(int i = 0; i < operator_index.size(); i++)
        // {
        //     cout << binary_parse_tree[operator_index[i]]->token->token_identificator << " ";
        // }
        // cout << endl << endl;

        // for(int j = 0; j < binary_parse_tree.size(); j++)
        // {
        //     cout << "=============================" << endl << endl;
        //     cout << "    PNode: " << binary_parse_tree[j] << endl;
        //     cout << "    |   |---token: " << binary_parse_tree[j]->token << endl;
        //     cout << "    |   |---token_identificator: " << binary_parse_tree[j]->token->token_identificator << endl;
        //     cout << "    |   |---token_attribute: " << binary_parse_tree[j]->token->token_attribute << endl;
        //     cout << "    |---precedence_left: " << binary_parse_tree[j]->precedence_left << endl;
        //     cout << "    |---precedence_right: " << binary_parse_tree[j]->precedence_right << endl;
        //     cout << "    |---pnode_left_link: " << binary_parse_tree[j]->pnode_left_link << endl;
        //     cout << "    |---pnode_right_link: " << binary_parse_tree[j]->pnode_right_link << endl;
        //     cout << endl << endl;
            
        // }
        // For debugging purposes, delete later

        operator_index.clear();
        operand_index.clear();
        
        for(int i = 0; i < binary_parse_tree.size(); i++) // Operator index position identifier
        {
            if(binary_parse_tree[i]->token->token_attribute == "operator")
            {
                operator_index.push_back(i);
            }
            else if(binary_parse_tree[i]->token->token_attribute == "operand")
            {
                operand_index.push_back(i);
            }
        }
    }
    
    binary_parse_tree_root = binary_parse_tree[operand_index[0]];
    operand_index.clear();
}

void Pratt::OPERATION()
{
    PNode* pnode_in_order_traveral = binary_parse_tree_root;

    while(pnode_in_order_traveral->pnode_left_link != nullptr)
    {
        
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