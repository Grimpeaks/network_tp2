#pragma once

#include <cstdint>

#include "streams.hpp"

using ReplicationClassID = uint32_t;



#define REPLICATED(id,className)                                    \
enum : ReplicationClassID{mClassID = id};                           \
virtual ReplicationClassID ClassID() const  { return mClassID;}     \
static GameObject* CreateInstance() {return new className();}       \

struct position
{
	float x;
	float y;
	float z;
};

struct compPosition
{
	uint32_t x;
	uint32_t y;
	uint32_t z;
};

struct rotation
{
	float x;
	float y;
	float z;
	float w;
};

struct compRotation
{
	uint16_t a;
	uint16_t b;
	uint16_t c;
	uint8_t i;
};


class GameObject
{
public:
	REPLICATED('GOBJ', GameObject)

	virtual void Destroy() {};
	virtual void Write(OutputStream&) {};
	virtual void Read(InputStream&) {};

private:
	
};