#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include "irecursivecurve.h"

#include <QAbstractListModel>
#include <QModelIndex>

class ComboBoxModel : public QAbstractListModel
{
public:
    explicit ComboBoxModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    // представление модели в виде списка пар элементов
    QList<QPair<QString, IRecursiveCurve*>> *values;
};

#endif // COMBOBOXMODEL_H
