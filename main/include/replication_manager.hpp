
#pragma once
#include <iostream>
#include <unordered_set>
#include "game_object.hpp"
#include "linking_context.hpp"
#include "utils.hpp"

using gameObjt = std::shared_ptr<GameObject>;
class ReplicationManager
{
public:
	void Replicate(OutputStream& stream, std::vector<gameObjt> list_goptr);
	void Replicate(MemoryStream memo);

private:
	enum class PacketType : uint32_t {
		Hello = 0x00,
		Sync = 0x01,
		Bye = 0x02,
		PacketType_Max
	};
	uint32_t m_protocolID = 0x4EDC7489;
	std::unordered_set<gameObjt> m_set;
	LinkingContext m_linkingContext = LinkingContext();
};

