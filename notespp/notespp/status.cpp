#include "notespp/status.h"

#if defined(NT)
#pragma pack(push, 1)
#endif

#include <osmisc.h>

#if defined(NT)
#pragma pack(pop)
#endif

namespace notespp {

Status::Status(STATUS status)
  : std::exception()
  , value_(status)
  , msg_(new char[MAX_MESSAGE_SIZE])
{}

Status::~Status()
{}

Status::Status(const Status &other)
  : std::exception(other)
  , value_(other.value_)
  , msg_(new char[MAX_MESSAGE_SIZE])
{}

Status &Status::operator=(const Status &other)
{
  if (this != &other)
  {
    std::exception::operator =(other);
    value_ = other.value_;
  }
  return *this;
}

Status &Status::operator=(STATUS status)
{
  value_ = status;
  return *this;
}

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

const char *Status::what() const
{
  WORD len = OSLoadString(
        NULLHANDLE,
        error(),
        msg_.data(),
        MAX_MESSAGE_SIZE
        );
  msg_.data()[len] = '\0';
  return msg_.data();
}

} // namespace notespp
