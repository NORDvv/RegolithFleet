#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "types/GridTypes.hpp"
#include "types/Position.hpp"

namespace rf
{
    class Map
    {
    public:
        Map() = default;
        Map(int rows, int cols);

        bool IsInside(const Position& pos) const;
        bool IsTraversable(const Position& pos) const;

        CellType GetCell(const Position& pos) const;
        void SetCell(const Position& pos, CellType type);

        int Rows() const;
        int Cols() const;

        std::vector<Position> GetAllTargets() const;
        std::vector<Position> GetDepotCells() const;

    private:
        int rows_ {0};
        int cols_ {0};
        std::vector<std::vector<CellType>> grid_;
    };
}  // namespace rf

#endif