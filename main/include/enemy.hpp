#pragma once

#include <string>

#include "game_object.hpp"

struct position
{
	float x;
	float y;
	float z;
};

struct rotation
{
	float x;
	float y;
	float z;
	float w;
};

class Enemy : GameObject
{
public:


private:
	REPLICATED(2, Enemy) // ?????????????????????

	std::string name;
	position enemyPos;
	rotation enemyRot;

	void Write(OutputStream&) override;
	void Read(InputStream&) override;
};