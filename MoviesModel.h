#pragma once
#include "C:\Qt\6.9.0\msvc2022_64\include\QtCore\qabstractitemmodel.h"
#include <service.h>
class MoviesModel :
    public QAbstractTableModel
{
private:
    Service& serv;
    
public:
    MoviesModel(Service& service, QObject* parent = nullptr);
	void refreshModel() {
		beginResetModel();
		endResetModel();
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
};

