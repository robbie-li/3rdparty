#ifndef LIBRARYBUILDMODEL_H
#define LIBRARYBUILDMODEL_H

#include <QScxmlCppDataModel>
#include "buildstep.h"

class LibraryBuildModel : public QScxmlCppDataModel
{
  Q_OBJECT
  Q_SCXML_DATAMODEL
public:
  LibraryBuildModel();

private:
  bool hasMoreSteps() const;
  QVariantMap eventData() const;
private:
  int step;
  QList<BuildStep> steps;
};

#endif // LIBRARYBUILDMODEL_H
