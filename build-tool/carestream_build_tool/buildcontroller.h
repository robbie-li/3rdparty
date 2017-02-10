#ifndef BUILDCONTROLLER_H
#define BUILDCONTROLLER_H

#include <QList>
#include <QObject>
#include <QString>

class BuildWorker;
class Library;
class QProcess;
class QThread;

class BuildController : public QObject
{
  Q_OBJECT
public:
  BuildController(const QList<Library*>& libs,
                  const QString& vc_version,
                  const QString& architecture);
  ~BuildController();
  void startBuild();
  void cancelBuild();
signals:
  void error(const QString& error);
  void message(QString message);
private:
  BuildWorker* worker_;
  QThread*     thread_;
};

#endif // BUILDCONTROLLER_H
