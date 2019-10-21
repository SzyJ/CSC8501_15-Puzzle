// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: RandomGrid.h
// Date: 21/10/2019

#pragma once
#include "fsm/State.h"
#include <Fixtures/Prompt.h>

namespace screen {

    class RandomGrid : public fsm::State {
    public:
        RandomGrid();
        ~RandomGrid();

        int GetUserChoice();

    private:
        WinTUI::Prompt* m_NumberPrompt;

        virtual void OnEnter() override;

    };

}
