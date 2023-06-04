#include <SFML/Graphics.hpp>

#ifndef COURSEWORK2_FIELD_H
#define COURSEWORK2_FIELD_H

#include "Button.h"
#include "Cfg.h"

#include <iostream>
#include <fstream>

class Field : public sf::Drawable {
    sf::RectangleShape _bg;
    sf::Vector2f _fieldGap;
    std::vector<sf::RectangleShape> _vertLines;
    std::vector<sf::RectangleShape> _horizLines;

    std::vector<std::vector<Button>> _cells;
    std::vector<std::vector<short>> _cellsValues;
    bool _isFieldValid = true;

    Button *_selectedCell = nullptr;
    sf::Vector2i _selectedCellPos;

    sf::Font _font;

    int _sudokuSize = 9;

    void _initLines();

    void _clearCellsColors();

    void _setSelectedCellColor();




public:
    Field();
    void setSize(int size){
        if(size%3 == 0) _sudokuSize = size;
        else throw "sudokuSize must be %3";
    }
    int getSize(){
        return _sudokuSize;
    }

    std::vector<std::vector<short>> getField() const;

    void setField(std::vector<std::vector<short>> field);

    void getFromFile(std::string fileName) {
        std::fstream in(fileName, std::ios_base::in);
//        std::cout<<in.is_open();
//        int i;
        in >> _sudokuSize;
        _cellsValues.clear();
        for (int i = 0; i < _sudokuSize; ++i) {
            _cellsValues.emplace_back();
            for (int j = 0; j < _sudokuSize; ++j)
                _cellsValues[i].push_back(0);
        }

        for (int row = 0; row < _sudokuSize; row++)
            for (int col = 0; col < _sudokuSize; col++) {
                in >> _cellsValues[row][col];
            }

    }

    bool validateField();
    void detectCollisions(sf::Vector2i mousePos, bool isPressed);

    void getNumber();
    void print() {
        for (int row = 0; row < _sudokuSize; row++){
            for (int col = 0; col < _sudokuSize; col++) {
                std::cout << _cellsValues[row][col] << " ";
            }
        std::cout << "\n";
    }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void resetValues();
};


#endif //COURSEWORK2_FIELD_H
