#ifndef GETSERVERLATENCYCMD_H
#define GETSERVERLATENCYCMD_H

#include "command.h"

class GetServerLatencyCmd
    : public Command
{
public:
  GetServerLatencyCmd();

  virtual const char *name() const override;

  virtual QStringList exec(const QCommandLineParser &parser) override;
};

#endif // GETSERVERLATENCYCMD_H
