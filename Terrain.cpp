#include "Terrain.h"

struct Node{
	float x;
	float y;
	float z;
};

struct Style{
	float r, g, b, a;
};

void project(Node *node, float flatX, float flatY, float flatZ, int sizeParam);
float brightness(int x, int y, float get, float max);
float average(float values[4]);

Terrain::Terrain(){};
int WIDTH, HEIGHT;

Terrain::Terrain(int details, int width, int height){
	cout<<"*New Terrain\n";
	windowW = WIDTH = width;
	windowH = HEIGHT = height;

	size = pow(2, details) +1;
	mapLenght = size*size;
	max = size - 1;
	map = (float*) malloc(sizeof(float)*(mapLenght));
	
};

int Terrain::get(int x, int y){
	if(x<0 || x> max | y<0 || y>max)
		return -1;
//	cout<<"x "<<x<<":::"<<" y"<<y<<":::"<<size<<":::"<<(x + size*y)<<"::"<<max<<"\n";
	return map[x + size*y];
}

void Terrain::set(int x, int y, float val){
	map[x + size*y] = val;
}

void Terrain::generate(float rough){
	cout<<"**Starting Generation\n";
	roughness = rough;

    set(0, 0, max+100);
    set(max, 0, max / 2);
    set(max, max, 0);
    set(0, max, max / 2);
    divide(max);
	cout<<"**Finished Generation \n";
}

void Terrain::divide(int sizeParam){
	//cout<<"***Dividing map "<< sizeParam <<"\n";

	float scale = roughness * sizeParam;
	int x, y, half = sizeParam/ 2;
        srand (time(NULL));
	if (half < 1) return;
	for (y = half; y < max; y += sizeParam) {
		for (x = half; x < max; x += sizeParam) {
			float aux = ((rand()%10000)/10000.0);
			//cout<<aux<<"::"<<scale<<"::"<<(aux * scale * 2 - scale)<<"::"<<half<<"\n";
			square(x, y, half, (aux * scale * 2 - scale));
		}
	}

	for (y = 0; y <= max; y += half) {
		for (x = (y + half) % sizeParam; x <= max; x += sizeParam) {
			float aux = ((rand()%10000)/10000.0);
			//cout<<aux<<"::"<<scale<<"::"<<(aux * scale * 2 - scale)<<"::"<<half<<"\n";
			diamond(x, y, half, aux * scale * 2 - scale);
		}
	}
	divide(sizeParam/ 2);
}


void Terrain::square(int x, int y, int sizeParam, float offset){
	float temp[4] = {
					get(x - sizeParam, y - sizeParam),   // upper left
					get(x + sizeParam, y - sizeParam),   // upper right
					get(x + sizeParam, y + sizeParam),   // lower right
					get(x - sizeParam, y + sizeParam)    // lower left
			        };
	float ave =  average(temp);
	set(x, y, ave + offset);	
}

void Terrain::diamond(int x, int y, int sizeParam, float offset){
	float temp[4] = {
					get(x, y - sizeParam),   // upper left
					get(x + sizeParam, y),   // upper right
					get(x , y + sizeParam),   // lower right
					get(x - sizeParam, y)    // lower left
			        };
	float ave =  average(temp);
	//if(ave<=0)
	//	cout<<x<<"::"<<y<<"::"<<ave<<"::"<<offset<<"::"<<(ave+offset)<<"\n";

	set(x, y, ave + offset);	
}

float average(float values[4]) {
	float count = 0;
	float sum = 0;
	for (int i = 0; i < 4; ++i){
		if(values[i] != -1.0){
			count++;
		}
		sum += values[i];

	}
	//cout<<sum<<" "<<values[0]<<" "<<values[1]<<" "<<values[2]<<" "<<values[3]<<" "<<count<<"\n";

	return sum / count;
}
void Terrain::draw(int x, int y){
	Node *top=new Node, *bottom=new Node, *water=new Node;

	float waterVal = size *0.3;
	float val = get(x, y);

	project(top, x, y, val, size);
//	project(bottom, x + 1, y, 0, size);
	project(water, x, y, waterVal, size);
		
	b = brightness(x, y, get(x + 1, y) - val, max);
//	cout<<x<<" "<<y<<"\n";

	xi = top->x;
	yi = top->y;
	zi = top->z;

//	rect(top, bottom, style);

}

float brightness(int x, int y, float slope, float max){
	if (y == max || x == max) {
		return 0;
	}else{
		float b = (int)(slope * 50) + 128;
		return b;
	}
}

void project(Node *node, float flatX, float flatY, float flatZ, int sizeParam) {
	float isomX = 0.5 * sizeParam + flatX - flatY;
	float isomY = 0.5 * flatX + flatY;

	float xzero = WIDTH * 0.5;
	float yzero = HEIGHT * 0.2;

	float z = sizeParam *0.5 - flatZ + isomY * 0.75;
	float x = (isomX - sizeParam *0.5)*6;
	float y = (sizeParam - isomY) * 0.005 +1;

	node->x= xzero + x / y;
	node->y= yzero + z / y;

	z = sizeParam *0.5 - 0 + isomY * 0.75;
	node->z= yzero + z / y;;
}
