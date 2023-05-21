
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include "Button.h"
#include "Field.h"
#include "Cfg.h"


class SudokuSolver {

    std::vector<std::vector<short>> _grid;
    const static int N = 9;


    bool _isPresentInCol(int col, int num) { //check whether num is present in col or not
        for (int row = 0; row < N; row++)
            if (_grid[row][col] == num)
                return true;
        return false;
    }

    bool _isPresentInRow(int row, int num) { //check whether num is present in row or not
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

    bool _findEmptyPlace(int &row, int &col) { //get empty location and update row and column
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


class UserInterface : public sf::Drawable {
    Button _closeBtn;
    Button _resetBtn;
    Button _solveBtn;
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

        _window = window;

    }

    void detectCollisions(sf::Vector2i mousePos, bool isPressed) {
        _showErr = false;
        _closeBtn.changeColorOnMousePosition(mousePos, isPressed);
        _resetBtn.changeColorOnMousePosition(mousePos, isPressed);
        _solveBtn.changeColorOnMousePosition(mousePos, isPressed);
        if (_closeBtn.isPressed())
            _window->close();
        if (_solveBtn.isPressed()) {
            SudokuSolver SS(_field.getField());
            if (SS.solveSudoku()) {
                _field.setField(SS.getGrid());
            } else {
                _showErr = true;
            }

        }
        if (_resetBtn.isPressed()) {
            _field.resetValues();
        }

    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(_closeBtn);
        target.draw(_solveBtn);
        target.draw(_resetBtn);
        if (_showErr)
            target.draw(_errorText);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(Cfg::WindowSize.x, Cfg::WindowSize.y), "SFML works!", sf::Style::None);

    Field field;
    UserInterface UI(&window, field);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            UI.detectCollisions(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
            field.detectCollisions(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
            field.getNumber();
        }

        window.clear(sf::Color(140, 245, 201));
        window.draw(field);
        window.draw(UI);
        window.display();
    }
    return 0;
}
