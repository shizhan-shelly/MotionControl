// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "KerfTableModel.h"

KerfTableModel::KerfTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

KerfTableModel::~KerfTableModel() {}

int KerfTableModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return kerf_variable_value_.count();
}

int KerfTableModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 2;
}

Qt::ItemFlags KerfTableModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return Qt::ItemIsEnabled;
  }
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant KerfTableModel::data(const QModelIndex &index, int role) const {
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
    return column == 0 ? row + 1 : kerf_variable_value_[row + 1];
   case Qt::BackgroundRole:
    return QVariant();
   case Qt::TextAlignmentRole:
    return QVariant(Qt::AlignCenter);
   default:
    return QVariant();
  }
}

QVariant KerfTableModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {

  if (role != Qt::DisplayRole) {
    return QVariant();
  }
  if (orientation == Qt::Horizontal) {
    switch (section) {
     case 0:
      return QString("Kerf Variable");
     case 1:
      return QString("Kerf Value");
     default:
      return QVariant();
    }
  } else {
    return QVariant();
  }
}

bool KerfTableModel::setData(const QModelIndex &index, const QVariant &value,
                             int role) {

  if (index.isValid() && role == Qt::EditRole) {
    emit dataChanged(index, index);
    return true;
  }
  return false;
}
