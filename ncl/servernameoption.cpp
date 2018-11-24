#include "servernameoption.h"

#include <QObject>

#define KEY_NAME "server"

ServerNameOption::ServerNameOption()
  : option_(
      KEY_NAME,
      QObject::tr("Server name."),
      "server-name"
      )
{}

const char *ServerNameOption::name() const
{
  return KEY_NAME;
}

const QCommandLineOption *ServerNameOption::ptr() const
{
  return &option_;
}
