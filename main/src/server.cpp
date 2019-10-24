#include "server.hpp"

Server::Server()
{
	listen("127.0.0.1", 4242);
	this->m_ServerThread = std::make_unique<std::thread>([this]() { m_loop->run(); });
}

Server::Server(std::string IP, int port)
{
	listen(IP, port);
	this->m_ServerThread = std::make_unique<std::thread>([this]() { m_loop->run(); }); 
}

Server::~Server()
{
	if (m_ServerThread != nullptr && m_ServerThread->joinable()) {
		m_ServerThread->join();
	}
}

void Server::listen(std::string IP, int port) {
	m_loop = uvw::Loop::getDefault();
	m_tcp = m_loop->resource<uvw::TCPHandle>();

	m_tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { std::cout << "Server : Something went wrong" << std::endl; });

	m_tcp->on<uvw::CloseEvent>([this](const uvw::CloseEvent&, uvw::TCPHandle&) { for (auto& client : m_clients) { client->close(); } });

	m_tcp->on<uvw::ListenEvent>([this](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		client->on<uvw::CloseEvent>([this](const uvw::CloseEvent&, uvw::TCPHandle&) { std::cout << "Server : Client disconnected" << std::endl; });
		srv.accept(*client);
		m_clients.push_back(client);
		std::cout << "Server : Client connected" << std::endl;
		});

	m_tcp->bind(IP, port);
	m_tcp->listen();
}

void Server::Send(uint8_t* data, size_t size)
{
	std::for_each(m_clients.begin(), m_clients.end(), [data, size](std::shared_ptr<uvw::TCPHandle> client) {
		client->write(reinterpret_cast<char*>(data), size);
		});
}