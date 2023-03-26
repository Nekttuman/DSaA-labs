#include <algorithm>
#include <climits>
#include <iostream>

namespace binHeap {
    const int maxnodes = 200000;
    const int maxedges = 1000000;

    void graphClear();

    void addEdge(int u, int v, int length);

    void hswap(int i, int j) ;

    void moveUp(int pos) ;

    void add(int id, int prio);

    void increasePriority(int id, int prio);

    void moveDown(int pos);

    int removeMin();

    void dijkstra(int s);


    void printAns();
//void algo() {
//    graphClear();
//    addEdge(0, 1, 10);
//    addEdge(1, 2, 5);
//    addEdge(0, 2, 8);
//
//    dijkstra(0);
//
//    for (int i = 0; i < 3; i++)
//        cout << prio[i] << endl;
//}

}