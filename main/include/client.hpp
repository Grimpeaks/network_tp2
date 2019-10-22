#pragma once
#include <iostream>
#include <uvw.hpp>
#include <memory>

class Client
{
public:
	Client();
	Client(std::string, int);

private:
	std::shared_ptr<uvw::Loop> m_loop = nullptr;
	std::shared_ptr<uvw::TCPHandle> m_tcp = nullptr;

	void conn(uvw::Loop&, std::string, int);
};