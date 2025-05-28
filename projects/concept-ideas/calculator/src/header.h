#include <iostream>
#include <vector>
// #include <stack>
// #include <queue>

using namespace std;

class Pratt
{
    public:
        Pratt(vector<string> &parsed_expression);
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

        void OPERATION();
        void PARSE();
        PNode* INSERT(PNode* &pnode_ptr, string string_arg);
        PNode* INITIALIZE(string string_arg);

        vector<PNode*> binary_parse_tree;
        vector<PNode*> pnode;
        vector<string> parsed_expression;
        // vector<string> parsed_operator;
        // vector<string> parsed_operand;

        int counter;
};