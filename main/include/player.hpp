#pragma once

#include <string>

#include "game_object.hpp"

class Player : GameObject
{
public:


private:
	std::string name;
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

	virtual void Write(OutputStream&) override;
	virtual void Read(InputStream&) override;
};