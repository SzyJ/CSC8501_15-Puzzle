// Author: Szymon Jackiewicz
// 
// Project: sandbox
// File: Main.cpp
// Date: 17/10/2019

#include <iostream>
#include <peng.h>
#include "UI/MainMenu.h"

int main() {

    std::cout << Peng::Math::Factorial(10);

    UI::MainMenu mainMenu;
    mainMenu.Show();

    return 0;
}
