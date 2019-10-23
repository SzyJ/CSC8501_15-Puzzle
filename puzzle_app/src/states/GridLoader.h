// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: GridLoader.h
// Date: 23/10/2019

#pragma once
#include "fsm/State.h"

namespace screen {

    class GridLoader : public fsm::State {
    public:
        GridLoader();
        ~GridLoader();

    private:
        virtual void OnEnter() override;

    };

}
