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
  // 自身で到達させたいサーバ名を設定する。
//  const QString serverName("Your/Server/Name");

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

  CommandLineParser cmdParser;
  cmdParser.addCommand(new GetServerLatencyCmd());
  cmdParser.addOption(new ServerNameOption());
  cmdParser.addOption(new TimeoutOption());
  cmdParser.addOption(new ReturnValuesOption());
  cmdParser.parse(app).subscribe(
        [](QVariantMap retValues) {
    QJsonDocument json;
    json.setObject(QJsonObject::fromVariantMap(retValues));
    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << json.toJson(QJsonDocument::Compact) << endl;
  }, [](std::exception_ptr ep) {
    QTextStream cerr(stderr, QIODevice::WriteOnly);
    try {
      std::rethrow_exception(ep);
    } catch (nx::Status status) {
      QJsonObject data {
        { "error", nx::String(status.what()).toQString() }
      };
      QJsonDocument json;
      json.setObject(data);
      cerr << json.toJson(QJsonDocument::Compact) << endl;
    } catch (QString e) {
      QJsonObject data { {"error", e} };
      QJsonDocument json;
      json.setObject(data);
      cerr << json.toJson(QJsonDocument::Compact) << endl;
    } catch (std::exception ex) {
      QJsonObject data { {"error", ex.what() } };
      QJsonDocument json;
      json.setObject(data);
      cerr << json.toJson(QJsonDocument::Compact) << endl;
    }
  });

  return 0;
}
