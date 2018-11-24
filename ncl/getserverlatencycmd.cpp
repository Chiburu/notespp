#include "getserverlatencycmd.h"
#include <QCommandLineParser>
#include <notespp/status.h>

GetServerLatencyCmd::GetServerLatencyCmd()
  : getServerLatency_()
{}

const char *GetServerLatencyCmd::name() const
{
  return "get-server-latency";
}

rx::observable<QVariantMap> GetServerLatencyCmd::exec(
    const QVariantMap &options
    )
{
  options_ = options;
  return rx::observable<>::create<InputValues>(
        [this](rx::subscriber<InputValues> o) {
    try {
      InputValues inputValues;
      inputValues.server_ = options_.value("server").toString();
      if (!options_.contains("server")) {
        throw QObject::tr("No server name.");
      }
      inputValues.timeout_ = 0;
      if (options_.contains("timeout")) {
        inputValues.timeout_ = static_cast<DWORD>(
              options_.value("timeout").toUInt()
              );
      }
      inputValues.enableVersion_ = false;
      inputValues.enableClientToServer_ = false;
      inputValues.enableServerToClient_ = false;
      if (options_.contains("return-values")) {
        QStringList retValues = options_
            .value("return-values")
            .toString()
            .split(",");
        if (retValues.contains("ver"))
          inputValues.enableVersion_ = true;
        if (retValues.contains("c2s"))
          inputValues.enableClientToServer_ = true;
        if (retValues.contains("s2c"))
          inputValues.enableServerToClient_ = true;
      }
      if (!inputValues.enabled()) {
        throw QObject::tr("No return values.");
      }
      o.on_next(inputValues);
      o.on_completed();
    }
    catch (...) {
      o.on_error(std::current_exception());
    }
  }).flat_map([this](InputValues inputValues) {
    // notesppからAPI関数を実行する。
    getServerLatency_.setValues(
      inputValues.enableVersion_,
      inputValues.enableClientToServer_,
      inputValues.enableServerToClient_
    );
    return getServerLatency_(
          nx::String::fromQString(inputValues.server_),
          inputValues.timeout_
          );
  }).map([](nx::GetServerLatency::ReturnValues values){
    QVariantMap retValues;
    if (values.version().enabled())
      retValues.insert(
            "version",
            static_cast<uint>(values.version().value())
            );
    if (values.clientToServer().enabled())
      retValues.insert(
            "clientToServer",
            static_cast<uint>(values.clientToServer().value())
            );
    if (values.serverToClient().enabled())
      retValues.insert(
            "serverToClient",
            static_cast<uint>(values.serverToClient().value())
            );
    return retValues;
  });
}
