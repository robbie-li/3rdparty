#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <QAbstractListModel>
#include <QList>

class Library;

class LibraryModel : public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(QString buildScriptsRootDirectory READ buildScriptsRootDirectory WRITE setBuildScriptsRootDirectory NOTIFY buildScriptsRootDirectoryChanged)
  Q_PROPERTY(QList<Library*> selectedLibraries READ selectedLibraries)
public:
  LibraryModel();

  QString buildScriptsRootDirectory() const;
  void setBuildScriptsRootDirectory(const QString& rootDirectory);
  Q_INVOKABLE void selectLibrary(const QString& library, const QString& version, bool selected);

  enum ScannerRoles {
    NameRole = Qt::UserRole + 1,
    VersionRole,
    UrlRole,
    SelectedRole
  };

  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const;

  QList<Library*> selectedLibraries() const;
signals:
  void buildScriptsRootDirectoryChanged(const QString& buildScriptsRootDirectory);
private:
  QList<Library*> libraries_;
  QString root_directory_;
};

#endif // LIBRARYMODEL_H
