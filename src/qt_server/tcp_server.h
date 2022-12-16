#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


class tcp_server : public QObject
{
    Q_OBJECT
public:
    explicit tcp_server(QObject *parent = nullptr);

public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotServerWrite();
    void slotFastResponse();
    void slotSlowResponse();
    void slotClientDisconnected();

signals:
    void slowResponse();
    void fastResponse();

private:
    QTcpServer * mTcpServer;
    QMap<int, QTcpSocket*> mTcpSocket;
};


#endif // TCP_SERVER_H
