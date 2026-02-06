#include "Graph.h"
#include <iostream>
#include <limits>

Graph::Graph() : vertexCount(0), maxVertices(10) {
    adjacencyMatrix = new int*[maxVertices];
    for (int i = 0; i < maxVertices; i++) {
        adjacencyMatrix[i] = new int[maxVertices];
        for (int j = 0; j < maxVertices; j++) {
            adjacencyMatrix[i][j] = 0;  // 0 means no edge
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < maxVertices; i++) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

void Graph::addPodcast(int id) {
    if (id < 0) return;
    
    // If id is larger than current capacity, resize
    if (id >= maxVertices) {
        while (id >= maxVertices) {
            resizeMatrix();
        }
    }
    
    if (id >= vertexCount) {
        vertexCount = id + 1;
    }
}

void Graph::addEdge(int podcast1, int podcast2, int weight) {
    if (podcast1 < 0 || podcast2 < 0 || weight <= 0) return;
    
    // Make sure vertices exist
    if (podcast1 >= vertexCount) addPodcast(podcast1);
    if (podcast2 >= vertexCount) addPodcast(podcast2);
    
    // For undirected graph
    adjacencyMatrix[podcast1][podcast2] = weight;
    adjacencyMatrix[podcast2][podcast1] = weight;
}

void Graph::dijkstra(int source) {
    if (source < 0 || source >= vertexCount) {
        std::cout << "Invalid source podcast ID!" << std::endl;
        return;
    }
    
    // Arrays for Dijkstra's algorithm
    int* distances = new int[vertexCount];
    bool* visited = new bool[vertexCount];
    int* parents = new int[vertexCount];
    
    // Initialize
    for (int i = 0; i < vertexCount; i++) {
        distances[i] = std::numeric_limits<int>::max();
        visited[i] = false;
        parents[i] = -1;  // -1 means no parent
    }
    
    distances[source] = 0;
    
    // Find shortest path for all vertices
    for (int count = 0; count < vertexCount - 1; count++) {
        int u = findMinDistance(distances, visited);
        visited[u] = true;
        
        // Update distances of adjacent vertices
        for (int v = 0; v < vertexCount; v++) {
            if (!visited[v] && adjacencyMatrix[u][v] != 0 &&
                distances[u] != std::numeric_limits<int>::max() &&
                distances[u] + adjacencyMatrix[u][v] < distances[v]) {
                distances[v] = distances[u] + adjacencyMatrix[u][v];
                parents[v] = u;
            }
        }
    }
    
    // Print results
    std::cout << "\nShortest paths from Podcast " << source << ":\n";
    std::cout << "----------------------------------------\n";
    std::cout << "To Podcast | Distance | Path\n";
    std::cout << "----------------------------------------\n";
    
    for (int i = 0; i < vertexCount; i++) {
        if (i == source) continue;
        
        if (distances[i] == std::numeric_limits<int>::max()) {
            std::cout << "     " << i << "     |   INF    | No path\n";
        } else {
            std::cout << "     " << i << "     |    " << distances[i] << "     | ";
            printPath(parents, i);
            std::cout << " -> " << i << "\n";
        }
    }
    
    // Clean up
    delete[] distances;
    delete[] visited;
    delete[] parents;
}

void Graph::resizeMatrix() {
    int newMax = maxVertices * 2;
    int** newMatrix = new int*[newMax];
    
    // Initialize new matrix
    for (int i = 0; i < newMax; i++) {
        newMatrix[i] = new int[newMax];
        for (int j = 0; j < newMax; j++) {
            if (i < maxVertices && j < maxVertices) {
                newMatrix[i][j] = adjacencyMatrix[i][j];
            } else {
                newMatrix[i][j] = 0;
            }
        }
    }
    
    // Delete old matrix
    for (int i = 0; i < maxVertices; i++) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
    
    adjacencyMatrix = newMatrix;
    maxVertices = newMax;
}

int Graph::findMinDistance(int* distances, bool* visited) {
    int min = std::numeric_limits<int>::max();
    int minIndex = -1;
    
    for (int v = 0; v < vertexCount; v++) {
        if (!visited[v] && distances[v] <= min) {
            min = distances[v];
            minIndex = v;
        }
    }
    
    return minIndex;
}

void Graph::printPath(int* parents, int target) {
    if (parents[target] == -1) {
        return;
    }
    
    printPath(parents, parents[target]);
    std::cout << parents[target] << " -> ";
}
