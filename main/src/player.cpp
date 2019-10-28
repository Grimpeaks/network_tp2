#include "player.hpp"


void Player::Write(OutputStream& outStream)
{
	// ENVOI DES DONNÉES
	//uint8_t dimension;

	// Envoi du nom
	outStream.WriteStr(name);

	// Envoi de la position
	compPosition compressedPosition;
	compressedPosition.x = packFloatPos(playerPos.x);
	compressedPosition.y = packFloatPos(playerPos.y);
	compressedPosition.z = packFloatPos(playerPos.z);

	//dimension = 3;
	//outStream.Write<uint8_t>(dimension);
	//outStream.Write(&compressedPosition.x, dimension);
	//outStream.Write<uint8_t>(dimension);
	//outStream.Write(&compressedPosition.y, dimension);
	//outStream.Write<uint8_t>(dimension);
	//outStream.Write(&compressedPosition.z, dimension);

	outStream.Write<uint32_t>(compressedPosition.x);
	outStream.Write<uint32_t>(compressedPosition.y);
	outStream.Write<uint32_t>(compressedPosition.z);

	// Envoi de la rotation
	compRotation compressedRotation = packRotation(playerRot);

	//dimension = 3;
	//outStream.Write<uint8_t>(dimension);
	//outStream.Write(&compressedRotation.a, dimension);
	//outStream.Write<uint8_t>(dimension);
	//outStream.Write(&compressedRotation.b, dimension);
	//outStream.Write<uint8_t>(dimension);
	//outStream.Write(&compressedRotation.c, dimension);
	//dimension = 1;
	//outStream.Write<uint8_t>(dimension);
	//outStream.Write(&compressedRotation.i, dimension);

	outStream.Write<uint16_t>(compressedRotation.a);
	outStream.Write<uint16_t>(compressedRotation.b);
	outStream.Write<uint16_t>(compressedRotation.c);
	outStream.Write<uint8_t>(compressedRotation.i);
}

void Player::Read(InputStream& inStream)
{
		//uint8_t dimension;
		//gsl::span<std::byte> readBytes;

		// Lecture du nom
		name = inStream.ReadStr();

		// Lecture de la position
		//dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		//readBytes = inStream.Read(dimension);
		//playerPos.x = unpackFloatPos(bytesToInt32(readBytes));

		//dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		//readBytes = inStream.Read(dimension);
		//playerPos.y = unpackFloatPos(bytesToInt32(readBytes));

		//dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		//readBytes = inStream.Read(dimension);
		//playerPos.z = unpackFloatPos(bytesToInt32(readBytes));

		playerPos.x = unpackFloatPos(inStream.Read<uint32_t>());
		playerPos.y = unpackFloatPos(inStream.Read<uint32_t>());
		playerPos.z = unpackFloatPos(inStream.Read<uint32_t>());

		// Lecture de la rotation
		//compRotation compressedRotation;

		//dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		//readBytes = inStream.Read(dimension);
		//compressedRotation.a = bytesToInt32(readBytes);

		//dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		//readBytes = inStream.Read(dimension);
		//compressedRotation.b = bytesToInt32(readBytes);

		//dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		//readBytes = inStream.Read(dimension);
		//compressedRotation.c = bytesToInt32(readBytes);

		//dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		//readBytes = inStream.Read(dimension);
		//compressedRotation.i = static_cast<char>(readBytes[0]);

		//playerRot = unpackRotation(compressedRotation);

		compRotation compressedRotation;
		compressedRotation.a = inStream.Read<uint16_t>();
		compressedRotation.b = inStream.Read<uint16_t>();
		compressedRotation.c = inStream.Read<uint16_t>();
		compressedRotation.i = inStream.Read<uint8_t>();
		playerRot = unpackRotation(compressedRotation);


		std::cout << "Player : \n"
			<< name << "\n"
			<< playerPos.x << "," << playerPos.y << "," << playerPos.z << "\n"
			<< playerRot.x << "," << playerRot.y << "," << playerRot.z << "," << playerRot.w << std::endl;
}

//uint32_t Player::bytesToInt32(gsl::span<std::byte> bytes) //////////////////////////////////////////////////////////////////
//{
//	uint32_t val = 0;
//	std::for_each(bytes.begin(), bytes.end(), [&val](std::byte byteToPush)
//		{
//			val << static_cast<uint32_t>(byteToPush);
//		}
//	);
//	return val;
//}

//compresses and limits between -500 and 500
uint32_t Player::packFloatPos(float floatVal)
{
	int compression = floatVal * 1000;
	if (compression > 500000) { compression = 500000; }
	else if (compression < -500000) { compression = -500000; }
	compression += 500000;
	return compression;
}

float Player::unpackFloatPos(uint32_t val)
{
	int signedVal;
	signedVal = val - 500000;
	float floatVal;
	floatVal = (float)signedVal / 1000.0;
	return floatVal;
}

//compresses and limits between -1 and 1
uint16_t Player::packFloatRot(float floatVal)
{
	int compression = floatVal * 1000;
	if (compression > 1000) { compression = 1000; }
	else if (compression < -1000) { compression = -1000; }
	compression += 1000;
	return static_cast<uint16_t>(compression);
}

float Player::unpackFloatRot(uint16_t val)
{
	int signedVal;
	signedVal = val - 1000;
	float floatVal;
	floatVal = (float)signedVal / 1000.0;
	return floatVal;
}

compRotation Player::packRotation(rotation structQuat)
{
	compRotation compressedRotation;
	std::vector<float> quaternion = { structQuat.x, structQuat.y, structQuat.z, structQuat.w };
	float maxValue = std::numeric_limits<float>::min();
	uint8_t maxIndex = 0;

	for (int i = 0; i < 4; i++)
	{
		float element = quaternion[i];
		if (element > maxValue)
		{
			maxIndex = i;
			maxValue = element;
		}
	}

	if (maxIndex == 0)
	{
		compressedRotation.a = (packFloatRot(quaternion.at(1)));
		compressedRotation.b = (packFloatRot(quaternion.at(2)));
		compressedRotation.c = (packFloatRot(quaternion.at(3)));
	}
	else if (maxIndex == 1)
	{
		compressedRotation.a = (packFloatRot(quaternion.at(0)));
		compressedRotation.b = (packFloatRot(quaternion.at(2)));
		compressedRotation.c = (packFloatRot(quaternion.at(3)));
	}
	else if (maxIndex == 2)
	{
		compressedRotation.a = (packFloatRot(quaternion.at(0)));
		compressedRotation.b = (packFloatRot(quaternion.at(1)));
		compressedRotation.c = (packFloatRot(quaternion.at(3)));
	}
	else
	{
		compressedRotation.a = (packFloatRot(quaternion.at(0)));
		compressedRotation.b = (packFloatRot(quaternion.at(1)));
		compressedRotation.c = (packFloatRot(quaternion.at(2)));
	}
	compressedRotation.i = maxIndex;
	return compressedRotation;
}

rotation Player::unpackRotation(compRotation compressedRotation)
{
	uint8_t maxIndex = compressedRotation.i;

	float a = unpackFloatRot(compressedRotation.a);
	float b = unpackFloatRot(compressedRotation.b);
	float c = unpackFloatRot(compressedRotation.c);
	float d = std::sqrt(1.0 - (a * a + b * b + c * c));

	rotation rot;
	if (maxIndex == 0)
	{
		rot.x = d;
		rot.y = a;
		rot.z = b;
		rot.w = c;
		return rot;
	}
	else if (maxIndex == 1)
	{
		rot.x = a;
		rot.y = d;
		rot.z = b;
		rot.w = c;
		return rot;
	}
	else if (maxIndex == 2)
	{
		rot.x = a;
		rot.y = b;
		rot.z = d;
		rot.w = c;
		return rot;
	}
	rot.x = a;
	rot.y = b;
	rot.z = c;
	rot.w = d;
	return rot;
}