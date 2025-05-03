#include <QCoreApplication>
#include <QTcpSocket>
#include <QDebug>
#include <iostream>

class Client : public QObject {

public:

  Client(std::string ip, int port_num) {
    QTcpSocket *socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, [socket]() {
      socket->write("Hello from client!");    // Lambda
      socket->flush();
    });

    connect(socket, &QTcpSocket::readyRead, this, [socket]() {
      QByteArray data = socket->readAll();    // Lambda
      qDebug() << "Received from server:" << data;
    });

    socket->connectToHost(ip.c_str(), port_num);

    sendMessage(socket, this);
  }

  int sendMessage(QTcpSocket *socket, Client *example){
    std::string msg;


    if (!socket->waitForConnected()) {
      std::cerr << "Connection failed!" << std::endl;
      return 1;
    }

    while(1){
      if(!socket->waitForReadyRead()){
        std::cerr << "No response from server." << std::endl;
        return 1;
      }

      QByteArray data = socket->readAll();
      std::cout << data.toStdString() << std::endl;


      std::getline(std::cin, msg);

      socket->write(msg.c_str());
      socket->flush();
    }

    return 0;
  }
};

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  Client client("127.0.0.1", 8080);

  return a.exec();
}
