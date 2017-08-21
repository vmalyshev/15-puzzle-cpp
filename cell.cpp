#include "cell.h"

Cell::Cell(int row, int column, int value):
    m_row(row),
    m_column(column),
    m_value(value) { }

int Cell::getColumn() const
{
    return m_column;
}

void Cell::setColumn(int value)
{
    m_column = value;
}

int Cell::getValue() const
{
    return m_value;
}

void Cell::setValue(int value)
{
    m_value = value;
}

int Cell::getRow() const
{
    return m_row;
}

void Cell::setRow(int value)
{
    m_row = value;
}

Cell::~Cell()
{

}
