#include "gamemodel.h"

GameModel::GameModel(QObject *parent):
    QAbstractListModel(parent)
{
    m_utility = std::shared_ptr<GameUtility> (new GameUtility());
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_utility->getCellsSize();
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int elementIndex = static_cast<int>(index.row());

    auto currentCell = m_utility->getCellByIndex(elementIndex);

    switch (role) {
    case Row:
        return currentCell->getRow();
    case Column:
        return currentCell->getColumn();
    case Value:
        return currentCell->getValue();
    }

    return QVariant();
}

QHash<int, QByteArray> GameModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Row] = "row";
    roles[Column] = "column";
    roles[Value] = "value";

    return roles;
}

void GameModel::shuffleCells()
{
    beginResetModel();
    m_utility->shuffleCells();
    endResetModel();
}

void GameModel::checkNeighbours(int index)
{
    int newIndex = m_utility->checkNeighbours(index);

    if (newIndex < 0) {
        return;
    }

    swapItem(index, newIndex);

    if (m_utility->isUserWin()) {
        emit userWon();
    }
}

void GameModel::swapItem(int from, int to)
{
    int max = std::max(from, to);
    int min = std::min(from, to);


    beginMoveRows(QModelIndex(), max, max, QModelIndex(), min);
    m_utility->swapCells(from, to);
    endMoveRows();

    if (max - min > 1) {
        beginMoveRows(QModelIndex(), min + 1, min + 1, QModelIndex(), max + 1);
        endMoveRows();
    }
}

int GameModel::getFieldSize() const
{
    return m_utility->getMapSetting();
}

GameModel::~GameModel()
{

}
