#ifndef CMDOPTION_H
#define CMDOPTION_H

#include <QCommandLineOption>

class CmdOption
{
public:
  CmdOption();

  virtual const QCommandLineOption *ptr() const = 0;
};

#endif // CMDOPTION_H
