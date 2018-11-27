#include "notespp/status.h"
#include "notespp/string.h"

#if defined(NT)
#pragma pack(push, 1)
#endif

#include <osmisc.h>
#include <misc.h>

#if defined(NT)
#pragma pack(pop)
#endif

namespace notespp {

Status::Status(STATUS status)
  : value_(status)
{}

STATUS Status::error() const
{
  return ERR(value_);
}

bool Status::noError() const
{
  return (error() == NOERROR);
}

bool Status::hasError() const
{
  return !noError();
}

bool Status::isRemote() const
{
  return ((STS_REMOTE & error()) != 0);
}

String Status::message() const
{
  CharArrayPtr buffer(new char[MAXSPRINTF]);
  WORD len = OSLoadString(
        NULLHANDLE,
        error(),
        buffer.data(),
        MAXSPRINTF
        );
  return String(buffer.data(), static_cast<int>(len));
}

Status &Status::operator=(STATUS status)
{
  value_ = status;
  return *this;
}

} // namespace notespp
