#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <math.h>

#include "game_object.hpp"

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
	uint16_t i;
};

class Player : GameObject
{
public:


private:
	REPLICATED('PLAY', Player) // ???????????

	std::string name;
	position playerPos;
	rotation playerRot;

	void Write(OutputStream&) override;
	void Read(InputStream&) override;
	uint32_t packFloatPos(float);
	uint16_t packFloatRot(float);
	float unpackFloatPos(uint32_t);
	float unpackFloatRot(uint16_t);
	compRotation packQuaternion(rotation);
	rotation  Player::unpackRotation(compRotation);
	uint32_t bytesToInt32(gsl::span<std::byte>);
	std::vector<std::byte> spanToVector(gsl::span<std::byte>);
};