#ifndef GETSERVERLATENCYCMD_H
#define GETSERVERLATENCYCMD_H

#include "command.h"
#include <notespp/server.h>
namespace nx {
using namespace notespp;
}

/**
 * @brief サーバと通信するときの待ち時間を返すコマンド
 * @class GetServerLatencyCmd
 */
class GetServerLatencyCmd
    : public Command
{
public:
  /**
   * @brief コマンド入力値の構造体
   */
  struct InputValues {
    QString server_;
    DWORD timeout_;
    bool enableVersion_;
    bool enableClientToServer_;
    bool enableServerToClient_;
    bool enabled() const {
      return enableVersion_ || enableClientToServer_ || enableServerToClient_;
    }
  };

  /**
   * @brief コンストラクタ
   */
  GetServerLatencyCmd();

  /**
   * @brief コマンド文字列
   * @return コマンド文字列を返す。
   */
  virtual const char *name() const override;

  /**
   * @brief コマンドの実行
   * @param options オプションデータマップ
   * @return オブザーバブルなQVariantMap
   */
  virtual rx::observable<QVariantMap> exec(
      const QVariantMap &options
      ) override;

private:
  nx::GetServerLatency getServerLatency_;
};

#endif // GETSERVERLATENCYCMD_H
