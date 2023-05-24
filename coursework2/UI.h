//
// Created by nektt on 5/24/2023.
//

#ifndef COURSEWORK2_UI_H
#define COURSEWORK2_UI_H

#include "Button.h"
#include "Field.h"
#include "SudokuSolver.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>


class UserInterface : public sf::Drawable {
    Button _closeBtn;
    Button _resetBtn;
    Button _solveBtn;
    Button _greedyAlgBtn;
    sf::RenderWindow *_window;
    Field &_field;

    sf::Font _font;
    sf::Text _errorText;
    bool _showErr = false;
public:

    explicit UserInterface(sf::RenderWindow *window, Field &field) : _field(field) {
        _closeBtn = Button(sf::Vector2f(100, 80), sf::Vector2f(Cfg::WindowSize.x - 110, 10), "Exit");

        _resetBtn = Button(sf::Vector2f(150, 80), sf::Vector2f(Cfg::WindowSize.x - 160, Cfg::WindowSize.y - 100),
                           "Reset");
        _solveBtn = Button(sf::Vector2f(150, 80), sf::Vector2f(Cfg::WindowSize.x - 160, Cfg::WindowSize.y - 200),
                           "Solve");
        _greedyAlgBtn = Button(sf::Vector2f(150, 80), sf::Vector2f(Cfg::WindowSize.x - 160, Cfg::WindowSize.y - 300),
                               "Greedy alg");


        _font.loadFromFile(Cfg::FontPath);

        _errorText.setFont(_font);
        _errorText.setFillColor(sf::Color::Black);
        _errorText.setCharacterSize(30);
        _errorText.setPosition(sf::Vector2f(Cfg::WindowSize.x / 2 - 100, 5));
        _errorText.setString("Solution Not Found");

        _closeBtn.setFont(_font);
        _closeBtn.setColors(sf::Color(255, 128, 128), sf::Color(252, 78, 78), sf::Color(252, 3, 3), sf::Color::White);
        _closeBtn.setTextSizePx(50);
        _closeBtn.setTextPosCenter();

        _resetBtn.setFont(_font);
        _resetBtn.setColors(sf::Color(252, 124, 250), sf::Color(166, 94, 165), sf::Color(171, 38, 169),
                            sf::Color::White);
        _resetBtn.setTextSizePx(50);
        _resetBtn.setTextPosCenter();

        _solveBtn.setFont(_font);
        _solveBtn.setColors(sf::Color(252, 124, 250), sf::Color(166, 94, 165), sf::Color(171, 38, 169),
                            sf::Color::White);
        _solveBtn.setTextSizePx(50);
        _solveBtn.setTextPosCenter();

        _greedyAlgBtn.setFont(_font);
        _greedyAlgBtn.setColors(sf::Color(252, 124, 250), sf::Color(166, 94, 165), sf::Color(171, 38, 169),
                                sf::Color::White);
        _greedyAlgBtn.setTextSizePx(25);
        _greedyAlgBtn.setTextPosCenter();


        _window = window;

    }

    void detectCollisions(sf::Vector2i mousePos, bool isPressed) {
        _showErr = false;
        _closeBtn.changeColorOnMousePosition(mousePos, isPressed);
        _resetBtn.changeColorOnMousePosition(mousePos, isPressed);
        _solveBtn.changeColorOnMousePosition(mousePos, isPressed);
        _greedyAlgBtn.changeColorOnMousePosition(mousePos, isPressed);
        if (_closeBtn.isPressed())
            _window->close();
        if (_solveBtn.isPressed()) {
            auto start = std::chrono::high_resolution_clock::now();
            SudokuSolver SS(_field.getField());
            if (SS.solveSudoku()) {
                _field.setField(SS.getGrid());
            } else
                _showErr = true;
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << duration.count()<<"\n" ;
        }
        if (_greedyAlgBtn.isPressed()) {
            GraphSudokuSolver GS;
            GS.sudokuGrid2Graph(_field.getField());
            GS.greedyColoring();
            _field.setField(GS.getGridFromColors());
        }
        if (_resetBtn.isPressed())
            _field.resetValues();

    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(_closeBtn);
        target.draw(_solveBtn);
        target.draw(_resetBtn);
        target.draw(_greedyAlgBtn);
        if (_showErr)
            target.draw(_errorText);
    }
};


#endif //COURSEWORK2_UI_H
