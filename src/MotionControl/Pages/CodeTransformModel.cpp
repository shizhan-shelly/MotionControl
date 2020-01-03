// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "../Pages/CodeTransformModel.h"

#include <assert.h>

#include "../database/codetransform/TransDBAccess.h"

static const std::string COLUMN_FIELD[] = {
  "ID",
  "TRANS_BEFORE",
  "TRANS_AFTER",
  "COMMENTS",

};

static const int ITEMS_NUM = 4;

CodeTransformModel::CodeTransformModel(QObject *parent)
    : QAbstractTableModel(parent) {}

CodeTransformModel::~CodeTransformModel() {}

bool CodeTransformModel::initial() {
  beginResetModel();
  TransDBAccess db;
  db_items_ = db.QueryAll("ECKELMANN");
  endResetModel();
  return true;
}

bool CodeTransformModel::save() {
  TransDBAccess db;
  return db.ReplaceAll(db_items_, "ECKELMANN");
}

bool CodeTransformModel::removeRows(int row, int count,
    const QModelIndex &parent) {

  assert(row >= 0 && count >= 0 && row + count <= rowCount());
  beginRemoveRows(parent, row, row + count - 1);

  for (int i = 0; i < count; ++i) {
    db_items_.removeAt(row);
  }

  endRemoveRows();
  return true;
}

bool CodeTransformModel::insertRow(int row, const QModelIndex &parent) {
  assert(row >= 0 && row <= rowCount());
  beginInsertRows(parent, row, row);
  std::map<std::string, std::string> insert_item;
  for (int i = 0; i < ITEMS_NUM; i++) {
    insert_item.insert(std::make_pair(COLUMN_FIELD[i], ""));
  }
  db_items_.insert(db_items_.begin() + row, insert_item);
  endInsertRows();
  return true;
}

int CodeTransformModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return db_items_.count();
}

int CodeTransformModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return ITEMS_NUM;
}

Qt::ItemFlags CodeTransformModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return Qt::ItemIsEnabled;
  }
  if (index.column() == 0) {
    return QAbstractItemModel::flags(index);
  }
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant CodeTransformModel::data(const QModelIndex &index, int role) const {
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
    return GetItemValue(index);
   case Qt::BackgroundRole:
    return QVariant();
   case Qt::TextAlignmentRole:
    return QVariant(Qt::AlignCenter);
   default:
    return QVariant();
  }
}

QVariant CodeTransformModel::headerData(int section,
    Qt::Orientation orientation,
    int role) const {

  if (role != Qt::DisplayRole) {
    return QVariant();
  }
  if (orientation == Qt::Horizontal) {
    switch (section) {
     case 0:
      return QObject::tr("ID");
     case 1:
      return QObject::tr("Transform Before");
     case 2:
      return QObject::tr("Transform After");
     case 3:
      return QObject::tr("Comments");
     default:
      return QVariant();
    }
  }
  return QVariant();
}

bool CodeTransformModel::setData(const QModelIndex &index, const QVariant &value,
    int role) {

  if (index.isValid() && role == Qt::EditRole) {
    SetItemValue(index, value.toString());
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

QString CodeTransformModel::GetItemValue(const QModelIndex &index) const {
  int row = index.row();
  int column = index.column();
  std::map<std::string, std::string>::const_iterator it =
      db_items_[row].find(COLUMN_FIELD[column]);

  return it != db_items_[row].end() ? it->second.c_str() : "";
}

void CodeTransformModel::SetItemValue(const QModelIndex &index, const QString &value) {
  int row = index.row();
  int column = index.column();
  if (row >= 0 && row < rowCount() && column > 0 && column < columnCount()) {
    std::map<std::string, std::string>::iterator it =
        db_items_[row].find(COLUMN_FIELD[column]);

    it->second = value.toStdString();
  }
}
