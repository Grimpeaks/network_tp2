#pragma once
#include <iostream>
#include <unordered_set>
#include <optional>
#include "game_object.hpp"
#include "linking_context.hpp"
#include "class_registry.hpp"
#include "utils.hpp"

using PacketTypeID = uint32_t;
using networkID = uint32_t;
using ProtocoleID = uint32_t;
using ptrGameObjt = GameObject*;

enum class PacketType : PacketTypeID {
	Hello = 0x00,
	Sync = 0x01,
	Bye = 0x02,
	PacketType_Max
};

class ReplicationManager
{
public:
	void Replicate(OutputStream& stream, std::vector<ptrGameObjt> list_goptr);
	void Replicate(InputStream& stream);
	LinkingContext m_linkingContext;

private:
	ProtocoleID m_protocolID = 0x4EDC7489;
	std::unordered_set<ptrGameObjt> m_set;
	
	Classregistry* m_classRegistry = Classregistry::get_Instance();
};

