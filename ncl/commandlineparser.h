#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QStringList>

#include <rxcpp/rx.hpp>
namespace rx {
using namespace rxcpp;
using namespace rxcpp::operators;
}

class QCoreApplication;
class Command;
class CmdOption;

class CommandLineParser
{
public:
  CommandLineParser();

  virtual ~CommandLineParser();

  void addCommand(Command *pCommand);

  void addOption(CmdOption *pOption);

  rx::observable<QStringList> parse(const QCoreApplication &app);

private:
  QList<Command*> cmdList_;
  QList<CmdOption*> optionList_;
};

#endif // COMMANDLINEPARSER_H
