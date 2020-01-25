#include "tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

#include <tema2/Objects.h>

#include <map>

#include "../../libs/stb/stb_image.h"

std::map<PowerUpType, glm::vec3> powerUpColor;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::loadMeshes()
{
	Mesh* mesha = Objects::CreatePlane("plane");
	meshes["plane"] = mesha;

	Mesh* meshb = Objects::CreatePropeller("propeller");
	meshes["propeller"] = meshb;

	Mesh* meshc = Objects::CreateSkyBox("skybox");
	meshes["skybox"] = meshc;

	Mesh* meshd = Objects::CreateObstacle("obstacle");
	meshes["obstacle"] = meshd;

	Mesh* meshe = Objects::CreateFuel("fuel");
	meshes["fuel"] = meshe;

	Mesh* meshf = Objects::CreateSea("sea");
	meshes["sea"] = meshf;

	Mesh* meshg = Objects::CreateCloudPart("cloud-l", 0);
	meshes["cloud-l"] = meshg;

	Mesh* meshh = Objects::CreateCloudPart("cloud-d", 1);
	meshes["cloud-d"] = meshh;

	Mesh* meshi = Objects::CreateLife("life");
	meshes["life"] = meshi;

	Mesh* meshj = Objects::CreateFuelBar("fuelBar");
	meshes["fuelBar"] = meshj;

	Mesh* meshk = Objects::CreateFuelBar2("fuelBar2");
	meshes["fuelBar2"] = meshk;

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	
	{

		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	const std::string textureLoc = "Source/Tema2/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "sky.png").c_str(), GL_REPEAT);
		mapTextures["grass"] = texture;
	}
}

void Tema2::loadShaders()
{
	const std::string sourceLoc = "Source/tema2/Shaders/";
	Shader* shader = new Shader("PlaneShader");
	shader->AddShader(sourceLoc + "PlaneVS.glsl", GL_VERTEX_SHADER);
	shader->AddShader(sourceLoc + "PlaneFS.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	Shader* shader2 = new Shader("SeaShader");
	shader2->AddShader(sourceLoc + "SeaVS.glsl", GL_VERTEX_SHADER);
	shader2->AddShader(sourceLoc + "SeaFS.glsl", GL_FRAGMENT_SHADER);
	shader2->CreateAndLink();
	shaders[shader2->GetName()] = shader2;

	Shader* shader3 = new Shader("CloudShader");
	shader3->AddShader(sourceLoc + "CloudVS.glsl", GL_VERTEX_SHADER);
	shader3->AddShader(sourceLoc + "CloudFS.glsl", GL_FRAGMENT_SHADER);
	shader3->CreateAndLink();
	shaders[shader3->GetName()] = shader3;

	Shader* shader4 = new Shader("PowerUpShader");
	shader4->AddShader(sourceLoc + "PowerUpVS.glsl", GL_VERTEX_SHADER);
	shader4->AddShader(sourceLoc + "PowerUpFS.glsl", GL_FRAGMENT_SHADER);
	shader4->CreateAndLink();
	shaders[shader4->GetName()] = shader4;

	Shader* shader5 = new Shader("SkyBox");
	shader5->AddShader(sourceLoc + "SkyVS.glsl", GL_VERTEX_SHADER);
	shader5->AddShader(sourceLoc + "SkyFS.glsl", GL_FRAGMENT_SHADER);
	shader5->CreateAndLink();
	shaders[shader5->GetName()] = shader5;

}

void Tema2::Init()
{
	glEnable(GL_CULL_FACE); //enable cull face
	glCullFace(GL_FRONT);
	glEnable(GL_BLEND);  //enable alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	renderCameraTarget = false;

	camera = new Camera(); //set the camera parameters
	camPosT = glm::vec3(23.f, 15.f, 5.f);
	camLookAtT = glm::vec3(0, 12.f, 0);
	camera->Set(camPosT, glm::vec3(0, 12, 0), glm::vec3(0, 1, 0));

	Pfov = 30;
	inaltime = 1;
	latime = 1;
	cameraType = 't';
	projectionMatrix = glm::perspective(RADIANS(30), window->props.aspectRatio, 0.01f, 100.0f);

	originalFPPosition = glm::vec3(1.f,2.5f,0.f); //the original camera positions for good camera positioning
	originalCameraCenter = glm::vec3(2.f, 2.25f, 0.f);
	
	seaRotation = 0; //the degrees the sea has to be rotated with
	time = 0; //global time for vertex shader sea deformation

	speed = 10.f; //the speed of the plane

	PropellerSpeed = 1000; //the speed the propeller rotates with

	plane = new Plane(glm::vec3(0, 12, 0)); //initiate the plane

	for(int i=0;i<360;i+=20) //generate equally spaced clouds
	{
		generateClouds(i);
	}

	for (int i = 0; i < 360; i+=10) //generate equally spacesd obstacles
	{
		generateObstacles(i);
	}

	obstacleScale = 0.5f; 
	obstacleRotation = 0; //rotation of all obstacles, power ups and fuel cells included

	for (int i = 0; i < 360; i += 40) //generate equally spacesd fuel cells
	{
		generateFuels(i);
	}

	generatePowerUps(); //generate the power ups
	speedUpTime = slowDownTime = invincibilityTime = 0; //power up time left

	loadMeshes(); //load the meshes
	loadShaders();

	{ //get the original first person camera position
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, plane->planePosition);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 0.1));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(plane->degrees), glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));

		cameraCenter = modelMatrix * glm::vec4(originalCameraCenter, 1);
		fpCameraPosition = modelMatrix * glm::vec4(originalFPPosition, 1);
	}

	//the center of the collision points depending on camera position
	collisionPointFP = glm::vec3(1.f, 2.5f, 0.f); //if the camera is first person, the collision point is the camera
	collisionPointTP = glm::vec3(2.f, 0, 0); //if it's third person, it's the front of the plane

	collisionPoints = { glm::vec3(1),glm::vec3(1),glm::vec3(1),glm::vec3(1) };
	obstacleCollisionPoints = { glm::vec3(-0.5f,0.5f,0.f),glm::vec3(0.5f,0.5f,0.f),glm::vec3(0.5f,-0.5f,0.f),glm::vec3(-0.5f,-0.5f,0.f) }; //collision rectangle

	generateBrokenPositions(5, 20); //generate the possible direction for the broken pieces

	hitBox = obstacleScale * 0.5f;

	returnSpeed=false; //flag for canceling a power up only once

	renderParticles = false; //flag for rendering the perticles or not

	powerUpColor[LIFE] = glm::vec3(1, 0, 0); //initialize the color <-> powerUpType map
	powerUpColor[SPEEDUP] = glm::vec3(0.7f, 0.2f, 0.2f);
	powerUpColor[SLOWDOWN] = glm::vec3(0.2f, 0.2f, 0.7f);
	powerUpColor[INVINCIBILITY] = glm::vec3(0.2f, 0.7f, 0.2f);

	std::vector<std::string> faces //get the skybox texture
	{
		"Source/Tema2/skybox2/right.jpg",
		"Source/Tema2/skybox2/left.jpg",
		"Source/Tema2/skybox2/top.jpg",
		"Source/Tema2/skybox2/bottom.jpg",
		"Source/Tema2/skybox2/front.jpg",
		"Source/Tema2/skybox2/back.jpg"
	};
	cubeMapTexture = loadCubemap(faces);
	
	shiny = 30; //set up illumination parameters
	kd = ks = 1.5;
	light_pos = glm::vec3(0, 25, -10);
}

void Tema2::generatePowerUps()
{
	generatePowerUp(LIFE); //one life

	for (int i = 0; i < 5; i++) //several speed ups/slow downs
	{
		generatePowerUp(SPEEDUP);
		generatePowerUp(SLOWDOWN);
	}

	for (int i = 0; i < 2; i++) //two invincibilities
		generatePowerUp(INVINCIBILITY);
}

void Tema2::generatePowerUp(PowerUpType puT) //generate the power up randomly
{
	Obstacles* obst = new Obstacles();
	obst->globalRotation = rand() % 360;
	powerUps.push_back(std::make_pair(obst, puT));
}

void Tema2::generatePowerUp(PowerUpType puT,int position) //generate the power up to refresh a used one( avoid useless insert/delete vector operations)
{
	Obstacles* obst = new Obstacles();
	obst->globalRotation = rand() % 360;
	powerUps[position]=(std::make_pair(obst, puT));
}

void Tema2::generateClouds(int globalRotation)
{
	for (int i = 0; i < 2; i++)
	{
		Cloud* cloud = new Cloud(rand() % 10);
		cloud->globalRotation = globalRotation;
		clouds.push_back(cloud);
	}
}

void Tema2::generateObstacles(int globalRotation) //same as generate power ups
{
		Obstacles* obst = new Obstacles();
		obst->globalRotation = globalRotation;
		obstacles.push_back(obst);

}

void Tema2::generateObstacles(int globalRotation,int position)
{
	Obstacles* obst = new Obstacles();
	obst->globalRotation = globalRotation;
	obstacles[position]=obst;

}

void Tema2::generateFuels(int globalRotation) //same as generate power ups
{
	Fuel* obst = new Fuel();
	obst->globalRotation = globalRotation;
	fuels.push_back(obst);
}

void Tema2::generateFuels(int globalRotation,int position)
{
	Fuel* obst = new Fuel();
	obst->globalRotation = globalRotation;
	fuels[position]=obst;
}

//generate directions for broken pieces
void Tema2::generateBrokenPositions(int numberOfPositions,int numberOfPieces)
{
	for (int i = 0; i < numberOfPositions; i++)
	{
		std::vector<glm::vec3> pos;
		for (int j = 0; j < numberOfPieces; j++)
			pos.push_back(glm::vec3( (float)(rand()%100)/1000 -0.05f, (float)(rand() % 100) / 1000 -0.05f, (float)(rand() % 100) / 1000-0.05f));
		brokenPositions.push_back(pos);
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.51f, 0.40f, 0.53f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

bool Tema2::checkCollision(std::vector<glm::vec3> planePoints, glm::vec3 obstaclePosition, float hitBox) 
{
	for (auto it : planePoints)
	{
		if (it.x >= obstaclePosition.x - hitBox && it.x <= obstaclePosition.x + hitBox)
			if (it.y >= obstaclePosition.y - hitBox && it.y <= obstaclePosition.y + hitBox)
				if (it.z >= obstaclePosition.z - hitBox && it.z <= obstaclePosition.z + hitBox)
					return true; //if the point is in the parallelepiped
	}
	return false;
}


void Tema2::renderParticlesF()
{
	if (cameraType == 't' && !plane->dead && renderParticles)
	{
		for (int i = 0; i < 5 + (int)plane->degrees / 10; i++)
		{
			glm::mat4 particleMM = glm::mat4(1);

			particleMM = glm::translate(particleMM, plane->planePosition);

			float x = ((float)(rand() % 100) / 100);
			int cone = 200 + (int)(x * 1000);
			float divi = ((float)cone) / 2000;
			glm::vec3 particlePos = glm::vec3(-x - 0.8, ((float)(rand() % cone)) / 1000 - divi, ((float)(rand() % 100)) / 1000 - 0.05f);
			particleMM = glm::rotate(particleMM, RADIANS(plane->degrees), glm::vec3(1, 0, 0));
			particleMM = glm::rotate(particleMM, RADIANS(90), glm::vec3(0, 1, 0));
			particleMM = glm::translate(particleMM, particlePos);
			particleMM = glm::scale(particleMM, glm::vec3(0.05f, 0.05f, 0.05f));

			RenderMeshColor(meshes["sphere"], shaders["PowerUpShader"], particleMM, glm::vec3(0, 0, 0));
		}
	}
}

void Tema2::renderClouds()
{
	for (auto it : clouds)
		if (it->globalRotation > 270 || it->globalRotation < 50)
		{
			for (int i = 0; i < it->positions.size(); i++)
			{
				glm::mat4 modelMatrix = glm::mat4(1);

				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -32.f, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(it->globalRotation), glm::vec3(1, 0, 0));
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 32.f, 0));

				modelMatrix = glm::translate(modelMatrix, it->positions[i]);
				modelMatrix = glm::scale(modelMatrix, it->scale[i]);

				modelMatrix = glm::rotate(modelMatrix, RADIANS(it->rotate[i][0]), glm::vec3(1, 0, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(it->rotate[i][1]), glm::vec3(0, 1, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(it->rotate[i][2]), glm::vec3(0, 0, 1));

				if (i % 2 == 0)
					RenderMeshColor(meshes["cloud-l"], shaders["CloudShader"], modelMatrix, meshes["cloud-l"]->vertices[0].color);
				else
					RenderMeshColor(meshes["cloud-d"], shaders["CloudShader"], modelMatrix, meshes["cloud-d"]->vertices[0].color);
			}
		}
}

void Tema2::renderObstacles()
{
	int idx = 0;
	for (auto it : obstacles)
	{
		if (it->globalRotation > 290 && it->globalRotation < 340)
		{

			if (it->broken != -1)
			{
				glm::mat4 mm = glm::mat4(1);
				for (int idx = 0; idx < brokenPositions[it->broken].size(); idx++)
				{
					mm = glm::mat4(1);
					mm = glm::translate(mm, glm::vec3(0, -32.f, 0));
					mm = glm::rotate(mm, RADIANS(it->globalRotation), glm::vec3(1, 0, 0));
					mm = glm::translate(mm, glm::vec3(0, 32.f, 0));

					mm = glm::translate(mm, it->positions);

					it->brokenPiecesPositions[idx] += brokenPositions[it->broken][idx];
					mm = glm::translate(mm, it->brokenPiecesPositions[idx]);

					if (it->shrinkScale > 0)
						it->shrinkScale -= 0.0005f;
					else
					{
						it->broken = -1;
						break;
					}
					mm = glm::scale(mm, glm::vec3(it->shrinkScale));

					mm = glm::rotate(mm, RADIANS(it->brokenPiecesRotation[idx]), glm::vec3(1, 0, 0));
					RenderMeshColor(meshes["fuel"], shaders["PowerUpShader"], mm, glm::vec3(0.5f, 0.f, 0.f));
				}
			}

			if (!it->dead)
			{

				glm::mat4 modelMatrix = glm::mat4(1);

				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -32.f, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(it->globalRotation), glm::vec3(1, 0, 0));
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 32.f, 0));

				modelMatrix = glm::translate(modelMatrix, it->positions);

				glm::vec3 posCenter = modelMatrix * glm::vec4(0, 0, 0, 1);

				if (!it->dead && checkCollision(collisionPoints, posCenter, hitBox))
				{
					if (invincibilityTime <= 0)
						plane->lives--;
					if (plane->lives == 0)
					{
						plane->dead = true;
						plane->deadSpeed = 0.05f;
					}
					it->dead = true;
					it->broken = rand() % 5;
					continue;
				}

				modelMatrix = glm::scale(modelMatrix, glm::vec3(obstacleScale, obstacleScale, obstacleScale));

				modelMatrix = glm::rotate(modelMatrix, 0.96f, glm::vec3(1, 0, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(obstacleRotation), glm::vec3(0, 1, 0));

				RenderMeshColor(meshes["obstacle"], shaders["PowerUpShader"], modelMatrix, meshes["obstacle"]->vertices[0].color);

			}
			if (it->globalRotation > -5 && it->globalRotation < 5 && it->dead)
			{
				generateObstacles(it->globalRotation, idx);
			}
			idx++;
		}
	}
}

void Tema2::renderFuel()
{
	int idx = 0;
	for (auto it : fuels)
	{
		if (it->globalRotation > 290 && it->globalRotation < 340)
		{
			for (int i = 0; i < it->positions.size(); i++)
			{

				if (it->broken[i] != -1)
				{
					glm::mat4 mm = glm::mat4(1);
					for (int idx = 0; idx < brokenPositions[it->broken[i]].size(); idx++)
					{
						mm = glm::mat4(1);
						mm = glm::translate(mm, glm::vec3(0, -32.f, 0));
						mm = glm::rotate(mm, RADIANS(it->globalRotation), glm::vec3(1, 0, 0));
						mm = glm::translate(mm, glm::vec3(0, 32.f, 0));

						mm = glm::translate(mm, it->positions[i]);

						it->brokenPiecesPositions[i][idx] += brokenPositions[it->broken[i]][idx];
						mm = glm::translate(mm, it->brokenPiecesPositions[i][idx]);

						if (it->shrinkScale[i] > 0)
							it->shrinkScale[i] -= 0.0005f;
						else
						{
							it->broken[i] = -1;
							break;
						}
						mm = glm::scale(mm, glm::vec3(it->shrinkScale[i]));

						mm = glm::rotate(mm, RADIANS(it->brokenPiecesRotation[i][idx]), glm::vec3(1, 0, 0));
						RenderMeshColor(meshes["fuel"], shaders["PowerUpShader"], mm, glm::vec3(0.36f, 0.48f, 0.58f));
					}
				}

				if (!it->consumed[i])
				{
					glm::mat4 modelMatrix = glm::mat4(1);

					modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -32.f, 0));
					modelMatrix = glm::rotate(modelMatrix, RADIANS(it->globalRotation), glm::vec3(1, 0, 0));
					modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 32.f, 0));

					modelMatrix = glm::translate(modelMatrix, it->positions[i]);

					glm::vec3 posCenter = modelMatrix * glm::vec4(0, 0, 0, 1);

					if (!it->consumed[i] && checkCollision(collisionPoints, posCenter, hitBox))
					{
						plane->gasTank += 10;
						if (plane->gasTank > 100) plane->gasTank = 100;
						it->consumed[i] = true;
						it->broken[i] = rand() % 5;
						it->refuel = true;
						continue;
					}

					modelMatrix = glm::scale(modelMatrix, glm::vec3(obstacleScale, obstacleScale, obstacleScale));

					modelMatrix = glm::rotate(modelMatrix, 0.96f, glm::vec3(1, 0, 0));
					modelMatrix = glm::rotate(modelMatrix, RADIANS(obstacleRotation), glm::vec3(0, 1, 0));


					RenderMeshColor(meshes["fuel"], shaders["PowerUpShader"], modelMatrix, meshes["fuel"]->vertices[0].color);
				}
			}
		}
		if (it->globalRotation > -5 && it->globalRotation < 5 && it->refuel)
			generateFuels(it->globalRotation, idx);
		idx++;
	}
}

void Tema2::renderPowerUps()
{
	int idx = 0;
	for (auto it : powerUps)
	{

		if (it.first->broken != -1 && it.first->globalRotation > 290 && it.first->globalRotation < 340)
		{
			glm::mat4 mm = glm::mat4(1);
			for (int idx = 0; idx < brokenPositions[it.first->broken].size(); idx++)
			{
				mm = glm::mat4(1);
				mm = glm::translate(mm, glm::vec3(0, -32.f, 0));
				mm = glm::rotate(mm, RADIANS(it.first->globalRotation), glm::vec3(1, 0, 0));
				mm = glm::translate(mm, glm::vec3(0, 32.f, 0));

				mm = glm::translate(mm, it.first->positions);

				it.first->brokenPiecesPositions[idx] += brokenPositions[it.first->broken][idx];
				mm = glm::translate(mm, it.first->brokenPiecesPositions[idx]);

				if (it.first->shrinkScale > 0)
					it.first->shrinkScale -= 0.0005f;
				else
				{
					it.first->broken = -1;
					break;
				}
				mm = glm::scale(mm, glm::vec3(it.first->shrinkScale));

				mm = glm::rotate(mm, RADIANS(it.first->brokenPiecesRotation[idx]), glm::vec3(1, 0, 0));
				RenderMeshColor(meshes["fuel"], shaders["PowerUpShader"], mm, powerUpColor[(PowerUpType)it.second]);
			}
		}

		if (!it.first->dead && it.first->globalRotation > 290 && it.first->globalRotation < 340)
		{

			glm::mat4 modelMatrix = glm::mat4(1);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -32.f, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(it.first->globalRotation), glm::vec3(1, 0, 0));
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 32.f, 0));

			modelMatrix = glm::translate(modelMatrix, it.first->positions);

			glm::vec3 posCenter = modelMatrix * glm::vec4(0, 0, 0, 1);

			if (it.second == LIFE)
			{
				if (!it.first->dead && checkCollision(collisionPoints, posCenter, hitBox + obstacleScale * 0.25f))
				{
					if (plane->lives <= 7)
						plane->lives++;
					it.first->dead = true;
					it.first->broken = rand() % 5;
					continue;
				}
			}
			else
				if (!it.first->dead && checkCollision(collisionPoints, posCenter, hitBox))
				{
					switch (it.second)
					{
					case INVINCIBILITY:
						invincibilityTime = 10.f;
						break;
					case SPEEDUP:

						if (speedUpTime <= 0)
							speed += 5.f;
						if (slowDownTime > 0)
							speed += 5.f;
						speedUpTime = 10.f;
						slowDownTime = 0.f;
						returnSpeed = true;
						flightType = 1;
						break;
					case SLOWDOWN:

						if (slowDownTime <= 0)
							speed -= 5.f;
						if (speedUpTime > 0)
							speed -= 5.f;
						slowDownTime = 10.f;
						speedUpTime = 0.f;
						returnSpeed = true;
						flightType = 2;
						break;
					}
					it.first->dead = true;
					it.first->broken = rand() % 5;
					continue;
				}

			modelMatrix = glm::scale(modelMatrix, glm::vec3(obstacleScale, obstacleScale, obstacleScale));

			modelMatrix = glm::rotate(modelMatrix, 0.96f, glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, RADIANS(obstacleRotation), glm::vec3(0, 1, 0));

			if (it.second == LIFE)
			{
				if (cameraType == 't')
					modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
				modelMatrix = glm::rotate(modelMatrix, RADIANS(-obstacleRotation), glm::vec3(0, 1, 0));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
				RenderMeshColor(meshes["life"], shaders["PowerUpShader"], modelMatrix, powerUpColor[(PowerUpType)it.second]);
			}
			else
			{
				RenderMeshColor(meshes["sphere"], shaders["PowerUpShader"], modelMatrix, powerUpColor[(PowerUpType)it.second]);
			}



		}
		if (it.first->globalRotation > -5 && it.first->globalRotation < 5 && it.first->dead)
			generatePowerUp((PowerUpType)it.second, idx);

		idx++;
	}
}

void Tema2::Update(float deltaTimeSeconds)
{
	//render the sky box
	glm::mat4 skyMM = glm::mat4(1);
	skyMM = glm::translate(skyMM, glm::vec3(0, 2.f, 0));
	skyMM = glm::scale(skyMM, glm::vec3(100));
	RenderSkyBox(skyMM);

	//compute the model matrix of the plane
	glm::mat4 planeModelMatrix = glm::mat4(1);
	planeModelMatrix = glm::translate(planeModelMatrix, plane->planePosition);
	planeModelMatrix = glm::scale(planeModelMatrix, glm::vec3(0.1, 0.1, 0.1));
	if (plane->dead)
	{
		planeModelMatrix = glm::rotate(planeModelMatrix, RADIANS(plane->degrees_dead), glm::vec3(0, 1, 0));
	}
	if (cameraType != 'f')
		planeModelMatrix = glm::rotate(planeModelMatrix, RADIANS(plane->degrees), glm::vec3(1, 0, 0));
	else
		planeModelMatrix = glm::rotate(planeModelMatrix, RADIANS(-15), glm::vec3(1, 0, 0));
	planeModelMatrix = glm::rotate(planeModelMatrix, RADIANS(90), glm::vec3(0, 1, 0));

	if (cameraType == 'f')
	{
		collisionPoints[0] = collisionPointFP + glm::vec3(0, 0.5f, 0.5f);
		collisionPoints[1] = collisionPointFP + glm::vec3(0, 0.5f, -0.5f);
		collisionPoints[2] = collisionPointFP + glm::vec3(0, -0.5f, -0.5f);
		collisionPoints[3] = collisionPointFP + glm::vec3(0, -0.5f, 0.5f);
	}
	else
	{
		collisionPoints[0] = collisionPointTP + glm::vec3(0, 0.5f, 0.5f);
		collisionPoints[1] = collisionPointTP + glm::vec3(0, 0.5f, -0.5f);
		collisionPoints[2] = collisionPointTP + glm::vec3(0, -0.5f, -0.5f);
		collisionPoints[3] = collisionPointTP + glm::vec3(0, -0.5f, 0.5f);
	}
	for (int i = 0; i < 4; i++)
		collisionPoints[i] = planeModelMatrix * glm::vec4(collisionPoints[i], 1);

	//particles
	renderParticlesF();
	
	//clouds
	renderClouds();

	//obstacles
	renderObstacles();
	
	renderFuel();
	
	renderPowerUps();
	
	//render the sea
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(5, 40, 40));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.f, -0.8f , 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(seaRotation), glm::vec3(1, 0, 0));
		RenderMesh(meshes["sea"], shaders["SeaShader"], modelMatrix);
	}

	//if the camera's third person, render the propeller. If it's not, don;t hurt your eyes...
	if (cameraType != 'f')
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, plane->planePosition);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 0.1));
		if (plane->dead)
			modelMatrix = glm::rotate(modelMatrix, RADIANS(plane->degrees_dead), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(plane->degrees), glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(propellerRotationDegrees), plane->rotationVector);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
		RenderMesh(meshes["propeller"], shaders["PlaneShader"], modelMatrix);
	}

	//update the camera
	cameraCenter = planeModelMatrix * glm::vec4(originalCameraCenter, 1);
	fpCameraPosition = planeModelMatrix * glm::vec4(originalFPPosition, 1);

	if (cameraType == 'f')
	{
		camera->Update(fpCameraPosition, cameraCenter);
	}


	//render the plane mesh
	RenderMesh(meshes["plane"], shaders["PlaneShader"], planeModelMatrix);

	//switch to third person if the plane's dead
	if (plane->dead && cameraType == 'f')
	{
		cameraType = 't';
		plane->cameraType = 't';
		plane->degrees = 0;
		plane->deadSpeed = 0.05f;
		PropellerSpeed = 1000;
		camLookAtT = glm::vec3(0, camPosT[1] - 3, 0);
		camera->Set(camPosT, camLookAtT, glm::vec3(0, 1, 0));
	}

}

//load the cubemap texture !!not my code, it's from a tutorial!!
unsigned int Tema2::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void Tema2::RenderSkyBox(const glm::mat4& modelMatrix)
{
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_FALSE);

	Mesh* mesh = meshes["box"];
	Shader* shader = shaders["SkyBox"];
	Texture2D* texture = mapTextures["grass"];
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	shader->Use();

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glActiveTexture(GL_TEXTURE0); //bind the skybox texture

	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);

	glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
}

//Render the HUD
void Tema2::HUD()
{
	Shader* shader = shaders["VertexColor"];
	shader->Use();

	glm::mat4 projectionMatrix = glm::ortho(0.f, 1.f, 1.f, 0.f, -1.f, 20.0f); //declare the new projection Matrix,viewMatrix
	glm::vec3 aux = glm::vec3(0,0,0);
	glm::mat4 viewMatrix = glm::lookAt(aux, glm::vec3(aux[0],aux[1],aux[2]-5),glm::vec3(0,1,0) );

	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix)); //and pass them to the shader
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 mm;
	
	//render the lives
	for (int i = 1; i <= plane->lives; i++) 
	{
		mm = glm::mat4(1);
		mm = glm::translate(glm::mat4(1), glm::vec3(0.075f*i, 0.075f, 0.f));
		mm = glm::rotate(mm, RADIANS(180), glm::vec3(1, 0, 0));
		mm = glm::scale(mm, glm::vec3(0.0075f, 0.015f, 0.015f));
		glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(mm));
		meshes["life"]->Render();
	}

	//render the fuel bars
	{
		mm = glm::mat4(1);
		mm = glm::translate(glm::mat4(1), glm::vec3(0.975f, 0.075f, 0.f));
		mm = glm::scale(mm, glm::vec3(3 * plane->gasTank / 100, 0.8f, 0.8f));
		glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(mm));
		meshes["fuelBar"]->Render();

		mm = glm::mat4(1);
		mm = glm::translate(glm::mat4(1), glm::vec3(0.975f, 0.075f, 0.f));
		mm = glm::scale(mm, glm::vec3(3.f, 0.8f, 0.8f));
		glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(mm));
		meshes["fuelBar2"]->Render();
	}

	shader = shaders["PowerUpShader"]; //change shader
	shader->Use();

	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	//invincibility remaining time
	mm = glm::mat4(1);
	mm = glm::translate(glm::mat4(1), glm::vec3(0.975f, 0.175f, 0.f));
	mm = glm::scale(mm, glm::vec3(3 * invincibilityTime /10 , 0.8f, 0.8f));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(mm));
	int loc_color = glGetUniformLocation(shader->program, "color");
	glUniform3fv(loc_color, 1, glm::value_ptr( powerUpColor[INVINCIBILITY]));
	meshes["fuelBar"]->Render();

	//slowdown remaining time
	mm = glm::mat4(1);
	mm = glm::translate(glm::mat4(1), glm::vec3(0.975f, 0.275f, 0.f));
	mm = glm::scale(mm, glm::vec3(3 * slowDownTime / 10, 0.8f, 0.8f));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(mm));
	loc_color = glGetUniformLocation(shader->program, "color");
	glUniform3fv(loc_color, 1, glm::value_ptr(powerUpColor[SLOWDOWN]));
	meshes["fuelBar"]->Render();

	//speedup remaining time
	mm = glm::mat4(1);
	mm = glm::translate(glm::mat4(1), glm::vec3(0.975f, 0.275f, 0.f));
	mm = glm::scale(mm, glm::vec3(3 * speedUpTime / 10, 0.8f, 0.8f));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(mm));
	loc_color = glGetUniformLocation(shader->program, "color");
	glUniform3fv(loc_color, 1, glm::value_ptr(powerUpColor[SPEEDUP]));
	meshes["fuelBar"]->Render();
}

void Tema2::FrameEnd()
{
	HUD();
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;
	shader->Use();
	int loc_eyepos = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eyepos, 1, glm::value_ptr(camera->position));

	int loc_lightpos = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(loc_lightpos, 1, glm::value_ptr(light_pos));

	int loc_shine = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1f(loc_shine, shiny);

	int loc_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(loc_kd, kd);

	int loc_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(loc_ks, ks);

	// render an object using the specified shader and the specified position
	
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	int loc_time = glGetUniformLocation(shader->program, "Time");
	glUniform1f(loc_time,RADIANS(time));

	mesh->Render();
}

//Render a mesh which has all the vertices of color "color"
void Tema2::RenderMeshColor(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix,const glm::vec3& color)
{
	if (!mesh || !shader || !shader->program)
		return;
	shader->Use();

	int loc_eyepos = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eyepos, 1, glm::value_ptr(camera->position));

	int loc_lightpos = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(loc_lightpos, 1, glm::value_ptr(light_pos));

	int loc_shine = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1f(loc_shine, shiny);

	int loc_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(loc_kd, kd);

	int loc_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(loc_ks, ks);

	// render an object using the specified shader and the specified position
	
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	int loc_color = glGetUniformLocation(shader->program, "color");
	glUniform3fv(loc_color, 1,glm::value_ptr(color));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (speed < 15.f && !plane->dead) //increase plane speed over time with a limit of 15
	{
		speed += 0.001f;
	}

	if (invincibilityTime > 0) //decrease powe up time
	{
		invincibilityTime -= 0.05f;
	}

	if (speedUpTime > 0)
	{
		speedUpTime -= 0.1f;
	}
	else
	{
		speedUpTime = 0;
	}

	if (slowDownTime>0)
	{
		slowDownTime -= 0.1f;
	}
	else
	{
		slowDownTime = 0;
	}

	if (returnSpeed) //if the power up is depleated, return to the normal speed
	{
		if (flightType == 1 && speedUpTime == 0)
		{
			speed -= 5.f;
			returnSpeed = false;
			flightType = 0;
		}
		if (flightType == 2 && slowDownTime == 0)
		{
			speed += 5.f;
			returnSpeed = false;
			flightType = 0;
		}
	}



	if(!plane->dead) //if the plane's up and running, burn some fuel
		plane->gasTank -= deltaTime*5;

	if (plane->gasTank < 0)
	{
		plane->dead = true;
		plane->deadSpeed = 0.05f;
		plane->gasTank = 0;
	}

	if (plane->dead) //if the plane is dead, initialize the death animation
	{
		plane->BUUUUUURN(deltaTime);
		speed -= 0.05f;
		if (speed < 0)
			speed = 0;
	}

	propellerRotationDegrees += deltaTime * PropellerSpeed; //rotate the propeller
	if (propellerRotationDegrees > 360) propellerRotationDegrees = 0;

	seaRotation += deltaTime * speed; //rotate the sea
	if (seaRotation >= 360)
	{
		seaRotation = 0;
	}

	time += 100*deltaTime; //get the time

	obstacleRotation += 300*deltaTime; //rotate obstacles

	bool addObstacles = false; //update obstacles, fuel cells, clouds and power ups positions and increase the difficulty
	for (auto it : obstacles)
	{
		it->globalRotation += deltaTime * speed;
		if (it->globalRotation > 360)
		{
			addObstacles = true;
			it->globalRotation = 0;
		}
	}
	if (addObstacles && obstacles.size() < 100) //by generating more obstacles, no more than 100, though
		generateObstacles(rand() % 360);

	for (auto it : powerUps)
	{
		it.first->globalRotation += deltaTime * speed;
		if (it.first->globalRotation > 360)
		{
			it.first->globalRotation = 0;
		}
	}

	for (auto it : fuels)
	{
		it->globalRotation += deltaTime * speed;
		if (it->globalRotation > 360)
			it->globalRotation = 0;
	}

	for (auto it : clouds)
	{
		it->globalRotation += deltaTime * speed;
		if (it->globalRotation > 360)
			it->globalRotation = 0;
		for (int i = 0; i < it->positions.size(); i++)
		{
			it->rotate[i][0] += deltaTime * 10;
			it->rotate[i][1] += deltaTime * 10;
			it->rotate[i][2] += deltaTime * 10;

		}
	}

	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 10.f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_L)) {
			Pfov++;
		}

		if (window->KeyHold(GLFW_KEY_K)) {
			Pfov--;
		}

		if (window->KeyHold(GLFW_KEY_M)) {
			latime += 0.01f;
		}

		if (window->KeyHold(GLFW_KEY_N)) {
			latime -= 0.01f;
		}

		if (window->KeyHold(GLFW_KEY_V)) {
			inaltime += 0.01f;
		}

		if (window->KeyHold(GLFW_KEY_B)) {
			inaltime -= 0.01f;
		}

		
	}

	if (cameraType == 't')
		projectionMatrix = glm::perspective(RADIANS(Pfov), window->props.aspectRatio, 0.01f, 200.0f);
	if (cameraType == 'f')
		projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, 0.01f, 300.0f);

	plane->Stabilize(camera,cameraType,&camPosT,&camLookAtT);	//stabilize the plane, TS ROCKS

	PropellerSpeed = 1000 + plane->degrees * 10; //alterate the propeller speed according to the plane acceleration
	if (plane->dead) PropellerSpeed = 0; //or make it 0 if the plane's dead
}

void Tema2::OnKeyPress(int key, int mods)
{

	if (key == GLFW_KEY_P) //enable particles
	{
		renderParticles = !renderParticles;
	}

	if (key == GLFW_KEY_C && !plane->dead) //switch between camera types
	{
		if (cameraType == 'f')
		{
			cameraType = 't';
			plane->cameraType = 't';
			plane->degrees = 0;
			PropellerSpeed = 1000;
			camLookAtT = glm::vec3(0, camPosT[1] - 3, 0);
			camera->Set(camPosT, camLookAtT, glm::vec3(0, 1, 0));
		}
		else
		{
			cameraType = 'f';
			PropellerSpeed = 10;
			camPosT[1] = camera->position[1];
			camLookAtT[1] = camera->center[1];
			camera->Set(fpCameraPosition, cameraCenter, glm::vec3(0, 1, 0));
			plane->cameraType = 'f';
			plane->degrees = -15;
		}
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && !plane->dead) //if you hold the left mouse button and you're not dead, you can control the plane
	{
			
		float sensivityOX = 0.01f;
		float sensivityOY = 0.01f;
		plane->Vertical_Move((float)deltaY * sensivityOY, true);

		{ //update the camera accordingly
			float val, mouseY = -(float)deltaY * sensivityOY;
			if (mouseY > 0)
				val = std::min(mouseY, 1.f);
			else
				val = std::max(mouseY, -1.f);

			if (cameraType == 't')
				camera->MoveUpward(val);
			else
				camPosT[1] += val;
		}
	}


	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-(float)deltaY * sensivityOX);
			camera->RotateFirstPerson_OY(-(float)deltaX * sensivityOY);

		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-(float)deltaY * sensivityOX);
			camera->RotateThirdPerson_OY(-(float)deltaX * sensivityOY);
		}

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	clickedX = mouseX;
	clickedY = mouseY;
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	clickedX = -1;
	clickedY = -1;
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
