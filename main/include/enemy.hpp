#pragma once

#include <string>

#include "game_object.hpp"

class Enemy : GameObject
{
public:


private:
	REPLICATED('ENEM', Enemy)

	std::string name;
	position enemyPos;
	rotation enemyRot;

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