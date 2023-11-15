#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include <QAbstractListModel>

class comboBoxModel : public QAbstractListModel
{
public:
    explicit comboBoxModel(QObject *parent = nullptr);
};

#endif // COMBOBOXMODEL_H
