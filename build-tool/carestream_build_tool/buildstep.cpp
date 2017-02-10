#include "buildstep.h"
#include <QDebug>
#include <QtXml>
#include "buildenvironment.h"

void BuildStep::setContent(const QDomElement& elem)
{
  program_ = elem.firstChildElement("program").text();
  working_directory_ = elem.firstChildElement("working_directory").text();
  QDomElement arguments = elem.firstChildElement("arguments");
  QDomNodeList arguments_nodes = arguments.childNodes();
  for( size_t i = 0; i < arguments_nodes.count(); ++i)
    {
      QString arg = arguments_nodes.at(i).toElement().text();
      arguments_.push_back(arg);
    }
}

bool BuildStep::execute(QProcess *process, BuildEnvironment* env)
{
  QString program = env->expand(program_);
  QStringList args = env->expand(arguments_);
  QString cwd = env->expand(working_directory_);
  process->setWorkingDirectory(cwd);
  process->start(program, args);
  process->waitForFinished(-1);
  return true;
}
