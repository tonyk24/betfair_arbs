#ifndef EXTSITESP_H
#define EXTSITESP_H

#include <list>

#include <QObject>
#include <QString>
#include <QNetworkReply>

class ExtSiteSPOdds
{
public:
  QString m_sportType;
  QString m_league;
  QDateTime m_startTime;
  QString m_title;
  QString m_homeTeam;
  QString m_awayTeam;



  // Odds
  double m_homeOdds;
  double m_awayOdds;
  double m_drawOdds;
};

class ExtSiteSP : public QObject
{
  Q_OBJECT

public:
  ExtSiteSP(QObject *parent = 0);

  void update();
signals:
  void resultUpdated(std::list<ExtSiteSPOdds> result);
public slots:
  void requestReceived(QNetworkReply *reply);
private:
  void parseResult(QString result);
};

#endif // EXTSITESP_H
