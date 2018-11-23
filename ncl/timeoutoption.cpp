#include "timeoutoption.h"

#include <QObject>

TimeoutOption::TimeoutOption()
  : CmdOption()
  , option_("timeout", QObject::tr("Timeout. [ms]"), "timeout")
{}

const QCommandLineOption *TimeoutOption::ptr() const
{
  return &option_;
}
