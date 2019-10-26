
#pragma once
#include <iostream>
#include <unordered_set>
#include "game_object.hpp"
#include "linking_context.hpp"
#include "utils.hpp"
using PacketTypeID = uint32_t;
enum class PacketType : PacketTypeID {
	Hello = 0x00,
	Sync = 0x01,
	Bye = 0x02,
	PacketType_Max
};
using gameObjt_ptr = std::shared_ptr<GameObject>;
class ReplicationManager
{
public:
	void Replicate(OutputStream& stream, std::vector<gameObjt_ptr> list_goptr);
private:
	
	uint32_t m_protocolID = 0x4EDC7489;
	std::unordered_set<gameObjt_ptr> m_set;
	LinkingContext m_linkingContext = LinkingContext();
};

