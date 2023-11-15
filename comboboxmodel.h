#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include "irecursivecurve.h"

#include <QAbstractListModel>
#include <QModelIndex>

class ComboBoxModel : public QAbstractListModel
{
public:
    explicit ComboBoxModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &) const;
    // вернуть элемент модели (определенную кривую)
    IRecursiveCurve *curve(const QModelIndex &index) const;

private:
    // представление модели в виде списка пар элементов
    QList<QPair<QString, IRecursiveCurve*>> *values;
};

#endif // COMBOBOXMODEL_H
