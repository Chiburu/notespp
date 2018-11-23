#ifndef RETURNVALUESOPTION_H
#define RETURNVALUESOPTION_H

#include "cmdoption.h"
#include <QStringList>

class ReturnValuesOption
    : public CmdOption
{
public:
  ReturnValuesOption();

  virtual const QCommandLineOption *ptr() const override;

private:
  QCommandLineOption option_;
};

#endif // RETURNVALUESOPTION_H
