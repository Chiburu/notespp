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
   * @brief 出力用データクラス
   * @class ReturnValues
   */
  class ReturnValues
  {
  public:
    ReturnValues(
        bool enableVersion,
        bool enableClientToServer,
        bool enableServerToClient
        )
      : version_(0, enableVersion),
        clientToServer_(0, enableClientToServer),
        serverToClient_(0, enableServerToClient)
    {}

    void setValues(
        bool enableVersion,
        bool enableClientToServer,
        bool enableServerToClient
        )
    {
      version_ = Value<WORD>(0, enableVersion);
      clientToServer_ = Value<DWORD>(0, enableClientToServer);
      serverToClient_ = Value<DWORD>(0, enableServerToClient);
    }

    Value<WORD> &version() { return version_; }
    Value<DWORD> &clientToServer() { return clientToServer_; }
    Value<DWORD> &serverToClient() { return serverToClient_; }

  private:
    Value<WORD> version_;
    Value<DWORD> clientToServer_;
    Value<DWORD> serverToClient_;
  };

  /**
   * @brief コンストラクタ
   * @param enableVersion バージョン取得を有効にする
   * @param enableClientToServer クライアントtoサーバを有効にする
   * @param enableServerToClient サーバtoクライアントを有効にする
   */
  explicit GetServerLatency(
      bool enableVersion = true,
      bool enableClientToServer = true,
      bool enableServerToClient = true
      );

  /**
   * @brief 有効値を設定する。
   * @param enableVersion バージョン値取得の有無
   * @param enableClientToServer クライアントtoサーバ待ち時間取得の有無
   * @param enableServerToClient サーバtoクライアント待ち時間取得の有無
   */
  void setValues(
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
      const String &serverName,
      DWORD timeout = 0
      );

private:
  ReturnValues values_;
  String serverName_;
  DWORD timeout_;
};

} // namespace notespp

#endif // NOTESPP_SERVER_H
