#include "commandlineparser.h"

#include <QCommandLineParser>
#include "command.h"
#include "cmdoption.h"

CommandLineParser::CommandLineParser()
  : cmdList_()
  , optionList_()
{}

CommandLineParser::~CommandLineParser()
{
  qDeleteAll(cmdList_);
  qDeleteAll(optionList_);
}

void CommandLineParser::addCommand(Command *pCommand)
{
  cmdList_.append(pCommand);
}

void CommandLineParser::addOption(CmdOption *pOption)
{
  optionList_.append(pOption);
}

ClData CommandLineParser::parse(const QCoreApplication &app)
{
  // コマンドラインパーサ(実体)を初期化する。
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();

  // コマンド引数を設定する。
  parser.addPositionalArgument("command", QObject::tr("Command"));

  // オプション引数を設定する。
  foreach (CmdOption *pOption, optionList_) {
    parser.addOption(*pOption->ptr());
  }

  // パースを実行する。
  parser.process(app);

  // オプション引数の指定値をマップにまとめる。
  QVariantMap options;
  foreach (CmdOption *pOption, optionList_) {
    const QCommandLineOption *ptr = pOption->ptr();
    if (parser.isSet(*ptr)) {
      QString value = parser.value(*ptr);
      options.insert(pOption->name(), value);
    }
  }

  // コマンド引数が指定されているか確認する。
  const QStringList args = parser.positionalArguments();
  if (args.isEmpty())
    throw QObject::tr("No Command.");

  // 指定のコマンドが存在するか確認し、あればオプションデータとともに返す。
  foreach (Command *pCmd, cmdList_) {
    QString cmd = pCmd->name();
    if (cmd == args.at(0)) {
      return std::make_tuple(pCmd, options);
    }
  }

  // 指定のコマンドが存在しなければ例外をスローする。
  throw QObject::tr("Not found command.");
}
