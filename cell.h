#ifndef CELL_H
#define CELL_H

class Cell
{
    int m_row;
    int m_column;
    int m_value;
public:
    Cell(int row, int column, int value);

    int getColumn() const;
    void setColumn(int value);

    int getValue() const;
    void setValue(int value);

    int getRow() const;
    void setRow(int value);

    ~Cell();
};

#endif // CELL_H
