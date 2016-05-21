#include "GluTerrain.h"

void init (void);
void keyboard(unsigned char key, int x, int y);
void specialKeysPress(int key, int x, int y);
void display(void);
void reshape(int w, int h);
int spaced(int e);
void displaySmallVectors(int line, int col, int size);
void displaySquares(int line, int col);
void displayPolygons(int line, int col);

Terrain * ter;
int displayM=0;
float testsize = 0.0, shoulder = 0.0f, elbow = 0.0f;
float  eyeX = 0.0, eyeY = 0.0, eyeZ=0.0, 
      centerX = 0.0, centerY = 0.0, centerZ=0.0;


GluTerrain::GluTerrain(int details, int width, int height, float roughness){
	terrain = new Terrain(details, width, height);
	ter = terrain;
	terrain->generate(roughness);

}
void GluTerrain::init (int argc, char **argv){
	cout<<"\n*Setting up glut \n";
	glutInit(&argc, argv);
	cout<<"testsize "<<atoi(argv[1])<<"\n";
	
	eyeX = eyeZ = eyeY = atoi(argv[1]);

	displayM = displayMode;

	glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);	
	glutInitWindowSize (terrain->windowW, terrain->windowH);
	glutInitWindowPosition (250, 0);
	glutCreateWindow ("Procedural");
/**
*	INIT
*/
	// selecionar cor de fundo (preto)
	glClearColor (0.0, 0.0, 0.0, 0.0);

	// inicializar sistema de viz.
	glShadeModel (GL_SMOOTH);

	glEnable(GL_LIGHTING);


	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);           // Utiliza cor do objeto como material
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glEnable(GL_LIGHTING);                 // Habilita luz
	glEnable(GL_DEPTH_TEST);               // HabilitaX-buffer
	glEnable(GL_CULL_FACE);                // Habilita Backface-Culling


	cout<<"**Finished Setting up glut \n";
	glutDisplayFunc(display);
 	glutReshapeFunc(reshape);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(ter->windowW, ter->windowW/ter->windowH, 0.1, 15000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	gluLookAt (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc( specialKeysPress );
	glutMainLoop();
	
}
void reshape (int w, int h){
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   	glLoadIdentity ();

    gluLookAt (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
}


void display(void){
	// Limpar todos os pixels
	glClear (GL_COLOR_BUFFER_BIT|| GL_DEPTH_BUFFER_BIT);

   
	//AUX = ter->size;
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

	switch(displayM){
		case 0: displaySmallVectors(ter->size, ter->size, 5); break;
		case 1: displayPolygons(ter->size, ter->size); break;
		case 2: displaySquares(ter->size, ter->size); break;
	}
   // N�o esperar!
   glutSwapBuffers();
   reshape(ter->windowW, ter->windowH);
}

//Espaço entre pontos do polygono
int spaced(int e){
	return e*3;
}

int velocity = 30;
void specialKeysPress(int key, int x, int y){
	//cout<< sqrt(pow(key,2)) << "\n";
	switch (key){
      case 100:
         centerX -= velocity;
      break;
      case 102:
         centerX += velocity;
      break;
      case 101:
         centerY += velocity;
      break;
      case 103:
         centerY -= velocity;
      break;
   }

//	cout<<"cX:"<<centerX<<" cY:"<<centerY<<" cZ:"<<centerZ<<"\n";
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
//	cout<<"x:"<<eyeX<<" y:"<<eyeY<<" z:"<<eyeZ<<"\n";
	glutPostRedisplay();
	
}

void displaySmallVectors(int line, int col, int size){
	
	for (float y = 0; y < col; y++) {
		for (float x = 0; x < line; x++) {
			glBegin(GL_LINES);	

			glColor3f (1.0, 1.0, 1.0);
			float yvert = ter->get(x,y)/2;
			if(yvert > 0){
				glVertex3f(spaced(x), yvert-size, spaced(y));

				glVertex3f(spaced(x), yvert, spaced(y));
			}
			glEnd();

		}
	}	
}

void displaySquares(int line, int col){
	for (float y = 0; y < col; y++) {
		for (float x = 0; x < line; x++) {
			glBegin(GL_LINES);	

			glColor3f (1.0, 1.0, 1.0);

			float yvert = ter->get(x,y)/2;
			if(yvert > 0){
				glVertex3f(spaced(x), yvert, spaced(y));
			}
			
			yvert = ter->get(x+1,y)/2;
			if(yvert > 0){
				glVertex3f(spaced(x+1), yvert, spaced(y));
			}

			if(yvert > 0){
				glVertex3f(spaced(x+1), yvert, spaced(y));
			}
			
			yvert = ter->get(x+1,y+1)/2;
			if(yvert > 0){
				glVertex3f(spaced(x+1), yvert, spaced(y+1));
			}

			if(yvert > 0){
				glVertex3f(spaced(x+1), yvert, spaced(y+1));
			}
						
			yvert = ter->get(x,y+1)/2;
			if(yvert > 0){
				glVertex3f(spaced(x), yvert, spaced(y+1));
			}
			
			if(yvert > 0){
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

void displayPolygons(int line, int col){
	for (float y = 0; y < col; y++) {
		for (float x = 0; x < line; x++) {
			glBegin(GL_POLYGON);	


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
			glEnd();

		}
	}	
}