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

//#include <QtDebug>

namespace notespp {

GetServerLatency::GetServerLatency(
    bool enableVersion,
    bool enableClientToServer,
    bool enableServerToClient
    )
  : values_(enableVersion, enableClientToServer, enableServerToClient)
{
//  qDebug() << "Creating GetServerLatency[default]." << this;
}

GetServerLatency::GetServerLatency(const GetServerLatency &other)
  : values_(other.values_)
{
//  qDebug() << "Creating GetServerLatency[copy].";
}

GetServerLatency &GetServerLatency::operator =(const GetServerLatency &other)
{
//  qDebug() << "Creating GetServerLatency[=]." << this;
  if (this != &other) {
    values_ = other.values_;
  }
  return *this;
}

GetServerLatency::GetServerLatency(GetServerLatency &&other)
  : values_(std::move(other.values_))
{
//  qDebug() << "Creating GetServerLatency[move]." << this;
}

GetServerLatency &GetServerLatency::operator =(GetServerLatency &&other)
{
//  qDebug() << "Creating GetServerLatency[m=]." << this;
  if (this != &other) {
    values_ = std::move(other.values_);
  }
  return *this;
}

GetServerLatency::~GetServerLatency()
{
//  qDebug() << "Deleting GetServerLatency." << this;
}

void GetServerLatency::setValues(
    bool enableVersion,
    bool enableClientToServer,
    bool enableServerToClient
    )
{
  values_.setValues(enableVersion, enableClientToServer, enableServerToClient);
}

rx::observable<GetServerLatency::ReturnValues> GetServerLatency::operator ()(
    String &&serverName,
    DWORD timeout
    )
{
//  qDebug() << "Calling GetServerLatency::operator ()." << this;
  return rx::observable<>::create<GetServerLatency::ReturnValues>(
        [this, serverName_ = std::move(serverName), timeout_ = timeout]
        (rx::subscriber<GetServerLatency::ReturnValues> o) {
//    qDebug() << "Calling rx::observable<>::create<GetServerLatency::ReturnValues>." << this;
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
