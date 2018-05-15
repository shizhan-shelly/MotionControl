// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_CUSTOMWIDGET_COMBOEDITOR_H__
#define WIDGET_CUSTOMWIDGET_COMBOEDITOR_H__

#include "../basewidget/BaseWidget.h"

class QComboBox;
class QHBoxLayout;
class QLabel;

namespace widget {

class ComboEditor : public BaseWidget {
  Q_OBJECT

 public:
  explicit ComboEditor(QWidget *parent = NULL);
  ~ComboEditor();

  void setupWidget(const QPair<QString, QList<QString> > &infor);

 private:
  QComboBox *combobox_;
  QHBoxLayout *layout_;
  QLabel *title_;

  void clearItems();
  void arrangeItems();

}; // class ComboEditor

} // namespace widget

#endif // WIDGET_CUSTOMWIDGET_COMBOEDITOR_H__
