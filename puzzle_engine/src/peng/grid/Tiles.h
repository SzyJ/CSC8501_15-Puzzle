// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: Tiles.h
// Date: 18/10/2019

#pragma once
#include <type_traits>
#include <vector>

namespace Peng {

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class Tiles {
    public:
        Tiles() = default;
        Tiles(int size)
            : m_Size(size), m_SeqLength(size) { }


        void SetSize(int size) {
            m_Size = size;
            m_SeqLength = size;
        }

        void SetTiles(const T* tiles) {
            m_TileState = tiles;
        }

    private:
        int m_Size = 0, m_SeqLength= 0;

        T* m_TileState;
        std::vector<T*> m_Subsequences;

    };

}
