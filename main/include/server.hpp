#pragma once
#include <iostream>
#include <uvw.hpp>
//#include <memory>
#include <vector>
#include <thread>

class Server
{
public:
	Server();
	Server(std::string, int);
	~Server();
	
	void Send(uint8_t*, size_t);

private:
	std::shared_ptr<uvw::Loop> m_loop = nullptr;
	std::shared_ptr<uvw::TCPHandle> m_tcp = nullptr;
	std::vector<std::shared_ptr<uvw::TCPHandle>> m_clients;
	std::unique_ptr<std::thread> m_ServerThread;

	void listen(std::string, int);
};