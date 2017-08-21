#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractListModel>
#include <memory.h>

#include <gameutility.h>

class GameModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int fieldSize READ getFieldSize CONSTANT)
public:
    explicit GameModel(QObject *parent = 0);

    enum Roles {
        Row = Qt::UserRole + 1,
        Column,
        Value
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void shuffleCells();
    Q_INVOKABLE void checkNeighbours(int index);

    int getFieldSize() const;

    ~GameModel();
private:
    void swapItem(int from, int to);

    std::shared_ptr<GameUtility> m_utility;
signals:
    void userWon();
};

#endif // GAMEMODEL_H
