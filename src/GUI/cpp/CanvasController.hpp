#ifndef CANVASCONTROLLER_H
#define CANVASCONTROLLER_H

#include "core/drawable.hpp"
#include <QLine>
#include <QObject>
#include <memory>
#include <qdebug.h>
#include <qglobal.h>
#include <qobject.h>
#include <qpoint.h>
#include <qvariant.h>
#include <iostream>

#include <core/manager.hpp>
#include <core/point.hpp>

class CanvasController : public QObject {
  Q_OBJECT

  Q_PROPERTY(QVariantList drawList READ drawList NOTIFY changedPoints)
  Q_PROPERTY(QVariantList transformList READ transformList NOTIFY changedTransform)

public:
  explicit CanvasController(core::Manager& manager, QObject *parent = nullptr)
    : manager(manager)
    , QObject(parent){}


  QVariantList drawList() {
    QVariantList pointList;
    for ( auto& drawable : this->manager.getDrawables()){
      if (!drawable->needsDrawing()) continue;
      if (auto point = std::dynamic_pointer_cast<core::Point>(drawable)){
        QVariantMap pointMap;
        pointMap["connected"] = point->isConnected();
        pointMap["x"] = point->getX();
        pointMap["y"] = point->getY();
        pointMap["color"] = point->getColor().value_or("black").c_str();
        if (point->isConnected()){
          pointMap["x2"] = point->getConnectedPoint().lock()->getX();
          pointMap["y2"] = point->getConnectedPoint().lock()->getY();
        }
        point->setState(core::Drawable::State::IsDrawn);
        pointList.append(QVariant::fromValue(pointMap));
        if (point->drawTransformation()) doTransform(point);
        emit changedTransform();
      }
      continue;
    }
    return pointList;
  }

  QVariantList transformList() {
    QVariantList tf = this->transformationList;
    this->transformationList.clear();
    return tf;
  }

  void doTransform(std::shared_ptr<core::Point> p){
    std::vector<Transform::Hough::Polair> listPolair = p->doTransform();
    QVariantList pointList;
    for (auto polpoint: listPolair){
      QVariantMap pointMap;
      pointMap["x"] = polpoint.angle;
      pointMap["y"] = polpoint.r;
      pointList.append(QVariant::fromValue(pointMap));
    }
    this->transformationList = pointList;
  }

  Q_INVOKABLE void addLine(const QPoint point) {
    std::weak_ptr<core::Drawable> lastPoint = this->manager.getLastDrawable();
    std::shared_ptr<core::Point> newPoint;
    if (auto last = lastPoint.lock()){
      if (auto prevpoint = std::dynamic_pointer_cast<core::Point>(last)){
        newPoint = std::make_shared<core::Point>(point.x(), point.y(), prevpoint);
        newPoint->setDrawTransformation(true);
        this->manager.addDrawable(std::move(newPoint));
        emit changedPoints();
        return;
      }
    }
    // no previous point, so just adding this one.
    newPoint = std::make_shared<core::Point>(point.x(), point.y());
    newPoint->setDrawTransformation(true);
    this->manager.addDrawable(std::move(newPoint));

    emit changedPoints();
  }

  Q_INVOKABLE void addReversePoint(const QPointF point){
    this->manager.removeType(core::Drawable::Type::ReverseTransformPoint);
    auto pol = Transform::Hough::Polair{
      float(point.y()),
      float(point.x())
    };
    auto listOfPoints = Transform::Hough::transformToCartesian(pol);
    if (listOfPoints.size() != 2) return;
    auto [x1, y1] = listOfPoints[0];
    auto [x2, y2] = listOfPoints[1];
    auto point1 = std::make_shared<core::Point>(x1,y1);
    auto point2 = std::make_shared<core::Point>(x2,y2, point1);

    point1->setColor("yellow");
    point1->setType(core::Drawable::Type::ReverseTransformPoint);
    point2->setColor("yellow");
    point2->setType(core::Drawable::Type::ReverseTransformPoint);

    this->manager.addDrawable(point1);
    this->manager.addDrawable(point2);

    this->manager.redrawAll();
    emit clearCanvas();
  }

  Q_INVOKABLE void addPoint(qint64 x, qint64 y) {
    auto point = std::make_shared<core::Point>(x, y);
    point->setDrawTransformation(true);
    this->manager.addDrawable( std::move(point) );
    emit changedPoints();
  }

  Q_INVOKABLE void clearAll(){
    this->manager.removeAll();
    emit clearCanvas();
    emit clearCanvasTransform();
  }

private:
  core::Manager& manager;
  QList<QPoint> m_points;
  QVariantList transformationList;

signals:
  void changedPoints() const;
  void changedTransform() const;
  void clearCanvas() const;
  void clearCanvasTransform() const;
};

#endif // DRAWINGCONTROLLER_H
