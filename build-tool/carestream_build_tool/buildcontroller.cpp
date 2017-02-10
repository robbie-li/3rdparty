#include "buildcontroller.h"

#include <QThread>
#include <QObject>

#include "buildworker.h"
#include "library.h"

BuildController::BuildController(const QList<Library*>& libs,
                                 const QString& vc_version,
                                 const QString& architecture)
  : worker_(new BuildWorker(libs, vc_version, architecture))
  , thread_(new QThread)
{
  worker_->moveToThread(thread_);
  QObject::connect(thread_, SIGNAL(started()),  worker_, SLOT(process()));
  QObject::connect(worker_, SIGNAL(finished()), thread_, SLOT(quit()));
  QObject::connect(worker_, &BuildWorker::error, this, &BuildController::error);
  QObject::connect(worker_, &BuildWorker::message, this, &BuildController::message);
}

BuildController::~BuildController()
{
  delete worker_;
  delete thread_;
}

void BuildController::startBuild()
{
  thread_->start();
}

void BuildController::cancelBuild()
{
  worker_->cancel();
  thread_->wait();
}
