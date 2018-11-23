#include "returnvaluesoption.h"

#include <QObject>

ReturnValuesOption::ReturnValuesOption()
  : CmdOption()
  , option_(
      "return-values",
      QObject::tr("Return value names."),
      "return-values"
      )
{}

const QCommandLineOption *ReturnValuesOption::ptr() const
{
  return &option_;
}
