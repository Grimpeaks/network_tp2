#include <iostream>
#include <string>

#include "client.hpp"
#include "server.hpp"

int main(int argc, char* argv[])
{
	std::string programType = argv[1];
	std::string IP = argv[2];
	int port = std::stoi(argv[3]);

	std::cout << "Starting the "	<< programType	<< std::endl 
			  << "IP : "			<< IP			<< std::endl 
			  << "Port : "			<< port			<< std::endl;

	if (programType == "client")
	{
		Client tcpClient(IP, port);
	}
	else if (programType == "server")
	{
		Server tcpServer(IP, port);

		//debug
		std::cin.ignore();
		std::array<uint8_t, 20> msgArray = { "Message trop cool" };
		std::uint8_t* message = msgArray.data();
		tcpServer.Send(message, 20);
		//debugEnd
	}
	else
	{
		std::cout << "L'argument 1 du main doit etre : client ou server" << std::endl;
	}
}