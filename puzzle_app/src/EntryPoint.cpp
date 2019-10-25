// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: EntryPoint.cpp
// Date: 25/10/2019

#include "fsm/Controller.h"

int main() {

    fsm::Controller::Get().Start(fsm::States::MainMenu);

    return 0;
}
