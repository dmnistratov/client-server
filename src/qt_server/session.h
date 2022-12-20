#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QTcpSocket>
#include <iostream>

#include "../../proto/messages.pb.h"

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QTcpSocket* socket, QObject *parent = nullptr);
    //~Session();

signals:
    //void updateConnections();

public:
    //void setConnections(int connections);
    qintptr getSocketDescriptor();

public slots:
    void slotServerRead();
    void slotServerWrite();

private:
    QTcpSocket* socket_;
    int connections_;
    TestTask::Messages::WrapperMessage* message_;

};

#endif // SESSION_H
