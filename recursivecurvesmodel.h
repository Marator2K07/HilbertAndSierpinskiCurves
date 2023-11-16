#ifndef RECURSIVECURVESMODEL_H
#define RECURSIVECURVESMODEL_H

#include "irecursivecurve.h"

#include <QAbstractListModel>
#include <QModelIndex>

class RecursiveCurvesModel : public QAbstractListModel
{
public:
    explicit RecursiveCurvesModel(QObject *parent = nullptr);
    void append(QString key, IRecursiveCurve *value);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    // представление модели в виде списка пар элементов
    QList<QPair<QString, IRecursiveCurve*>> *values;
};

#endif // RECURSIVECURVESMODEL_H
