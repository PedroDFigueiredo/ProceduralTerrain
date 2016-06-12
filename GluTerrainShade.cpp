#include "GluTerrain.h"

void init (void);
void keyboard(unsigned char key, int x, int y);
void specialKeysPress(int key, int x, int y);
void display(void);
void reshape(int w, int h);
int spaced(int e);
void displaySmallVectors(int line, int col, int size);
void displaySquares(int line, int col);
void idle ();
void displayPolygons(int line, int col);
void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular,
					  GLfloat *brilho, GLfloat *emissao );

Terrain * ter;
int displayM=0, angle=225, initPosition=0;
float testsize = 0.0, shoulder = 0.0f, elbow = 0.0f, xvar=290, zvar=290;
float  eyeX = 0.0, eyeY = 0.0, eyeZ=0.0, 
      centerX = 0.0, centerY = 0.0, centerZ=0.0;


float kc = 0.1f;
float kl = 0.04f;
float kq = 0.0005f;

// Material do teapot
GLfloat object_ambient[]   = { 0.25725, 0.1995, 0.0745, 1.0 };
GLfloat object_difusa[]    = { 0.80164, 0.60648, 0.22648, 1.0 };
GLfloat object_especular[] = { 0.828281, 0.555802, 0.366065, 1.0 };
GLfloat object_emissao[]   = { 0.0, 0.0, 0.0, 1.0 };
GLfloat object_brilho[]    = { 160.0 };

// Defini parametros da luz
GLfloat cor_luz[]			= { 0.5f, 0.5f, 0.5f, 1.0};
GLfloat cor_luz_amb[]	= { 0.02, 0.02, 0.02, 0.02};
GLfloat posicao_luz[4];
GLfloat cor_fonte_luz[]	= { 1.0, 1.0, 0.0, 1.0};
GLfloat cor_emissao[]	= { 0.2, 0.2, 0.0, 1.0 };

GluTerrain::GluTerrain(int details, int width, int height, float roughness){
	terrain = new Terrain(details, width, height);
	ter = terrain;
	terrain->generate(roughness);
}

void GluTerrain::init (int argc, char **argv){
	cout<<"\n*Setting up glut \n";
	glutInit(&argc, argv);
	cout<<"testsize "<<atoi(argv[1])<<"\n";
	
	initPosition = eyeX = eyeZ = eyeY = atoi(argv[1]);
  	centerZ = eyeZ + sin(angle*M_PI/180)*initPosition;
  	centerX = eyeX + cos(angle*M_PI/180)*initPosition;     
  	cout<<"centerY"<<( sin(45*M_PI/180)	)<<"\n";

	displayM = displayMode;

	posicao_luz[0] = 1500;
	posicao_luz[1] = 2000.0;
	posicao_luz[2] = 1500;
	posicao_luz[3] = 1.0;

	glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);	
	glutInitWindowSize (terrain->windowW, terrain->windowH);
	glutInitWindowPosition (250, 0);
	glutCreateWindow ("Procedural");
/**
*	INIT
*/
	// selecionar cor de fundo (preto)
	glClearColor (0.0, 0.0, 0.0, 0.0);

	// inicializar sistema de luz.
	glShadeModel (GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glEnable(GL_DEPTH_TEST);               // HabilitaX-buffer
	glEnable(GL_CULL_FACE);                // Habilita Backface-Culling

	// Define parametros da luz 0
   glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz_amb);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
   glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
   glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

	cout<<"**Finished Setting up glut \n";
	glutDisplayFunc(display);
 	glutReshapeFunc(reshape);
 	glutIdleFunc(idle);

	/*glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(ter->windowW, ter->windowW/ter->windowH, 0.1, 15000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	gluLookAt (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);*/

	glutKeyboardFunc(keyboard);
	glutSpecialFunc( specialKeysPress );
	glutMainLoop();
	
}
void reshape (int w, int h){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(ter->windowW, ter->windowW/ter->windowH, 0.1, 15000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	gluLookAt (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
}


void display(void){
	// Limpar todos os pixels
	//glClear (GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
	reshape(ter->windowW, ter->windowH);
   
   glBegin(GL_LINES);
   //RED AXIS x
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(ter->windowH, 0.0f, 0.0f);
   //GREEN AXIS y
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, ter->windowH, 0.0f);
   //BLUEA AXIS z
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, ter->windowH);
	glEnd();

	glBegin(GL_LINES);
   //RED AXIS x
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0, 0.0f, 0);
		glVertex3f(centerX, centerY, centerZ);
	glEnd();

	// Posiciona esfera que representa a fonte de luz 0 no mundo
   	glPushMatrix();
		glTranslatef(posicao_luz[0],posicao_luz[1],posicao_luz[2]);
		glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_fonte_luz);
		glMaterialfv(GL_FRONT, GL_EMISSION, cor_emissao);
		glutSolidSphere(30,30,30);
	glPopMatrix();

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, kc);
   	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, kl);
   	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, kq);

   	setMaterial(object_ambient, object_difusa,object_especular, object_brilho, object_emissao);

	switch(displayM){
		case 0: displaySmallVectors(ter->size, ter->size, 5); break;
		case 1: displayPolygons(ter->size, ter->size); break;
		case 2: displaySquares(ter->size, ter->size); break;
	}
   // N�o esperar!
   glutSwapBuffers();
}

void idle () {
   glutPostRedisplay();
}

//Espaço entre pontos do polygono
int spaced(int e){
	return e*3;
}

int velocity = 30;
void specialKeysPress(int key, int x, int y){
    cout<<angle<<":"<<centerX<<"::"<<centerZ<<"\n";
	switch (key){
		case 100:
		 //centerX -= velocity;
		 	angle-1<0?angle = 350-angle: angle -=1;   

		  	centerZ = eyeZ + sin(angle*M_PI/180)*initPosition;
		  	centerX = eyeX + cos(angle*M_PI/180)*initPosition;     
		break;
		case 102:
		 // centerX = eyeX + velocity;
		  	angle+1>360? angle = angle -360: angle += 1;
		 	centerZ = eyeZ + sin(angle*M_PI/180)*initPosition;
		  	centerX = eyeX + cos(angle*M_PI/180)*initPosition;     
		break;
		case 101:
		 centerY += velocity;
		break;
		case 103:
		 centerY -= velocity;
		break;
	}

	/*	switch (key)
   {
      case GLUT_KEY_LEFT:
         posicao_luz[0]-=0.2;
      break;
      case GLUT_KEY_RIGHT:
         posicao_luz[0]+=0.2;
      break;
      case GLUT_KEY_UP:
         posicao_luz[1]+=0.2;
      break;
      case GLUT_KEY_DOWN:
         posicao_luz[1]-=0.2;
      break;
      case GLUT_KEY_PAGE_DOWN:
         posicao_luz[2]-=0.2;
      break;
      case GLUT_KEY_PAGE_UP:
         posicao_luz[2]+=0.2;
      break;
   }*/
/*
   x' = x cos θ − y sin θ
    y' = x sin θ + y cos θ
*/
	cout<<"angle"<<angle<<"   cX:"<<centerX<<" cY:"<<centerY<<" cZ:"<<centerZ<<"\n";
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   	switch (key){
	
	   case 'w':
	      eyeY +=velocity;
	   break;
	   case 's':
	      eyeY -=velocity;
	   break;
	   case 'a':
	      eyeX -=velocity;
	   break;
	   case 'd':
	      eyeX +=velocity;
	   break;
	   case 'c':
	      eyeZ -=velocity;
	   break;
	   case 'z':
	      eyeZ +=velocity;
	   break;
	   case 'm':
	      centerZ -=velocity;
	   break;
	   case 'n':
	      centerZ +=velocity;
	   break;
	}
  	centerZ = eyeZ + sin(angle*M_PI/180)*initPosition;
  	centerX = eyeX + cos(angle*M_PI/180)*initPosition;     

//	cout<<"x:"<<eyeX<<" y:"<<eyeY<<" z:"<<eyeZ<<"\n";
	glutPostRedisplay();
	
}

void displaySmallVectors(int line, int col, int size){

	glBegin(GL_LINES);
	
	for (float y = 0; y < col; y++) {
		for (float x = 0; x < line; x++) {
			glColor3f (1.0, 1.0, 1.0);
			float yvert = ter->get(x,y)/2;
			if(yvert > 0){
				glVertex3f(spaced(x), yvert-size, spaced(y));
				glVertex3f(spaced(x), yvert, spaced(y));
			}
		}
	}
	glEnd();
}

void setMaterial(GLfloat *ambiente, GLfloat *difusa, GLfloat *especular,
					  GLfloat *brilho, GLfloat *emissao ) {
   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, brilho);
   glMaterialfv(GL_FRONT, GL_EMISSION, emissao);
}

void displaySquares(int line, int col){

	//glutSolidTeapot(50.0);
   	//return;

	for (float y = 0; y < col; y++) {
		for (float x = 0; x < line; x++) {
			glBegin(GL_LINES);

			glColor3f (1.0, 1.0, 1.0);

			float yvert = ter->get(x,y)/2;
			if(yvert > 0) {
				glVertex3f(spaced(x), yvert, spaced(y));
			}
			
			yvert = ter->get(x+1,y)/2;
			if(yvert > 0){
				glVertex3f(spaced(x+1), yvert, spaced(y));
				glVertex3f(spaced(x+1), yvert, spaced(y));
			}
			
			yvert = ter->get(x+1,y+1)/2;
			if(yvert > 0){
				glVertex3f(spaced(x+1), yvert, spaced(y+1));
				glVertex3f(spaced(x+1), yvert, spaced(y+1));
			}
						
			yvert = ter->get(x,y+1)/2;
			if(yvert > 0){
				glVertex3f(spaced(x), yvert, spaced(y+1));
				glVertex3f(spaced(x), yvert, spaced(y+1));
			}
			
			yvert = ter->get(x,y)/2;
			if(yvert > 0){
				glVertex3f(spaced(x), yvert, spaced(y));
			}
			
			glEnd();

		}
	}
}

void checkLight(int x, int z, float yvert){
	if(ter->get(x, z+1)>0){
		if(yvert < ter->get(x, z+1))
			glColor3f (0.0, 0.0, 0.0);
		else
			glColor3f (1.0, 1.0, 1.0);
	}
}

void displayPolygons(int line, int col) {

	glBegin(GL_POLYGON);

	for (float y = 0; y < col; y++) {
		for (float x = 0; x < line; x++) {
			
			float yvert = ter->get(x,y)/2;
			if(yvert > 0){
				glVertex3f(spaced(x), yvert, spaced(y));
				checkLight(x, y, yvert);
			}

			yvert = ter->get(x+1,y)/2;
			if(yvert > 0){
				glVertex3f(spaced(x+1), yvert, spaced(y));
				checkLight(x+1, y, yvert);
			}

			yvert = ter->get(x+1,y+1)/2;
			if(yvert > 0){
				glVertex3f(spaced(x+1), yvert, spaced(y+1));
				checkLight(x+1, y+1, yvert);
			}

			yvert = ter->get(x,y+1)/2;
			if(yvert > 0){
				glVertex3f(spaced(x), yvert, spaced(y+1));
				checkLight(x, y+1, yvert);
			}
		}
	}
	glEnd();
}