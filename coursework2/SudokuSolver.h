//
// Created by nektt on 5/24/2023.
//

#ifndef COURSEWORK2_SUDOKUSOLVER_H
#define COURSEWORK2_SUDOKUSOLVER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Cfg.h"

const int N = 81;

class GraphSudokuSolver {
    std::list<int> *adj;

    int result[81];
public:
    GraphSudokuSolver() {
        adj = new std::list<int>[N];
    }

    ~GraphSudokuSolver() { delete[] adj; }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    void sudokuGrid2Graph(const std::vector<std::vector<short>> &grid) {

        for (int vertNum = 0; vertNum < 81; ++vertNum) {
            int vLine = vertNum / 9, vCol = vertNum % 9;
            for (int cur = 0; cur < 9; ++cur) {
                if (vertNum + cur - vCol != vertNum)
                    // add row links
                    addEdge(vertNum, vertNum + cur - vCol);
                if (vertNum != cur * 9 + vCol)
                    // add col links
                    addEdge(vertNum, cur * 9 + vCol);
            }
            // add square links
            for (int i = (vLine / 3) * 3; i < ((vLine / 3) + 1) * 3; ++i) {
                for (int j = (vCol / 3) * 3; j < ((vCol / 3) + 1) * 3; ++j) {
                    int nE = (i) * 9 + (j);
                    if (nE != vertNum)
                        addEdge(vertNum, nE);
                }
            }
            result[vertNum] = grid[vLine][vCol] - 1;
        }

    }


    std::vector<std::vector<short>> getGridFromColors() {
        std::vector<std::vector<short>> grid;
        for (int i = 0; i < 9; ++i) {
            grid.emplace_back();
            for (int j = 0; j < 9; ++j)
                grid[i].emplace_back();
        }
        for (int vertNum = 0; vertNum < 81; ++vertNum) {
            int vLine = vertNum / 9, vCol = vertNum % 9;
            grid[vLine][vCol] = result[vertNum] + 1;
        }
        return grid;
    }


    void greedyColoring() {
        // A temporary array to store the available colors. True
        // value of IsLinkedCr[cr] would mean that the color cr is
        // assigned to one of its adjacent vertices
        bool IsLinkedCr[N];
        for (int u = 0; u < N; u++)
            IsLinkedCr[u] = false;

        // Assign colors to remaining V-1 vertices
        for (int u = 0; u < N; u++) {
            if (result[u] != -1)
                continue;
            // Process all adjacent vertices and flag their colors
            // as unavailable
            std::list<int>::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
                if (result[*i] != -1)
                    IsLinkedCr[result[*i]] = true;

            // Find the first available color
            int cr;
            for (cr = 0; cr < N; cr++)
                if (!IsLinkedCr[cr])
                    break;

            result[u] = cr; // Assign the found color

            // Reset the values back to false for the next iteration
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
                if (result[*i] != -1)
                    IsLinkedCr[result[*i]] = false;
        }

//        // print the result
//        for (int u = 0; u < N; u++)
//            std::cout << "Vertex " << u << " --->  Color "
//                      << result[u] << std::endl;
    }
};

class SudokuSolver {

    std::vector<std::vector<short>> _grid;
    const static int N = 9;


    bool _isPresentInCol(int col, int num) {
        //check whether num is present in col or not
        for (int row = 0; row < N; row++)
            if (_grid[row][col] == num)
                return true;
        return false;
    }

    bool _isPresentInRow(int row, int num) {
        //check whether num is present in row or not
        for (int col = 0; col < N; col++)
            if (_grid[row][col] == num)
                return true;
        return false;
    }

    bool _isPresentInBox(int boxStartRow, int boxStartCol, int num) {
        //check whether num is present in 3x3 box or not
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (_grid[row + boxStartRow][col + boxStartCol] == num)
                    return true;
        return false;
    }

    bool _findEmptyPlace(int &row, int &col) {
        //get empty location and update row and column
        for (row = 0; row < N; row++)
            for (col = 0; col < N; col++)
                if (_grid[row][col] == 0) //marked with 0 is empty
                    return true;
        return false;
    }

    bool _isValidPlace(int row, int col, int num) {
        //when item not found in col, row and current 3x3 box
        return !_isPresentInRow(row, num) && !_isPresentInCol(col, num) && !_isPresentInBox(row - row % 3,
                                                                                            col - col % 3, num);
    }


public:
    SudokuSolver(std::vector<std::vector<short>> grid) {
        _grid = grid;
    }

    bool solveSudoku() {
        int row, col;
        if (!_findEmptyPlace(row, col))
            return true; //when all places are filled
        for (int num = 1; num <= 9; num++) { //valid numbers are 1 - 9
            if (_isValidPlace(row, col, num)) { //check validation, if yes, put the number in the grid
                _grid[row][col] = num;
                if (solveSudoku()) //recursively go for other rooms in the grid
                    return true;
                _grid[row][col] = 0; //turn to unassigned space when conditions are not satisfied
            }
        }
        return false;
    }

    std::vector<std::vector<short>> getGrid() {
        return _grid;
    }
};


#endif //COURSEWORK2_SUDOKUSOLVER_H
