#include <iostream>
#include "binHeap.h"


#include "fibHeap.h"

#include <chrono>
#include <vector>

int main() {
    int nodesCount, dijStartIndex;
    nodesCount = 1000;
    std::vector<int> density = {100,75,50,25,10};
    std::vector<int> fibo, normal, bin;
    for (int i : density) {
        std::cout << "\n\ndens = " << i;
        dijStartIndex = 2;

        fibHeap::graph *myGraph = fibHeap::generateRandomGraph(nodesCount, i);
        fibHeap::shortestOrder = new std::vector<int>[nodesCount];
        std::cout << "\n" << myGraph->graphNumVertices;

        auto start = std::chrono::high_resolution_clock::now();
        dijkstra_normal(myGraph, dijStartIndex);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "\n\nnormal: " << duration.count() << "\n";
        normal.push_back(duration.count());


        start = std::chrono::high_resolution_clock::now();
        fibHeap::dijkstraFibanocci(myGraph, dijStartIndex);
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "fibo: " << duration.count() << "\n";
        fibo.push_back(duration.count());

        binHeap::graphClear();
        for(const auto& edge: myGraph->adjacentListMap){
            int first = edge.first;
            for (auto second: edge.second) {
                binHeap::addEdge(first, second->destNode, second->edgeLen);
            }
        }


        start = std::chrono::high_resolution_clock::now();
        binHeap::dijkstra(0);
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "binHeap: " << duration.count() << "\n";
        bin.push_back(duration.count());

    }


    for (auto i: fibo)
        std::cout<<i<<", ";
    std::cout<<"\nnormal:\n";

    for (auto i: normal)
        std::cout<<i<<", ";

    std::cout<<"\nbin:\n";

    for (auto i: bin)
        std::cout<<i<<", ";

    std::cout<<"\ndensity\n";
    for (auto i: density)
        std::cout<<nodesCount*(nodesCount-1)*i/100.0/2<<", ";


    return 0;
}
