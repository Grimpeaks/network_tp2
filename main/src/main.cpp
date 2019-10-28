#include <iostream>
#include <string>
#include <vector>

#include "client.hpp"
#include "server.hpp"
#include "replication_manager.hpp"
#include "class_registry.hpp"
#include "game_object.hpp"
#include "player.hpp"
#include "enemy.hpp"

int main(int argc, char* argv[])
{
	std::string programType = argv[1];
	std::string IP = argv[2];
	int port = std::stoi(argv[3]);

	std::cout << "Starting the " << programType << std::endl
		<< "IP : " << IP << std::endl
		<< "Port : " << port << std::endl;
		
	Classregistry* m_classRegistry = Classregistry::get_Instance();
	m_classRegistry->RegisterClasse<Player>();
	m_classRegistry->RegisterClasse<Enemy>();

	if (programType == "client")
	{
		Client tcpClient(IP, port);
	}
	else if (programType == "server")
	{
		Server tcpServer(IP, port);
		ReplicationManager m_replicationManager;

		std::cin.ignore();

		std::vector<GameObject*> objPtrVector;
		Player* playerPtr = reinterpret_cast<Player*>(m_classRegistry->Create('PLAY'));
		Enemy* enemyPtr = reinterpret_cast<Enemy*>(m_classRegistry->Create('ENEM'));
		objPtrVector.push_back(reinterpret_cast<GameObject*>(enemyPtr));
		objPtrVector.push_back(reinterpret_cast<GameObject*>(playerPtr));
		m_replicationManager.m_linkingContext.AddTo_Context(reinterpret_cast<GameObject*>(enemyPtr));
		m_replicationManager.m_linkingContext.AddTo_Context(reinterpret_cast<GameObject*>(playerPtr));

		OutputStream streamToSend;
		m_replicationManager.Replicate(streamToSend, objPtrVector);
		tcpServer.Send(reinterpret_cast<uint8_t*>(streamToSend.Data().data()), streamToSend.Size());
	}
	else
	{
		std::cout << "L'argument 1 du main doit etre : client ou server" << std::endl;
	}
}