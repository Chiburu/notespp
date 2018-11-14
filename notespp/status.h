#ifndef NOTESPP_STATUS_H
#define NOTESPP_STATUS_H

#include "notespp_global.h"

namespace notespp {

class NOTESPPSHARED_EXPORT Status
    : public std::exception
{
public:
  /**
   * @brief 文字列に変換する際のバッファサイズです。
   */
  static const size_t MAX_MESSAGE_SIZE = 256;

  /**
   * @brief コンストラクタ
   * @param status ステータス値
   */
  Status(STATUS status = NOERROR);

  /**
   * @brief コピーコンストラクタ
   * @param other コピー元オブジェクト
   */
  Status(const Status &other);

  /**
   * @brief デストラクタ
   */
  virtual ~Status();

  /**
   * @brief フラグを除去した純粋なエラー値です。
   * @return エラー値
   */
  STATUS error() const;

  /**
   * @brief エラーがない場合Trueを返します。
   * @return エラーがない場合はTrue
   */
  bool noError() const;

  /**
   * @brief エラーがある場合Trueを返します。
   * @return エラーがある場合はTrue
   */
  bool hasError() const;

  /**
   * @brief ドミノ側で起きたエラーの場合Trueを返します。
   * @return ドミノ側で起きたエラーの場合True
   */
  bool isRemote() const;

  /**
   * @brief ステータス値からエラーメッセージ文字列を取得します。
   * @return エラーメッセージ文字列へのポインタ
   */
  virtual const char *what() const;

  /**
   * @brief 代入演算子
   * @param other 代入元オブジェクト
   * @return 代入後のオブジェクト
   */
  Status &operator=(const Status &other);

  /**
   * @brief STATUS値からの代入演算子
   * @param status STATUS値
   * @return Statusオブジェクト
   */
  Status &operator=(STATUS status);

private:
  STATUS value_;
  mutable CharArrayPtr msg_;
};

} // namespace notespp

#endif // NOTESPP_STATUS_H
