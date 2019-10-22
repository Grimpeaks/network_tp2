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

	m_tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { /* handle errors */ });

	m_tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent&, uvw::TCPHandle& tcp) {
		auto dataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
		tcp.write(std::move(dataWrite), 2);
		tcp.close();
		});

	m_tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle&) {
		std::cout << evt.data << std::endl;
		});

	m_tcp->connect(IP, port);
}