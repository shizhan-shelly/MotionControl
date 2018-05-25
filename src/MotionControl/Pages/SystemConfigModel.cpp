// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../Pages/SystemConfigModel.h"

#include <assert.h>

#include "../Pages/SystemConfigItem.h"

SystemConfigModel::SystemConfigModel(QObject *parent)
    : QAbstractTableModel(parent) {}

SystemConfigModel::~SystemConfigModel() {}

int SystemConfigModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return system_config_items_.count();
}

int SystemConfigModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 7;
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
  if (row < 0 || row >= rowCount() || column < 0 || column >= columnCount()) {
    return QVariant();
  }
  switch (role) {
   case Qt::DisplayRole:
   case Qt::EditRole:
    return QString(system_config_items_[row]->GetItemElement(column).c_str());
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
    switch (section) {
     case 0:
      return QString("Cut Chart ID");
     case 1:
      return QString("Plasma Power Vendor");
     case 2:
      return QString("Plasma Power Model");
     case 3:
      return QString("Gas Box Model");
     case 4:
      return QString("Torch Model");
     case 5:
      return QString("Version");
     case 6:
      return QString("Selected Record");
     default:
      return QVariant();
    }
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

void SystemConfigModel::insertRecord(int row, SystemConfigItem *record) {
  assert(row >= 0 && row <= system_config_items_.size());
  beginInsertRows(QModelIndex(), row, row);
  system_config_items_.insert(row, record);
  endInsertRows();
}

void SystemConfigModel::clear() {
  if (!system_config_items_.empty()) {
    int count = rowCount();
    beginRemoveRows(QModelIndex(), 0, count - 1);
    for (int i = 0; i < count; i++) {
      SystemConfigItem *remove_item = system_config_items_[i];
      if (remove_item) {
        delete remove_item;
        remove_item = NULL;
      }
    }
    system_config_items_.clear();
    endRemoveRows();
  }
}
