#include "tcp_server.h"
#include <QDebug>
#include <QCoreApplication>

tcp_server::tcp_server(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &tcp_server::slotNewSession);

    if(!mTcpServer->listen(QHostAddress::Any, 25555)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void tcp_server::slotNewSession()
{
    Session * newSession = new Session(mTcpServer->nextPendingConnection());
    mSessions.insert(newSession->getSocketDescriptor(), newSession);
    connect(newSession, &Session::updateConnections, this, &tcp_server::updateSocketConnections);
    connect(newSession, &Session::sessionClosed, this, &tcp_server::slotCloseSession);
}

void tcp_server::slotCloseSession(qintptr descriptor)
{
    delete mSessions[descriptor];
    mSessions.remove(descriptor);
}

void tcp_server::updateSocketConnections(qintptr descriptor)
{
    mSessions.value(descriptor)->setConnections(mSessions.size());
}
