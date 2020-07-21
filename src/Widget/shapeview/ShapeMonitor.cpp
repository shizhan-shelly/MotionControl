// Copyright 2013 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ShapeMonitor.h"

#include <assert.h>
#include <math.h>

#include <QtGui/QGraphicsLineItem>
#include <QtGui/QGraphicsScene>
#include <QtGui/QMouseEvent>
#include <QtGui/QPen>
#include <QtGui/QStackedLayout>

#include "AuxiliaryWidget.h"
#include "CircleItem.h"
#include "OptimizePoints.h"
#include "OutLineItem.h"
#include "ShapeView.h"
#include "SortCircles.h"

ShapeMonitor::ShapeMonitor(QWidget *parent) : QWidget(parent)
                                            , scale_(0) {

  setMouseTracking(true);
  monitor_widget_ = new AuxiliaryWidget(this);

  scene_ = new QGraphicsScene;
  scene_->setItemIndexMethod(QGraphicsScene::NoIndex);

  shape_view_ = new ShapeView(this);
  shape_view_->setScene(scene_);

  stacked_layout_ = new QStackedLayout;
  stacked_layout_->addWidget(monitor_widget_);
  stacked_layout_->addWidget(shape_view_);
  stacked_layout_->setStackingMode(QStackedLayout::StackAll);
  stacked_layout_->setContentsMargins(0, 0, 0, 0);
  setLayout(stacked_layout_);
}

ShapeMonitor::~ShapeMonitor() {}

void ShapeMonitor::initialWidget(const QVector<QPointF> &ext_points,
    const QVector<QVector<QPointF> > &in_points,
    const QVector<QPair<QPointF, double> > &circles) {

  clearAll();
  setExtOutLine(ext_points);
  setInternalLine(in_points);
  setCircles(circles);
  autoFitInWidget();
}

void ShapeMonitor::setEditable(bool enable) {
  stacked_layout_->setCurrentIndex(enable ? 1 : 0);
}

void ShapeMonitor::setExtOutLine(const QVector<QPointF> &points) {
  assert(points.count() > 2);
  QVector<QPointF> optimize_points = points;
  OptimizePoints::Simplify(optimize_points, 1);
  for (int i = 0; i < optimize_points.count() - 1; i++) {
    polygon_lines_.push_back(scene_->addLine(optimize_points[i].x(),
        optimize_points[i].y(), optimize_points[i + 1].x(),
        optimize_points[i + 1].y()));

  }
  polygon_lines_.push_back(scene_->addLine(optimize_points.last().x(),
      optimize_points.last().y(), optimize_points.first().x(),
      optimize_points.first().y()));

}

void ShapeMonitor::setInternalLine(const QVector<QVector<QPointF> > &points) {
  for (int i = 0; i < points.count(); i++) {
    assert(points[i].count() > 2);
    QVector<QPointF> optimize_points = points[i];
    OptimizePoints::Simplify(optimize_points, 1);
    outlines_.push_back(new OutLineItem);
    outlines_.last()->initialPoints(optimize_points);
    scene_->addItem(outlines_.last());
  }
}

void ShapeMonitor::setCircles(const QVector<QPair<QPointF, double> > &circles) {
  assert(!circles.isEmpty());
  for (int i = 0; i < circles.count(); i++) {
    circles_.push_back(new CircleItem);
    circles_.last()->setupCircle(circles[i].second);
    circles_.last()->setPos(circles[i].first);
    scene_->addItem(circles_.last());
  }
}

void ShapeMonitor::addCircle(const QPointF &pos, double radius) {
  circles_.push_back(new CircleItem);
  circles_.last()->setupCircle(radius);
  circles_.last()->setPos(pos);
  scene_->addItem(circles_.last());
}

void ShapeMonitor::deleteCircle(const QPointF &pos) {
  CircleItem *item = (CircleItem *)scene_->itemAt(pos);
  if (item) {
    scene_->removeItem(item);
    circles_.remove(circles_.indexOf(item));
    delete item;
  }
}

void ShapeMonitor::setColor(const QColor &line_color,
                            const QColor &circle_color) {

  for (int i = 0; i < polygon_lines_.count(); i++) {
    polygon_lines_[i]->setPen(QPen(QBrush(line_color), 0.5));
  }
  for (int i = 0; i < outlines_.count(); i++) {
    outlines_[i]->setLineColor(line_color);
  }
  for (int i = 0; i < circles_.count(); i++) {
    circles_[i]->setCircleColor(circle_color);
  }
}

void ShapeMonitor::clearAll() {
  punched_circles_.clear();
  monitor_widget_->clearAll();

  circles_.clear();
  outlines_.clear();
  polygon_lines_.clear();
  scene_->clear();
}

bool ShapeMonitor::isCollided() {
  for (int i = 0; i < circles_.count(); i++) {
    if (!circles_[i]->collidingItems().isEmpty()) {
      return true;
    }
  }
  return false;
}

void ShapeMonitor::getCircles(QVector<QPointF> &circle_infos) const {
  for (int i = 0; i < circles_.count(); i++) {
    circle_infos.push_back(circles_[i]->pos());
  }
  SortCircles::Sort(circle_infos);
}

void ShapeMonitor::onLocated(const QPointF &pos) {
   cursor_point_ = pos;
   monitor_widget_->onLocated(shape_view_->mapFromScene(cursor_point_));
}

void ShapeMonitor::onPunched(const QPointF &pos, double radius) {
  punched_circles_.push_back(QPair<QPointF, double>(pos, radius));
  displayPunchedCircles();
}

void ShapeMonitor::onZoom(double scale) {
  shape_view_->scale(scale, scale);
  scale_ = scale;
  onLocated(cursor_point_);
  displayPunchedCircles();
}

void ShapeMonitor::mouseMoveEvent(QMouseEvent *event) {
  QPoint calc_pos = AccuratePosition(event->pos());
  emit currentPosition(shape_view_->mapToScene(calc_pos));
}

void ShapeMonitor::autoFitInWidget() {
  shape_view_->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
  scale_ = 1;
}

void ShapeMonitor::displayPunchedCircles() {
  QVector<QPair<QPointF, double> > pixel_cirles;
  for (int i = 0; i < punched_circles_.count(); ++i) {
    QPoint org_pixel = shape_view_->mapFromScene(QPointF(0, 0));
    QPoint rad_pixel = shape_view_->mapFromScene(
        QPointF(punched_circles_[i].second, 0));

    double x0 = org_pixel.x();
    double y0 = org_pixel.y();
    double x1 = rad_pixel.x();
    double y1 = rad_pixel.y();
    double radius_pixel = sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));
    QPoint point = shape_view_->mapFromScene(punched_circles_[i].first);
    pixel_cirles.push_back(QPair<QPointF, double>(QPointF(point), radius_pixel));
  }
  monitor_widget_->onPunched(pixel_cirles);
}

void ShapeMonitor::onTranslate(double delt_x, double delt_y) {
  shape_view_->setTransformationAnchor(QGraphicsView::NoAnchor);
  shape_view_->translate(delt_x, delt_y);

  onLocated(cursor_point_);
  displayPunchedCircles();
}

void ShapeMonitor::onDeleted() {
  QList<QGraphicsItem *> selected_items = scene_->selectedItems();
  for (int i = 0; i < selected_items.count(); i++) {
    CircleItem *item = (CircleItem *)selected_items[i];
    scene_->removeItem(item);
    circles_.remove(circles_.indexOf(item));
    delete item;
  }
}

QPoint ShapeMonitor::AccuratePosition(const QPoint &orig_pos) {
  QRectF calibrate_rect = shape_view_->mapToScene(
      QRect(orig_pos.x() - 6, orig_pos.y() - 6, 12, 12)).boundingRect();

  QList<QGraphicsItem *> item_list = scene_->items(calibrate_rect,
                                     Qt::IntersectsItemBoundingRect);

  if (item_list.count() == 0 || !isLineItems(item_list)) {
    monitor_widget_->onCloseToPoint(orig_pos, false);
    return orig_pos;
  } else {
    QPoint calc_pos = CalculateNearestPoint(orig_pos, item_list);
    monitor_widget_->onCloseToPoint(calc_pos, true);
    return calc_pos;
  }
}

QPoint ShapeMonitor::CalculateNearestPoint(const QPoint &point,
    const QList<QGraphicsItem *> &item_list) {

  assert(!item_list.empty());
  QPointF orig_pos = shape_view_->mapToScene(point);
  QMap<double, QPointF> sort_map;
  for (int i = 0; i < item_list.count(); i++) {
    QGraphicsLineItem *item = (QGraphicsLineItem *)item_list[i];
    sort_map.insert(pow((orig_pos.x() - item->line().p1().x()), 2) +
                    pow((orig_pos.y() - item->line().p1().y()), 2),
                    item->line().p1());

    sort_map.insert(pow((orig_pos.x() - item->line().p2().x()), 2) +
                    pow((orig_pos.y() - item->line().p2().y()), 2),
                    item->line().p2());

  }
  return shape_view_->mapFromScene(sort_map.begin().value());
}

bool ShapeMonitor::isLineItems(const QList<QGraphicsItem *> &item_list) {
  assert(!item_list.empty());
  for (int i = 0; i < item_list.count(); i++) {
    if (!qgraphicsitem_cast<QGraphicsLineItem *>(item_list[i])) {
      return false;
    }
  }
  return true;
}
