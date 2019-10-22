#include "client.hpp"

Client::Client()
{
	conn(*m_loop, "127.0.0.1", 4242);
	m_loop->run();
}

Client::Client(std::string IP, int port)
{
	conn(*m_loop, IP, port);
	m_loop->run();
}

void Client::conn(uvw::Loop &loop, std::string IP, int port) {
	m_tcp = loop.resource<uvw::TCPHandle>();

	m_tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent &, uvw::TCPHandle &) { /* handle errors */ });

	//m_tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent &, uvw::TCPHandle &tcp) {
 //       auto dataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
 //       tcp.write(std::move(dataWrite), 2);
 //       tcp.close();
 //   });

	m_tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle &){
        //std::cout << evt.data << std::endl;
		//Quand le serveur envoie une donnée, vous devez désérialiser cette donnée au moyen d’un gestionnaire de réplication.
    });

	m_tcp->connect(IP, port);
}