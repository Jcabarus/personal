#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Token
{
    string token_identificator;
    string token_attribute;
}; 

class Pratt
{
    public:
        Pratt(vector<Token*> &tokenized_expression_vector);
        void Result();
        ~Pratt();

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
        void OPERATION();
        PNode* INITIALIZE(Token *token);

        vector<PNode*> binary_parse_tree;
        vector<char> order_of_operation;
        PNode* binary_parse_tree_root;
};