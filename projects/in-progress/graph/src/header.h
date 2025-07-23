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
        void Traversals();

    private:
        void PRINT();
        void INSERT(GNode* &graph_ptr, int node_source, int node_destination, int node_weight);
        GNode* INITIALIZE(int node_source, int node_destination, int node_weight);

        GNode* *graph_ptr; // Graph structure
        int num_nodes, num_edges;
};

class Algorithm
{
    public:
        Algorithm(Graph::GNode* *&graph_ptr);

        void BFS(int node_source);
        void DFS(int node_source);
        void Prim(int node_source);
        void Kruskal();
        void Dijkstra(int node_source);

    private:
        Graph::GNode* *alg_graph_ptr;
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
        void Print();
        bool Search(Graph::GNode* &search_node); // returns true if search is found
        bool Empty(); // returns true if queue is empty

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
    
        void Enq(Graph::GNode* node); // Enqeues from the back
        void Deq(); // Dequeues from the front
        void Print();
        bool Search(Graph::GNode* &search_node); // returns true if search is found
        bool Empty(); // returns true if queue is empty

        QNode* queue_front_ptr;
        QNode* queue_back_ptr;
    
    private:
        QNode* INITIALIZE(Graph::GNode* node);
};