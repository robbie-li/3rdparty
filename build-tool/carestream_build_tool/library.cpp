#include "library.h"
#include <QtXml/QtXml>
#include <QFile>
#include <QDebug>

#include "buildenvironment.h"
#include "buildstep.h"

Q_DECLARE_METATYPE(QList<Library*>)

Library::Library(const QDomDocument &doc)
  : selected_(false)
{
  QDomElement docElem = doc.documentElement();

  QDomElement elem1 = docElem.firstChildElement("name");
  name_ = elem1.text();

  QDomElement elem2 = docElem.firstChildElement("version");
  version_ = elem2.text();

  QDomElement elem3 = docElem.firstChildElement("url");
  url_ = elem3.text();

  setupBuildStep(doc);
}

void Library::build(QProcess *process, BuildEnvironment *env)
{
  process_ = process;

  for(auto step: steps_)
    {
      step.execute(process_, env);
    }
}

void Library::cancel(QProcess *process)
{
  process->kill();
}

void Library::setupBuildStep(const QDomDocument &doc)
{
  QDomElement docElem = doc.documentElement();

  QDomElement steps = docElem.firstChildElement("steps");

  QDomNodeList& step_nodes = steps.childNodes();

  for( size_t i = 0; i < step_nodes.count(); ++i)
    {
      BuildStep s;
      s.setContent(step_nodes.at(i).toElement());
      steps_.push_back(s);
    }
}
