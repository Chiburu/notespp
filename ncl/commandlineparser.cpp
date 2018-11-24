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

rx::observable<QVariantMap> CommandLineParser::parse(
    const QCoreApplication &app
    )
{
  return rx::observable<>::create<ClData>(
        [this, &app](rx::subscriber<ClData> o) {
    try {
      QCommandLineParser parser;
      parser.addHelpOption();
      parser.addVersionOption();

      parser.addPositionalArgument("command", QObject::tr("Command"));
      foreach (CmdOption *pOption, optionList_) {
        parser.addOption(*pOption->ptr());
      }
      parser.process(app);
      QVariantMap options;
      foreach (CmdOption *pOption, optionList_) {
        const QCommandLineOption *ptr = pOption->ptr();
        if (parser.isSet(*ptr)) {
          QString value = parser.value(*ptr);
          options.insert(pOption->name(), value);
        }
      }
      const QStringList args = parser.positionalArguments();
      if (args.isEmpty())
        throw QObject::tr("No Command.");
      foreach (Command *pCmd, cmdList_) {
        QString cmd = pCmd->name();
        if (cmd == args.at(0)) {
          o.on_next(std::make_tuple(pCmd, options));
          o.on_completed();
          return;
        }
      }
      throw QObject::tr("Not found command.");
    } catch (...) {
      o.on_error(std::current_exception());
    }
  }).flat_map([](ClData cldata) {
    Command *pCmd = std::get<0>(cldata);
    QVariantMap options = std::get<1>(cldata);
    return pCmd->exec(options);
  });
}
