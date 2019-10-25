// Author: Szymon Jackiewicz
// 
// Project: puzzle_app
// File: State.h
// Date: 25/10/2019

#pragma once

namespace fsm {

    class Machine;

    class State {
        friend class Machine;
    public:

        virtual ~State() = default;

    protected:
        State() {}

        virtual void OnEnter() = 0;

        virtual void OnExit() {};

    };
}
