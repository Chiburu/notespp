#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QVariantMap>

#include <rxcpp/rx.hpp>
namespace rx {
using namespace rxcpp;
using namespace rxcpp::operators;
}

class QCoreApplication;
class Command;
class CmdOption;

typedef std::tuple<Command*,QVariantMap> ClData;

/**
 * @brief コマンドラインパーサ
 * @class CommandLineParser
 */
class CommandLineParser
{
public:
  /**
   * @brief コンストラクタ
   */
  CommandLineParser();

  /**
   * @brief デストラクタ
   */
  virtual ~CommandLineParser();

  /**
   * @brief コマンドを追加する。
   * @param pCommand コマンドへのポインタ
   */
  void addCommand(Command *pCommand);

  /**
   * @brief コマンドオプションを追加する。
   * @param pOption コマンドオプションへのポインタ
   */
  void addOption(CmdOption *pOption);

  /**
   * @brief コマンドラインをパースして、コマンドを実行し、結果を返す。
   * @param app アプリケーション
   * @return コマンドの実行結果
   */
  rx::observable<QVariantMap> parse(const QCoreApplication &app);

private:
  QList<Command*> cmdList_;
  QList<CmdOption*> optionList_;
};

#endif // COMMANDLINEPARSER_H
