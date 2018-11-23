#ifndef SERVERNAMEOPTION_H
#define SERVERNAMEOPTION_H

#include "cmdoption.h"

class ServerNameOption
    : public CmdOption
{
public:
  ServerNameOption();

  virtual const QCommandLineOption *ptr() const override;

private:
  QCommandLineOption option_;
};

#endif // SERVERNAMEOPTION_H
