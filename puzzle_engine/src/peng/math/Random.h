// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: Random.h
// Date: 22/10/2019

#pragma once

#include <unordered_set>

namespace Peng {

    class Random {
    public:
        Random();
        ~Random();

        static int GetInt(int min, int max);
        static int GetInt(int max) { return GetInt(0, max); }

    private:


    };

    class RandomSession {
    public:
        RandomSession() = delete;

        RandomSession(int numbersFrom, int numbersTo)
            : m_NumbersFrom(numbersFrom), m_NumbersTo(numbersTo) {
            for (int possibleNumber = numbersFrom; possibleNumber < numbersTo; ++possibleNumber) {
                m_RemainingNumbers.insert(possibleNumber);
            }
        }

        ~RandomSession();

        int GetNew(bool& success);
        int GetNew();

    private:
        int m_NumbersFrom, m_NumbersTo;
        std::unordered_set<int> m_RemainingNumbers;

    };

}
