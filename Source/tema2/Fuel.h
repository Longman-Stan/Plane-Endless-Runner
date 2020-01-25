#pragma once

#include <Core/Engine.h>
#include <time.h>

#define NUM_OF_FUEL_CELLS 5
#define NUM_OF_BROKEN_PIECES 20

class Fuel // a fuel object
{
public:
	std::vector<glm::vec3>  positions; //positions of the 5 chosen fuel thetrhedron
	float globalRotation; 

	bool consumed[5]; //see whether they're consumed or not
	bool refuel; //flag for regenerating the fuel group
	Fuel(); 

	//addition to simulate breaking of the thetrahedrons
	std::vector<int> broken; //the type of  broken or -1 if  this component is not broken
	std::vector<float> shrinkScale; //the scale of shrink
	std::vector < std::vector<glm::vec3> > brokenPiecesPositions;
	std::vector < std::vector<float> > brokenPiecesRotation;

};