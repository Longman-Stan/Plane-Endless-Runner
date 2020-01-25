#include "Objects.h"

Mesh* Objects::CreatePlane(std::string plane_name)
{

	glm::vec4 planeColor = glm::vec4(0.f, 0.39f, 0.f, 1.f);
	glm::vec4 glass = glm::vec4(0.f, 0.75f, 1.f, 0.f);
	glm::vec4 red = glm::vec4(1.f, 0.f, 0.f, 1.f);
	glm::vec4 redish = glm::vec4(0.8f, 0.f, 0.f, 1.f);
	glm::vec4 black = glm::vec4(0.f, 0.f, 0.f, 1.f);
	glm::vec4 skin = glm::vec4(0.96f, 0.96f, 0.86f,1.f);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0.f,0.f,0.f), planeColor), //0
		VertexFormat(glm::vec3(-1.f,2.f,-2.f), planeColor), //1
		VertexFormat(glm::vec3(-1.f, 0.5f ,-8.f), planeColor), //2
		VertexFormat(glm::vec3(1.f, 0.5f ,-8.f), planeColor), //3
		VertexFormat(glm::vec3(2.f, 2.f, -2.f), planeColor), //4
		VertexFormat(glm::vec3(4.f, 1.f, -1.f), planeColor), //5
		VertexFormat(glm::vec3(4.f, 1.f, 1.f), planeColor), //6
		VertexFormat(glm::vec3(2.f, 2.f, 2.f), planeColor), //7
		VertexFormat(glm::vec3(1.f, 0.5f ,8.f), planeColor), //8
		VertexFormat(glm::vec3(-1.f, 0.5f, 8.f), planeColor), //9
		VertexFormat(glm::vec3(-1.f, 2.f, 2.f), planeColor), //10
		VertexFormat(glm::vec3(0,0,0), planeColor), //11 -am uitat sa-l pun cand am desenat mesa, aia e
		VertexFormat(glm::vec3(-7.f, 1.f, 1.f), planeColor), //12
		VertexFormat(glm::vec3(-7.f, 0.25f, 3.f), planeColor), //13
		VertexFormat(glm::vec3(-6.f, 0.25f, 3.f), planeColor), //14
		VertexFormat(glm::vec3(-5.f, 1.f, 1.f), planeColor), //15
		VertexFormat(glm::vec3(-5.f, 1.f, -1.f), planeColor), //16
		VertexFormat(glm::vec3(-6.f, 0.25f, -3.f), planeColor), //17
		VertexFormat(glm::vec3(-7.f, 0.25f, -3.f), planeColor), //18
		VertexFormat(glm::vec3(-7.f, 1.f, -1.f), planeColor), //19
		VertexFormat(glm::vec3(-7.f, 4.f, 0.25f), planeColor), //20
		VertexFormat(glm::vec3(-7.f, 4.f, -0.25f), planeColor), //21
		VertexFormat(glm::vec3(-6.f, 4.f, -0.25f), planeColor), //22
		VertexFormat(glm::vec3(-5.f, 1.f, -0.5f), planeColor), //23
		VertexFormat(glm::vec3(-5.f, 1.f, 0.5f), planeColor), //24
		VertexFormat(glm::vec3(-6.f, 4.f, 0.25f), planeColor), //25
		VertexFormat(glm::vec3(1.5f, 2.f, 1.5f), glass), //26
		VertexFormat(glm::vec3(2.f, 2.f, 1.f), glass), //27
		VertexFormat(glm::vec3(2.f, 2.f, -1.f), glass), //28
		VertexFormat(glm::vec3(1.5f, 2.f, -1.5f), glass), //29
		VertexFormat(glm::vec3(1.5f, 3.f, -1.f), glass), //30
		VertexFormat(glm::vec3(1.5f, 3.f, 1.f), glass), //31
		VertexFormat(glm::vec3(2.f, 1.f, 2.f), planeColor), //32
		VertexFormat(glm::vec3(-1.f, 1.f, 2.f), black), //33
		VertexFormat(glm::vec3(-1.f, -1.f, 2.f), black), //34
		VertexFormat(glm::vec3(2.f, -1.f, 2.f), planeColor), //35
		VertexFormat(glm::vec3(1.f, -0.5f, 8.f), planeColor), //36
		VertexFormat(glm::vec3(-1.f, -0.5f, 8.f), planeColor), //37
		VertexFormat(glm::vec3(-5.f, -0.25f, 1.f), planeColor), //38
		VertexFormat(glm::vec3(-6.f, -0.25f, 3.f), planeColor), //39
		VertexFormat(glm::vec3(-7.f, -0.25f, 3.f), planeColor), //40
		VertexFormat(glm::vec3(-7.f, -1.f, 1.f), planeColor), //41
		VertexFormat(glm::vec3(-1.f, -2.f, 2.f), planeColor), //42
		VertexFormat(glm::vec3(2.f, -2.f, 2.f), planeColor), //43
		VertexFormat(glm::vec3(4.f, -1.f, 1.f), planeColor), //44
		VertexFormat(glm::vec3(-1.f, 1.f, -2.f), black), //45
		VertexFormat(glm::vec3(2.f, 1.f, -2.f), planeColor), //46
		VertexFormat(glm::vec3(2.f, -1.f, -2.f), planeColor), //47
		VertexFormat(glm::vec3(-1.f, -1.f, -2.f), black), //48
		VertexFormat(glm::vec3(-1.f, -0.5f, -8.f), planeColor), //49
		VertexFormat(glm::vec3(1.f, -0.5f, -8.f), planeColor), //50
		VertexFormat(glm::vec3(-5.f, -0.25f, -1.f), planeColor), //51
		VertexFormat(glm::vec3(-6.f, -0.25f, -3.f), planeColor), //52
		VertexFormat(glm::vec3(-7.f, -0.25f, -3.f), planeColor), //53
		VertexFormat(glm::vec3(-7.f, -1.f, -1.f), planeColor), //54
		VertexFormat(glm::vec3(-1.f, -2.f, -2.f), planeColor), //55
		VertexFormat(glm::vec3(2.f, -2.f, -2.f), planeColor), //56
		VertexFormat(glm::vec3(4.f, -1.f, -1.f), planeColor), //57
		VertexFormat(glm::vec3(0.f, 3.f, 0.5f), black), //58
		VertexFormat(glm::vec3(0.f, 3.f, -0.5f), black), //59
		VertexFormat(glm::vec3(0.25f, 2.25f, -0.5f), red), //60
		VertexFormat(glm::vec3(0.25f, 2.25f, -1.f), red), //61
		VertexFormat(glm::vec3(0.75f, 2.25f, -1.f), red), //62
		VertexFormat(glm::vec3(0.75f, 2.25f, -0.5f), red), //63
		VertexFormat(glm::vec3(1.f, 3.f, -0.5f), black), //64
		VertexFormat(glm::vec3(1.f, 3.f, 0.5f), black), //65
		VertexFormat(glm::vec3(0.75f, 2.25f, 0.5f), red), //66
		VertexFormat(glm::vec3(0.75f, 2.25f, 1.f), red), //67
		VertexFormat(glm::vec3(0.25f, 2.25f, 1.f), red), //68
		VertexFormat(glm::vec3(0.25f, 2.25f, 0.5f), red), //69
		VertexFormat(glm::vec3(0.f, 2.f, 0.5f), redish), //70
		VertexFormat(glm::vec3(0.f, 2.f, -0.5f), redish), //71
		VertexFormat(glm::vec3(0.25f, 2.f, -0.5f), red), //72
		VertexFormat(glm::vec3(0.25f, 2.f, -1.f), red), //73
		VertexFormat(glm::vec3(0.75f, 2.f, -1.f), red), //74
		VertexFormat(glm::vec3(0.75f, 2.f, -0.5f), red), //75
		VertexFormat(glm::vec3(1.f, 2.f, -0.5f), redish), //76
		VertexFormat(glm::vec3(1.f, 2.f, 0.5f), redish), //77
		VertexFormat(glm::vec3(0.75f, 2.f, 0.5f), red), //78
		VertexFormat(glm::vec3(0.75f, 2.f, 1.f), red), //79
		VertexFormat(glm::vec3(0.25f, 2.f, 1.f), red), //80
		VertexFormat(glm::vec3(0.25f, 2.f, 0.5f), red), //81

		VertexFormat(glm::vec3(0.f, 2.25f, 0.5f), redish), //82 //gat haina
		VertexFormat(glm::vec3(0.f, 2.25f, -0.5f), redish), //83
		VertexFormat(glm::vec3(1.f, 2.25f, -0.5f), redish), //84
		VertexFormat(glm::vec3(1.f, 2.25f, 0.5f), redish), //85

		VertexFormat(glm::vec3(0.f, 2.25f, 0.5f), skin), //86 //gat piele
		VertexFormat(glm::vec3(0.f, 2.25f, -0.5f), skin), //87
		VertexFormat(glm::vec3(1.f, 2.25f, -0.5f), skin), //88
		VertexFormat(glm::vec3(1.f, 2.25f, 0.5f), skin), //89

		VertexFormat(glm::vec3(1.f, 3.f, -0.5f), skin), //90 //frunte
		VertexFormat(glm::vec3(1.f, 3.f, 0.5f), skin), //91

		VertexFormat(glm::vec3(0.f, 2.25f, 0.5f), black), //92 //ceafa
		VertexFormat(glm::vec3(0.f, 2.25f, -0.5f), black), //93

		VertexFormat(glm::vec3(-7.f, 0.5f, 1.f), black), //94 -12 jos
		VertexFormat(glm::vec3(-7.f, 0.5f, -1.f), black), //95 -19 jos

		VertexFormat(glm::vec3(-7.f, -0.5f, 1.f), black), //96 -12 si mai jos
		VertexFormat(glm::vec3(-7.f, -0.5f, -1.f), black), //97 -19 si mai jos

		VertexFormat(glm::vec3(-7.f, 1.f, 0.5f), black), //98 -20 mai jos
		VertexFormat(glm::vec3(-7.f, 1.f, -0.5f), black) //99 -21 si mai jos

	};

	for (auto it : vertices)
		it.normal = it.position;

	std::vector<unsigned short> indices =
	{

		//put the pilot

		//head
		58,59,64,
		58,64,65,
		58,92,59,
		59,92,93,

		58,65,92,
		59,93,64,

		89,86,91,
		87,88,90,

		91,90,88,
		91,88,89,

		60,61,62,
		60,62,63,
		60,72,73,
		60,73,61,
		62,61,74,
		61,73,74,
		63,62,74,
		63,74,75,

		68,69,66,
		68,66,67,
		69,68,81,
		68,80,81,
		68,67,80,
		67,79,80,
		67,66,78,
		67,78,79,

		83,82,71,
		82,70,71,
		84,83,71,
		84,71,76,
		85,84,76,
		85,76,77,
		82,85,77,
		82,77,70,

		//corp superior
		12,19,1,
		12,1,10,
		10,1,4,
		10,4,7,
		7,4,5,
		7,5,6,

		//corp lateral dreapta
		12,10,41,
		10,42,41,
		10,7,42,
		7,43,42,
		7,6,44,
		7,44,43,

		//corp lateral stanga
		1,19,54,
		1,54,55,
		1,55,56,
		56,4,1,
		4,56,57,
		4,57,5,

		//corp inferior 
		55,54,42,
		42,54,41,
		56,42,43,
		56,55,42,
		57,43,44,
		56,43,57,

		//fata 
		6,5,57,
		6,57,44,

		//spate
		19,12,41,
		19,41,54,

		//aripa mica stanga
		95,18,17, //top
		95,17,16, 
		16,17,51, //front
		17,52,51,
		17,18,53, //out
		17,53,52,
		52,53,97, //bottom
		52,97,51,
		18,95,97, //back
		18,97,53,

		//aripa mica dreapta
		13,94,15, //top
		13,15,14,
		14,15,38, //front
		14,38,39,
		13,14,39, //out
		13,39,40,
		96,39,38, //bottom
		96,40,39,
		94,13,96, //back
		13,40,96,

		//aripa mica sus
		20,21,22, //top
		20,22,25,
		25,22,23, //front
		25,23,24,
		20,25,24, //right
		20,24,98,
		22,21,99, //left
		22,99,23,
		21,20,98, //back
		21,98,99,

		//aripa stanga
		45,2,3, //top
		45,3,46, 
		3,2,50, //out
		2,49,50,
		50,49,48,
		48,47,50, //bottom
		50,47,3,
		3,50,47, //front
		3,47,46,
 		45,48,49, //back
		45,49,2,
	
		//aripa dreapta
		32,8,33, //top
		8,9,33,
		9,8,36, //out
		9,36,37,
		37,36,34, //bottom
		36,35,34,
		32,35,8, //front
		8,35,36, 
		33,9,34, //back
		9,37,34,

		//windshield
		26,31,27,
		30,29,28,
		31,30,27,
		30,28,27,

	};

	Mesh* plane = new Mesh(plane_name);
	plane->InitFromData(vertices, indices);

	return plane;
}

Mesh* Objects::CreatePropeller(std::string name)
{

	glm::vec4 trunk = glm::vec4(0.2f, 0.2f, 0.2f , 1.f);
	glm::vec4 prop = glm::vec4(0.7f, 0.7f, 0.7f, 1.f);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(4.f, 0.5f, 0.5f),trunk), //0
		
		//trunk
		VertexFormat(glm::vec3(4.5f, 0.5f, 0.5f),trunk), //1
		VertexFormat(glm::vec3(4.5f, 0.5f, -0.5f),trunk), //2
		VertexFormat(glm::vec3(4.5f, -0.5f, -0.5f),trunk), //3
		VertexFormat(glm::vec3(4.5f, -0.5f, 0.5f),trunk), //4

		VertexFormat(glm::vec3(4.f, 0.75f, 0.75f),trunk), //5
		VertexFormat(glm::vec3(4.f, 0.75f, -0.75f),trunk), //6
		VertexFormat(glm::vec3(4.f, -0.75f, -0.75f),trunk), //7
		VertexFormat(glm::vec3(4.f, -0.75f, 0.75f),trunk), //8

		//propeller top
		VertexFormat(glm::vec3(4.f, 0.25f, 0.25f),prop), //9
		VertexFormat(glm::vec3(4.f, 0.25f, -0.25f),prop), //10
		VertexFormat(glm::vec3(4.f, 3.f, -0.3f),prop), //11
		VertexFormat(glm::vec3(4.f, 3.f, 0.3f),prop), //12
		VertexFormat(glm::vec3(4.25f, 0.25f, 0.25f),prop), //13
		VertexFormat(glm::vec3(4.25f, 0.25f, -0.25f),prop), //14
		VertexFormat(glm::vec3(4.25f, 3.f, -0.3f),prop), //15
		VertexFormat(glm::vec3(4.25f, 3.f, 0.3f),prop), //16

		//propeller right
		VertexFormat(glm::vec3(4.f, 0.25f, -0.25f),prop), //17
		VertexFormat(glm::vec3(4.f, -0.25f, -0.25f),prop), //18
		VertexFormat(glm::vec3(4.f, 0.3f, -3.f),prop), //19
		VertexFormat(glm::vec3(4.f, -0.3f, -3.f),prop), //20

		VertexFormat(glm::vec3(4.25f, 0.25f, -0.25f),prop), //21
		VertexFormat(glm::vec3(4.25f, -0.25f, -0.25f),prop), //22
		VertexFormat(glm::vec3(4.25f, 0.3f, -3.f),prop), //23
		VertexFormat(glm::vec3(4.25f, -0.3f, -3.f),prop), //24

		//propeller bot
		VertexFormat(glm::vec3(4.f, -0.25f, -0.25f),prop), //25
		VertexFormat(glm::vec3(4.f, -0.25f, 0.25f),prop), //26
		VertexFormat(glm::vec3(4.f, -3.f, -0.3f),prop), //27
		VertexFormat(glm::vec3(4.f, -3.f, 0.3f),prop), //28
		VertexFormat(glm::vec3(4.25f, -0.25f, -0.25f),prop), //29
		VertexFormat(glm::vec3(4.25f, -0.25f, 0.25f),prop), //30
		VertexFormat(glm::vec3(4.25f, -3.f, -0.3f),prop), //31
		VertexFormat(glm::vec3(4.25f, -3.f, 0.3f),prop), //32

		//propeller left
		VertexFormat(glm::vec3(4.f, 0.25f, 0.25f),prop), //33
		VertexFormat(glm::vec3(4.f, -0.25f, 0.25f),prop), //34
		VertexFormat(glm::vec3(4.f, 0.3f, 3.f),prop), //35
		VertexFormat(glm::vec3(4.f, -0.3f, 3.f),prop), //36
		VertexFormat(glm::vec3(4.25f, 0.25f, 0.25f),prop), //37
		VertexFormat(glm::vec3(4.25f, -0.25f, 0.25f),prop), //38
		VertexFormat(glm::vec3(4.25f, 0.3f, 3.f),prop), //39
		VertexFormat(glm::vec3(4.25f, -0.3f, 3.f),prop), //40
	};

	std::vector<unsigned short> indices =
	{
		1,2,3,
		1,3,4,
		5,6,2,
		5,2,1,
		5,1,4,
		5,4,8,
		2,6,7,
		2,7,3,
		4,3,7,
		4,7,8,
		6,5,7,
		5,7,8,

		10,9,11,
		9,11,12,
		9,10,14,
		9,14,13,
		9,13,16,
		9,16,12,
		14,10,11,
		14,11,15,
		13,14,15,
		13,15,16,
		12,15,11,
		12,16,15,

		17,21,22,
		17,22,18,
		21,23,24,
		21,24,22,
		17,19,23,
		17,23,21,
		22,24,20,
		22,20,18,
		17,18,20,
		17,20,19,
		23,19,20,
		23,20,24,

		26,25,29,
		26,29,30,
		30,29,31,
		30,31,32,
		26,30,32,
		26,32,28,
		29,25,27,
		29,27,31,
		25,26,27,
		26,27,28,
		32,31,27,
		32,27,28,

		37,33,34,
		37,34,38,
		39,37,38,
		39,38,40,
		35,33,37,
		35,37,39,
		33,35,36,
		33,36,34,
		35,39,36,
		39,36,40,
		38,34,36,
		38,36,40

	};
	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, indices);
	return mesh;
}

Mesh* Objects::CreateSkyBox(std::string name)
{
	glm::vec3 sky = glm::vec3(0.51f, 0.40f, 0.53f);
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.5f,0.5f,0.5f),sky),//0
		VertexFormat(glm::vec3(-0.5f,0.5f,-0.5f),sky),//1
		VertexFormat(glm::vec3(0.5f,0.5f,-0.5f),sky),//2
		VertexFormat(glm::vec3(0.5f,0.5f,0.5f),sky),//3
		VertexFormat(glm::vec3(-0.5f,-0.5f,0.5f),sky),//4
		VertexFormat(glm::vec3(-0.5f,-0.5f,-0.5f),sky),//5
		VertexFormat(glm::vec3(0.5f,-0.5f,-0.5f),sky),//6
		VertexFormat(glm::vec3(0.5f,-0.5f,0.5f),sky),//7
	};

	std::vector<unsigned short> indices =
	{
		2,1,0,
		0,3,2,
		0,4,3,
		4,7,3,
		7,2,3,
		7,6,2,
		1,5,4,
		1,4,0,
		2,6,5,
		2,5,1,
		5,6,7,
		5,7,4
	};

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, indices);

	return mesh;
}

Mesh* Objects::CreateCloudPart(std::string cloudPart, char index)
{
	glm::vec3 cloudColor;
	
	if (index == 0)
		cloudColor = glm::vec3(0.5f, 0.5f, 0.5f);
	else
		cloudColor = glm::vec3(0.4f, 0.4f, 0.4f);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.5f,0.5f,0.5f),cloudColor),//0
		VertexFormat(glm::vec3(-0.5f,0.5f,-0.5f),cloudColor),//1
		VertexFormat(glm::vec3(0.5f,0.5f,-0.5f),cloudColor),//2
		VertexFormat(glm::vec3(0.5f,0.5f,0.5f),cloudColor),//3
		VertexFormat(glm::vec3(-0.5f,-0.5f,0.5f),cloudColor),//4
		VertexFormat(glm::vec3(-0.5f,-0.5f,-0.5f),cloudColor),//5
		VertexFormat(glm::vec3(0.5f,-0.5f,-0.5f),cloudColor),//6
		VertexFormat(glm::vec3(0.5f,-0.5f,0.5f),cloudColor),//7
	};

	for (auto it : vertices)
		it.normal = it.position;

	std::vector<unsigned short> indices =
	{
		2,1,0,
		0,3,2,
		0,4,3,
		4,7,3,
		7,2,3,
		7,6,2,
		1,5,4,
		1,4,0,
		2,6,5,
		2,5,1,
		5,6,7,
		5,7,4
	};

	Mesh* mesh = new Mesh(cloudPart);
	mesh->InitFromData(vertices, indices);

	return mesh;
}

#define SQ2 0.70710678118f

Mesh* Objects::CreateObstacle(std::string name)
{
	glm::vec3 obstacle = glm::vec3(0.5f, 0.f, 0.f);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-SQ2,0.f,0.f), obstacle, glm::vec3(-1.f, 0.f, 0.f)), //0
		VertexFormat(glm::vec3(0.f,0.f,-SQ2),obstacle, glm::vec3(0.f, 0.f, -1.f)), //1
		VertexFormat(glm::vec3(SQ2,0.f,0.f), obstacle, glm::vec3(1.f, 0.f, 0.f)), //2
		VertexFormat(glm::vec3(0.f,0.f,SQ2),obstacle, glm::vec3(0.f, 0.f, 1.f)), //3
		VertexFormat(glm::vec3(-0.25f,0.7f,0.25f),obstacle, glm::vec3(0.f,1.f,0.f)), //4
		VertexFormat(glm::vec3(-0.25f,0.7f,-0.25f),obstacle, glm::vec3(0.f,1.f,0.f)), //5
		VertexFormat(glm::vec3(0.25f,0.7f,-0.25f),obstacle , glm::vec3(0.f,1.f,0.f)), //6
		VertexFormat(glm::vec3(0.25f,0.7f,0.25f),obstacle, glm::vec3(0.f,1.f,0.f)), //7
		VertexFormat(glm::vec3(-0.25f,-0.7f,0.25f),obstacle, glm::vec3(0.f,-1.f,0.f)), //8
		VertexFormat(glm::vec3(-0.25f,-0.7f,-0.25f),obstacle, glm::vec3(0.f,-1.f,0.f)), //9
		VertexFormat(glm::vec3(0.25f,-0.7f,0.25f),obstacle, glm::vec3(0.f,-1.f,0.f)), //10
		VertexFormat(glm::vec3(0.25f,-0.7f,-0.25f),obstacle, glm::vec3(0.f,-1.f,0.f)), //11
	};

	for (auto it : vertices)
	{
		it.normal = it.position;
	}

	std::vector<unsigned short> indices = {
		4,5,6,
		4,6,7,
		0,5,4,
		1,6,5,
		7,6,2,
		4,7,3,
		8,9,0,
		9,11,1,
		10,2,11,
		3,10,8,
		10,11,8,
		11,9,8,
		0,4,3,
		0,1,5,
		1,2,6,
		7,2,3,
		9,1,0,
		1,11,2,
		2,10,3,
		8,0,3
	};

	//std::vector<glm::vec3> normals = getNormals(vertices, indices);

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices,indices);
	return mesh;
}

Mesh* Objects::CreateFuel(std::string name)
{
	glm::vec3 fuel = glm::vec3(0.36f, 0.48f, 0.58f);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-1.f, -0.5f, 0.f), fuel, glm::vec3(-1.f, 0.f, 0.f)), //0
		VertexFormat(glm::vec3(0.f, -0.5f, -1.f), fuel,  glm::vec3(0.f, 0.f, -1.f)), //1
		VertexFormat(glm::vec3(1.f, -0.5f, 0.f), fuel,  glm::vec3(1.f, 0.f, 0.f)), //2
		VertexFormat(glm::vec3(0.f, -0.5f, 1.f), fuel,  glm::vec3(0.f, 0.f, -1.f)), //3
		VertexFormat(glm::vec3(0.f, 1.f, 0.f), fuel,  glm::vec3(0.f, 1.f, 0.f)) //4
	};

	std::vector<unsigned short> indices = {
		2,1,0, 
		2,0,3,
		0,1,4,
		4,1,2,
		4,2,3,
		4,3,0
	};

	//std::vector<glm::vec3> normals = getNormals(vertices, indices);

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, indices);
	return mesh;
}

#define MagicNumber (10000+(float)(rand()%1000)-500 )/10000

Mesh* Objects::CreateSea(std::string name)
{
	srand(time(NULL));
	glm::vec3 sea = glm::vec3(0.36f, 0.67f, 0.93f);
	glm::vec3 sea2 = glm::vec3(0.16f, 0.17f, 0.93f);
	glm::vec3 sea3 = glm::vec3(0.27f, 0.4f, 0.93f);
	glm::vec3 sea4 = glm::vec3(0.05f, 0.5f, 0.93f);

	//glm::vec3 sea2 = glm::vec3(0.26f, 0.57f, 0.93f);
	//glm::vec3 sea3 = glm::vec3(0.16f, 0.47f, 0.93f);
	//glm::vec3 sea4 = glm::vec3(0.06f, 0.37f, 0.93f);
	std::vector<VertexFormat> vertices;
	
	int points=0;

	std::vector<float> degrees;
	for (int i = 0; i < 360; i += 5,points++)
		degrees.push_back(i);

	 //= { 0,45,90,135,180,225,270,315 };

	for (int i = 0; i < 6; i++)
	{
		for (int j=0;j<points;j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
				vertices.push_back(VertexFormat(glm::vec3(-(float)2 * i, MagicNumber*sin(RADIANS(degrees[j])), MagicNumber*cos(RADIANS(degrees[j]))), sea, glm::vec3(0, 1, 0)));
			if (i % 2 == 0 && j % 2 == 1)
				vertices.push_back(VertexFormat(glm::vec3(-(float)2 * i, MagicNumber * sin(RADIANS(degrees[j])), MagicNumber * cos(RADIANS(degrees[j]))), sea2, glm::vec3(0, 1, 0)));
			if (i % 2 == 1 && j % 2 == 0)
				vertices.push_back(VertexFormat(glm::vec3(-(float)2 * i, MagicNumber * sin(RADIANS(degrees[j])), MagicNumber * cos(RADIANS(degrees[j]))), sea3, glm::vec3(0, 1, 0)));
			if (i % 2 == 1 && j % 2 == 1)
				vertices.push_back(VertexFormat(glm::vec3(-(float)2 * i, MagicNumber * sin(RADIANS(degrees[j])), MagicNumber * cos(RADIANS(degrees[j]))), sea4, glm::vec3(0, 1, 0)));
		}
	}

	std::vector<unsigned short> indices;

	int i, j, k;
	for (i = 0; i < 5; i++)
	{
		for (j = i * points, k = (i + 1) * points; j < (i + 1) * points - 1; j++, k++)
			if (i % 2 == 0)
			{
				indices.push_back(j); indices.push_back(k + 1); indices.push_back(j + 1);
				indices.push_back(j); indices.push_back(k); indices.push_back(k + 1);
			}
			else
			{
				indices.push_back(j);   indices.push_back(k); indices.push_back(j + 1);
				indices.push_back(j+1); indices.push_back(k); indices.push_back(k + 1);
			}

		if (i % 2 == 0)
		{
			indices.push_back(j); indices.push_back((i+1)* points); indices.push_back(i* points);
			indices.push_back(j); indices.push_back(k); indices.push_back((i+1)* points);
		}
		else
		{
			indices.push_back(j); indices.push_back(k); indices.push_back((i* points));
			indices.push_back(i*points); indices.push_back(k); indices.push_back((i+1)* points);
		}
	}

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, indices);
	return mesh;
}

Mesh* Objects::CreateLife(std::string name)
{
	glm::vec3 red = glm::vec3(0.85f, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(0.f, 0.0f, 0.f), red), //0
		
		VertexFormat(glm::vec3(0.46f, 1.0f, 0.f), red), //1
		VertexFormat(glm::vec3(1.12f, 1.54f, 0.f), red), //2
		VertexFormat(glm::vec3(2.42f, 0.84f, 0.f), red), //3
		VertexFormat(glm::vec3(2.56f, 0.28f, 0.f), red), //4
		VertexFormat(glm::vec3(2.f, -1.52f, 0.f), red), //5
		VertexFormat(glm::vec3(0.96f, -2.32f, 0.f), red), //6

		VertexFormat(glm::vec3(0.f, -3.0f, 0.f), red), //7

		VertexFormat(glm::vec3(-0.96f, -2.32f, 0.f), red), //13
		VertexFormat(glm::vec3(-2.f, -1.52f, 0.f), red), //12
		VertexFormat(glm::vec3(-2.56f, 0.28f, 0.f), red), //11
		VertexFormat(glm::vec3(-2.42f, 0.84f, 0.f), red), //10
		VertexFormat(glm::vec3(-1.12f, 1.54f, 0.f), red), //9
		VertexFormat(glm::vec3(-0.46f, 1.0f, 0.f), red), //8

		VertexFormat(glm::vec3(1.8f, 1.4f, 0.f), red), //14
		VertexFormat(glm::vec3(-1.8f, 1.4f, 0.f), red), //15

		VertexFormat(glm::vec3(2.35f, -0.72f, 0.f), red), //16
		VertexFormat(glm::vec3(-2.35f, -0.72f, 0.f), red), //17
	};

	std::vector<unsigned short> indices = {
		0,1,3,
		1,2,3,
		0,3,4,
		0,4,5,
		0,5,6,
		0,6,7,
		0,7,8,
		0,8,9,
		0,9,10,
		0,10,11,
		0,11,13,
		11,12,13,
		2,14,3,
		11,15,12,
		4,16,5,
		10,9,17
	};
	
	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices,indices);
	return mesh;
}

Mesh* Objects::CreateFuelBar(std::string name)
{
	glm::vec3 fuel = glm::vec3(0.8f, 0.79f, 0.65f);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(0.f, -0.05f, 0.f), fuel), //0
		VertexFormat(glm::vec3(0.f, 0.05f, 0.f), fuel), //1
		VertexFormat(glm::vec3(-0.1f, 0.05f, 0.f), fuel), //2
		VertexFormat(glm::vec3(-0.1f, -0.05f, 0.f), fuel), //3
	};

	std::vector<unsigned short> indices = {
		0,1,2,
		0,2,3
	};

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, indices);
	return mesh;
}

Mesh* Objects::CreateFuelBar2(std::string name)
{
	glm::vec3 fuel = glm::vec3(0.1f, 0.09f, 0.05f);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(0.f, -0.05f, 0.f), fuel), //0
		VertexFormat(glm::vec3(0.f, 0.05f, 0.f), fuel), //1
		VertexFormat(glm::vec3(-0.1f, 0.05f, 0.f), fuel), //2
		VertexFormat(glm::vec3(-0.1f, -0.05f, 0.f), fuel), //3
	};

	std::vector<unsigned short> indices = {
		0,1,2,
		0,2,3
	};

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, indices);
	return mesh;
}
