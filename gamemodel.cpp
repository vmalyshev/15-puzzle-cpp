#include "gamemodel.h"

GameModel::GameModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_utility = std::shared_ptr<GameUtility> (new GameUtility());
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_utility->getCellsCollectionSize();
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
    m_utility->shuffleCellsCollection();
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

int GameModel::getGameFieldSize() const
{
    return m_utility->getMapSettings();
}

GameModel::~GameModel()
{

}

void GameModel::swapItem(int fromPosition, int toPosition)
{
    int rowStartObject = fromPosition / getGameFieldSize();
    int columnStartObject = fromPosition % getGameFieldSize();

    int rowFinishObject = toPosition / getGameFieldSize();
    int columnFinishObject = toPosition % getGameFieldSize();

    if (rowStartObject == rowFinishObject) {
        if (toPosition > fromPosition) {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition+1);
        } else {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition);
        }
        m_utility->swapCells(fromPosition, toPosition);
        endMoveRows();
    }

    if (columnStartObject == columnFinishObject) {
        if(toPosition > fromPosition) {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition + 1);
            m_utility->swapCells(fromPosition, toPosition);
            endMoveRows();

            beginMoveRows(QModelIndex(), toPosition - 1, toPosition - 1, QModelIndex(), fromPosition);
            endMoveRows();
        } else {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition);
            m_utility->swapCells(fromPosition, toPosition);
            endMoveRows();

            beginMoveRows(QModelIndex(), toPosition + 1, toPosition + 1, QModelIndex(), fromPosition + 1);
            endMoveRows();
        }
    }
}
