#ifndef BUILDWORKER_H
#define BUILDWORKER_H

#include <QList>
#include <QObject>
#include <QString>

class Library;
class QProcess;

class BuildWorker : public QObject
{
  Q_OBJECT
public:
  BuildWorker(const QList<Library*>& libs,
              const QString& vc_version,
              const QString& architecture);
  ~BuildWorker();
public slots:
  void process();
  void cancel();
private slots:
  void onReadyReadStandardOutput();
  void onReadyReadStandardError();
signals:
  void finished();
  void error(const QString& err);
  void message(QString message);
private:
  QProcess*       process_;
  QList<Library*> libraries_;
  QString         vc_version_;
  QString         architecture_;
};

#endif // BUILDWORKER_H
