// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: Tiles.h
// Date: 18/10/2019

#pragma once
#include <type_traits>
#include <vector>

#define PENG_POS(x, y) (x + (y * m_Size))

namespace Peng {

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class Grid {
    public:
        Grid() = default;
        Grid(int size)
            : m_Size(size), m_SeqLength(size) { }


        void SetSize(int size) {
            m_Size = size;
            m_SeqLength = size;
        }

        void SetTiles(const T* tiles, int size) {
            m_Size = size;
            m_SeqLength = size;
            const unsigned int tileCount = (m_Size * m_Size) - 1;
            auto* newArray = new T[tileCount];

            std::memcpy(newArray, tiles, tileCount * sizeof(T));
            m_TileState = newArray;
        }

        const T* GetValue(unsigned int xIndex, unsigned int yIndex) {
            return &m_TileState[PENG_POS(xIndex, yIndex)];
        }

    private:
        unsigned int m_Size = 0, m_SeqLength= 0;

        T* m_TileState;
        std::vector<T*> m_Subsequences;

    };

}
