#-------------------------------------------------
#
# Project created by QtCreator 2018-11-14T15:14:43
#
#-------------------------------------------------

QT       -= gui

TARGET = notespp
TEMPLATE = lib

DEFINES += NOTESPP_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    notespp/string.cpp \
    notespp/status.cpp \
    notespp/server.cpp \
    notespp/main.cpp

HEADERS += \
    notespp/string.h \
    notespp/status.h \
    notespp/server.h \
    notespp/notespp_global.h \
    notespp/main.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

# ===== ここまでQtコンソールアプリケーションの既定値 =====

# アプリケーション説明
QMAKE_TARGET_PRODUCT = Notes Commandline
QMAKE_TARGET_DESCRIPTION = Notes Commandline Tool
QMAKE_TARGET_COPYRIGHT = (c) Chiburu Systems

# バージョン設定
VERSION = 0.0.2

# 翻訳ファイル
TRANSLATIONS += ncl.ja_JP.ts

# Notes C APIのインストール先(区切りはWindowsでもスラッシュ)
NOTES_C_API_DIR = Z:/Users/Shared/notesapi

# Notes C APIのインクルードファイルの場所
INCLUDEPATH += $$NOTES_C_API_DIR/include
DEPENDPATH += $$NOTES_C_API_DIR/include

# Windowsの場合
win32 {
  # Windowsに必要なシンボル
  DEFINES += W W32 NT
  # 不要な警告を非表示
  QMAKE_CXXFLAGS += -wd4503 -wd4005
  # 64ビット版
  contains(QMAKE_TARGET.arch, x86_64) {
    DEFINES += W64 ND64 _AMD64_
    LIBS += -L$$NOTES_C_API_DIR/lib/mswin64/
  }
  # 32ビット版
  else {
    LIBS += -L$$NOTES_C_API_DIR/lib/mswin32/
  }
}

# OS共通のリンクライブラリ
LIBS += -lnotes

# rxcpp
INCLUDEPATH += C:/Users/tkond/Documents/WinAppProjects/RxCpp/Rx/v2/src
DEPENDPATH += C:/Users/tkond/Documents/WinAppProjects/RxCpp/Rx/v2/src
