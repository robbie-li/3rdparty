#ifndef BUILDSTEP_H
#define BUILDSTEP_H

#include <QObject>
#include <QString>

class QProcess;
class BuildEnvironment;
class QDomElement;

class BuildStep
{
public:
  void setContent(const QDomElement& elem);
  bool execute(QProcess* process, BuildEnvironment* env);
public:
  QString     program_;
  QStringList arguments_;
  QString     working_directory_;
};

Q_DECLARE_METATYPE(BuildStep)

#endif // BUILDSTEP_H
