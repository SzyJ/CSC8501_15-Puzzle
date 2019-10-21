#pragma once
#include "fsm/State.h"
#include "fsm/Machine.h"
#include "states/MainMenu.h"
#include "states/RandomGrid.h"

#include <unordered_map>

namespace fsm {

    enum States {
        MainMenu,
        RandomGrid
    };

    class Controller {
    public:
        Controller(Controller const& copy) = delete;
        void operator=(Controller const& assign) = delete;

        ~Controller() = default;

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
        static inline std::unordered_map<States, State*> InitialiseStateMap() {
            std::unordered_map<States, State*> allStates;
            allStates[MainMenu] = new screen::MainMenu();
            allStates[RandomGrid] = new screen::RandomGrid();

            return allStates;
        }

        static inline std::unordered_map<States, State*> m_allStates = InitialiseStateMap();

        Controller() = default;

    };

}
