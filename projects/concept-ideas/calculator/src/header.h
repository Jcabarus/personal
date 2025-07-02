#include <iostream>
#include <vector>
// #include <stack>
// #include <queue>

using namespace std;

struct Token
{
    vector<char> operands;
    vector<char> operators;
};

class Pratt
{
    public:
        Pratt(Token &token);
        int Result();
        ~Pratt();

    private:
        struct PNode
        {
            string expression;

            int unique_id;
            int precendence_left;
            int precendence_right;

            PNode* pnode_left_link;
            PNode* pnode_right_link;
        };

        void PARSE();
        void OPERATION();
        PNode* INSERT(PNode* &pnode_ptr, string string_arg);
        PNode* INITIALIZE(string string_arg);

        vector<PNode*> binary_parse_tree;
        vector<PNode*> pnode;
        vector<string> parsed_expression;
        // vector<string> parsed_operator;
        // vector<string> parsed_operand;

        int counter;
};