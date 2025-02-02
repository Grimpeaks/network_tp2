#include "client.hpp"

Client::Client()
{
	conn("127.0.0.1", 4242);
	m_ClientThread = std::make_unique<std::thread>([this]() { m_loop->run(); });
}

Client::Client(std::string IP, int port)
{
	conn(IP, port);
	m_ClientThread = std::make_unique<std::thread>([this]() { m_loop->run(); });
}

Client::~Client()
{
	if (m_ClientThread != nullptr && m_ClientThread->joinable()) {
		m_ClientThread->join();
	}
}

void Client::conn(std::string IP, int port) {
	m_loop = uvw::Loop::getDefault();
	m_tcp = m_loop->resource<uvw::TCPHandle>();

	m_tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { std::cout << "Client : Something went wrong" << std::endl; });

	m_tcp->on<uvw::ConnectEvent>([this](const uvw::ConnectEvent&, uvw::TCPHandle& tcp) {
		tcp.read();

		////debug
		//std::cin.ignore();
		//m_tcp->close();
		////
		});

	m_tcp->on<uvw::DataEvent>([this](const uvw::DataEvent& evt, uvw::TCPHandle&) {
		gsl::span<char> receivedData(evt.data.get(), evt.length);
		InputStream receivedStream(receivedData);
		m_replicationManager.Replicate(receivedStream);
		});

	m_tcp->connect(IP, port);
}