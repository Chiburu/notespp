#ifndef NOTESPP_MAIN_H
#define NOTESPP_MAIN_H

#include "notespp_global.h"

namespace notespp {

class NOTESPPSHARED_EXPORT Main
{
public:
  /**
   * @brief コンストラクタ
   * @param argc コマンドライン引数の数
   * @param argv コマンドライン引数の格納先
   * @details
   *
   * アプリケーション起動時にNotes C APIを初期化します。
   * 初期化に成功していれば、オブジェクトが破棄される際に終了処理が実行されます。
   */
  explicit Main(int argc, char **argv);

  /**
   * @brief デストラクタ
   */
  virtual ~Main();

  /**
   * @brief NotesInitExtended関数を実行します。
   * @param argc コマンドライン引数の数
   * @param argv コマンドライン引数の格納先
   * @return NotesInitExtended関数の戻り値
   */
  static STATUS start(int argc, char **argv);

  /**
   * @brief NotesTerm関数を実行します。
   */
  static void end();

private:
  STATUS result_;

  Main(const Main &);
  Main &operator=(const Main &);
};

} // namespace notespp

#endif // NOTESPP_MAIN_H
