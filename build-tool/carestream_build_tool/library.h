#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QProcess>
#include <QVariant>
#include "macro.h"
#include "buildstep.h"

class QDomDocument;
class BuildEnvironment;

class Library : public QObject
{
  Q_OBJECT
public:
  Library(const QDomDocument& doc);

  DEFINE_PROPERTY(QString, name)
  DEFINE_PROPERTY(QString, version)
  DEFINE_PROPERTY(QString, url)
  DEFINE_PROPERTY(bool,    selected)

  void build(QProcess* process, BuildEnvironment* env);

signals:
  void buildSuccess(Library* library);
  void buildFailure(Library* library);
  void stepFinished(Library* library, BuildStep step);
  void stepError(Library* library, BuildStep step);

protected:
  void cancel(QProcess* process);
  void setupBuildStep(const QDomDocument& doc);

protected:
  std::vector<BuildStep>  steps_;
  QProcess*               process_;
};

#endif // LIBRARY_H
