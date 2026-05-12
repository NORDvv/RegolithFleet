#ifndef POSITION_HPP
#define POSITION_HPP

#include <cstddef>

namespace rf
{
    struct Position
    {
        int row {0};
        int col {0};

        bool operator==(const Position& other) const
        {
            return row == other.row && col == other.col;
        }

        bool operator!=(const Position& other) const
        {
            return !(*this == other);
        }
    };
}  // namespace rf

#endif