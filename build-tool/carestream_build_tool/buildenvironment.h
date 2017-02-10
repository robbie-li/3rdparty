#ifndef BUILDENVIRONMENT_H
#define BUILDENVIRONMENT_H

#include <QString>
#include <QMap>

class Library;

class BuildEnvironment
{
public:
  BuildEnvironment(const QString& compiler, const QString& architecture, Library* library);
  void setRootDirectory(QString& rootDirectory);
  QString expand(const QString& str) const;
  QStringList expand(const QStringList& str) const;
private:
  QMap<QString, QString> map_;
  Library* library_;
};

#endif // BUILDENVIRONMENT_H
