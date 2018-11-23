#ifndef TIMEOUTOPTION_H
#define TIMEOUTOPTION_H

#include "cmdoption.h"

class TimeoutOption
    : public CmdOption
{
public:
  TimeoutOption();

  virtual const QCommandLineOption *ptr() const override;

private:
  QCommandLineOption option_;
};

#endif // TIMEOUTOPTION_H
