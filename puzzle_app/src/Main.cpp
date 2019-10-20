// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: Main.cpp
// Date: 17/10/2019

#include <iostream>
#include <peng.h>
#include "states/MainMenu.h"
#include "fsm/Controller.h"

int main() {
//
//    std::cout << Peng::Math::Factorial(10);
//
//
//
//    ui::MainMenu mainMenu;
//    mainMenu.Show();
//
    fsm::Controller::Get().Start(fsm::States::MainMenu);

    return 0;
}
