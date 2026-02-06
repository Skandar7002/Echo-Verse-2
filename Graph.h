#ifndef GRAPH_H
#define GRAPH_H

class Graph {
private:
    int** adjacencyMatrix;
    int vertexCount;
    int maxVertices;
    
    void resizeMatrix();
    int findMinDistance(int* distances, bool* visited);
    void printPath(int* parents, int target);
    
public:
    Graph();
    ~Graph();
    
    void addPodcast(int id);
    void addEdge(int podcast1, int podcast2, int weight);
    void dijkstra(int source);
};

#endif
