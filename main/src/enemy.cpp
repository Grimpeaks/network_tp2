#include "enemy.hpp"

void Enemy::Write(OutputStream& outStream)
{
	// ENVOI DES DONNÉES
	// Envoi du nom
	outStream.WriteStr(name);

	// Envoi de la position
	compPosition compressedPosition;
	compressedPosition.x = packFloatPos(enemyPos.x);
	compressedPosition.y = packFloatPos(enemyPos.y);
	compressedPosition.z = packFloatPos(enemyPos.z);;
	outStream.Write<uint32_t>(compressedPosition.x);
	outStream.Write<uint32_t>(compressedPosition.y);
	outStream.Write<uint32_t>(compressedPosition.z);

	// Envoi de la rotation
	compRotation compressedRotation = packRotation(enemyRot);
	outStream.Write<uint16_t>(compressedRotation.a);
	outStream.Write<uint16_t>(compressedRotation.b);
	outStream.Write<uint16_t>(compressedRotation.c);
	outStream.Write<uint8_t>(compressedRotation.i);
}

void Enemy::Read(InputStream& inStream)
{
	// Lecture du nom
	name = inStream.ReadStr();

	// Lecture de la position
	enemyPos.x = unpackFloatPos(inStream.Read<uint32_t>());
	enemyPos.y = unpackFloatPos(inStream.Read<uint32_t>());
	enemyPos.z = unpackFloatPos(inStream.Read<uint32_t>());

	// Lecture de la rotation
	compRotation compressedRotation;
	compressedRotation.a = inStream.Read<uint16_t>();
	compressedRotation.b = inStream.Read<uint16_t>();
	compressedRotation.c = inStream.Read<uint16_t>();
	compressedRotation.i = inStream.Read<uint8_t>();
	enemyRot = unpackRotation(compressedRotation);

	std::cout << "Enemy : \n"
		<< name << "\n"
		<< enemyPos.x << "," << enemyPos.y << "," << enemyPos.z << "\n"
		<< enemyRot.x << "," << enemyRot.y << "," << enemyRot.z << "," << enemyRot.w << std::endl;
}

uint32_t Enemy::packFloatPos(float floatVal)
{
	int compression = floatVal * 1000;
	if (compression > 500000) { compression = 500000; }
	else if (compression < -500000) { compression = -500000; }
	compression += 500000;
	return compression;
}

float Enemy::unpackFloatPos(uint32_t val)
{
	int signedVal;
	signedVal = val - 500000;
	float floatVal;
	floatVal = (float)signedVal / 1000.0;
	return floatVal;
}

uint16_t Enemy::packFloatRot(float floatVal)
{
	int compression = floatVal * 1000;
	if (compression > 1000) { compression = 1000; }
	else if (compression < -1000) { compression = -1000; }
	compression += 1000;
	return static_cast<uint16_t>(compression);
}


float Enemy::unpackFloatRot(uint16_t val)
{
	int signedVal;
	signedVal = val - 1000;
	float floatVal;
	floatVal = (float)signedVal / 1000.0;
	return floatVal;
}

compRotation Enemy::packRotation(rotation structQuat)
{
	compRotation compressedRotation;
	std::vector<float> quaternion = { structQuat.x, structQuat.y, structQuat.z, structQuat.w };
	float maxValue = std::numeric_limits<float>::min();
	uint8_t maxIndex = 0;
	float sign = 1;


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

rotation Enemy::unpackRotation(compRotation compressedRotation)
{
	int maxIndex = compressedRotation.i;

	float a = unpackFloatRot(compressedRotation.a);
	float b = unpackFloatRot(compressedRotation.b);
	float c = unpackFloatRot(compressedRotation.c);
	float d = sqrt(1.0f - (a * a + b * b + c * c));

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