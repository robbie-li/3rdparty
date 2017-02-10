#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "librarymodel.h"
#include "buildprocess.h"
#include "library.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication::setApplicationName("Carestream Build Toolkit");
  QGuiApplication::setOrganizationDomain("com.carestream.dental");
  QGuiApplication::setOrganizationName("Carestream");
  QGuiApplication app(argc, argv);

  qmlRegisterType<LibraryModel>("com.carestream.dental", 1, 0, "LibraryModel");
  qmlRegisterType<BuildProcess>("com.carestream.dental", 1, 0, "BuildProcess");
  qRegisterMetaType<QList<Library*>>("QList<Library*>");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QLatin1String("qrc:/main.qml")));

  return app.exec();
}
