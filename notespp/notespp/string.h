#ifndef NOTESPP_STRING_H
#define NOTESPP_STRING_H

#include <notespp/notespp_global.h>

#include <QByteArray>

namespace notespp {

/**
 * @brief LMBCS文字列
 * @class String
 */
class NOTESPPSHARED_EXPORT String
{
public:
  /**
   * @brief デフォルトコンストラクタ
   */
  String();

  /**
   * @brief バイナリから作成するコンストラクタ
   * @param pData LMBCS文字列へのポインタ
   * @param size LMBCS文字列のバイト長、ヌル終端していれば省略可能
   */
  String(const char *pData, int size = -1);

  /**
   * @brief QStringに変換する。
   * @return 変換したQString
   */
  QString toQString() const;

  /**
   * @brief 文字数を返す。
   * @return LMBCS文字列の文字数(バイト数ではない)
   */
  int charSize() const;

  /**
   * @brief バイナリデータへのポインタを返す。
   * @return バイナリデータへのポインタ
   */
  const char *constData() const;

  /**
   * @brief QStringからString文字列を作成する。
   * @param qstr 変換するQStringオブジェクト
   * @return 変換したStringオブジェクト
   */
  static String fromQString(const QString &qstr);

private:
  QByteArray bytes_;
};

/**
 * @brief LMBCS変換関数オブジェクトの基底クラス
 */
class TranslateLmbcs
{
public:
  /**
   * @brief コンストラクタ
   * @param bufferSize バッファサイズ
   */
  TranslateLmbcs(WORD bufferSize = MAXWORD - 1);

  /**
   * @brief 文字列を指定したモードで変換する。
   * @param mode 変換モード
   * @param source 変換元の文字列
   * @return 変換後の文字列
   */
  QByteArray translate(WORD mode, const QByteArray &source) const;

protected:
  WORD bufferSize_;
};

/**
 * @brief LMBCS文字列からUnicode(UTF-16)に変換する関数オブジェクト
 */
class NOTESPPSHARED_EXPORT LmbcsToUnicode
    : public TranslateLmbcs
{
public:
  LmbcsToUnicode(WORD bufferSize = MAXWORD - 1);

  QByteArray operator ()(const QByteArray &source) const;
};

/**
 * @brief Unicode(UTF-16)からLMBCS文字列に変換する関数オブジェクト
 */
class NOTESPPSHARED_EXPORT UnicodeToLmbcs
    : public TranslateLmbcs
{
public:
  UnicodeToLmbcs(WORD bufferSize = MAXWORD - 1);

  QByteArray operator ()(const QByteArray &source) const;
};

} // namespace notespp

#endif // NOTESPP_STRING_H
