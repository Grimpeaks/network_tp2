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

	std::string name = "NoNamePlayer";
	position playerPos = { 0,0,0 };
	rotation playerRot = { 0,0,0,0 };

	void Write(OutputStream&) override;
	void Read(InputStream&) override;

	uint32_t packFloatPos(float);
	uint16_t packFloatRot(float);
	float unpackFloatPos(uint32_t);
	float unpackFloatRot(uint16_t);
	compRotation packRotation(rotation);
	rotation unpackRotation(compRotation);
	//uint32_t bytesToInt32(gsl::span<std::byte>);
};