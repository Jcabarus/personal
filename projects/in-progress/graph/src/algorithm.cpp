#include "header.h"

Algorithm::Algorithm(Graph::GNode* *&graph_ptr)
{
    alg_graph_ptr = graph_ptr;
}

void Algorithm::BFS(int node_source)
{
    Graph::GNode* *bfs_traversal = alg_graph_ptr;

    Graph::GNode* source_node = bfs_traversal[node_source - 1];
    
    Queue bfs;
    Queue visited_node;

    bfs.Enq(source_node); // Enqueue source_node

    while(!bfs.Empty())
    {
        Graph::GNode* node_links = bfs.queue_front_ptr->node_ptr;
        
        while(node_links != nullptr) // Enqueue its links
        {
            if(!bfs.Search(bfs_traversal[node_links->node_destination - 1]) && !visited_node.Search(bfs_traversal[node_links->node_destination - 1])) // If (not found)
            {
                bfs.Enq(bfs_traversal[node_links->node_destination - 1]);
            }

            node_links = node_links->node_link;
        }
        
        visited_node.Enq(bfs.queue_front_ptr->node_ptr);

        bfs.Deq(); // Dequeue front
    }

    cout << "BFS (" << node_source << "): ";

    while(!visited_node.Empty())
    {
        cout << visited_node.queue_front_ptr->node_ptr->node_source << " ";

        visited_node.Deq();
    }

    cout << endl;
}

void Algorithm::DFS(int node_source)
{

}

void Algorithm::Prim(int node_source)
{

}

void Algorithm::Kruskal()
{

}

void Algorithm::Dijkstra(int node_source)
{

}