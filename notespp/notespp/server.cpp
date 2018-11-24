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
  : values_(enableVersion, enableClientToServer, enableServerToClient)
  , serverName_()
  , timeout_(0)
{}

void GetServerLatency::setValues(
    bool enableVersion,
    bool enableClientToServer,
    bool enableServerToClient
    )
{
  values_.setValues(enableVersion, enableClientToServer, enableServerToClient);
}

rx::observable<GetServerLatency::ReturnValues> GetServerLatency::operator ()(
    const String &serverName,
    DWORD timeout
    )
{
  serverName_ = serverName;
  timeout_ = timeout;
  return rx::observable<>::create<GetServerLatency::ReturnValues>(
        [this]
        (rx::subscriber<GetServerLatency::ReturnValues> o) {
    try {
      Status status = NSFGetServerLatency(
            const_cast<char*>(serverName_.constData()),
            timeout_,
            values_.clientToServer().pValue(),
            values_.serverToClient().pValue(),
            values_.version().pValue()
            );
      if (status.hasError())
        throw status;
      o.on_next(values_);
      o.on_completed();
    }
    catch (...) {
      o.on_error(std::current_exception());
    }
  });
}

} // namespace notespp
