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
  beginResetModel();
  //OCutter *cutter = OCutter::GetInstance();
  keyword_filed_.clear();
  //cutter->GetCutChart()->GetCurrentSelectedRecord(keyword_filed_);
  //diameters_ = QVector<double>::fromStdVector(
  //    cutter->GetNesting()->GetInteriorProfileDiameter(keyword_filed_));

  //interior_profile_items_.clear();
  //foreach (double diameter, diameters_) {
  //  char buf[256];
  //  sprintf(buf, "%.1f", diameter);
  //  interior_profile_items_.push_back(
  //      cutter->GetNesting()->GetInteriorProfileItemValue(buf,
  //      keyword_filed_));

  //}
  endResetModel();
  return !diameters_.isEmpty();
}

bool NestingModel::saveNesting() {
  for (int i = 0; i < diameters_.size(); i++) {
    char buf[256];
    sprintf(buf, "%.1f", diameters_[i]);
  //  OCutter *cutter = OCutter::GetInstance();
  //  cutter->GetNesting()->SetInteriorProfileItemValue(buf,
  //      interior_profile_items_[i], keyword_filed_);

  }
  return true;
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
    return column == 0 ? diameters_[row] : atof(GetItemValue(index).c_str());
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
    SetItemValue(index, value.toString());
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

std::string NestingModel::GetItemValue(const QModelIndex &index) const {
  int row = index.row();
  int column = index.column();
  if (column > 0 && column < ITEMS_NUM) {
    std::map<std::string, std::string>::const_iterator it =
        interior_profile_items_[row].find(LIST_ITEMS[column]);

    return it != interior_profile_items_[row].end() ? it->second : "";
  }
  return "";
}

void NestingModel::SetItemValue(const QModelIndex &index, const QString &value) {
  int row = index.row();
  int column = index.column();
  if (column > 0 && column < ITEMS_NUM) {
    std::map<std::string, std::string>::iterator it =
        interior_profile_items_[row].find(LIST_ITEMS[column]);

    if (it != interior_profile_items_[row].end()) {
      it->second = value.toStdString();
    }
  }
}
