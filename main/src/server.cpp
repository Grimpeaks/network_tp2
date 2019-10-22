#include "server.hpp"

Server::Server()
{
	listen("127.0.0.1", 4242);
	m_loop->run();
}

Server::Server(std::string IP, int port)
{
	listen(IP, port);
	m_loop->run();
}

void Server::listen(std::string IP, int port) {
	m_loop = uvw::Loop::getDefault();
	m_tcp = m_loop->resource<uvw::TCPHandle>();

	m_tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { std::cout << "An error occured" << std::endl; });

	m_tcp->on<uvw::ListenEvent>([this](const uvw::ListenEvent&, uvw::TCPHandle& srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) { ptr->close(); });
		client->once<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle& client) { client.close(); });
		srv.accept(*client);
		m_clients.push_back(client);
		std::cout << "Listen" << std::endl;
		});

	m_tcp->bind(IP, port);
	m_tcp->listen();
}

void Server::Send(std::shared_ptr<uint8_t> data, size_t size)
{
	std::for_each(m_clients.begin(), m_clients.end(), [data, size](std::shared_ptr<uvw::TCPHandle> client) {
		client->write(reinterpret_cast<char*>(data.get()), size);
		});
}