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

rx::observable<QStringList> CommandLineParser::parse(
    const QCoreApplication &app
    )
{
  return rx::observable<>::create<QStringList>(
        [this, &app](rx::subscriber<QStringList> o) {
    try {
      QCommandLineParser parser;

      parser.addHelpOption();
      parser.addVersionOption();

      parser.addPositionalArgument("command", QObject::tr("Command"));
      foreach (CmdOption *pOption, optionList_) {
        parser.addOption(*pOption->ptr());
      }
      parser.process(app);

      const QStringList args = parser.positionalArguments();
      foreach (Command *pCmd, cmdList_) {
        QString cmd = pCmd->name();
        if (cmd == args.at(0)) {
          o.on_next(pCmd->exec(parser));
          o.on_completed();
          return;
        }
      }
      throw std::exception("No Command.");
    } catch (...) {
      o.on_error(std::current_exception());
    }
  });
}
