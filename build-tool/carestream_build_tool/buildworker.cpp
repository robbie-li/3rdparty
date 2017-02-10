#include "buildworker.h"

#include <QDebug>
#include <QDir>

#include "buildenvironment.h"
#include "library.h"

BuildWorker::BuildWorker(const QList<Library*>& libs,
                         const QString& vc_version,
                         const QString& architecture)
  : libraries_(libs)
  , vc_version_(vc_version)
  , architecture_(architecture)
  , process_(new QProcess(this))
{
  connect(process_, &QProcess::readyReadStandardError, this, &BuildWorker::onReadyReadStandardError);
  connect(process_, &QProcess::readyReadStandardOutput, this, &BuildWorker::onReadyReadStandardOutput);
}

BuildWorker::~BuildWorker()
{
  delete process_;
}

void BuildWorker::process()
{
  qDebug() << "Visual C++  :" << vc_version_;
  qDebug() << "Architecture:" << architecture_;

  for(auto library: libraries_)
    {
      BuildEnvironment* env = new BuildEnvironment(vc_version_, architecture_, library);
      env->setRootDirectory(QDir::homePath());
      QString msg = QLatin1String("Building:") + library->get_name() + " " + library->get_version();
      emit message(msg);
      library->build(process_, env);
    }

  emit finished();
}

void BuildWorker::cancel()
{
  qDebug() << "Build Process Killed";
  emit message(QLatin1String("Build Process Killed"));
  process_->kill();
}

void BuildWorker::onReadyReadStandardOutput()
{
  QString output = QString::fromUtf8(process_->readAllStandardOutput());
  emit message(output);
}

void BuildWorker::onReadyReadStandardError()
{
  QString error = QString::fromUtf8(process_->readAllStandardError());
  emit message(error);
}

