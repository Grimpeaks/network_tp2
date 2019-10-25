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
	signedVal = val - 50000;
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
	return compression;
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