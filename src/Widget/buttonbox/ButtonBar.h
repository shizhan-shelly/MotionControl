// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef WIDGET_BUTTONBOX_BUTTONBAR_H__
#define WIDGET_BUTTONBOX_BUTTONBAR_H__

#include <QtCore/QMap>
#include <QWidget>

class QButtonGroup;
class QGridLayout;

namespace widget {

class ButtonBar : public QWidget {
  Q_OBJECT

 public:
  explicit ButtonBar(QWidget *parent = NULL);
  ~ButtonBar();

  void initBar(const QMap<int, QString> &bar_infor);

 signals:
  void ButtonChecked(int id);

 private:
  QButtonGroup *btn_group_;
  QGridLayout *layout_;

  static const int MAX_BTN_CNT = 4;

  void removeButtons();

}; // class ButtonBar

} // namespace widget

#endif // WIDGET_BUTTONBOX_BUTTONBAR_H__
