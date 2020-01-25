#include <Core/Engine.h>
#include <time.h>

#define NUM_OF_BROKEN_PIECES 20

class Obstacles
{
public:
	glm::vec3 positions; //position of the obstacle
	float globalRotation; //rotation over the sea
	bool dead; 
	Obstacles();
	int broken; 
	float shrinkScale;
	std::vector<glm::vec3> brokenPiecesPositions;
	std::vector<float> brokenPiecesRotation;
};