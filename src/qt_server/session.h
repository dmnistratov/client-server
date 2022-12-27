#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QTcpSocket>
#include <iostream>
#include <QTimer>
#include <QDateTime>

#include "../../proto/messages.pb.h"

using namespace TestTask::Messages;

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QTcpSocket* socket, QObject *parent = nullptr);
    ~Session();

signals:
    void updateConnections(qintptr descriptor);
    void fastRespond();
    void slowRespond();
    void readyWrite(WrapperMessage* respond_message);
    void sessionClosed(qintptr descriptor);

public:
    void setConnections(int connections);
    qintptr getSocketDescriptor();

public slots:
    void slotServerRead();
    void slotServerWrite(WrapperMessage* respond_message);
    void slotFastRespond();
    void slotSlowRespond();

private:
    QTcpSocket* socket_;
    int connections_;
    WrapperMessage* message_;
    QTimer* timer_;

};

#endif // SESSION_H
