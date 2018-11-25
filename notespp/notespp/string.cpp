#include "notespp/string.h"

#include <QString>

#if defined(NT)
#pragma pack(push, 1)
#endif

#include <nls.h>
#include <osmisc.h>

#if defined(NT)
#pragma pack(pop)
#endif

//#include <QtDebug>

namespace notespp {

String::String()
  : bytes_()
{
//  qDebug() << "Creating String[default]. len=" << bytes_.size();
}

String::String(const char *pData, int size)
  : bytes_(pData, size)
{
//  qDebug() << "Creating String[bytes]. len=" << bytes_.size();
}

String::String(const String &other)
{
//  qDebug() << "Creating String[copy]. len=" << other.bytes_.size();
  bytes_ = other.bytes_;
}

String &String::operator=(const String &other)
{
//  qDebug() << "Creating String[=]. len=" << other.bytes_.size();
  if (this != &other) {
    bytes_ = other.bytes_;
  }
  return *this;
}

String::String(String &&other)
{
//  qDebug() << "Creating String[move]. len=" << other.bytes_.size();
  bytes_ = std::move(other.bytes_);
}

String &String::operator=(String &&other)
{
//  qDebug() << "Creating String[m=]. len=" << other.bytes_.size();
  if (this != &other) {
    bytes_ = std::move(other.bytes_);
  }
  return *this;
}

String::~String()
{
//  qDebug() << "Deleting String. len=" << bytes_.size();
}

QString String::toQString() const
{
  // 必要なバッファサイズを割り出す。
  WORD bufferSize = static_cast<WORD>(std::min<int>(
        charSize() * sizeof(ushort),
        static_cast<int>(MAXWORD - 1)
        ));

  // 関数オブジェクトLmbcsToUnicodeでUnicode(UTF-16)に変換する。
  QByteArray rawUnicode = LmbcsToUnicode(bufferSize)(bytes_);

  // バイナリ状のUTF-16からQStringオブジェクトを作成する。
  return QString::fromUtf16(
        reinterpret_cast<ushort*>(const_cast<char*>(rawUnicode.constData())),
        rawUnicode.size() / sizeof(ushort)
        );
}

int String::charSize() const
{
  QByteArray s = bytes_.left(MAXWORD - 1);
  WORD numChars = 0;
  NLS_STATUS status = NLS_string_chars(
        reinterpret_cast<const BYTE*>(s.constData())
        , NLS_NULLTERM
        , &numChars
        , OSGetLMBCSCLS()
        );
  if (status != NLS_SUCCESS)
    return -1;

  return static_cast<int>(numChars);
}

const char *String::constData() const
{
  return bytes_.constData();
}

String String::fromQString(const QString &qstr)
{
  // 必要なバッファサイズを割り出す。
  WORD bufferSize = static_cast<WORD>(std::min<int>(
        qstr.size() * 3,
        static_cast<int>(MAXWORD - 1)
        ));

  // QStringをUnicode(UTF-16)にする。
  QByteArray rawUnicode(
        reinterpret_cast<const char*>(qstr.utf16()),
        qstr.size() * 2
        );

  // LMBCS化してStringオブジェクトに変換して返す。
  QByteArray rawLmbcs = UnicodeToLmbcs(bufferSize)(rawUnicode);
  return String(rawLmbcs.constData(), rawLmbcs.size());
}

TranslateLmbcs::TranslateLmbcs(WORD bufferSize)
  : bufferSize_(bufferSize)
{}

QByteArray TranslateLmbcs::translate(
    WORD mode,
    const QByteArray &source
    ) const
{
  CharArrayPtr buffer(new char[bufferSize_]);
  WORD len = OSTranslate(
        mode
        , source.constData()
        , static_cast<WORD>(source.size())
        , buffer.data()
        , bufferSize_
        );
  return QByteArray(buffer.data(), static_cast<int>(len));
}

LmbcsToUnicode::LmbcsToUnicode(WORD bufferSize)
  : TranslateLmbcs(bufferSize)
{}

QByteArray LmbcsToUnicode::operator ()(const QByteArray &source) const
{
  return translate(OS_TRANSLATE_LMBCS_TO_UNICODE, source);
}

UnicodeToLmbcs::UnicodeToLmbcs(WORD bufferSize)
  : TranslateLmbcs(bufferSize)
{}

QByteArray UnicodeToLmbcs::operator ()(const QByteArray &source) const
{
  return translate(OS_TRANSLATE_UNICODE_TO_LMBCS, source);
}

} // namespace notespp
