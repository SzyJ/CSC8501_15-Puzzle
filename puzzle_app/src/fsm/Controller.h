#pragma once
#include "fsm/State.h"
#include "fsm/Machine.h"
#include "states/MainMenu.h"

#include <unordered_map>

namespace fsm {

    enum States {
        MainMenu
    };

    class Controller {
    public:
        Controller(Controller const& copy) = delete;
        void operator=(Controller const& assign) = delete;

        static Controller& Get() {
            static Controller instance;
            return instance;
        }

        static void Start(States state) {
            Machine::Get().SetInitialState(m_allStates[state]);
        }

        static void GoTo(States state) {
            Machine::Get().ChangeState(m_allStates[state]);
        }

    private:
        static std::unordered_map<States, State*> m_allStates;

        Controller() {
            m_allStates[MainMenu] = new ui::MainMenu;
        }

    };

}
