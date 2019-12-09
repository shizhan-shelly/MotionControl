// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/widgets/extendedio/ExtendedBoardModel.h"

ExtendedBoardModel::ExtendedBoardModel(QObject *parent)
    : QAbstractTableModel(parent) {}

ExtendedBoardModel::~ExtendedBoardModel() {}

void ExtendedBoardModel::initialExtendedBoard(const QVector<BoardItem> &initial) {
  beginResetModel();
  board_items_ = initial;
  endResetModel();
}

QVector<BoardItem> ExtendedBoardModel::GetExtendedBoard() const {
  return board_items_;
}

int ExtendedBoardModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return board_items_.count();
}

int ExtendedBoardModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 3;
}

Qt::ItemFlags ExtendedBoardModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return Qt::ItemIsEnabled;
  }
  if (index.column() == 0) {
    return QAbstractItemModel::flags(index);
  }
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant ExtendedBoardModel::data(const QModelIndex &index, int role) const {
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
    if (column == 0) {
      return board_items_[row].group_;
    } else if (column == 1) {
      return board_items_[row].model_;
    } else if (column == 2) {
      return board_items_[row].addr_;
    } else {
      return QVariant();
    }
   case Qt::BackgroundRole:
    return QVariant();
   case Qt::TextAlignmentRole:
    return QVariant(Qt::AlignCenter);
   default:
    return QVariant();
  }
}

QVariant ExtendedBoardModel::headerData(int section, Qt::Orientation orientation,
                                        int role) const {

  if (role != Qt::DisplayRole) {
    return QVariant();
  }
  if (orientation == Qt::Horizontal) {
    switch (section) {
     case 0:
      return QObject::tr("Extended Board Group");
     case 1:
      return QObject::tr("Extended Board Model");
     case 2:
      return QObject::tr("Extended Board Address");
     default:
      return QVariant();
    }
  } else {
    return QVariant();
  }
}

bool ExtendedBoardModel::setData(const QModelIndex &index, const QVariant &value,
                                 int role) {

  if (index.isValid() && role == Qt::EditRole) {
    int row = index.row();
    int column = index.column();
    QString get = value.toString();
    if (column == 0) {
      board_items_[row].group_ = get.toInt();
    } else if (column == 1) {
      board_items_[row].model_ = get;
    } else if (column == 2) {
      board_items_[row].addr_ = get;
    } else {
      return false;
    }
    emit dataChanged(index, index);
    return true;
  }
  return false;
}
