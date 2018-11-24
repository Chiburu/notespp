#include "timeoutoption.h"

#include <QObject>

#define KEY_NAME "timeout"

TimeoutOption::TimeoutOption()
  : option_(
      KEY_NAME,
      QObject::tr("Timeout. [ms]"),
      "timeout"
      )
{}

const char *TimeoutOption::name() const
{
  return KEY_NAME;
}

const QCommandLineOption *TimeoutOption::ptr() const
{
  return &option_;
}
