#include "comboboxmodel.h"

ComboBoxModel::ComboBoxModel(QObject *parent)
    : QAbstractListModel{parent}
{
    values = new QList<QPair<QString, IRecursiveCurve*>>();
}

int ComboBoxModel::rowCount(const QModelIndex &) const
{
    return values->count();
}

IRecursiveCurve *ComboBoxModel::curve(const QModelIndex &index) const
{
    IRecursiveCurve *curve;
    curve = this->values->value(index.row()).second;
    return curve;
}
