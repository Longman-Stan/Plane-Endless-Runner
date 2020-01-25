#include "Obstacles.h"

Obstacles::Obstacles()
{
	float posz = (float)(rand() % 200) / 20 + 30; 
	positions = glm::vec3(0, 0, posz);
	globalRotation = 0;
	dead = false;
	broken = -1;
	shrinkScale = 0.3f;
	for (int i = 0; i < NUM_OF_BROKEN_PIECES; i++)
	{
		brokenPiecesPositions.push_back(glm::vec3(0.f));
		brokenPiecesRotation.push_back((float(rand() % 360)));
	}
}