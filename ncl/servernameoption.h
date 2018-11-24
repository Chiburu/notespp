#ifndef SERVERNAMEOPTION_H
#define SERVERNAMEOPTION_H

#include "cmdoption.h"

/**
 * @brief サーバ名を指定するコマンドラインオプション
 * @class ServerNameOption
 */
class ServerNameOption
    : public CmdOption
{
public:
  ServerNameOption();

  const char *name() const override;

  virtual const QCommandLineOption *ptr() const override;

private:
  QCommandLineOption option_;
};

#endif // SERVERNAMEOPTION_H
