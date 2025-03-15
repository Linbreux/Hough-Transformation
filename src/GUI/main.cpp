#include <QDebug>
#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <core/manager.hpp>

#include "cpp/CanvasController.hpp"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  QQmlContext *context = engine.rootContext();

  core::Manager manager;
  CanvasController canvasController(manager);
  context->setContextProperty("canvasController", &canvasController);

  engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}
