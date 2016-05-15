#include <GL/glut.h>
#include "Terrain.h"


class GluTerrain{
	public:
	Terrain *terrain;
	int windowX, windowY;

	GluTerrain();
	GluTerrain(int details, int width, int height, float roughness);
	void init(int argc, char** argv);
};
