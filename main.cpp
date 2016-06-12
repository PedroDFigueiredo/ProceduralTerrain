/**
	g++ -o main GluTerrainShade.cpp Terrain.cpp main.cpp -lGL -lGLU -lglut -lGL -lGLU -lglut
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "GluTerrain.h"
#include <GL/glut.h>

int main(int argc, char** argv) {
	float roghness =1.5;
	int displayMode = 0;

	if(argc > 2)
		roghness = atoi(argv[2]);

	if(argc > 3)
		displayMode = (int) atoi(argv[3]);
	
	GluTerrain *gt = new GluTerrain(10, 1122, 683, roghness);
	gt->displayMode = displayMode;
	gt->init(argc, argv);
}
