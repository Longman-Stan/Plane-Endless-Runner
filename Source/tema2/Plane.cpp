#include "Plane.h"

constexpr auto MAX_GASTANK_CAPACITY = 100.f;
constexpr auto MAX_PLANE_TILT = 45.f;
constexpr auto MAX_PLANE_VERTICAL_MOVEMENT = 1.f;
constexpr auto DEAD_PLANE_TILT = 70.f;


Plane::Plane(glm::vec3 planePosition)
{
	this->planePosition = planePosition;
	rotationVector = glm::vec3(0, 0, 1);
	gasTank = MAX_GASTANK_CAPACITY;
	degrees = 0;
	lives = 3;
	cameraType = 't';
	dead = false;
	degrees_dead = 0;
}

void Plane::Vertical_Move(float mouseY,bool rotate)
{
	float val;
	
	if(mouseY>0)
		val= -std::min(mouseY, MAX_PLANE_VERTICAL_MOVEMENT);
	else
		val= -std::max(mouseY, -MAX_PLANE_VERTICAL_MOVEMENT);

	planePosition[1] += val;

	if(rotate) 
		Rotate_Plane(val);

}

void Plane::Rotate_Plane(float value)
{
	degrees += 50*value;
	if (!dead)
	{
		degrees = std::max(degrees, -MAX_PLANE_TILT);
		degrees = std::min(degrees, MAX_PLANE_TILT);
	}
	else
	{
		degrees = std::max(degrees, -DEAD_PLANE_TILT);
		degrees = std::min(degrees, DEAD_PLANE_TILT);
	}

}

void Plane::Stabilize(Camera* cam, char cameraType,glm::vec3* camPosT,glm::vec3* camCenter)
{
	float limit=0;
	if (cameraType == 'f')
	{
		limit = -5;// atan(5 / planePosition[1]);
	}

	//std::cout << limit << '\n';
	if (degrees > limit)
	{
		degrees -= 1.f;
		if (degrees< limit)
			degrees = limit;
		Vertical_Move(-0.05f,false);
		
		if (cameraType == 't')
			cam->MoveUpward(0.05f);
		else
		{
			(*camPosT)[1] += 0.05f;
			(*camCenter)[1] += 0.5f;
		}

	}
	if(degrees < limit)
	{
		degrees += 1.f;
		if (degrees > limit)
			degrees = limit;
		Vertical_Move(0.05f,false);

		if (cameraType == 't')
			cam->MoveUpward(-0.05f);
		else
		{
			(*camPosT)[1] -= 0.05f;
			(*camCenter)[1] -= 0.5f;
		}
	}
	
}

#define G 5.f

void Plane::BUUUUUURN(float deltaT)
{
	deadSpeed += 0.01f*deltaT*G;
	if(planePosition[1]>0)
		Vertical_Move(deadSpeed, true);
	degrees_dead += deadSpeed*50;
	if (degrees_dead >= 360) degrees_dead = 0;
}