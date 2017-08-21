#ifndef GAMEUTILITY_H
#define GAMEUTILITY_H

#include <QList>

#include <memory>

#include "cell.h"

class GameUtility
{
public:
    GameUtility();

    void generateMap();
    void shuffleCellsCollection();

    std::shared_ptr<Cell> getCellByIndex(int index) const;
    void swapCells(int fromPosition, int toPosition);

    int checkNeighbours(int currentCellIndex) const;
    bool isUserWin() const;

    int getMapSettings() const;
    int getCellsCollectionSize() const;

    ~GameUtility();
private:
    QList<std::shared_ptr<Cell>> m_cells;

    const int m_mapSize = 4;

    bool checkCellIndex(int index) const;

    bool isTaskSolve() const;
};

#endif // GAMEUTILITY_H
