#include "returnvaluesoption.h"

#include <QObject>

#define KEY_NAME "return-values"

ReturnValuesOption::ReturnValuesOption()
  : option_(
      KEY_NAME,
      QObject::tr("Return value names."),
      "return-values"
      )
{}

const char *ReturnValuesOption::name() const
{
  return KEY_NAME;
}

const QCommandLineOption *ReturnValuesOption::ptr() const
{
  return &option_;
}
