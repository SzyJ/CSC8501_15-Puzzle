#pragma once
#include "fsm/State.h"

namespace fsm {

    class Machine {
    public:
        Machine(Machine const& copy) = delete;
        void operator=(Machine const& assign) = delete;

        static Machine& Get() {
            static Machine instance;
            return instance;
        }

        void SetInitialState(State* newState) {
            if (m_CurrentState != nullptr) {
                return;
            }

            m_CurrentState = newState;
            m_CurrentState->OnEnter();
        }

        void ChangeState(State* newState) {
            m_CurrentState->OnExit();
            m_CurrentState = newState;
            m_CurrentState->OnEnter();
        }

    private:
        State* m_CurrentState = nullptr;

        Machine() {}
        
    };

}
