#ifndef CMDOPTION_H
#define CMDOPTION_H

#include <QCommandLineOption>

/**
 * @brief コマンドオプションクラス
 * @class CmdOption
 */
class CmdOption
{
public:
  /**
   * @brief オプション名を返す。
   * @return オプション名
   */
  virtual const char *name() const = 0;

  /**
   * @brief オプションオブジェクトへのポインタを返す。
   * @return オプションオブジェクトへのポインタ
   */
  virtual const QCommandLineOption *ptr() const = 0;
};

#endif // CMDOPTION_H
