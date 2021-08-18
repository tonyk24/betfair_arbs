#include <QElapsedTimer>
#include <QCoreApplication>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>


#include "globalstoragemodel.h"
#include "controller.h"

bool compare_country (const std::pair<QString, QString>& first, const std::pair<QString, QString>& second)
{
  return first.first < second.first;
}

Controller::Controller()
  : m_httpJsonClient(0, "https://api.betfair.com/exchange/betting/json-rpc/v1") {
}

Controller::~Controller() {
}

void Controller::listCompetition() {
  QJsonObject jsonObj;
  jsonObj[QString("jsonrpc")] = QString("2.0");
  jsonObj[QString("id")] = QJsonValue(1);
  jsonObj[QString("method")] = QString("SportsAPING/v1.0/listCompetitions");

  QJsonObject jsonObjParams;

  QJsonObject jsonObjFilter;

  QJsonArray jsonArray;
  jsonArray.append(QJsonValue(1));
  jsonObjFilter[QString("eventTypeIds")] = jsonArray;

  jsonObjParams[QString("filter")] = jsonObjFilter;

  jsonObj[QString("params")] = jsonObjParams;

  QObject::connect(&m_httpJsonClient, SIGNAL(replyFinish(QString)),
                   this, SLOT(replyFinish(QString)));

  m_httpJsonClient.send(jsonObj);
}

std::list<std::pair<QString,QString> > Controller::readCsvFile() {
  std::list<std::pair<QString,QString> > ret;
  QFile inputFile("C:/Users/Tony/Documents/project/Betfair/code/MainBetfairProject/SrcGenerator/inputCsv.csv");
  if (inputFile.open(QIODevice::ReadOnly))
  {
     QTextStream in(&inputFile);
     while (!in.atEnd())
     {
        QString line = in.readLine();
        if (line.trimmed().size() > 0)
        {
          QStringList strList = line.split(",");
          ret.push_back(std::make_pair(strList.at(0), strList.at(1)));
        }
     }
     inputFile.close();
  }
  else
  {
    qDebug() << "Unable to open file: ";
  }
  return ret;
}

void Controller::writeCSV(std::list<std::pair<QString, QString> > mergedList) {
  QFile file("inputCsv.csv");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
      return;

  QTextStream out(&file);

  for (std::list<std::pair<QString, QString> >::iterator it = mergedList.begin();
       it != mergedList.end(); it++) {
    out << it->first << "," << it->second << "\n";
  }
}

void Controller::replyFinish(QString answer) {
  QObject::disconnect(&m_httpJsonClient, SIGNAL(replyFinish(QString)),
                      this, SLOT(replyFinish(QString)));
  QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

  QJsonObject jsonObj = jsonResponse.object();

  std::list<Triple> compList;

  if (jsonObj["result"].isArray())
  {
    QJsonArray jsonArray = jsonObj["result"].toArray();
    for (QJsonArray::iterator it = jsonArray.begin();
         it != jsonArray.end(); it++) {
      QJsonObject compObj = (*it).toObject();
      QJsonObject compItemObj = compObj["competition"].toObject();

      QString competitionRegion =compObj["competitionRegion"].toString();
      QString compId = compItemObj["id"].toString();
      QString compName = compItemObj["name"].toString();

      compList.push_back(Triple(compId, compName, competitionRegion));

      qDebug() << compName << ", " << compId << ", " << competitionRegion;
      /*
      BfEvent bfEvent = BfEvent(QString(eventItemObj["id"].toString()),
          QString(eventItemObj["name"].toString()),
          QString(eventItemObj["countryCode"].toString()),
          QString(eventItemObj["timezone"].toString()),
          QString(eventItemObj["openDate"].toString()));
*/
    }
  }

  // Merge retrieved entries and CSV entries.

  std::list<std::pair<QString, QString> > mergedList = csvList;
  for (std::list<Triple>::iterator it = compList.begin();
       it != compList.end(); it++) {
    QString name=it->m_c + "_" + it->m_b.replace(" ", "_").replace("(", "").replace(")", "").replace(".", "").replace("_-_", "_").replace("'", "").replace("/","");
    QString id = it->m_a;

    mergedList.push_back(std::make_pair(name, id));
  }
  mergedList.sort(compare_country);
  mergedList.unique();

  // Dont start with number
  QRegExp rx("(\\d)");
  for (std::list<std::pair<QString, QString> >::iterator it = mergedList.begin();
       it != mergedList.end(); it++) {
    if (rx.exactMatch(it->first.at(0))) {
      it->first = "Nr" + it->first;
    }
  }
  writeCSV(mergedList);


  ////////////////// PRINT TO FILE
  ///
  writeHeaderFile(mergedList);
}

void Controller::writeHeaderFile(std::list<std::pair<QString, QString> >mergedList) {
  QFile file("bfcompetition.h");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
      return;

  QTextStream out(&file);

  out << "#ifndef BfCompetition_H" << "\n";
  out << "#define BfCompetition_H" << "\n\n";

  out << "#include <list>" << "\n";
  out << "#include <QString>" << "\n\n";

  out << "class BfCompetition {" << "\n";
  out << "  public:" << "\n";
  out << "  enum Competition {" << "\n";
  out << "    ALL=-1,\n";
  out << "    UNKOWN=-2,\n";

  // Print enum
  for (std::list<std::pair<QString, QString> >::const_iterator it = mergedList.begin();
       it != mergedList.end(); it++) {
    out << "    " << it->first
        << "=" << it->second << ",\n";
  }

  out << "  };" << "\n\n";
  out << "  static QString toStr(Competition cp) {" << "\n";

  // Print toStr()
  std::list<std::pair<QString, QString> >::const_iterator it = mergedList.begin();

  if (it != mergedList.end()) {
    QString name=it->first;
    out << "    if (cp == ALL) {" << "\n";
    out << "      return QString(\"ALL\");" << "\n";
    out << "    }" << "";
    out << " else if (cp == " << name << ") {" << "\n";
    out << "      return QString(\"" << name <<"\");" << "\n";
    out << "    }";
    for (; it != mergedList.end(); it++) {
      QString name=it->first;
      out << " else if (cp == " << name << ") {" << "\n";
      out << "      return QString(\"" << name <<"\");" << "\n";
      out << "    }";
    }
    out << "\n";
  }

  out << "    return QString(\"UNDEFINED\");" << "\n";
  out << "  }" << "\n";

  // ---------------------------------------------------------------------------
  // Print int to enum
  // ---------------------------------------------------------------------------
  out << "  static Competition toEnum(int val) {\n";
  it = mergedList.begin();

  if (it != mergedList.end()) {
    QString name = it->first;
    QString id = it->second;

    out << "    if (val == -1) {" << "\n";
    out << "      return ALL;" << "\n";
    out << "    } else if (val == -2) {" << "\n";
    out << "      return UNKOWN;" << "\n";
    out << "    }" << "";
    out << " else if (val == " << id << ") {" << "\n";
    out << "      return " << name <<";\n";
    out << "    }";
    for (; it != mergedList.end(); it++) {
      QString name=it->first;
      QString id = it->second;
      out << " else if (val == " << id << ") {" << "\n";
      out << "      return " << name <<";\n";
      out << "    }";
    }
    out << "\n";
  }

  out << "    return UNKOWN;\n";
  out << "  }\n";

  // ---------------------------------------------------------------------------
  // Print the enums into a single list
  // ---------------------------------------------------------------------------
  out << "  static std::list<Competition> oneList() {\n";
  out << "    std::list<Competition> theList;\n";
  for (std::list<std::pair<QString, QString> >::const_iterator it = mergedList.begin();
       it != mergedList.end(); it++) {
    out << "    theList.push_back(" << it->first << ");\n";
  }
  out << "    return theList;\n";
  out << "  }\n";

  // ---------------------------------------------------------------------------
  // Print split of enums into two lists
  // ---------------------------------------------------------------------------
  out << "  static std::list<Competition> twoListSplit(int side) {\n";
  out << "    std::list<Competition> theList1;\n";
  out << "    std::list<Competition> theList2;\n";
  int counter = 0;
  for (std::list<std::pair<QString, QString> >::const_iterator it = mergedList.begin();
       it != mergedList.end(); it++, counter++) {
    if (counter % 2 == 0) {
      out << "    theList1.push_back(" << it->first << ");\n";
    } else {
      out << "    theList2.push_back(" << it->first << ");\n";
    }
  }
  out << "    if (side == 0) {\n";
  out << "      return theList1;\n";
  out << "    }\n;";
  out << "    return theList2;\n";
  out << "  }\n";

  out << "};" << "\n\n";

  out << "#endif // BfCompetition_H" << "\n";
}

void Controller::run() {
  // Creat configfile
  GlobalStorageModel::saveConfig("", // User
                                 "",          // Pass
                                 "2",                       // UnitCounts
                                 "0",                       // UnitIndex (0-index)
                                 "FpQ3aPEJUKhuzN1x",        // appKey
                                 "9vpYxU95Nl6HoKF4",        // appKeyDelayed
                                 120.0,                     // maxExposure
                                 true);                     // doDataLogging
  GlobalStorageModel::loadConfig();

  QElapsedTimer timer;
  timer.start();

  qint64 lastTime = timer.elapsed();

  csvList = readCsvFile();

  if (csvList.size() == 0) {
    qDebug() << "Expecting non-empty csv file.. exiting...";
    return;
  }
  listCompetition();

  while (true) {
    if (timer.elapsed() - lastTime > 10000) {
      lastTime = timer.elapsed();
      // Get events if less than limit
    }

    QCoreApplication::processEvents();
  }
}

void Controller::aboutToQuitApp() {

}
