
#include "client.h"

Client::Client(std::string ip, int port_num) {

  socket = new QTcpSocket(this);

         // connect(socket, &QTcpSocket::readyRead, this, [socket]() {
         //   QByteArray data = socket->readAll();    // Lambda
         //   qDebug() << "Received from server:" << data;
         // });



  socket->connectToHost(ip.c_str(), port_num);

  Connect(socket);
}

Client::~Client(){}

int Client::Connect(QTcpSocket *socket){

  if (!socket->waitForConnected()) {
    std::cerr << "Connection failed!" << std::endl;
    connectStatus = 0;
    return 1;
  }

  connectStatus = 1;

  return 0;
}

bool Client::isConnected(){
  return connectStatus;
}

// void Client::onConnectDo(){

//   connect(socket, &QTcpSocket::connected, this, [this]() {
//     socket->write("SUP");    // Lambda
//     socket->flush();
//   });

// }

void Client::writeMessage(std::string mesgToSend){
  socket->write(mesgToSend.c_str());
  socket->flush();
}

void Client::readMessage(){}

int main(){
  Client cli("127.0.0.1", 8080);

  cli.writeMessage("TEST");

}
