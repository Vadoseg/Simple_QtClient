#ifndef CLIENT_H
#define CLIENT_H

#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>
#include <iostream>

class Client : public QObject {

  public:
    Client(std::string ip, int port_num);
    bool isConnected();
    virtual ~Client();
    virtual void writeMessage(std::string mesgToSend);
    virtual void readMessage();

    // virtual void onConnectDo();


  private:
    int Connect(QTcpSocket *socket);
    bool connectStatus = 0;
    QTcpSocket *socket;


};

#endif // CLIENT_H
