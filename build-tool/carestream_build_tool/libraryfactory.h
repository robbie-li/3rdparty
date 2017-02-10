#ifndef LIBRARYFACTORY_H
#define LIBRARYFACTORY_H

#include <QString>

class Library;

class LibraryFactory
{
private:
  LibraryFactory();
public:
  static LibraryFactory &instance();
  Library* createLibrary(const QString& xml_description_path);
private:
  static LibraryFactory* instance_;
};

#endif // LIBRARYFACTORY_H
