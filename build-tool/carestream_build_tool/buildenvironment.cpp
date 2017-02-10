#include "buildenvironment.h"
#include <QDir>
#include <QRegularExpression>
#include <QDebug>
#include <QUrl>
#include "library.h"

BuildEnvironment::BuildEnvironment(const QString& compiler, const QString& architecture, Library* library)
  : library_(library)
{
  map_.insert(QLatin1String("compiler"), compiler);
  map_.insert(QLatin1String("architecture"), architecture);
  map_.insert(QLatin1String("address_model"), architecture.right(2));

  map_.insert(QLatin1String("name"), library->get_name());
  map_.insert(QLatin1String("version"), library->get_version());
  map_.insert(QLatin1String("url"), library->get_url());

  QUrl url(library->get_url());
  map_.insert(QLatin1String("tarball"), url.fileName());
}

void BuildEnvironment::setRootDirectory(QString &rootDirectory)
{
  QDir root(rootDirectory);
  root.mkdir(library_->get_name() + " "+ library_->get_version());
  QDir distdir(root.absolutePath()  + "/" + library_->get_name() + " "+ library_->get_version());
  map_.insert(QLatin1String("distdir"), QDir::toNativeSeparators(distdir.absolutePath() + "/"));
}

QString BuildEnvironment::expand(const QString &str) const
{
  QString result = str;
  QString pattern = "%(\\w+)%";

  QRegularExpression rx(pattern);

  QRegularExpressionMatchIterator i = rx.globalMatch(str);
  while (i.hasNext())
    {
      QRegularExpressionMatch m = i.next();
      if (m.hasMatch())
        {
          QString target = m.captured(0);
          QString key = m.captured(1);

          if(map_.contains(key))
            {
              result.replace(m.captured(0), map_[key]);
            }
        }
    }

  return result;
}

QStringList BuildEnvironment::expand(const QStringList &strs) const
{
  QStringList result;

  for (QString str: strs)
    {
      result.push_back(expand(str));
    }

  return result;
}
