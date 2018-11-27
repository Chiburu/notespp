#ifndef NOTESPP_STATUS_H
#define NOTESPP_STATUS_H

#include <notespp/notespp_global.h>

namespace notespp {

class String;

class NOTESPPSHARED_EXPORT Status
{
public:
  /**
   * @brief コンストラクタ
   * @param status ステータス値
   */
  Status(STATUS status = NOERROR);

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
   * @brief エラーメッセージ文字列を返す。
   * @return エラーメッセージ文字列
   */
  String message() const;

  /**
   * @brief STATUS値からの代入演算子
   * @param status STATUS値
   * @return Statusオブジェクト
   */
  Status &operator=(STATUS status);

private:
  STATUS value_;
};

} // namespace notespp

#endif // NOTESPP_STATUS_H
