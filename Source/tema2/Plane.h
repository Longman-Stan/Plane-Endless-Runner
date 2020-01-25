#pragma once

#include <Core/Engine.h>
#include "camera.h"
#include <iostream>

class Plane
{
public:
	glm::vec3 rotationVector; //the vector this plane rotates around
	glm::vec3 planePosition; //the position the plane mush be placed at
	float degrees; //the plane inclination in degrees
	float degrees_dead; //rotation angle for falling animation
	float gasTank; //how much fuel the plane has 
	int lives; //how many lives the plane has
	char cameraType;
	bool dead;

	float deadSpeed; //the speed of falling when you're dead

	Plane(glm::vec3 planePosition);
	void Vertical_Move(float mouseY,bool rotate); //a function that changes the plane position with mouseY and rotates the plane if rotate is true
	void Rotate_Plane(float value); //a function that changes the plane inclination according to value
	void Stabilize(Camera* cam, char cameraType,glm::vec3* camPosT,glm::vec3* camCenter); //a function that returns the plane to the horizontal
	void BUUUUUURN(float deltaT); //the death animation
	//void Stabilize();
};