// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "KerfTableModel.h"

#include <math.h>

KerfTableModel::KerfTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

KerfTableModel::~KerfTableModel() {}

void KerfTableModel::initialKerfTableValue(const QVector<double> &initial) {
  kerf_variable_value_ = initial;
}

QVector<double> KerfTableModel::GetKerfTableValue() const {
  return kerf_variable_value_;
}

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
  if (index.column() == 0) {
    return QAbstractItemModel::flags(index);
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
    return column == 0 ? row : correctKerfValue(row);
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
      return tr("Kerf Variable");
     case 1:
      return tr("Kerf Value(mm)");
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
    int row = index.row();
    bool ok = true;
    double get = value.toDouble(&ok);
    if (ok) {
      kerf_variable_value_[row] = fabs(get);
      emit dataChanged(index, index);
    }
    return ok;
  }
  return false;
}

double KerfTableModel::correctKerfValue(int index) const {
  if (index >= rowCount()) {
    return 0.0;
  }
  static double MAX_KERF_VALUE = 20;
  if (kerf_variable_value_[index] > MAX_KERF_VALUE) {
    return MAX_KERF_VALUE;
  }
  return fabs(kerf_variable_value_[index]);
}
