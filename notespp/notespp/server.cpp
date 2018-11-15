#include "notespp/server.h"
#include "notespp/status.h"

#include <QByteArray>

#if defined(NT)
#pragma pack(push, 1)
#endif

#include <nsfdb.h>

#if defined(NT)
#pragma pack(pop)
#endif

namespace notespp {

GetServerLatency::GetServerLatency(
    bool enableVersion,
    bool enableClientToServer,
    bool enableServerToClient
    )
  : version_(0, enableVersion)
  , clientToServer_(0, enableClientToServer)
  , serverToClient_(0, enableServerToClient)
{}

rx::observable<GetServerLatency::ReturnValues> GetServerLatency::operator ()(
    const String &serverName,
    DWORD timeout
    )
{
  return rx::observable<>::create<GetServerLatency::ReturnValues>(
        [this, &serverName, &timeout](rx::subscriber<GetServerLatency::ReturnValues> o) {
    try {
      Status status = NSFGetServerLatency(
            const_cast<char*>(serverName.constData()),
            timeout,
            clientToServer_.pValue(),
            serverToClient_.pValue(),
            version_.pValue()
            );
      if (status.hasError())
        throw status;
      GetServerLatency::ReturnValues values;
      values.version_ = version_.value();
      values.clientToServer_ = clientToServer_.value();
      values.serverToClient_ = serverToClient_.value();
      o.on_next(values);
      o.on_completed();
    }
    catch (...) {
      o.on_error(std::current_exception());
    }
  });
}

} // namespace notespp
