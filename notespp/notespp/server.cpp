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
    bool bVersion,
    bool bC2S,
    bool bS2C
    )
  : values_(bVersion, bC2S, bS2C)
{}

rx::observable<GetServerLatency::ReturnValues> GetServerLatency::operator ()(
    String &&serverName,
    DWORD timeout
    )
{
  return rx::observable<>::create<GetServerLatency::ReturnValues>(
        [this, serverName_ = std::move(serverName), timeout_ = timeout]
        (rx::subscriber<GetServerLatency::ReturnValues> o) {
    try {
      Status status = NSFGetServerLatency(
            const_cast<char*>(serverName_.constData()),
            timeout_,
            values_.clientToServer_.pValue(),
            values_.serverToClient_.pValue(),
            values_.version_.pValue()
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
