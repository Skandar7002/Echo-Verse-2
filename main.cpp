#include "Graph.h"
#include <iostream>

void showMenu() {
    std::cout << "\n=== Podcast Listening Path Optimizer ===\n";
    std::cout << "1. Add Podcast\n";
    std::cout << "2. Add Connection Between Podcasts\n";
    std::cout << "3. Find Shortest Listening Paths\n";
    std::cout << "4. Auto Test\n";
    std::cout << "5. Exit\n";
    std::cout << "Choice: ";
}

void addPodcast(Graph& graph) {
    int id;
    
    std::cout << "Podcast ID: ";
    std::cin >> id;
    
    graph.addPodcast(id);
    std::cout << "Podcast " << id << " added.\n";
}

void addConnection(Graph& graph) {
    int podcast1, podcast2, weight;
    
    std::cout << "First Podcast ID: ";
    std::cin >> podcast1;
    
    std::cout << "Second Podcast ID: ";
    std::cin >> podcast2;
    
    std::cout << "Connection Weight (similarity/transition cost): ";
    std::cin >> weight;
    
    if (weight <= 0) {
        std::cout << "Weight must be positive!\n";
        return;
    }
    
    graph.addEdge(podcast1, podcast2, weight);
    std::cout << "Connection added between Podcast " << podcast1 << " and Podcast " << podcast2 << " with weight " << weight << ".\n";
}

void findShortestPaths(Graph& graph) {
    int source;
    
    std::cout << "Starting Podcast ID: ";
    std::cin >> source;
    
    graph.dijkstra(source);
}

void autoTest(Graph& graph) {
    std::cout << "\n=== Starting Auto Test ===\n";
    
    std::cout << "\nAdding podcasts 0-6...\n";
    for (int i = 0; i < 7; i++) {
        graph.addPodcast(i);
    }
    
    std::cout << "\nAdding connections (edges) between podcasts...\n";
    // Create a sample graph
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 5, 5);
    graph.addEdge(4, 6, 2);
    graph.addEdge(5, 6, 1);
    
    std::cout << "\nFinding shortest paths from Podcast 0:\n";
    graph.dijkstra(0);
    
    std::cout << "\n\nFinding shortest paths from Podcast 3:\n";
    graph.dijkstra(3);
    
    std::cout << "\n\nTesting unreachable podcast...\n";
    graph.addPodcast(10);  // Isolated vertex
    graph.dijkstra(0);  // Should show INF for podcast 10
    
    std::cout << "\n=== Auto Test Completed ===\n";
}

int main() {
    Graph podcastGraph;
    int choice;
    
    do {
        showMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                addPodcast(podcastGraph);
                break;
                
            case 2:
                addConnection(podcastGraph);
                break;
                
            case 3:
                findShortestPaths(podcastGraph);
                break;
                
            case 4:
                autoTest(podcastGraph);
                break;
                
            case 5:
                std::cout << "Exiting program.\n";
                break;
                
            default:
                std::cout << "Invalid choice!\n";
        }
    } while(choice != 5);
    
    return 0;
}
