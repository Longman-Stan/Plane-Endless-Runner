#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include "../include/math.h"
#include <time.h>

namespace Objects
{
	// Creates the meshes I'll use in the program
	Mesh* CreatePlane(std::string plane_name);
	Mesh* CreatePropeller(std::string name);
	Mesh* CreateSkyBox(std::string name);
	Mesh* CreateObstacle(std::string name);
	Mesh* CreateFuel(std::string name);
	Mesh* CreateSea(std::string name);
	Mesh* CreateCloudPart(std::string cloudPart, char index);
	Mesh* CreateLife(std::string name);
	Mesh* CreateFuelBar(std::string name);
	Mesh* CreateFuelBar2(std::string name);
}

