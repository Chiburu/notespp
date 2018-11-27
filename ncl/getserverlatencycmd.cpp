#include "getserverlatencycmd.h"
#include <QCommandLineParser>
#include <notespp/status.h>

GetServerLatencyCmd::GetServerLatencyCmd()
{}

const char *GetServerLatencyCmd::name() const
{
  return "get-server-latency";
}

QVariantMap GetServerLatencyCmd::exec(QVariantMap &&options)
{
  if (!options.contains("server"))
    throw QObject::tr("No server name.");
  QString server = options.value("server").toString();

  DWORD timeout = 0;
  if (options.contains("timeout"))
    timeout = static_cast<DWORD>(options.value("timeout").toUInt());

  bool bVersion = false;
  bool bClientToServer = false;
  bool bServerToClient = false;
  if (options.contains("return-values")) {
    QStringList retValues = options
        .value("return-values")
        .toString()
        .split(",");
    if (retValues.contains("ver"))
      bVersion = true;
    if (retValues.contains("c2s"))
      bClientToServer = true;
    if (retValues.contains("s2c"))
      bServerToClient = true;
  }
  if (!bVersion && !bClientToServer && !bServerToClient)
    throw QObject::tr("No return values.");

  QVariantMap retValues;
  std::exception_ptr ep;
  nx::GetServerLatency(bVersion, bClientToServer, bServerToClient)(
        nx::String::fromQString(server), timeout).subscribe(
        [&retValues](nx::GetServerLatency::ReturnValues values)
  {
    if (values.version_.enabled())
      retValues.insert(
            "version",
            static_cast<uint>(values.version_.value())
            );
    if (values.clientToServer_.enabled())
      retValues.insert(
            "clientToServer",
            static_cast<uint>(values.clientToServer_.value())
            );
    if (values.serverToClient_.enabled())
      retValues.insert(
            "serverToClient",
            static_cast<uint>(values.serverToClient_.value())
            );
  },
  [&ep](std::exception_ptr exp) { ep = exp; }
  );
  if (ep) { std::rethrow_exception(ep); }
  return retValues;
}
