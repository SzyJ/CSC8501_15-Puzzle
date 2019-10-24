#pragma once

#include "fsm/State.h"
#include <Fixtures/Matrix.h>
#include <Fixtures/Prompt.h>
#include <Fixtures/Menu.h>


namespace screen {

    class GridBuilder : public fsm::State {
    public:
        GridBuilder();
        ~GridBuilder();

    private:
        WinTUI::Prompt* m_MatrixInput = nullptr;
        WinTUI::Matrix<int>* m_GridBuilder = nullptr;
        WinTUI::Menu* m_PrintToFileMenu = nullptr;

        inline void ConfigureMatrixPrompt();
        inline void ConfigureGridBuilder();
        inline void ConfigurePrintMenu();

        virtual void OnEnter() override;


    };

}

