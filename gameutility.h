#ifndef GAMEUTILITY_H
#define GAMEUTILITY_H

#include <QList>
#include <memory>

#include "cell.h"

typedef QList<std::shared_ptr<Cell>> cellsCollection;

class GameUtility
{
    cellsCollection m_cells;

    const int m_mapSize = 4;

    const int m_mapItemsSize = m_mapSize * m_mapSize;

    bool checkIndex(int index);

    bool isTaskSolve();
public:
    GameUtility();

    void shuffleCells();

    void generateMap();

    int getCellsSize();

    int getMapSetting() const;

    std::shared_ptr<Cell> getCellByIndex(int index);

    void swapCells(int from, int to);

    int checkNeighbours(int index);

    bool isUserWin();

    ~GameUtility();
};

#endif // GAMEUTILITY_H
