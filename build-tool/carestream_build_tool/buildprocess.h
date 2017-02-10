#ifndef BUILDPROCESS_H
#define BUILDPROCESS_H

#include <QProcess>
#include <QString>
#include <QList>

class Library;
class BuildController;

class BuildProcess : public QObject
{
  Q_OBJECT
public:
  BuildProcess(QObject* parent = 0);
  Q_INVOKABLE void build(const QString& vc_version, const QString &architecture, const QList<Library*> &libraries);
  Q_INVOKABLE void cancelBuild();
signals:
  void message(QString message);
private:
  BuildController* controller_;
};

#endif // BUILDPROCESS_H
