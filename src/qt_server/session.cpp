#include "session.h"

Session::Session(QTcpSocket* socket,QObject *parent)
    : QObject{parent}, socket_{socket}
{
    // on slow request emit update connections
    // connect slow & fast emit
    // emit disconnect for tcp_server when socket disconnected
    connect(socket_, &QTcpSocket::readyRead, this, &Session::slotServerRead);
}

// ADD ~Session !!!!!!!!!!!!!!!
qintptr Session::getSocketDescriptor()
{
    return socket_->socketDescriptor();
}

void Session::slotServerRead()
{
    // Add read size
    while(socket_->bytesAvailable()>0)
    {
        QByteArray byte = socket_->readAll();
        QString data = QString(byte);
        message_ = new TestTask::Messages::WrapperMessage();
        message_->ParseFromString(data.toStdString());
        if (message_->has_request_for_fast_response())
            std::cout << "Fast" << std::endl;
            // emit fast respond
        if (message_->has_request_for_slow_response())
            std::cout << "Slow" << std::endl;
            //emit slow respond
       std::string request;
       // Write #TODO
       message_->SerializeToString(&request);
        socket_->write(byte);
    }
}

void Session::slotServerWrite()
{

}
