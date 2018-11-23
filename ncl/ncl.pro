QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    commandlineparser.cpp \
    command.cpp \
    cmdoption.cpp \
    getserverlatencycmd.cpp \
    servernameoption.cpp \
    timeoutoption.cpp \
    returnvaluesoption.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# ===== ここまでQtコンソールアプリケーションの既定値 =====

# アプリケーション説明
QMAKE_TARGET_PRODUCT = Notes Commandline
QMAKE_TARGET_DESCRIPTION = Notes Commandline Tool
QMAKE_TARGET_COMPANY = Chiburu Systems
QMAKE_TARGET_COPYRIGHT = (c) 2018 Chiburu Systems

# バージョン設定
VERSION = 0.0.5

VERSIONS = $$split(VERSION, ".")
VER_MAJ = $$member(VERSIONS, 0)
VER_MIN = $$member(VERSIONS, 1)
VER_PAT = $$member(VERSIONS, 2)

# for QCoreApplication Properties
DEFINES += PROJECT_PRODUCT=$$join(QMAKE_TARGET_PRODUCT, +)
DEFINES += PROJECT_COMPANY=$$join(QMAKE_TARGET_COMPANY, +)
DEFINES += PROJECT_DOMAIN=chiburu.com
DEFINES += PROJECT_VERSION=$$VERSION

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

DISTFILES += \
    ncl.ja_JP.ts

RESOURCES += \
    ncl.qrc

# notespp
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../notespp/release/
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../notespp/debug/
else:unix: LIBS += -L$$OUT_PWD/../notespp/
LIBS += -lnotespp0
INCLUDEPATH += $$PWD/../notespp
DEPENDPATH += $$PWD/../notespp

# rxcpp
INCLUDEPATH += C:/Users/tkond/Documents/WinAppProjects/RxCpp/Rx/v2/src
DEPENDPATH += C:/Users/tkond/Documents/WinAppProjects/RxCpp/Rx/v2/src

HEADERS += \
    commandlineparser.h \
    command.h \
    cmdoption.h \
    getserverlatencycmd.h \
    servernameoption.h \
    timeoutoption.h \
    returnvaluesoption.h
