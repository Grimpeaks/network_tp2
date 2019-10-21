#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <math.h>

#include "game_object.hpp"

class Player : GameObject
{
public:


private:
	Player();

	REPLICATED('PLAY', Player)

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
	rotation unpackRotation(compRotation);
	uint32_t bytesToInt32(gsl::span<std::byte>);
};