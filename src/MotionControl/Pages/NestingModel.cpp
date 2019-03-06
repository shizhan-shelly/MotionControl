// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "NestingModel.h"

//#include "cutter/OCutter.h"

static const std::string LIST_ITEMS[] = {
  "Diameter",
  "CuttingSpeed",
  "LeadInSpeed",
  "Kerf",
  "AsynchronousStop",

};

static const int ITEMS_NUM = 5;

NestingModel::NestingModel(QObject *parent) : QAbstractTableModel(parent) {}

NestingModel::~NestingModel() {}

bool NestingModel::initialNesting() {
  OCutter *cutter = OCutter::GetInstance();
  keyword_filed_.clear();
  cutter->GetCutChart()->GetCurrentSelectedRecord(keyword_filed_);
  diameters_ = QVector<double>::fromStdVector(
      cutter->GetNesting()->GetInteriorProfileDiameter(keyword_filed_));

  return !diameters_.isEmpty();
}

int NestingModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return diameters_.count();
}

int NestingModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return ITEMS_NUM;
}

Qt::ItemFlags NestingModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return Qt::ItemIsEnabled;
  }
  if (index.column() == 0) {
    return QAbstractItemModel::flags(index);
  }
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant NestingModel::data(const QModelIndex &index, int role) const {
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
    return atof(GetItemValue(index).c_str());
   case Qt::BackgroundRole:
    return QVariant();
   case Qt::TextAlignmentRole:
    return QVariant(Qt::AlignCenter);
   default:
    return QVariant();
  }
}

QVariant NestingModel::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role) const {

  if (role != Qt::DisplayRole) {
    return QVariant();
  }
  if (orientation == Qt::Horizontal) {
    switch (section) {
     case 0:
     case 1:
     case 2:
     case 3:
     case 4:
      return LIST_ITEMS[section].c_str();
     default:
      return QVariant();
    }
  }
  return QVariant();
}

bool NestingModel::setData(const QModelIndex &index, const QVariant &value,
    int role) {

  if (index.isValid() && role == Qt::EditRole) {
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

std::string NestingModel::GetItemValue(const QModelIndex &index) const {
  int row = index.row();
  int column = index.column();
  char diameter[] = "*";
  sprintf(diameter, "%.1f", diameters_[row]);
  OCutter *cutter = OCutter::GetInstance();
  std::map<std::string, std::string> interior_profile_items =
      cutter->GetNesting()->GetInteriorProfileItemValue(diameter,
      keyword_filed_);

  if (column == 0) {
    return diameter;
  }
  return interior_profile_items[LIST_ITEMS[column].c_str()];
}
