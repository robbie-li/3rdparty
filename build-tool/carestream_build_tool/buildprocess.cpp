#include "buildprocess.h"

#include "buildcontroller.h"
#include "buildenvironment.h"
#include "buildworker.h"
#include "library.h"

BuildProcess::BuildProcess(QObject* parent) : QObject(parent), controller_(nullptr)
{
}

void BuildProcess::build(const QString &vc_version, const QString &architecture, const QList<Library*> &libraries)
{
  cancelBuild();
  controller_ = new BuildController(libraries, vc_version, architecture);
  controller_->startBuild();
  connect(controller_, &BuildController::message, this, &BuildProcess::message);
}

void BuildProcess::cancelBuild()
{
  if(controller_)
    {
      controller_->cancelBuild();
      delete controller_;
      controller_ = nullptr;
    }
}
