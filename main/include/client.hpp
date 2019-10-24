#pragma once
#include <iostream>
#include <uvw.hpp>
//#include <memory>
#include <thread>

class Client
{
public:
	Client();
	Client(std::string, int);
	~Client();

private:
	std::shared_ptr<uvw::Loop> m_loop = nullptr;
	std::shared_ptr<uvw::TCPHandle> m_tcp = nullptr;
	std::unique_ptr<std::thread> m_ClientThread;

	void conn(std::string, int);

};