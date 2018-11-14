#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextStream>

#include <main.h>
#include <server.h>
#include <status.h>
namespace nx {
using namespace notespp;
}

int main(int argc, char *argv[])
{
  // 自身で到達させたいサーバ名を設定する。
  const char *pServer = "Your/Server/Name";

  QCoreApplication app(argc, argv);

  QTranslator translator;
  translator.load(QLocale(), "ncl", ".", ":/translations", ".qm");
  app.installTranslator(&translator);

  // Notes C APIを初期化する。
  nx::Main notesMain(argc, argv);

  // notesppからAPI関数を実行する。
  nx::GetServerLatency getServerLatency(true, true, true);
  getServerLatency(pServer, 0).subscribe(
        [&pServer](nx::GetServerLatency::ReturnValues values) {
    // 標準出力
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << QObject::tr("Build version of '%1'").arg(pServer)
        << ": "
        << values.version_
        << endl
        << QObject::tr("Latency time for client to server")
        << ": "
        << QString("%1 ms").arg(values.clientToServer_)
        << endl
        << QObject::tr("Latency time for server to client")
        << ": "
        << QString("%1 ms").arg(values.serverToClient_)
        << endl;
  }
  , [](std::exception_ptr ep) {
    try {std::rethrow_exception(ep);}
    catch (nx::Status status) {
      // 標準エラー出力
      QTextStream out(stderr, QIODevice::WriteOnly);
      out << QObject::tr("NSFGetServerLatency status")
          << ": "
          << status.error()
          << endl;
    }
  });

  return 0;
}
