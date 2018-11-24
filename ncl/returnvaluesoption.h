#ifndef RETURNVALUESOPTION_H
#define RETURNVALUESOPTION_H

#include "cmdoption.h"
#include <QStringList>

/**
 * @brief 関数か返す値を指定するコマンドラインオプション
 * @class ReturnValuesOption
 */
class ReturnValuesOption
    : public CmdOption
{
public:
  ReturnValuesOption();

  const char *name() const override;

  virtual const QCommandLineOption *ptr() const override;

private:
  QCommandLineOption option_;
};

#endif // RETURNVALUESOPTION_H
