#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct Token
{
    string token_identity;
    string token_attribute;
}; 

class Pratt
{
    public:
        Pratt(vector<Token*> &tokenized_expression_vector);
        float Result();

    private:
        struct PNode
        {
            Token *token;
            int precedence_left;
            int precedence_right;
            
            PNode* pnode_left_link;
            PNode* pnode_right_link;
        };

        void PARSE(vector<Token *> &tokenized_expression_vector);
        void VECTOR_INITIALIZATION();
        void PARSE_OPERATION();
        void AFFINITY_ASSIGNMENT(int mode, vector<Token*> *tokenized_expression_vector = nullptr);
        PNode* INITIALIZE(Token *token);
        void POSTORDER(PNode* pnode_pointer);
        void CLEANUP();

        vector<PNode*> binary_parse_tree;
        vector<int> operand_index_position, operator_index_position, operation_index_position;
        vector<char> order_of_operation;
        PNode* binary_parse_tree_root;

};  