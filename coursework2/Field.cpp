//
// Created by nektt on 5/21/2023.
//
#include "Field.h"



//
// Created by nektt on 5/21/2023.
//
#include <SFML/Graphics.hpp>

void Field::_initLines() {
    for (int i = 0; i < 8; ++i) {
        sf::Vector2f vertPos(_fieldGap + sf::Vector2f((i + 1) * Cfg::CellSizePx, 0));
        if ((i + 1) % 3 == 0)
            _vertLines.emplace_back(sf::Vector2f(4, Cfg::CellSizePx * 9));
        else
            _vertLines.emplace_back(sf::Vector2f(2, Cfg::CellSizePx * 9));
        _vertLines[i].setPosition(vertPos);
        _vertLines[i].setFillColor(sf::Color::Black);

        sf::Vector2f horizPos(_fieldGap + sf::Vector2f(0, (i + 1) * Cfg::CellSizePx));
        if ((i + 1) % 3 == 0)
            _horizLines.emplace_back(sf::Vector2f(Cfg::CellSizePx * 9, 4));
        else
            _horizLines.emplace_back(sf::Vector2f(Cfg::CellSizePx * 9, 2));
        _horizLines[i].setPosition(horizPos);
        _horizLines[i].setFillColor(sf::Color::Black);

    }
}


void Field::_setSelectedCellColor() {
    if (_selectedCell != nullptr)
        _selectedCell->setColors(sf::Color(167, 235, 235), sf::Color(151, 176, 176), sf::Color(167, 235, 235),
                                 sf::Color::Black);
}


Field::Field() {
    _fieldGap.x = 100;
    _fieldGap.y = 100;
    _bg.setFillColor(sf::Color::White);
    _bg.setSize(sf::Vector2f(450, 450));
    _bg.setOutlineColor(sf::Color::Black);
    _bg.setOutlineThickness(2);
    _bg.setPosition(_fieldGap);

    _selectedCellPos = sf::Vector2i(-1, -1);

    _font.loadFromFile(Cfg::FontPath);

    for (int i = 0; i < 9; ++i) {
        _cells.emplace_back();
        _cellsValues.emplace_back();
        for (int j = 0; j < 9; ++j) {
            _cells[i].push_back(Button(sf::Vector2f(Cfg::CellSizePx, Cfg::CellSizePx), _fieldGap + sf::Vector2f(
                    Cfg::CellSizePx * (i), Cfg::CellSizePx * (j)), "0"));
            _cells[i][j].setTextSizePx(18);
            _cells[i][j].setColors(sf::Color::White, sf::Color(151, 176, 176), sf::Color(167, 235, 235),
                                   sf::Color::Black);
            _cells[i][j].setFont(_font);
            _cells[i][j].setTextPosCenter();

            _cellsValues[i].push_back(0);
        }
    }
    _cellsValues = {
            {3, 0, 6, 5, 0, 8, 4, 0, 0},
            {5, 2, 0, 0, 0, 0, 0, 0, 0},
            {0, 8, 7, 0, 0, 0, 0, 3, 1},
            {0, 0, 3, 0, 1, 0, 0, 8, 0},
            {9, 0, 0, 8, 6, 3, 0, 0, 5},
            {0, 5, 0, 0, 9, 0, 6, 0, 0},
            {1, 3, 0, 0, 0, 0, 2, 5, 0},
            {0, 0, 0, 0, 0, 0, 0, 7, 4},
            {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };
    _clearCellsColors();

    for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++){
            if (_cellsValues[col][row] == 0)
                _cells[row][col].setText(" ");
            else
                _cells[row][col].setText(std::to_string(_cellsValues[col][row]));
        }

    _initLines();
}

std::vector<std::vector<short>> Field::getField() const {
    return _cellsValues;
}

void Field::setField(std::vector<std::vector<short>> field){
    resetValues();
    _cellsValues = field;
    for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++){
            if (_cellsValues[row][col] == 0)
                _cells[row][col].setText(" ");
            else
                _cells[row][col].setText(std::to_string(_cellsValues[col][row]));
        }
}


void Field::detectCollisions(sf::Vector2i mousePos, bool isPressed) {
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            _cells[i][j].changeColorOnMousePosition(mousePos, isPressed);
            if (_cells[i][j].isPressed() && &_cells[i][j] != _selectedCell) {
                _selectedCell = &_cells[i][j];
                _setSelectedCellColor();
                _selectedCellPos = sf::Vector2i(i, j);
            }
        }
}

void Field::getNumber() {
    if (_selectedCell == nullptr)
        return;
    short num = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        num = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        num = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        num = 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        num = 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        num = 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        num = 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        num = 6;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        num = 7;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        num = 8;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        num = 9;
    if (num != -1) {
        _cellsValues[_selectedCellPos.y][_selectedCellPos.x] = num;
        _selectedCell->setText(std::to_string(num)=="0"?" ":std::to_string(num));

        _validateField();
        if (!_isFieldValid) {
            _selectedCell->setColors(sf::Color::Red, sf::Color(151, 176, 176), sf::Color::Red,
                                     sf::Color::Black);
        } else {
            _clearCellsColors();
        }
    }
}

void Field::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_bg);

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            target.draw(_cells[i][j]);
        }

    std::for_each(_vertLines.begin(), _vertLines.end(), [&](const auto &item) {
        target.draw(item);
    });

    std::for_each(_horizLines.begin(), _horizLines.end(), [&](const auto &item) {
        target.draw(item);
    });


}

void Field::resetValues() {
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            _cellsValues[i][j] = 0;
            _cells[i][j].setText(" ");
            _cells[i][j].setColors(sf::Color::White, sf::Color(151, 176, 176), sf::Color(167, 235, 235),
                                   sf::Color::Black);
        }
    _isFieldValid = true;
}

void Field::_clearCellsColors() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (_cellsValues[j][i])
                _cells[i][j].setColors(sf::Color(232, 232, 232), sf::Color(151, 176, 176), sf::Color(167, 235, 235),
                                   sf::Color::Black);
            else
                _cells[i][j].setColors(sf::Color::White, sf::Color(151, 176, 176), sf::Color(167, 235, 235),
                                       sf::Color::Black);
        }
    }
}

void Field::_validateField() {
    // rows
    for (auto line: _cellsValues) {
        for (auto item = line.begin(); item != line.end(); item++) {
            if (std::find(item + 1, line.end(), *item) != line.end() && *item != 0) {
                _isFieldValid = false;
                return;
            } else {
                _isFieldValid = true;
            }
        }
    }
    // colls
    for (int i = 0; i < 9; ++i) {
        bool alreadyInCol[] = {false, false, false, false, false, false, false, false, false, false};
        for (int j = 0; j < 9; ++j) {
            if (alreadyInCol[_cellsValues[j][i]] && _cellsValues[j][i] != 0) {
                _isFieldValid = false;
                return;
            } else {
                alreadyInCol[_cellsValues[j][i]] = true;
                _isFieldValid = true;
            }
        }
    }
    // squads
    for (int squadN = 0; squadN < 9; squadN++) {
        bool alreadyInCol[] = {false, false, false, false, false, false, false, false, false, false};
        for (int i = (squadN / 3) * 3; i < (squadN / 3) * 3 + 3; ++i) {
            for (int j = (squadN % 3) * 3; j < (squadN % 3) * 3 + 3; ++j) {
                if (alreadyInCol[_cellsValues[j][i]] && _cellsValues[j][i] != 0) {
                    _isFieldValid = false;
                    return;
                } else {
                    alreadyInCol[_cellsValues[j][i]] = true;
                    _isFieldValid = true;
                }
            }
        }
    }
}