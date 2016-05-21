/**
	g++ -o main GluTerrain.cpp Terrain.cpp main.cpp -lGL -lGLU -lglut -lGL -lGLU -lglut

*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "GluTerrain.h"
#include <GL/glut.h>

int main(int argc, char** argv){
	float roghness =1.5;
	int displayMode = 0;

	if(argv[2])
		roghness = atoi(argv[2]);

	if(argv[3])
		displayMode = (int) atoi(argv[3]);
	
	GluTerrain *gt = new GluTerrain(10, 1122, 683, roghness);
	gt->displayMode = displayMode;
	gt->init(argc, argv);

}
