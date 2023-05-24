#include <SFML/Graphics.hpp>

#ifndef COURSEWORK2_FIELD_H
#define COURSEWORK2_FIELD_H

#include "Button.h"
#include "Cfg.h"

#include <iostream>

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

    void _initLines();

    void _clearCellsColors();

    void _setSelectedCellColor();

    void _validateField();



public:
    Field();

    std::vector<std::vector<short>> getField() const;

    void setField(std::vector<std::vector<short>> field);

    void detectCollisions(sf::Vector2i mousePos, bool isPressed);

    void getNumber();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void resetValues();
};


#endif //COURSEWORK2_FIELD_H
