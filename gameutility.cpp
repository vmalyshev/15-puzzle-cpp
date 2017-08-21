#include "gameutility.h"

#include <random>
#include <algorithm>

GameUtility::GameUtility()
{
    generateMap();
}

void GameUtility::generateMap()
{
    m_cells.reserve(m_mapSize * m_mapSize);

    for (int row = 0; row < m_mapSize; row++) {
        for (int column = 0; column < m_mapSize; column++) {
            m_cells.push_back(std::shared_ptr<Cell> (new Cell(row, column, row*m_mapSize + column)));
        }
    }

    shuffleCellsCollection();
}

void GameUtility::shuffleCellsCollection()
{
    auto rndEngine = std::default_random_engine { };

    do {
        std::shuffle(std::begin(m_cells), std::end(m_cells), rndEngine);
    } while (isTaskSolve());
}

std::shared_ptr<Cell> GameUtility::getCellByIndex(int index) const
{
    return m_cells.at(index);
}

void GameUtility::swapCells(int fromPosition, int toPosition)
{
    m_cells.swap(fromPosition, toPosition);
}

int GameUtility::checkNeighbours(int currentCellIndex) const
{
    if (checkCellIndex(currentCellIndex))
        return -1;

    int currentCellRow = currentCellIndex / m_mapSize;
    int currentCellColumn = currentCellIndex % m_mapSize;

    int leftIndex = currentCellIndex - 1;
    int leftRow = leftIndex / m_mapSize;
    if (leftRow == currentCellRow && checkCellIndex(leftIndex)) {
        return leftIndex;
    }

    int rightIndex = currentCellIndex + 1;
    int rightRow = rightIndex / m_mapSize;
    if (rightRow == currentCellRow && checkCellIndex(rightIndex)) {
        return rightIndex;
    }

    int upIndex = currentCellIndex - m_mapSize;
    int upColumn = upIndex % m_mapSize;
    if (currentCellColumn == upColumn && checkCellIndex(upIndex)) {
        return upIndex;
    }

    int downIndex = currentCellIndex + m_mapSize;
    int downColumn = downIndex % m_mapSize;
    if (currentCellColumn == downColumn && checkCellIndex(downIndex)) {
        return downIndex;
    }

    return -1;
}

bool GameUtility::isUserWin() const
{
    for (int i = 0; i < m_cells.size() - 1; i++) {
        if (m_cells.at(i)->getValue() != i + 1) {
            return false;
        }
    }
    return true;
}

int GameUtility::getMapSettings() const
{
    return m_mapSize;
}

int GameUtility::getCellsCollectionSize() const
{
    return m_cells.size();
}

GameUtility::~GameUtility()
{

}

bool GameUtility::checkCellIndex(int index) const
{
    if (index >= 0 && index < m_cells.size()) {
        return getCellByIndex(index)->getValue() == 0;
    }
    return false;
}

bool GameUtility::isTaskSolve() const
{
    int sum = 0;
    int zeroValueItemPosition;
    for (int i = 0; i < m_cells.size(); i++) {
        if (checkCellIndex(i)) {
            zeroValueItemPosition = i;
            continue;
        }

        for (int j = i; j < m_cells.size(); j++) {
            if ((getCellByIndex(i) < getCellByIndex(j)) && getCellByIndex(j)->getValue() != 0) {
                sum += 1;
            }
        }
    }

    int rowWithZeroValue = zeroValueItemPosition / 2 + 1;
    bool result = ((sum + rowWithZeroValue) % 2 == 0);
    return result;
}
