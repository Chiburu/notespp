#ifndef COMMAND_H
#define COMMAND_H

class QString;
class QStringList;
class QCommandLineParser;

class Command
{
public:
  Command();

  virtual const char *name() const = 0;

  virtual QStringList exec(const QCommandLineParser &parser) = 0;
};

#endif // COMMAND_H
