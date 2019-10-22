#include "client.hpp"

Client::Client()
{
	conn("127.0.0.1", 4242);
	m_loop->run();
}

Client::Client(std::string IP, int port)
{
	conn(IP, port);
	m_loop->run();
}

void Client::conn(std::string IP, int port) {
	m_loop = uvw::Loop::getDefault();
	m_tcp = m_loop->resource<uvw::TCPHandle>();

	m_tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent &, uvw::TCPHandle &) { std::cout << "An error occured" << std::endl; });

	m_tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent &, uvw::TCPHandle &tcp) {
        auto dataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
        tcp.write(std::move(dataWrite), 2);
        tcp.close();
		std::cout << "Connect" << std::endl;
    });

	m_tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle &){
        std::cout << evt.data << std::endl;
		std::cout << "Data" << std::endl;
		//Quand le serveur envoie une donnée, vous devez désérialiser cette donnée au moyen d’un gestionnaire de réplication.
    });

	m_tcp->connect(IP, port);
}