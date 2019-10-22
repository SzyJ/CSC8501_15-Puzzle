// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: Random.cpp
// Date: 22/10/2019

#include "Random.h"

#include <cstdlib>

namespace Peng {
    int Random::GetInt(int min, int max) {
        return min + (rand() % (max - min));
    }

    int RandomSession::GetNew(bool& success) {
        if (m_RemainingNumbers.empty()) {
            success = false;
            return 0;
        }

        success = true;

        return GetNew();
    }

    int RandomSession::GetNew() {
        int nextIndex = Random::GetInt(static_cast<int>(m_RemainingNumbers.size()));

        auto it = m_RemainingNumbers.begin();

        std::advance(it, nextIndex);

        auto test = m_RemainingNumbers.extract(it);

        return test.value();
    }


}
