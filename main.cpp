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

void printT(Terrain *e);

int main(int argc, char** argv){
	cout<<argv[2]<<"::::::::::::::::\n";
	GluTerrain *gt = new GluTerrain(10, 1122, 683, atoi(argv[2]));
	gt->init(argc, argv);

}

void printT(Terrain *e){
	cout <<"size: "<<e->size<<":::max: "<<e->max<<"\n";
	int mapLenght  = e->mapLenght;
	for (int i = 0; i < mapLenght; ++i)
	{
		if(e->map[i] <= 0.0)
			cout <<"#"<<i<<" "<<e->map[i]<< "#";
	}

	cout <<"\n";

}
