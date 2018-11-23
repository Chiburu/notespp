#include "getserverlatencycmd.h"
#include <QCommandLineParser>
#include <notespp/status.h>
#include <notespp/server.h>
namespace nx {
using namespace notespp;
}

GetServerLatencyCmd::GetServerLatencyCmd()
  : Command()
{}

const char *GetServerLatencyCmd::name() const
{
  return "get-server-latency";
}

QStringList GetServerLatencyCmd::exec(const QCommandLineParser &parser)
{
  if (!parser.isSet("server")) {
    return QStringList() << QObject::tr("No server name.");
  }
  QString server = parser.value("server");

  DWORD timeout = 0;
  if (parser.isSet("timeout")) {
    timeout = static_cast<DWORD>(parser.value("timeout").toULong());
  }

  bool bVer = false;
  bool bC2S = false;
  bool bS2C = false;
  if (parser.isSet("return-values")) {
    QStringList retValues = parser.value("return-values").split(",");
    if (retValues.contains("ver"))
      bVer = true;
    if (retValues.contains("c2s"))
      bC2S = true;
    if (retValues.contains("s2c"))
      bS2C = true;
  }
  if (!bVer && !bC2S && !bS2C) {
    return QStringList() << QObject::tr("No return values.");
  }

  QStringList retList;

  // notesppからAPI関数を実行する。
  nx::GetServerLatency getServerLatency(bVer, bC2S, bS2C);
  getServerLatency(nx::String::fromQString(server), timeout).subscribe(
        [&retList](nx::GetServerLatency::ReturnValues values) {
    if (values.version().enabled())
      retList << QObject::tr("Build version: %1").arg(values.version().value());
    if (values.clientToServer().enabled())
      retList << QObject::tr("Client to Server: %1")
                 .arg(values.clientToServer().value());
    if (values.serverToClient().enabled())
      retList << QObject::tr("Server to Client: %1")
                 .arg(values.serverToClient().value());
  }
  , [&retList](std::exception_ptr ep) {
    try {std::rethrow_exception(ep);}
    catch (nx::Status status) {
      retList << nx::String(status.what()).toQString();
    }
  });
  return retList;
}
