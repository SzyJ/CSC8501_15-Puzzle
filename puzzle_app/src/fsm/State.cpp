#include "fsm/State.h"
#include "fsm/Machine.h"

namespace fsm {

    void State::GoTo(State* state) {
        Machine::Get().ChangeState(state);
    }

}
