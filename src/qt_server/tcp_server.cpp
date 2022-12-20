#include "tcp_server.h"
#include <QDebug>
#include <QCoreApplication>

tcp_server::tcp_server(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &tcp_server::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 25555)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void tcp_server::slotNewConnection()
{
    std::cout << "New connection" << std::endl;
    Session * newSession = new Session(mTcpServer->nextPendingConnection());
    mSessions.insert(newSession->getSocketDescriptor(), newSession);
    std::cout << newSession->getSocketDescriptor() << std::endl;

    //connect(mTcpSocket[key], &QTcpSocket::readyRead, this, &tcp_server::slotServerRead);
    //connect(mTcpSocket[key], &QTcpSocket::disconnected, this, &tcp_server::slotClientDisconnected);
}
/*
void tcp_server::slotServerRead()
{
    // Read data, emit fast or slow respond
    //while(mTcpSocket[]->bytesAvailable()>0)
    {
        //QByteArray array = mTcpSocket->readAll();

        //mTcpSocket->write(array);
    }
}

void tcp_server::slotServerWrite()
{
    //Send data back to client
}

void tcp_server::slotFastResponse()
{
    //fast response
}

void tcp_server::slotSlowResponse()
{
    //slow response
    //connect(this, &tcp_server::slowResponse, this, &tcp_server::slotServerWrite);
    //connect(timer, &QTimer::timeout, this, [this](){ emit slowResponse(); });
}*/

void tcp_server::slotClientDisconnected()
{
    //mTcpSocket->close();
}
