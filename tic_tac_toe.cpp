#include "tic_tac_toe.h"
#include <limits>
#include <iostream>

// We're in a cpp file and I'm not worried about any
// name collisions.
using namespace tic_tac_toe;

namespace
{
    bool same(char a, char b, char c)
    {
        return a == b && b == c;
    }

    bool between(int value, int low, int high)
    {
        return (value >= low) && (value <= high);
    }
}

bool Grid::hasWinner() const
{
    return checkRows()
        || checkColumns()
        || checkDiagonals();
}

bool Grid::isTie() const
{
    return (!hasWinner()) && (filled >= 9);
}

bool Grid::setTile(bool isX, int tileNumber)
{
    if (!between(tileNumber, 1, 9)) {
        return false;
    }

    --tileNumber;
    int row = tileNumber / ROWS;
    int column = tileNumber % COLUMNS;

    if (isFreeCell(row, column)) {
        cells[row][column] = isX ? 'X' : 'O';
        ++filled;
        return true;
    }

    return false;
}

std::ostream& Grid::printRow(std::ostream& os, int index) const
{
    for (auto&& cell : cells[index]) {
        os << '[' << cell << ']';
    }

    return os;
}

bool Grid::checkRows() const
{
    return checkRow(0)
        || checkRow(1)
        || checkRow(2);
}

bool Grid::checkColumns() const
{
    return checkColumn(0)
        || checkColumn(1)
        || checkColumn(2);
}

bool Grid::checkDiagonals() const
{
    bool d1 = same(cells[0][0],
                   cells[1][1],
                   cells[2][2]);

    bool d2 = same(cells[0][2],
                   cells[1][1],
                   cells[2][0]);

    return d1 || d2;
}

bool Grid::checkRow(int index) const
{
    return same(cells[index][0],
                cells[index][1],
                cells[index][2]);
}

bool Grid::checkColumn(int index) const
{
    return same(cells[0][index],
                cells[1][index],
                cells[2][index]);
}

bool Grid::isFreeCell(int row, int column) const
{
    char value = cells[row][column];
    return (value != 'X') && (value != 'O');
}

std::ostream& tic_tac_toe::operator<< (std::ostream& os, const Grid& grid)
{
    grid.printRow(os, 0) << '\n';
    grid.printRow(os, 1) << '\n';
    grid.printRow(os, 2) << '\n';

    return os;
}

void Game::play(bool xStarts)
{
    bool isX = xStarts;
    while(step(isX)) {
        isX = !isX;
    }
}

bool Game::step(bool isX)
{
    std::cout << grid << '\n';
    const char player = isX ? 'X' : 'O';

    while (true) {
        int tileNumber = getTileNumber(player);
        if (grid.setTile(isX, tileNumber)) {
            break;
        }

        std::cout << "Error, tile already covered. "
                     "Please choose another tile." "\n";
    }

    if (hasWinner()) {
        std::cout << grid << '\n';
        std::cout << player << " wins!" "\n";
        return false;
    }

    else if (isTie()) {
        std::cout << grid << '\n';
        std::cout << "Draw game!" "\n";
        return false;
    }

    return true;
}

int Game::getTileNumber(char player) const
{
    while (true) {
        std::cout << "Please select a tile (1-9):\n";
        std::cout << player << " > ";
        int tileNumber = 0;
        std::cin >> tileNumber;
        if (between(tileNumber, 1, 9)) {
            return tileNumber;
        }

        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        std::cout << "Error, invalid value!" "\n";
    }
}

bool Game::hasWinner() const
{
    return grid.hasWinner();
}

bool Game::isTie() const
{
    return grid.isTie();
}
