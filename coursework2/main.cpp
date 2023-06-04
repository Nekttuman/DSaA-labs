
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Field.h"
#include "SudokuSolver.h"
#include "Cfg.h"
#include "UI.h"
#include "TestSudokuGenerate.h"

long long timeTest(std::string path, int boxSW, int boxSH) {
    Field F;
    F.getFromFile(path);

    SudokuSolver SS(F.getField(), F.getSize());
    SS.setBoxSize(boxSW,boxSH);

    auto start = std::chrono::high_resolution_clock::now();
    if (SS.solveSudoku() == false)
        std::cout<<"Not solved\n";
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    F.setField(SS.getGrid());
    return duration.count();

}

int main() {
//    sf::RenderWindow window(sf::VideoMode(Cfg::WindowSize.x, Cfg::WindowSize.y), "SFML works!", sf::Style::None);
//
//    Field field;
//    UserInterface UI(&window, field);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//            UI.detectCollisions(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
//            field.detectCollisions(sf::Mouse::getPosition(window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
//            field.getNumber();
//        }
//
//        window.clear(sf::Color(140, 245, 201));
//        window.draw(field);
//        window.draw(UI);
//        window.display();
//    }



    TestSudokuGenerate* TG;// = new TestSudokuGenerate(N, K);
    for (int folder = 50; folder<=60; folder +=5){
        long long Sum = 0;
        for(int file = 1; file <=100;++file)
        {
//            std::cout<<folder<<"  "<<file<<"\n";
//            TG = new TestSudokuGenerate(9, folder);
//            TG->fillValues();
//            TG->SaveToFile("F:/repos/DSaA-labs/coursework2/testData/"+ to_string(folder)+"/test"+ to_string(file)+".txt");
//            delete TG;

            Sum+=timeTest("F:/repos/DSaA-labs/coursework2/testData/"+ to_string(folder)+"/test"+ to_string(file)+".txt",3,3);
//            std:cout<<Sum<<" ";
        }
        std::cout<<"avg time for "<<folder<<" empty cells  "<<(double)Sum/100<<"  milliS\n";
    }


    return 0;
}
