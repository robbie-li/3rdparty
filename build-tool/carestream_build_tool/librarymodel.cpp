#include "librarymodel.h"
#include <QDir>
#include <QSettings>
#include <QDebug>

#include "library.h"
#include "libraryfactory.h"

LibraryModel::LibraryModel()
{
  QSettings setting;
  root_directory_ = setting.value("Root Directory").toString();
  qDebug() << "Build Script Directory:"  << root_directory_;

  if(!root_directory_.isEmpty())
    {
      setBuildScriptsRootDirectory(root_directory_);
    }
}

QString LibraryModel::buildScriptsRootDirectory() const
{
  return root_directory_;
}

void LibraryModel::setBuildScriptsRootDirectory(const QString &rootDirectory)
{
  qDebug() << "Update Build Script Directory:"  << rootDirectory;
  QDir rootDir(rootDirectory);

  if(rootDirectory.isEmpty() || !rootDir.exists()) { return; }

  root_directory_ = rootDirectory;

  beginResetModel();
  libraries_.clear();

  QStringList filters;
  filters << "*.xml";
  for(auto file: rootDir.entryInfoList(filters, QDir::Files))
    {
      Library* library = LibraryFactory::instance().createLibrary(file.absoluteFilePath());
      libraries_.push_back(library);
    }

  QSettings setting;
  setting.setValue("Root Directory", rootDirectory);
  endResetModel();
}

void LibraryModel::selectLibrary(const QString &name, const QString& version, bool selected)
{
  qDebug() << "Library:" << name << ", Version:" << version <<", Selected:" << selected;
  for( auto library: libraries_)
    {
      if(library->get_version() == version && library->get_name() == name)
        {
          library->set_selected(selected);
        }
    }
}

int LibraryModel::rowCount(const QModelIndex &parent) const
{
  return (int)libraries_.size();
}

QVariant LibraryModel::data(const QModelIndex &index, int role) const
{
  if(index.row() < 0 || index.row() > libraries_.size())
    {
      return QVariant();
    }

  switch(role)
    {
    case NameRole:
      return libraries_.at(index.row())->get_name();
    case VersionRole:
      return libraries_.at(index.row())->get_version();
    case UrlRole:
      return libraries_.at(index.row())->get_url();
    case SelectedRole:
      return libraries_.at(index.row())->get_selected();
    }

  return QVariant();
}

QHash<int, QByteArray> LibraryModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[NameRole]     = "name";
  roles[VersionRole]  = "version";
  roles[UrlRole]      = "url";
  roles[SelectedRole] = "selected";
  return roles;
}

QList<Library*> LibraryModel::selectedLibraries() const
{
  QList<Library*> results;

  for( auto library: libraries_)
    {
      if(library->get_selected())
        {
          qDebug() << "Add Library:" << library->get_name() << ", Version:" << library->get_version();
          results.push_back(library);
        }
    }

  return results;
}
