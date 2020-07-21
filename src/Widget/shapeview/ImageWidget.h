// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef IMAGEWIDGET_CALIBRATELISTWIDGETITEM_H__
#define IMAGEWIDGET_CALIBRATELISTWIDGETITEM_H__

#include <QtGui/QWidget>

class QLabel;
class QPushButton;

class ImageWidget : public QWidget {
  Q_OBJECT

 public:
  explicit ImageWidget(QWidget *parent = NULL);
  ~ImageWidget();

  void setImage();

 public slots:
  void onDisplay(const QPointF &pos);

 signals:
  void scaled(double scale);

 protected:
  void paintEvent(QPaintEvent *event);

 private:
  QLabel *label_;
  QPushButton *zoom_in_button_;
  QPushButton *zoom_out_button_;

 private slots:
  void onZoomInClicked();
  void onZoomOutClicked();

};

#endif // IMAGEWIDGET_CALIBRATELISTWIDGETITEM_H__
