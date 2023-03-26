//
// Created by nektt on 3/5/2023.
//

#include "binHeap.h"

#include <algorithm>
#include <climits>
#include <iostream>

namespace binHeap{


// graph
    int edges;
    int last[maxnodes], head[maxedges], previous[maxedges], len[maxedges];
    int prio[maxnodes], pred[maxnodes];

    void printAns(){
        for (int i = 0;i<10;++i)
        std::cout<<prio[i]<<" ";
    }


// heap
    int h[maxnodes];
    int pos2Id[maxnodes];
    int id2Pos[maxnodes];
    int hsize;



    void graphClear() {
        std::fill(last, last + maxnodes, -1);
        edges = 0;
    }


    void addEdge(int u, int v, int length) {
        head[edges] = v;
        len[edges] = length;
        previous[edges] = last[u];
        last[u] = edges++;
    }

    void hswap(int i, int j) {
        std::swap(h[i], h[j]);
        std::swap(pos2Id[i], pos2Id[j]);
        std::swap(id2Pos[pos2Id[i]], id2Pos[pos2Id[j]]);
    }

    void moveUp(int pos) {
        while (pos > 0) {
            int parent = (pos - 1) >> 1;
            if (h[pos] >= h[parent]) {
                break;
            }
            hswap(pos, parent);
            pos = parent;
        }
    }

    void add(int id, int prio) {
        h[hsize] = prio;
        pos2Id[hsize] = id;
        id2Pos[id] = hsize;
        moveUp(hsize++);
    }

    void increasePriority(int id, int prio) {
        int pos = id2Pos[id];
        h[pos] = prio;
        moveUp(pos);
    }

    void moveDown(int pos) {
        while (pos < (hsize >> 1)) {
            int child = 2 * pos + 1;
            if (child + 1 < hsize && h[child + 1] < h[child]) {
                ++child;
            }
            if (h[pos] <= h[child]) {
                break;
            }
            hswap(pos, child);
            pos = child;
        }
    }

    int removeMin() {
        int res = pos2Id[0];
        int lastNode = h[--hsize];
        if (hsize > 0) {
            h[0] = lastNode;
            int id = pos2Id[hsize];
            id2Pos[id] = 0;
            pos2Id[0] = id;
            moveDown(0);
        }
        return res;
    }


    void dijkstra(int s) {
        std::fill(pred, pred + maxnodes, -1);
        std::fill(prio, prio + maxnodes, INT_MAX);
        prio[s] = 0;
        hsize = 0;
        add(s, 0);

        while (hsize) {
            int u = removeMin();
            for (int e = last[u]; e >= 0; e = previous[e]) {
                int v = head[e];
                int nprio = prio[u] + len[e];
                if (prio[v] > nprio) {
                    if (prio[v] == INT_MAX)
                        add(v, nprio);
                    else
                        increasePriority(v, nprio);
                    prio[v] = nprio;
                    pred[v] = u;
                }
            }
        }
    }

}