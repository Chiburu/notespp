#ifndef NOTESPP_SERVER_H
#define NOTESPP_SERVER_H

#include <notespp/string.h>
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
  class Value
  {
  public:
    Value(const T &value, bool enabled)
      : value_(value)
      , enabled_(enabled)
    {}

    T *pValue() { return (enabled_) ? &value_ : nullptr; }
    T value() const { return value_; }
    bool enabled() const { return enabled_; }

  private:
    T value_;
    bool enabled_;
  };

  /**
   * @brief 出力用データ構造体
   * @struct ReturnValues
   */
  struct ReturnValues
  {
    Value<WORD> version_;
    Value<DWORD> clientToServer_;
    Value<DWORD> serverToClient_;
    ReturnValues(bool bVersion, bool bC2S, bool bS2C)
      : version_(0, bVersion),
        clientToServer_(0, bC2S),
        serverToClient_(0, bS2C)
    {}
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
      String &&serverName,
      DWORD timeout = 0
      );

private:
  ReturnValues values_;
};

} // namespace notespp

#endif // NOTESPP_SERVER_H
