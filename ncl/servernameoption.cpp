#include "servernameoption.h"

#include <QObject>

ServerNameOption::ServerNameOption()
  : CmdOption()
  , option_("server", QObject::tr("Server name."), "server-name")
{}

const QCommandLineOption *ServerNameOption::ptr() const
{
  return &option_;
}
