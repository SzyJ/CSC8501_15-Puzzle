// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: Sequence.h
// Date: 23/10/2019

#pragma once
#include <type_traits>

namespace Peng {

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    struct Sequence {

        Sequence(T* sequenceArray, unsigned int sequenceLength)
            : m_SequenceArray(sequenceArray), m_SequenceLength(sequenceLength) { }

        T* m_SequenceArray;
        unsigned int m_SequenceLength;

    };

}
