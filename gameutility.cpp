#include "gameutility.h"

#include <algorithm>
#include <random>

#include <QDebug>

int GameUtility::getMapSetting() const
{
    return m_mapSize;
}

bool GameUtility::checkIndex(int index)
{
    if (index >= 0 && index < m_mapItemsSize) {
        return getCellByIndex(index)->getValue() == 0;
    }
    return false;
}

std::shared_ptr<Cell> GameUtility::getCellByIndex(int index)
{
    return m_cells.at(index);
}

void GameUtility::swapCells(int from, int to)
{
    m_cells.swap(from, to);
}

int GameUtility::checkNeighbours(int index)
{
    if (checkIndex(index))
        return -1;

    int currentCellRow = index / m_mapSize;
    int currentCellColumn = index % m_mapSize;

    int leftIndex = index - 1;
    int leftRow = leftIndex / m_mapSize;
    if (leftRow == currentCellRow && checkIndex(leftIndex)) {
        return leftIndex;
    }

    int rightIndex = index + 1;
    int rightRow = rightIndex / m_mapSize;
    if (rightRow == currentCellRow && checkIndex(rightIndex)) {
        return rightIndex;
    }

    int upIndex = index - m_mapSize;
    int upColumn = upIndex % m_mapSize;
    if (currentCellColumn == upColumn && checkIndex(upIndex)) {
        return upIndex;
    }

    int downIndex = index + m_mapSize;
    int downColumn = downIndex % m_mapSize;
    if (currentCellColumn == downColumn && checkIndex(downIndex)) {
        return downIndex;
    }

    return -1;
}

bool GameUtility::isUserWin()
{
    for (int i = 0; i < m_mapItemsSize - 1; i++) {
        if (m_cells.at(i)->getValue() != i + 1) {
            return false;
        }
    }
    return true;
}

bool GameUtility::isTaskSolve()
{
    int sum = 0;
    int zeroValueItemPosition;
    for (int i = 0; i < m_mapItemsSize; i++) {
        if (checkIndex(i)) {
            zeroValueItemPosition = i;
            continue;
        }

        for (int j = i; j < m_mapItemsSize; j++) {
            if ((getCellByIndex(i) < getCellByIndex(j)) && getCellByIndex(j)->getValue() != 0) {
                sum += 1;
            }
        }
    }

    int rowWithZeroValue = zeroValueItemPosition / 2 + 1;
    bool result = ((sum + rowWithZeroValue) % 2 == 0);
    return result;
}

void GameUtility::shuffleCells()
{
    auto rnd = std::default_random_engine { };

    do {
        std::shuffle(std::begin(m_cells), std::end(m_cells), rnd);
    } while (isTaskSolve());
}

GameUtility::GameUtility()
{
    generateMap();
}

void GameUtility::generateMap()
{
    m_cells.reserve(m_mapItemsSize);

    for (int row = 0; row < m_mapSize; row++) {
        for (int column = 0; column < m_mapSize; column++) {
            m_cells.push_back(std::shared_ptr<Cell> (new Cell(row, column, row*m_mapSize + column)));
        }
    }

    shuffleCells();
}

int GameUtility::getCellsSize()
{
    return m_cells.size();
}

GameUtility::~GameUtility()
{

}

