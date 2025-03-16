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


  QVariantList drawList();
  QVariantList transformList();

  void doTransform(std::shared_ptr<core::Point> p);

  Q_INVOKABLE void addLine(const QPoint point);
  Q_INVOKABLE void addReversePoint(const QPointF point);
  Q_INVOKABLE void addPoint(qint64 x, qint64 y);

  Q_INVOKABLE void clearAll();

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
