#ifndef TIMEOUTOPTION_H
#define TIMEOUTOPTION_H

#include "cmdoption.h"

/**
 * @brief タイムアウト時間を指定するコマンドラインオプション
 * @class TimeoutOption
 */
class TimeoutOption
    : public CmdOption
{
public:
  TimeoutOption();

  const char *name() const override;

  virtual const QCommandLineOption *ptr() const override;

private:
  QCommandLineOption option_;
};

#endif // TIMEOUTOPTION_H
