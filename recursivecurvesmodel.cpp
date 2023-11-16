#include "recursivecurvesmodel.h"

RecursiveCurvesModel::RecursiveCurvesModel(QObject *parent)
    : QAbstractListModel{parent}
{
    values = new QList<QPair<QString, IRecursiveCurve*>>();
}

void RecursiveCurvesModel::append(QString key, IRecursiveCurve *value)
{
    int newRowIndex = this->values->count()+1;
    // прежде чем добавить элемент нужно вызвать beginInsertRows
    // и при окончании добавления - соотвественно вызывать endInsertRows
    this->beginInsertRows(QModelIndex(), newRowIndex, newRowIndex);
        values->append(QPair<QString, IRecursiveCurve*>(key, value));
    endInsertRows();
}

int RecursiveCurvesModel::rowCount(const QModelIndex &) const
{
    return values->count();
}

QVariant RecursiveCurvesModel::data(const QModelIndex &index, int role) const
{
    QVariant value;

    switch (role) {
    case Qt::DisplayRole: //string
        value = this->values->value(index.row()).first;
        break;
    case Qt::UserRole: //data
        value = QVariant::fromValue(this->values->value(index.row()).second);
        break;
    default:

        break;
    }

    return value;
}
