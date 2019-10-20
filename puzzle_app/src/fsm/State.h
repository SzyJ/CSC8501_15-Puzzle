#pragma once

namespace fsm {

    class Machine;
    class State {
        friend class Machine;
    public:
        
        virtual ~State() = default;

    protected:
        State() {}

        void GoTo(State* state);

        virtual void OnEnter() {};
        virtual void OnExit() {};

    };
}