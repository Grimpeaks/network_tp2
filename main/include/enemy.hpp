#pragma once

#include <string>
#include <iostream>

#include "game_object.hpp"

class Enemy : public GameObject
{
public:
	Enemy() = default;
	REPLICATED('ENEM', Enemy)
	void Write(OutputStream&) override;
	void Read(InputStream&) override;

private:
	std::string name = "NoNameEnemy";
	position enemyPos = { 6.5,4.3,2.1 };
	rotation enemyRot = { 0.615,-0.002,-0.748,0.249 };

	uint32_t packFloatPos(float);
	uint16_t packFloatRot(float);
	float unpackFloatPos(uint32_t);
	float unpackFloatRot(uint16_t);
	compRotation packRotation(rotation);
	rotation unpackRotation(compRotation);
};