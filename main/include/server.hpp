#pragma once
#include <iostream>
#include <uvw.hpp>
#include <memory>
#include <vector>

class Server
{
public:
	Server();
	Server(std::string, int);

private:
	std::shared_ptr<uvw::Loop> m_loop = nullptr;
	std::shared_ptr<uvw::TCPHandle> m_tcp = nullptr;
	std::vector<std::shared_ptr<uvw::TCPHandle>> m_clients;

	void listen(uvw::Loop& loop, std::string, int);
	void Send(std::shared_ptr<uint8_t>, size_t);
};