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
        int nextIndex = Random::GetInt(m_RemainingNumbers.size());

        auto it = m_RemainingNumbers.begin();
        for (int i = 0; i < nextIndex; ++nextIndex, ++it) {}

        auto test = m_RemainingNumbers.extract(it);

        return test.value();
    }


}
