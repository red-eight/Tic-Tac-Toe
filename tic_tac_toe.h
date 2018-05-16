#ifndef MY_TIC_TAC_TOE_H
#define MY_TIC_TAC_TOE_H
#include <array>
#include <iosfwd>

namespace tic_tac_toe
{
    class Grid
    {
    public:
        static const int COLUMNS = 3;
        static const int ROWS = 3;

        bool hasWinner() const;
        bool isTie() const;
        bool setTile(bool isX, int tileNumber);
        std::ostream& printRow(std::ostream& os, int index) const;

    private:
        int filled = 0;

        std::array<std::array<char, COLUMNS>, ROWS> cells = {{
            {{'1', '2', '3'}},
            {{'4', '5', '6'}},
            {{'7', '8', '9'}},
        }};

        bool checkRows() const;
        bool checkColumns() const;
        bool checkDiagonals() const;

        bool checkRow(int index) const;
        bool checkColumn(int index) const;

        bool isFreeCell(int row, int column) const;
    };

    std::ostream& operator<< (std::ostream& os, const Grid& grid);

    class Game
    {
    public:
        void play(bool xStarts = true);
        bool step(bool isX);

    private:
        Grid grid;

        int getTileNumber(char player) const;
        bool hasWinner() const;
        bool isTie() const;
    };
}

#endif
