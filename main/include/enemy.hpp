#pragma once

#include <string>

#include "game_object.hpp"

class Enemy : GameObject
{
public:
	REPLICATED('ENEM', Enemy)
	void Write(OutputStream&) override;
	void Read(InputStream&) override;

private:
	std::string name = "NoNameEnemy";
	position enemyPos = { 0,0,0 };
	rotation enemyRot = { 0,0,0,0 };

	uint32_t packFloatPos(float);
	uint16_t packFloatRot(float);
	float unpackFloatPos(uint32_t);
	float unpackFloatRot(uint16_t);
	compRotation packRotation(rotation);
	rotation unpackRotation(compRotation);
};