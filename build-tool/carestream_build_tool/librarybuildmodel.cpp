#include "librarybuildmodel.h"
#include <QScxmlEvent>

LibraryBuildModel::LibraryBuildModel()
{
}

bool LibraryBuildModel::hasMoreSteps() const
{
  return step < steps.size();
}

QVariantMap LibraryBuildModel::eventData() const
{
  return scxmlEvent().data().value<QVariantMap>();
}
