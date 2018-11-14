#ifndef NOTESPP_SERVER_H
#define NOTESPP_SERVER_H

#include "notespp_global.h"
#include <rxcpp/rx.hpp>

namespace rx {
using namespace rxcpp;
using namespace rxcpp::operators;
}

namespace notespp {

/**
 * @brief サーバへの待ち時間、サーバからの待ち時間、サーバのバージョンを取得する関数オブジェクト。
 * @class GetServerLatency
 */
class NOTESPPSHARED_EXPORT GetServerLatency
{
public:
  /**
   * @brief 内部管理用値クラス
   * @class InnerValue
   * @tparam T データ型
   */
  template <typename T>
  class InnerValue
  {
  public:
    InnerValue(const T &value, bool enabled)
      : value_(value)
      , enabled_(enabled)
    {}

    T *pValue() { return (enabled_) ? &value_ : nullptr; }
    T value() const { return value_; }

  private:
    T value_;
    bool enabled_;
  };

  /**
   * @brief 出力用データ型
   * @struct ReturnValues
   */
  struct ReturnValues
  {
    WORD version_;
    DWORD clientToServer_;
    DWORD serverToClient_;
  };

  /**
   * @brief コンストラクタ
   * @param enableVersion バージョン取得を有効にする
   * @param enableClientToServer クライアントtoサーバを有効にする
   * @param enableServerToClient サーバtoクライアントを有効にする
   */
  GetServerLatency(
      bool enableVersion = true,
      bool enableClientToServer = true,
      bool enableServerToClient = true
      );

  /**
   * @brief 関数を実行する。
   * @param serverName サーバ名
   * @param timeout タイムアウト時間(0ならデフォルト)
   * @return ReturnValuesを流すObservable
   */
  rx::observable<ReturnValues> operator ()(
      const QByteArray &serverName,
      DWORD timeout = 0
      );

private:
  InnerValue<WORD> version_;
  InnerValue<DWORD> clientToServer_;
  InnerValue<DWORD> serverToClient_;
};

} // namespace notespp

#endif // NOTESPP_SERVER_H
