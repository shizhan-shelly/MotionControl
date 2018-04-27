// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SystemConfigModel.h"

SystemConfigModel::SystemConfigModel(QObject *parent)
    : QAbstractTableModel(parent) {}

SystemConfigModel::~SystemConfigModel() {}

int SystemConfigModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 1;
}

int SystemConfigModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 2;
}

Qt::ItemFlags SystemConfigModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return Qt::ItemIsEnabled;
  }
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant SystemConfigModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }
  int row = index.row();
  int column = index.column();
  if (row < 0 || row >= 1 || column < 0 || column >= 2) {
    return QVariant();
  }
  switch (role) {
   case Qt::DisplayRole:
   case Qt::EditRole:
    return 100;
   case Qt::BackgroundRole:
    return QVariant();
   case Qt::TextAlignmentRole:
    return QVariant(Qt::AlignCenter);
   default:
    return QVariant();
  }
}

QVariant SystemConfigModel::headerData(int section,
                                       Qt::Orientation orientation,
                                       int role) const {

  if (role != Qt::DisplayRole) {
    return QVariant();
  }
  if (orientation == Qt::Horizontal) {
    return QString("database");
  } else {
    return QString("%1").arg(section + 1);
  }
}

bool SystemConfigModel::setData(const QModelIndex &index,
                                const QVariant &value,
                                int role) {

  if (index.isValid() && role == Qt::EditRole) {
    emit dataChanged(index, index);
    return true;
  }
  return false;
}
