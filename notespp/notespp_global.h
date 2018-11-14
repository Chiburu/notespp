#ifndef NOTESPP_GLOBAL_H
#define NOTESPP_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QScopedPointer>

#if defined(NOTESPP_LIBRARY)
#  define NOTESPPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NOTESPPSHARED_EXPORT Q_DECL_IMPORT
#endif

#if defined(NT)
#pragma pack(push, 1)
#endif

#include <global.h>

#if defined(NT)
#pragma pack(pop)
#endif

/**
 * @brief 文字列配列用スコープドスマートポインタ
 */
using CharArrayPtr = QScopedPointer<char, QScopedPointerArrayDeleter<char>>;

#endif // NOTESPP_GLOBAL_H
