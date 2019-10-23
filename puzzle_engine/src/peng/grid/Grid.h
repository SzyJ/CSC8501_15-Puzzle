// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: Tiles.h
// Date: 18/10/2019

#pragma once
#include <type_traits>
#include <vector>
#include <ostream>

#define PENG_POS(x, y) (x + (y * m_Size))

namespace Peng {

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class Grid {
    public:
        Grid() = default;
        Grid(const Grid& copy) = delete;

        Grid(int size)
            : m_Size(size), m_SeqLength(size) { }
        ~Grid() {
            delete[] m_TileState;
        }

        void SetSize(int size) {
            m_Size = size;
            m_SeqLength = size;
        }

        void SetTiles(T* tiles, int size) {
            m_Size = size;
            m_SeqLength = size;
            const unsigned int tileCount = (m_Size * m_Size) - 1;
            T* newArray = new T[tileCount];

            std::memcpy(newArray, tiles, tileCount * sizeof(T));
            m_TileState = newArray;
        }

        T GetValue(unsigned int xIndex, unsigned int yIndex) {
            return m_TileState[PENG_POS(xIndex, yIndex)];
        }

        int GetSize() const {
            return m_Size;
        }

        template <typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
        friend std::ostream& operator<<(std::ostream&, Grid<U>&);

    private:
        unsigned int m_Size = 0, m_SeqLength= 0;

        T* m_TileState = nullptr;
        std::vector<T*> m_Subsequences;

    };

    template <typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
    std::ostream& operator<<(std::ostream& ostream, Grid<U>& grid) {
        for (unsigned int col = 0; col < grid.m_Size; ++col) {
            for (unsigned int row = 0; row < grid.m_Size; ++row) {
                if (row == grid.m_Size - 1 && col == grid.m_Size - 1) {
                    break;
                }
                ostream << grid.GetValue(row, col);

                if (row != grid.m_Size - 1) {
                    ostream << '\t';
                }
            }
            ostream << std::endl;
        }

        return ostream;
    }

}
