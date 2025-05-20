#ifndef CLIENT_H
#define CLIENT_H

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>
#include <iostream>
#include <QDataStream>

class Client : public QObject {
    Q_OBJECT

  public:
    explicit Client(std::string ip, int port_num);
    virtual ~Client();
    int checkConnect();
    bool isConnected();

    QTcpSocket *socket;

    virtual void socketWrite(const QByteArray &data);
    virtual void socketRead();

  private:
    bool connectionStatus = 0;

  signals:
    void connectedToServer();
    void connectTimeout();
};

#endif // CLIENT_H
