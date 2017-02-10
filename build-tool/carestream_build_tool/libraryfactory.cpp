#include "libraryfactory.h"
#include <QtXml>
#include "library.h"

LibraryFactory* LibraryFactory::instance_ = nullptr;

LibraryFactory::LibraryFactory()
{
}

LibraryFactory &LibraryFactory::instance()
{
  if(instance_ == nullptr)
    {
      instance_ = new LibraryFactory;
    }

  return *instance_;
}

Library *LibraryFactory::createLibrary(const QString &xml_description_path)
{
  QDomDocument doc;
  QFile xml(xml_description_path);
  if (!xml.open(QIODevice::ReadOnly))
    {
      qDebug() << "failed to open";
      return nullptr;
    }
  qDebug() << "Reading XML:" << xml_description_path;
  if (!doc.setContent(&xml))
    {
      qDebug() << "failed to read";
      xml.close();
      return nullptr;
    }
  xml.close();

  return new Library(doc);
}
