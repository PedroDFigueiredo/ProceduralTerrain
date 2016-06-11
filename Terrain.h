#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

struct Node{
	float x;
	float y;
	float z;
};

class Terrain{
public:
	int size, max, mapLenght, windowW, windowH;
	
	float *map, roughness, xi, yi, zi, b;

	Terrain();
	Terrain(int details, int width, int height);
	int get(int x, int y);
	void set(int x, int y, float);
	void generate(float roughness);
	void divide(int sizeParam);

	
	void square(int x, int y, int sizeParam, float offset);
	void diamond(int x, int y, int sizeParam, float offset);
	void draw(int x, int y);
private:
	float brightness(int x, int y, float slope, float max);
	void project(Node *node, float flatX, float flatY, float flatZ, int sizeParam);
};