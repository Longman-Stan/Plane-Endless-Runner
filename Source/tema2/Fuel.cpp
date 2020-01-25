#include "Fuel.h"

Fuel::Fuel()
{
	float posz = (float)(rand() % 200) / 20 + 30;
	positions.push_back(glm::vec3(0, 0.f, posz)); //well chosen values so that the fuel cells will form an arch over the sea
	positions.push_back(glm::vec3(0, 1.f, posz-0.5f));
	positions.push_back(glm::vec3(0, 1.8f, posz-1.2f));
	positions.push_back(glm::vec3(0, 2.3f, posz-2.3f));
	positions.push_back(glm::vec3(0, 2.5f, posz-3.5f));
	globalRotation = 0;
	for (int i = 0; i < NUM_OF_FUEL_CELLS; i++) consumed[i] = false;
	refuel = false;
	for (int i = 0; i < NUM_OF_FUEL_CELLS; i++)
	{

		std::vector<glm::vec3> bpp;
		std::vector<float> bpr;

		broken.push_back(-1);
		shrinkScale.push_back(0.3f);
		for (int i = 0; i < NUM_OF_BROKEN_PIECES; i++)
		{
			bpp.push_back(glm::vec3(0.f));
			bpr.push_back((float(rand() % 360)));
		}
		brokenPiecesPositions.push_back(bpp);
		brokenPiecesRotation.push_back(bpr);
	}
}