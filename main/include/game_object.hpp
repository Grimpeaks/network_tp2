#pragma once

#include <cstdint>

#include "streams.hpp"

using ReplicationClassID = uint32_t;
using PacketTypeID = uint8_t;

#define REPLICATED(id,className)                                    \
enum : ReplicationClassID{mClassID = id};                           \
virtual ReplicationClassID ClassID() const  { return mClassID;}     \
static GameObject* CreateInstance() {return new className();}       \

enum class PacketType : PacketTypeID
{
	Hello = 0x00,
	Sync = 0x01,
	Bye = 0x02,
	PacketType_Max
};

class GameObject
{
public:


private:
	REPLICATED('GOBJ', GameObject)
	virtual void Destroy();
	virtual void Write(OutputStream&);
	virtual void Read(InputStream&);
};