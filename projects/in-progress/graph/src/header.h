#include <iostream>
#include <fstream>

using namespace std;

class Graph
{
    public:
        struct GNode
        {
            int node_source, node_destination, node_weight;
            GNode* node_link;
        };

        Graph(ifstream &read_file); // Graph constructor
        ~Graph();

    private:
        void BFS();
        void DFS();
        void PRIM();
        void KRUSKAL();
        void DIJKSTRA();

        void PRINT();
        void INSERT(GNode* &graph_ptr, int node_source, int node_destination, int node_weight);
        GNode* INITIALIZE(int node_source, int node_destination, int node_weight);

        GNode* *graph_ptr; // Graph structure
        int num_nodes, num_edges;
};

class Stack
{
    public:
        struct SNode
        {
            Graph::GNode* node_ptr;
            SNode* stack_link;
        };

        Stack();
        ~Stack();

        void Push(Graph::GNode* node);
        void Pop();

    private:
        SNode* INITIALIZE(Graph::GNode* node);
        void PRINT();
        
        SNode* stack_top_ptr;
        SNode* stack_bottom_ptr;
    };
    
    class Queue
    {
        public:
        struct QNode
        {
            Graph::GNode* node_ptr;
            QNode* queue_link;
        };
        
        Queue();
        ~Queue();
        
        void Enq(Graph::GNode* node);
        void Deq();
        
    private:
        QNode* INITIALIZE(Graph::GNode* node);

        QNode* queue_front_ptr;
        QNode* queue_back_ptr;
};