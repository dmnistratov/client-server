#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>

#include "session.h"


class tcp_server : public QObject
{
    Q_OBJECT
public:
    explicit tcp_server(QObject *parent = nullptr);

public slots:
    void slotNewConnection();
    //void slotServerRead();
    //void slotServerWrite();
    //void slotFastResponse();
    //void slotSlowResponse();
    void slotClientDisconnected();

    //void updateSocketConnections();

signals:
    //void slowResponse();
    //void fastResponse();

private:
    QTcpServer * mTcpServer;
    QMap<qintptr, Session*> mSessions;
};


#endif // TCP_SERVER_H
