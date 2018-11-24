#ifndef COMMAND_H
#define COMMAND_H

#include <QVariantMap>
class QCommandLineParser;

#include <rxcpp/rx.hpp>
namespace rx {
using namespace rxcpp;
using namespace rxcpp::operators;
}

/**
 * @brief コマンドクラス
 * @class Command
 */
class Command
{
public:
  /**
   * @brief コマンド文字列
   * @return コマンド文字列を返す。
   */
  virtual const char *name() const = 0;

  /**
   * @brief コマンドの実行
   * @param options オプションデータマップ
   * @return オブザーバブルなQVariantMap
   */
  virtual rx::observable<QVariantMap> exec(
      const QVariantMap &options
      ) = 0;

protected:
  QVariantMap options_;
};

#endif // COMMAND_H
