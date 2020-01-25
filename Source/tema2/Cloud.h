#pragma once

#include <Core/Engine.h>
#include <time.h>

class Cloud //a class that defines a cloud object
{
public:
	std::vector<glm::vec3>  positions; //each piece position
	std::vector<glm::vec3> rotate; //rotation
	std::vector<glm::vec3> scale; //and scale
	float globalRotation; //the global position compared to the center of the cylinder 
	
	Cloud(int numBoxes); //constructor
};