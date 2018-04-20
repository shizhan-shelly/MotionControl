// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include <QtCore/QAbstractTableModel.h>

class SystemConfigModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit SystemConfigModel(QObject *parent = NULL);
  ~SystemConfigModel();

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  // The dataChanged() signal should be emitted if the data was successfully set.
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

}; // class SystemConfigModel
