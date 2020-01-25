#pragma once
#include <Component/SimpleScene.h>
#include "camera.h"
#include "Plane.h"
#include "Cloud.h"
#include "Obstacles.h"
#include "Fuel.h"

enum PowerUpType
{
	LIFE,
	SLOWDOWN,
	SPEEDUP,
	INVINCIBILITY
};

class Tema2 : public SimpleScene
{

public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
	void RenderMeshColor(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix,const glm::vec3& color);
	void RenderSkyBox(const glm::mat4& modelMatrix);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void generateClouds(int GlobalRotation);
	void generateObstacles(int GlobalRotation);
	void generateFuels(int GlobalRotation);
	bool checkCollision(std::vector<glm::vec3> planePoints, glm::vec3 obstaclePosition, float hitBox);

	void generateObstacles(int globalRotation, int position);
	void generateFuels(int globalRotation, int position);
	void generatePowerUps();
	void generatePowerUp(PowerUpType puT);
	void generatePowerUp(PowerUpType puT,int position);

	void generateBrokenPositions(int numberOfPositions,int numberOfPieces);
	
	void loadMeshes();

	void loadShaders();

	void HUD();

	unsigned int loadCubemap(std::vector< std::string > faces);

	void renderParticlesF();
	void renderClouds();
	void renderObstacles();
	void renderFuel();
	void renderPowerUps();

protected:
	Tema2::Camera* camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;

	float Pfov;
	float latime, inaltime;
	char cameraType;

	float propellerRotationDegrees;

	float seaRotation;


	Plane* plane;

	int clickedX, clickedY;
	float time;

	std::vector<Cloud*> clouds;
	std::vector<Obstacles*> obstacles;
	std::vector<Fuel*> fuels;

	glm::vec3 originalFPPosition;
	glm::vec3 originalCameraCenter;
	glm::vec3 cameraCenter;
	glm::vec3 fpCameraPosition;

	float PropellerSpeed;

	float obstacleRotation;
	float obstacleScale;

	glm::vec3 camPosT;
	glm::vec3 camLookAtT;
	float speed;

	glm::vec3 collisionPointFP;
	glm::vec3 collisionPointTP;
	std::vector< glm::vec3> collisionPoints;
	std::vector< glm::vec3> obstacleCollisionPoints;
	float hitBox;

	std::vector<std::pair<Obstacles*,int>> powerUps;

	float speedUpTime;
	float slowDownTime;
	float invincibilityTime;

	bool changeSpeed;
	bool returnSpeed;

	int flightType;

	std::vector< std::vector<glm::vec3>> brokenPositions;
	
	float renderParticles;

	std::unordered_map<std::string, Texture2D*> mapTextures;

	unsigned int cubeMapTexture;

	glm::vec3 light_pos;
	float kd, ks, shiny;
};