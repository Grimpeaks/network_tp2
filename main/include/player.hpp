#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <cmath>

#include "game_object.hpp"

class Player : public GameObject
{
public:
	Player() = default;
	REPLICATED('PLAY', Player)
	void Write(OutputStream&) override;
	void Read(InputStream&) override;

private:
	std::string name = "NoNamePlayer";
	position playerPos = { 1.2,3.4,5.6 };
	rotation playerRot = { -0.016,-0.361,0.855,-0.373 };

	uint32_t packFloatPos(float);
	uint16_t packFloatRot(float);
	float unpackFloatPos(uint32_t);
	float unpackFloatRot(uint16_t);
	compRotation packRotation(rotation);
	rotation unpackRotation(compRotation);
	//uint32_t bytesToInt32(gsl::span<std::byte>);
};