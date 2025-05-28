#include "header.h"

Graph::Graph(ifstream &read_file)
{
    int input_buffer_a, input_buffer_b, input_buffer_c; // File input buffer

    read_file >> input_buffer_a; // Read-in the line of the file
    read_file >> input_buffer_b; // Read-in the line of the file

    num_nodes = input_buffer_a;
    num_edges = input_buffer_b;
    
    graph_ptr = new GNode*[num_nodes]; // Dynamically allocates array of GNode pointers with the size of num_nodes
    
    for(int i = 0; i < num_nodes; i++) // Initalize graph_ptr to NULL
    {
        graph_ptr[i] = nullptr;
    }

    while(read_file >> input_buffer_a >> input_buffer_b >> input_buffer_c)
    {
        INSERT(graph_ptr[input_buffer_a - 1], input_buffer_a, input_buffer_b, input_buffer_c);
        INSERT(graph_ptr[input_buffer_b - 1], input_buffer_b, input_buffer_a, input_buffer_c);
    }
}

Graph::~Graph()
{
    // cout << "~Graph()" << endl;

    for(int i = 0; i < num_nodes; i++)
    {
        while(graph_ptr[i] != nullptr)
        {
            if(graph_ptr[i]->node_link == nullptr)
            {
                delete graph_ptr[i];
                graph_ptr[i] = nullptr;
            }
            else
            {
                GNode* graph_delete, *graph_update;
                graph_update = graph_ptr[i];
                graph_delete = graph_ptr[i];
    
                while(graph_delete->node_link != nullptr)
                {
                    graph_delete = graph_delete->node_link;
                }
            
                while(graph_update->node_link != graph_delete)
                {
                    graph_update = graph_update->node_link;
                }
            
                graph_delete->node_link = nullptr;
                graph_update->node_link = nullptr;
                
                delete graph_delete;
            }
        }
    }

    delete[] graph_ptr;
}

void Graph::Traversals()
{
    Algorithm algorithm(graph_ptr);

    algorithm.BFS(1);
    algorithm.BFS(2);
    algorithm.BFS(3);
    algorithm.BFS(4);
}

void Graph::PRINT()
{
    for(int i = 0; i < num_nodes; i++)
    {
        GNode* print_graph = graph_ptr[i];

        cout << "[" << i + 1 << "]: ";
        
        while(print_graph != nullptr)
        {
            cout << print_graph->node_destination << " ";
            print_graph = print_graph->node_link;
        }
        
        cout << endl;
    }
    
    cout << endl;
    
    for(int i = 0; i < num_nodes; i++)
    {
        GNode* print_graph = graph_ptr[i];
        
        cout << "[" << i + 1 << "]: ";

        while(print_graph != nullptr)
        {
            cout << print_graph->node_weight << " ";
            print_graph = print_graph->node_link;
        }

        cout << endl;
    }
}

void Graph::INSERT(GNode* &graph_ptr, int node_source, int node_destination, int node_weight)
{
    GNode* insert_node = INITIALIZE(node_source, node_destination, node_weight);
    
    if(graph_ptr == nullptr)
    {
        graph_ptr = insert_node;
    }
    else
    {
        GNode* graph_temp = graph_ptr;

        while(graph_temp->node_link != nullptr)
        {
            graph_temp = graph_temp->node_link;
        }

        graph_temp->node_link = insert_node;
    }
}

Graph::GNode* Graph::INITIALIZE(int node_source, int node_destination, int node_weight)
{
    GNode* initialize_node = new GNode;

    initialize_node->node_source = node_source;
    initialize_node->node_destination = node_destination;
    initialize_node->node_weight = node_weight;
    initialize_node->node_link = nullptr;

    return initialize_node;
}