// Author: Szymon Jackiewicz
// 
// Project: puzzle_engine
// File: Grid.h
// Date: 24/10/2019

#pragma once
#include <type_traits>
#include <vector>
#include <ostream>
#include <algorithm>

#define PENG_POS(x, y) (x + (y * m_Width))
#define PENG_ALL_TILES ((m_Width * m_Height) - 1)

namespace Peng {

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class Grid {
    public:
        Grid() = default;

        Grid(const Grid& copy) {
            SetTiles(copy.m_Tiles, copy.GetWidth(), copy.GetHeight());
        };

        ~Grid() {
            delete[] m_Tiles;
        }

        void SetTiles(T* tiles, unsigned int size) {
            SetTiles(tiles, size, size);
        }

        void SetTiles(T* tiles, unsigned int width, unsigned int height) {
            m_Width = width;
            m_Height = height;
            m_Tiles = new T[PENG_ALL_TILES];

            std::memcpy(m_Tiles, tiles, PENG_ALL_TILES * sizeof(T));

            FindSubsequences();
        }

        T GetValue(unsigned int xIndex, unsigned int yIndex) const {
            return m_Tiles[PENG_POS(xIndex, yIndex)];
        }

        unsigned int GetSubsequenceCombinations(unsigned int findSeqLen) const {
            unsigned int count = 0;

            for (unsigned int subseqLen : m_SequenceLengths) {
                if (subseqLen >= findSeqLen) {
                    count += 1 + subseqLen - findSeqLen;
                }
            }

            return count;
        }

        unsigned int GetWidth() const {
            return m_Width;
        }

        unsigned int GetHeight() const {
            return m_Height;
        }

        template <typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
        friend std::ostream& operator<<(std::ostream&, Grid<U>&);

    private:
        unsigned int m_Width = 0, m_Height = 0;

        T* m_Tiles = nullptr;

        std::vector<unsigned int> m_SequenceLengths;

        void FindSubsequences() {
            m_SequenceLengths.clear();

            T* sortedTiles = new T[PENG_ALL_TILES];
            std::memcpy(sortedTiles, m_Tiles, sizeof(T) * PENG_ALL_TILES);

            std::sort(sortedTiles, sortedTiles + PENG_ALL_TILES);

            unsigned int sequenceCounter = 1;
            int lastVal = sortedTiles[0];

            for (int ind = 1; ind < PENG_ALL_TILES; ++ind) {
                if (sortedTiles[ind] == (lastVal + 1)) {
                    ++sequenceCounter;
                }
                else {
                    m_SequenceLengths.push_back(sequenceCounter);
                    sequenceCounter = 1;
                }
                lastVal = sortedTiles[ind];
            }

            m_SequenceLengths.push_back(sequenceCounter);

            delete[] sortedTiles;
        }

    };

    template <typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
    std::ostream& operator<<(std::ostream& ostream, Grid<U>& grid) {
        for (unsigned int col = 0; col < grid.m_Height; ++col) {
            for (unsigned int row = 0; row < grid.m_Width; ++row) {
                if (col == grid.m_Height - 1 && row == grid.m_Width - 1) {
                    break;
                }
                ostream << grid.GetValue(row, col);

                if (row != grid.m_Width - 1) {
                    ostream << '\t';
                }
            }
            ostream << std::endl;
        }

        return ostream;
    }

}
