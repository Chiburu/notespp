#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>

#include "commandlineparser.h"
#include "getserverlatencycmd.h"
#include "servernameoption.h"
#include "timeoutoption.h"
#include "returnvaluesoption.h"

#include <notespp/main.h>
#include <notespp/status.h>
#include <notespp/string.h>
namespace nx {
using namespace notespp;
}

#define EVALUATE(f,x) f(x)
#define TO_STR_HELPER(s) #s
#define TO_STR(s) QString(EVALUATE(TO_STR_HELPER, s)).split("+").join(" ")

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  app.setApplicationName(TO_STR(PROJECT_PRODUCT));
  app.setApplicationVersion(TO_STR(PROJECT_VERSION));
  app.setOrganizationDomain(TO_STR(PROJECT_DOMAIN));
  app.setOrganizationName(TO_STR(PROJECT_COMPANY));

  QTranslator translator;
  translator.load(QLocale(), "ncl", ".", ":/translations", ".qm");
  app.installTranslator(&translator);

  // Notes C APIを初期化する。
  nx::Main notesMain(argc, argv);

  // コマンドラインパーサを初期化する。
  CommandLineParser cmdParser;
  cmdParser.addCommand(new GetServerLatencyCmd());
  cmdParser.addOption(new ServerNameOption());
  cmdParser.addOption(new TimeoutOption());
  cmdParser.addOption(new ReturnValuesOption());

  QJsonDocument json;
  QTextStream cout(stdout, QIODevice::WriteOnly);
  QTextStream cerr(stderr, QIODevice::WriteOnly);

  try {
    // コマンドラインをパースして、コマンドポインタとオプションデータを取得する。
    ClData cldata = cmdParser.parse(app);

    // 戻り値を分解する。
    Command* pCommand = std::get<0>(cldata);
    QVariantMap options = std::get<1>(cldata);

    // コマンドを実行して戻り値データを取得する。
    QVariantMap retValues = pCommand->exec(std::move(options));

    // 戻り値データをJSON形式にまとめて出力する。
    json.setObject(QJsonObject::fromVariantMap(retValues));
    cout << json.toJson(QJsonDocument::Compact) << endl;
  }
  catch (nx::Status status) {
    // ステータス型例外
    QJsonObject data {
      { "error", status.message().toQString() }
    };
    json.setObject(data);
    cerr << json.toJson(QJsonDocument::Compact) << endl;
  }
  catch (QString e) {
    // QString型例外
    QJsonObject data { { "error", e } };
    json.setObject(data);
    cerr << json.toJson(QJsonDocument::Compact) << endl;
  }
  catch (std::exception ex) {
    // std::exception型例外
    QJsonObject data { { "error", ex.what() } };
    json.setObject(data);
    cerr << json.toJson(QJsonDocument::Compact) << endl;
  }

  return 0;
}
