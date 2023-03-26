#include <iostream>
#include <map>
#include <list>
#include <climits>
#include <cstdio>
#include <memory>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>

namespace fibHeap {
    std::vector<int> *shortestOrder;
    int *distanceToBest;
    int numVertices;


    struct node {
        int index;
    };


    struct adjNode {
        int destNode;
        int edgeLen;
    };

    struct graph {
        int graphNumVertices;
        std::map<int, std::list<adjNode *>> adjacentListMap;
    };


    struct fibonacciNode {
        int degree;
        fibonacciNode *parent;
        fibonacciNode *child;
        fibonacciNode *left;
        fibonacciNode *right;
        bool mark;
        bool isInfinity;
        int key;
        int nodeIndex;
    };

    struct fibonacciHeap {
        fibonacciNode *minNode;
        int numNodes;

        fibonacciHeap() {
            numNodes = 0;
            minNode = nullptr;
        }
    };

    void fibHeapInsert(fibonacciHeap *fibHeapObj, fibonacciNode *newNode, int key) {
        fibonacciNode *minNode = fibHeapObj->minNode;
        newNode->key = key;
        newNode->degree = 0;
        newNode->parent = nullptr;
        newNode->child = nullptr;
        newNode->left = newNode;
        newNode->right = newNode;
        newNode->mark = false;
        newNode->isInfinity = false;
        if (minNode != nullptr) {
            fibonacciNode *minLeftTemp = minNode->left;
            minNode->left = newNode;
            newNode->right = minNode;
            newNode->left = minLeftTemp;
            minLeftTemp->right = newNode;
        }

        if (minNode == nullptr || minNode->key > newNode->key)
            fibHeapObj->minNode = newNode;


        fibHeapObj->numNodes = fibHeapObj->numNodes + 1;
    }

    void fibHeapExistingToRoot(fibonacciHeap *fibHeapObj, fibonacciNode *newNode) {
        fibonacciNode *minNode = fibHeapObj->minNode;
        newNode->parent = nullptr;
        newNode->mark = false;

        if (minNode != nullptr) {
            fibonacciNode *minLeftTemp = minNode->left;
            minNode->left = newNode;
            newNode->right = minNode;
            newNode->left = minLeftTemp;
            minLeftTemp->right = newNode;

            if (minNode->key > newNode->key)
                fibHeapObj->minNode = newNode;

        } else {
            fibHeapObj->minNode = newNode;
            newNode->right = newNode;
            newNode->left = newNode;
        }
    }

    fibonacciHeap *fibHeapMake() {
        auto *newFibHeap = new fibonacciHeap;
        newFibHeap->numNodes = 0;
        newFibHeap->minNode = nullptr;
        return newFibHeap;
    }


    fibonacciHeap *fibHeapUnion(fibonacciHeap *fibHeapFirst, fibonacciHeap *fibHeapSecond) {

        fibonacciHeap *appendedFibHeap = fibHeapMake();
        fibonacciNode *firstHeapMinNode = fibHeapFirst->minNode;
        fibonacciNode *secondHeapMinNode = fibHeapSecond->minNode;

        if (fibHeapSecond->minNode == nullptr)
            appendedFibHeap->minNode = firstHeapMinNode;
        else if (fibHeapFirst->minNode == nullptr)
            appendedFibHeap->minNode = secondHeapMinNode;
        else {
            fibonacciNode *firstHeapMinNodeLeftTemp =
                    firstHeapMinNode->left;
            fibonacciNode *secondHeapMinNodeLeftTemp =
                    secondHeapMinNode->left;
            firstHeapMinNode->left = secondHeapMinNodeLeftTemp;
            secondHeapMinNode->left = firstHeapMinNodeLeftTemp;
            firstHeapMinNodeLeftTemp->right = secondHeapMinNode;
            secondHeapMinNodeLeftTemp->right = firstHeapMinNode;

            if (secondHeapMinNode->key < firstHeapMinNode->key)
                appendedFibHeap->minNode = secondHeapMinNode;
            else
                appendedFibHeap->minNode = firstHeapMinNode;
        }

        appendedFibHeap->numNodes = fibHeapFirst->numNodes
                                    + fibHeapSecond->numNodes;
        return appendedFibHeap;
    }

    void fibHeapAddChild(fibonacciNode *parentNode, fibonacciNode *newChildNode) {
        if (parentNode->degree == 0) {
            parentNode->child = newChildNode;
            newChildNode->right = newChildNode;
            newChildNode->left = newChildNode;
            newChildNode->parent = parentNode;
        } else {
            fibonacciNode *firstChild = parentNode->child;
            fibonacciNode *firstChildLeftTemp = firstChild->left;
            firstChild->left = newChildNode;
            newChildNode->right = firstChild;
            newChildNode->left = firstChildLeftTemp;
            firstChildLeftTemp->right = newChildNode;
        }
        newChildNode->parent = parentNode;
        parentNode->degree = parentNode->degree + 1;
    }


    void fibHeapRemoveNodeFromRoot(fibonacciNode *node) {
        if (node->right != node) {
            node->right->left = node->left;
            node->left->right = node->right;
        }

        if (node->parent != nullptr) {
            int parentDegree = node->parent->degree;
            if (parentDegree == 1)
                node->parent->child = nullptr;
            else
                node->parent->child = node->right;

            node->parent->degree = node->parent->degree - 1;
        }
    }

    void fibHeapLink(fibonacciHeap *heap_inst, fibonacciNode *highNode, fibonacciNode *lowNode) {
        fibHeapRemoveNodeFromRoot(highNode);
        fibHeapAddChild(lowNode, highNode);
        highNode->mark = false;
    }

    void fibHeapConsolidate(fibonacciHeap *heap_inst) {
        int node_degree;
        int count = 0, root_count = 0;
        if (heap_inst->numNodes > 1) {
            int degree_table_size = heap_inst->numNodes;
            std::vector<fibonacciNode *> degree_table;
            fibonacciNode *current_node = heap_inst->minNode;
            fibonacciNode *start_node = heap_inst->minNode;
            fibonacciNode *existing_node_degree_array, *current_consolidating_node;

            fibonacciNode *tempNode = heap_inst->minNode;
            fibonacciNode *iterating_node = heap_inst->minNode;
            do {
                root_count++;
                iterating_node = iterating_node->right;
            } while (iterating_node != tempNode);

            while (count < root_count) {
                current_consolidating_node = current_node;
                current_node = current_node->right;
                node_degree = current_consolidating_node->degree;
                while (true) {
                    while (node_degree >= degree_table.size())
                        degree_table.push_back(nullptr);
                    if (degree_table[node_degree] == nullptr) {
                        degree_table[node_degree] = current_consolidating_node;
                        break;
                    } else {
                        existing_node_degree_array = degree_table[node_degree];
                        if (current_consolidating_node->key > existing_node_degree_array->key) {
                            fibonacciNode *temp_node = current_consolidating_node;
                            current_consolidating_node = existing_node_degree_array;
                            existing_node_degree_array = temp_node;
                        }
                        if (existing_node_degree_array == current_consolidating_node) break;
                        fibHeapLink(heap_inst, existing_node_degree_array,
                                    current_consolidating_node);
                        degree_table[node_degree] = nullptr;
                        node_degree++;
                    }
                }
                count++;
            }

            heap_inst->minNode = nullptr;
            for (int i = 0; i < degree_table.size(); i++) {
                if (degree_table[i] != nullptr)
                    fibHeapExistingToRoot(heap_inst, degree_table[i]);

            }
        }
    }

    fibonacciNode *fibHeapExtractMin(fibonacciHeap *heap_inst) {

        fibonacciNode *min_node = heap_inst->minNode;
        std::ofstream myfile;
        myfile.open("order_fib.txt", std::ios_base::app);

        myfile << "FIB -- MIN NODE " << min_node->nodeIndex << "\n";

        if (min_node != nullptr) {
            int degree = min_node->degree;
            fibonacciNode *current_child = min_node->child;
            fibonacciNode *removed_child;
            int count = 0;
            while (count < degree) {
                removed_child = current_child;
                current_child = current_child->right;
                fibHeapExistingToRoot(heap_inst, removed_child);
                count++;
            }

            fibHeapRemoveNodeFromRoot(min_node);
            heap_inst->numNodes = heap_inst->numNodes - 1;
            if (heap_inst->numNodes == 0)
                heap_inst->minNode = nullptr;
            else {
                heap_inst->minNode = min_node->right;
                fibonacciNode *min_node_left_temp = min_node->left;
                heap_inst->minNode->left = min_node_left_temp;
                min_node_left_temp->right = heap_inst->minNode;
                fibHeapConsolidate(heap_inst);
            }
        }
        return min_node;
    }


    void fibHeapCut(fibonacciHeap *heap_inst, fibonacciNode *node,
                    fibonacciNode *node_parent) {

        fibHeapRemoveNodeFromRoot(node);
        fibHeapExistingToRoot(heap_inst, node);

    }

    void fibHeapCascadingCut(fibonacciHeap *heap_inst, fibonacciNode *node) {
        fibonacciNode *parent_node = node->parent;
        if (parent_node != nullptr) {
            if (node->mark == false)
                node->mark = true;
            else {
                fibHeapCut(heap_inst, node, parent_node);
                fibHeapCascadingCut(heap_inst, parent_node);
            }
        }

    }

    void fibHeapDecreaseKey(fibonacciHeap *heap_inst, fibonacciNode *node_inst, int new_key) {
        int old_key = node_inst->key;

        if (new_key > old_key)
            return;


        node_inst->key = new_key;
        if (node_inst->parent != nullptr) {
            if (node_inst->key < node_inst->parent->key) {
                fibonacciNode *parent_node = node_inst->parent;
                fibHeapCut(heap_inst, node_inst, node_inst->parent);
                fibHeapCascadingCut(heap_inst, parent_node);
            }
        }

        if (node_inst->key < heap_inst->minNode->key) {
            heap_inst->minNode = node_inst;
        }

    }

    graph *createGraph(int graph_size) {
        graph *graph_inst = new graph;
        graph_inst->graphNumVertices = graph_size;
        return graph_inst;
    }


    void addEdge(graph *graph_obj, int src, int dest, int edge_len) {
        adjNode *new_node = new adjNode;
        new_node->destNode = dest;
        new_node->edgeLen = edge_len;
        graph_obj->adjacentListMap[src].push_back(new_node);

        adjNode *new_node_2 = new adjNode;
        new_node_2->destNode = src;
        new_node_2->edgeLen = edge_len;
        graph_obj->adjacentListMap[dest].push_back(new_node_2);
    }

    int getMinDistantUnmarkedNode(graph *graph_obj, int *distance_to_dest, bool *marked);

    int *dijkstra_normal(graph *graph_instance, int src) {
        int count_marked = 0;
        distanceToBest = new int[graph_instance->graphNumVertices];
        bool *marked = new bool[graph_instance->graphNumVertices];
        for (int i = 0; i < graph_instance->graphNumVertices; i++)
            distanceToBest[i] = INT_MAX;

        for (int i = 0; i < graph_instance->graphNumVertices; i++)
            marked[i] = false;


        distanceToBest[src] = 0;

        while (count_marked < graph_instance->graphNumVertices) {
            getMinDistantUnmarkedNode(graph_instance, distanceToBest, marked);
            count_marked++;
        }

        return distanceToBest;
    }


    int getMinDistantUnmarkedNodeFibHeap(graph *graph_obj,
                                         fibonacciHeap *heap, fibonacciNode **node_array, bool *marked);

    fibonacciNode **dijkstraFibanocci(graph *graph_instance, int src) {
        int count_marked = 0;
        fibonacciNode **node_array =
                new fibonacciNode *[graph_instance->graphNumVertices];
        bool *marked = new bool[graph_instance->graphNumVertices];
        fibonacciHeap *heap_inst = new fibonacciHeap;

        for (int i = 0; i < graph_instance->graphNumVertices; i++) {
            marked[i] = false;
            node_array[i] = new fibonacciNode;
            if (i == src)
                fibHeapInsert(heap_inst, node_array[i], 0);
            else
                fibHeapInsert(heap_inst, node_array[i], INT_MAX);

            node_array[i]->nodeIndex = i;
        }

        while (count_marked < graph_instance->graphNumVertices) {
            getMinDistantUnmarkedNodeFibHeap(graph_instance, heap_inst, node_array, marked);
            count_marked++;
        }


        return node_array;
    }

    int getMinDistantUnmarkedNode(graph *graph_obj, int *distance_to_dest, bool *marked) {
        int min_distance = INT_MAX;
        int min_node_index;

        for (int i = 0; i < graph_obj->graphNumVertices; i++) {
            if ((!marked[i]) && (min_distance >= distance_to_dest[i])) {
                min_distance = distance_to_dest[i];
                min_node_index = i;
            }
        }
        std::ofstream myfile;
        myfile.open("order_normal.txt", std::ios_base::app);
        myfile << "NORMAL -- MIN NODE " << min_node_index << ":";

        if (shortestOrder[min_node_index].size() < 0) {
            for (int i = 0; i < shortestOrder[min_node_index].size(); i++)
                myfile << shortestOrder[min_node_index][i] << "-";

        }

        myfile << "\n";
        myfile.close();
        marked[min_node_index] = true;

        std::list<adjNode *> adj_list_for_node =
                graph_obj->adjacentListMap[min_node_index];

        for (std::list<adjNode *>::iterator it = adj_list_for_node.begin();
             it != adj_list_for_node.end(); ++it) {
            int adj_node_index = (*it)->destNode;
            if (marked[adj_node_index] == false) {
                if (distance_to_dest[adj_node_index]
                    > distance_to_dest[min_node_index] + (*it)->edgeLen) {
                    distance_to_dest[adj_node_index] =
                            distance_to_dest[min_node_index] + (*it)->edgeLen;
                    shortestOrder[adj_node_index].push_back(min_node_index);
                }
            }
        }
        return min_node_index;
    }


    int getMinDistantUnmarkedNodeFibHeap(graph *graph_obj,
                                         fibonacciHeap *heap, fibonacciNode **node_array, bool *marked) {

        int min_distance = INT_MAX;
        fibonacciNode *min_node = fibHeapExtractMin(heap);
        int min_node_index;

        if (min_node != nullptr) {
            min_node_index = min_node->nodeIndex;
            marked[min_node_index] = true;
            std::list<adjNode *> adj_list_for_node = graph_obj->adjacentListMap[min_node_index];
            for (std::list<adjNode *>::iterator it = adj_list_for_node.begin();
                 it != adj_list_for_node.end(); ++it) {
                int adj_node_index = (*it)->destNode;

                if (marked[adj_node_index] == false) {
                    if (node_array[adj_node_index]->key > node_array[min_node_index]->key + (*it)->edgeLen) {
                        fibHeapDecreaseKey(heap, node_array[adj_node_index],
                                           node_array[min_node_index]->key + (*it)->edgeLen);
                    }
                }
            }
        }

        return min_node_index;
    }

    graph *generateRandomGraph(int vertices, int density) {
        int num_nodes = vertices;
        graph *my_graph = createGraph(num_nodes);
        std::map<std::pair<int, int>, int> check_map;
        long double num_edges = num_nodes * (num_nodes - 1) / 2;
        num_edges = num_edges * density / 100.0;
        long double count = 0;

        while (count < num_edges) {
            int start, end, weight;
            start = rand() % num_nodes;
            end = rand() % num_nodes;
            if (start > end) {
                int temp = start;
                start = end;
                end = temp;
            }
            std::pair<int, int> edge(start, end);
            weight = (rand() % 1000) + 1;

            if (check_map.find(edge) == check_map.end() and start != end) {
                check_map[edge] = 1;
                addEdge(my_graph, start, end, weight);
                count++;
            }
        }

        return my_graph;
    }
}