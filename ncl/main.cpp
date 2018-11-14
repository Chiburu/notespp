#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextStream>

// Notes C APIのインクルードは、Windowsではアラインメントを1バイトにして読み込む。
#ifdef NT
#pragma pack(push, 1)
#endif

#include <global.h>
#include <nsfdb.h>

#ifdef NT
#pragma pack(pop)
#endif

// 待ち時間を読み取る場合はこのシグネチャを有効にする。
//#define GET_LATENCY_TIME

// 自身で到達させたいサーバ名を設定する。
const char *pServer = "Your/server/name";

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  QTranslator translator;
  translator.load(QLocale(), "ncl", ".", ":/translations", ".qm");
  app.installTranslator(&translator);

  // 標準出力
  QTextStream out(stdout, QIODevice::WriteOnly);

  // Notes C APIを初期化する。
  STATUS initStatus = NotesInitExtended(argc, argv);
  out << QObject::tr("NotesInitExtended status")
      << ": "
      << ERR(initStatus)
      << endl;

  // 戻り値格納変数を用意する。
  WORD serverVersion = 0;
#ifdef GET_LATENCY_TIME
  DWORD clientToServer_ms, serverToClient_ms;
#endif

  // API関数を実行する。
  STATUS status = NSFGetServerLatency(
        const_cast<char*>(pServer),
        0, // <- 既定のタイムアウト時間を指定
#ifdef GET_LATENCY_TIME
        &clientToServer_ms, &serverToClient_ms,
#else
        nullptr, nullptr,
#endif
        &serverVersion
        );
  out << QObject::tr("NSFGetServerLatency status")
      << ": "
      << ERR(status)
      << endl;

  // エラーがあれば終了する。
  if (ERR(status) != NOERROR) {
    return 1;
  }

  // 戻り値を標準出力に表示する。
  out << QObject::tr("Build version of '%1'").arg(pServer)
      << ": "
      << serverVersion
      << endl;
#ifdef GET_LATENCY_TIME
  out << QObject::tr("Latency time for client to server")
      << ": "
      << QString("%1 ms").arg(clientToServer_ms)
      << endl
      << QObject::tr("Latency time for server to client")
      << ": "
      << QString("%1 ms").arg(serverToClient_ms)
      << endl;
#endif

  // Notes C APIを終了する。
  if (ERR(initStatus) == NOERROR)
    NotesTerm();

  return 0;
}
