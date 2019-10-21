#include "enemy.hpp"

void Enemy::Write(OutputStream& outStream)
{
	// ENVOI DES DONNÉES
	uint8_t dimension;

	// Envoi du nom
	outStream.WriteStr(name);

	// Envoi de la position
	compPosition compressedPosition;
	compressedPosition.x = packFloatPos(enemyPos.x);
	compressedPosition.y = packFloatPos(enemyPos.y);
	compressedPosition.z = packFloatPos(enemyPos.z);

	dimension = 3;
	outStream.Write<uint8_t>(dimension);
	outStream.Write(&compressedPosition.x, dimension);
	outStream.Write<uint8_t>(dimension);
	outStream.Write(&compressedPosition.y, dimension);
	outStream.Write<uint8_t>(dimension);
	outStream.Write(&compressedPosition.z, dimension);

	// Envoi de la rotation
	compRotation compressedRotation = packQuaternion(enemyRot);

	dimension = 3;
	outStream.Write<uint8_t>(dimension);
	outStream.Write(&compressedRotation.a, dimension);
	outStream.Write<uint8_t>(dimension);
	outStream.Write(&compressedRotation.b, dimension);
	outStream.Write<uint8_t>(dimension);
	outStream.Write(&compressedRotation.c, dimension);
	dimension = 1;
	outStream.Write<uint8_t>(dimension);
	outStream.Write(&compressedRotation.i, dimension);
}

void Enemy::Read(InputStream& inStream)
{
	if (inStream.Read(1)[0] == static_cast<std::byte>(PacketType::Sync))
	{
		uint8_t dimension;
		gsl::span<std::byte> readBytes;

		// Lecture du nom
		name = inStream.ReadStr();

		// Lecture de la position
		dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		readBytes = inStream.Read(dimension);
		enemyPos.x = unpackFloatPos(bytesToInt32(readBytes));

		dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		readBytes = inStream.Read(dimension);
		enemyPos.y = unpackFloatPos(bytesToInt32(readBytes));

		dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		readBytes = inStream.Read(dimension);
		enemyPos.z = unpackFloatPos(bytesToInt32(readBytes));

		// Lecture de la rotation
		compRotation compressedRotation;
		const auto identityCallback = [](std::byte b) { return b; };

		dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		readBytes = inStream.Read(dimension);
		compressedRotation.a = bytesToInt32(readBytes);

		dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		readBytes = inStream.Read(dimension);
		compressedRotation.b = bytesToInt32(readBytes);

		dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		readBytes = inStream.Read(dimension);
		compressedRotation.c = bytesToInt32(readBytes);

		dimension = static_cast<std::uint8_t>(inStream.Read(1)[0]);
		readBytes = inStream.Read(dimension);
		compressedRotation.i = static_cast<char>(readBytes[0]);

		enemyRot = unpackRotation(compressedRotation);

		//si Obj Id existe

		//sinon

	}
}

uint32_t Enemy::bytesToInt32(gsl::span<std::byte> bytes)
{
	uint32_t val = 0;
	std::for_each(bytes.begin(), bytes.end(), [&val](std::byte byteToPush)
		{
			val << static_cast<uint32_t>(byteToPush);
		}
	);
	return val;
}

float Enemy::unpackFloatPos(uint32_t val)
{
	int signedVal;
	signedVal = val - 50000;
	float floatVal;
	floatVal = (float)signedVal / 1000.0;
	return floatVal;
}

float Enemy::unpackFloatRot(uint16_t val)
{
	int signedVal;
	signedVal = val - 1000;
	float floatVal;
	floatVal = (float)signedVal / 1000.0;
	return floatVal;
}

uint32_t Enemy::packFloatPos(float floatVal)
{
	int compression = floatVal * 1000;
	if (compression > 500000) { compression = 500000; }
	else if (compression < -500000) { compression = -500000; }
	compression += 500000;
	return compression;
}

uint16_t Enemy::packFloatRot(float floatVal)
{
	int compression = floatVal * 1000;
	if (compression > 1000) { compression = 1000; }
	else if (compression < -1000) { compression = -1000; }
	compression += 1000;
	return compression;
}

compRotation Enemy::packQuaternion(rotation structQuat)
{
	compRotation compressedRotation;
	std::vector<float> quaternion = { structQuat.x, structQuat.y, structQuat.z, structQuat.w };
	float maxValue = std::numeric_limits<float>::min();
	char maxIndex = 0;
	float sign = 1;


	for (int i = 0; i < 4; i++)
	{
		float element = quaternion[i];
		float absolute = abs(quaternion[i]);
		if (absolute > maxValue)
		{
			sign = (element < 0) ? -1 : 1;
			maxIndex = i;
			maxValue = absolute;
		}
	}

	if (maxIndex == 0)
	{
		compressedRotation.a = (packFloatRot(quaternion.at(1) * sign));
		compressedRotation.b = (packFloatRot(quaternion.at(2) * sign));
		compressedRotation.c = (packFloatRot(quaternion.at(3) * sign));
	}
	else if (maxIndex == 1)
	{
		compressedRotation.a = (packFloatRot(quaternion.at(0) * sign));
		compressedRotation.b = (packFloatRot(quaternion.at(2) * sign));
		compressedRotation.c = (packFloatRot(quaternion.at(3) * sign));
	}
	else if (maxIndex == 2)
	{
		compressedRotation.a = (packFloatRot(quaternion.at(0) * sign));
		compressedRotation.b = (packFloatRot(quaternion.at(1) * sign));
		compressedRotation.c = (packFloatRot(quaternion.at(3) * sign));
	}
	else
	{
		compressedRotation.a = (packFloatRot(quaternion.at(0) * sign));
		compressedRotation.b = (packFloatRot(quaternion.at(1) * sign));
		compressedRotation.c = (packFloatRot(quaternion.at(2) * sign));
	}
	compressedRotation.i = maxIndex;
	return compressedRotation;
}

rotation Enemy::unpackRotation(compRotation compressedRotation)
{
	char maxIndex = compressedRotation.i;

	float a = (float)unpackFloatRot(compressedRotation.a);
	float b = (float)unpackFloatRot(compressedRotation.b);
	float c = (float)unpackFloatRot(compressedRotation.c);
	float d = sqrt(1.0 - (a * a + b * b + c * c));

	rotation rot;
	if (maxIndex == 0)
	{
		rot.x = d;
		rot.x = a;
		rot.x = b;
		rot.x = c;
		return rot;
	}
	else if (maxIndex == 1)
	{
		rot.x = a;
		rot.x = d;
		rot.x = b;
		rot.x = c;
		return rot;
	}
	else if (maxIndex == 2)
	{
		rot.x = a;
		rot.x = b;
		rot.x = d;
		rot.x = c;
		return rot;
	}
	rot.x = a;
	rot.x = b;
	rot.x = c;
	rot.x = d;
	return rot;
}