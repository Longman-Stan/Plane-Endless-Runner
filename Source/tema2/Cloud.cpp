#include "Cloud.h"

Cloud::Cloud(int numBoxes) //numBoxes = how many boxes form a cloud
{
	float scaleVal;
	float posx=0, posy=0, posz=0;
	posx = rand() % 30 - 15; //generate the first box 
	posy = rand() % 10 + 10; //the sea intersects the Oy axis at 8, so i generate the point above 10 to take into account the sea deformations
	posz = rand() % 20 - 20; //the z coordinate is somewhere on the negative part, not that important, heere just for a more pronounced random factor

	scaleVal = 70+ rand() % 50; //chosen based on observation
	scaleVal /= 100;
	scale.push_back(glm::vec3(scaleVal, scaleVal, scaleVal));
	positions.push_back( glm::vec3(posx,posy,posz));
	rotate.push_back( glm::vec3( rand()%90,rand()%90,rand()%90) ); 

	for (int i = 0; i < numBoxes; i++) //all the othres are linked to this one
	{
		posx += 0.01f;
		posy = posy + ((float)(rand() % 6 - 3)) / 10;
		posz = posz + 0.5 + ((float)(rand() % 3)) / 10;
		positions.push_back(glm::vec3(posx,posy, posz));
		scaleVal =  70 + rand() % 50;
		scaleVal /= 100;
		scale.push_back(glm::vec3(scaleVal, scaleVal, scaleVal));
		rotate.push_back(glm::vec3(rand() % 90, rand() % 90, rand() % 90));
	}

	globalRotation = 0;

}