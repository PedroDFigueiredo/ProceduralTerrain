#include "GluTerrain.h"

void init (void);
void keyboard(unsigned char key, int x, int y);
void specialKeysPress(int key, int x, int y);
void display(void);
void reshape(int w, int h);
int spaced(int e);

Terrain * ter;
int AUX=10;
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

	glEnable(GL_LIGHT0);                   // habilita luX 0
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
	gluPerspective(ter->windowW, ter->windowW/ter->windowH, 0.5, 5000.0);

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
	glDisable(GL_LIGHTING);
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
	glEnable(GL_LIGHTING);

	for (float y = 0; y < ter->size; y++) {
		for (float x = 0; x < ter->size; x++) {
			glBegin(GL_LINES);	

			glColor3f (1.0, 1.0, 1.0);
			float zvert = ter->get(x,y)/2;
			if(zvert > 0){
				glVertex3f(spaced(x), zvert-5, spaced(y));

				glVertex3f(spaced(x), zvert, spaced(y));
			}

			/*float zvert = ter->get(x,y)/2;
			if(zvert > 0){
				glVertex3f(spaced(x), zvert, spaced(y));
			}
			
			zvert = ter->get(x+1,y)/2;
			if(zvert > 0){
				glVertex3f(spaced(x+1), zvert, spaced(y));
			}

			if(zvert > 0){
				glVertex3f(spaced(x+1), zvert, spaced(y));
			}
			
			zvert = ter->get(x+1,y+1)/2;
			if(zvert > 0){
				glVertex3f(spaced(x+1), zvert, spaced(y+1));
			}

			if(zvert > 0){
				glVertex3f(spaced(x+1), zvert, spaced(y+1));
			}
						
			zvert = ter->get(x,y+1)/2;
			if(zvert > 0){
				glVertex3f(spaced(x), zvert, spaced(y+1));
			}
			
			if(zvert > 0){
				glVertex3f(spaced(x), zvert, spaced(y+1));
			}
			
			zvert = ter->get(x,y)/2;
			if(zvert > 0){
				glVertex3f(spaced(x), zvert, spaced(y));
			}
			*/
			glEnd();

		}
	}
//	cout<<":::::::::::::::::::::::::::::::::::\n";


   // N�o esperar!
   glutSwapBuffers();
   reshape(ter->windowW, ter->windowH);
}

//Espaço entre pontos do polygono
int spaced(int e){
	return e*3;
}

void specialKeysPress(int key, int x, int y){
	//cout<< sqrt(pow(key,2)) << "\n";
	switch (key){
      case 100:
         centerX -= 10;
      break;
      case 102:
         centerX += 10;
      break;
      case 101:
         centerY += 10;
      break;
      case 103:
         centerY -= 10;
      break;
   }

	cout<<"cX:"<<centerX<<" cY:"<<centerY<<" cZ:"<<centerZ<<"\n";
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   	switch (key){
	
	   case 'w':
	      eyeY +=10;
	   break;
	   case 's':
	      eyeY -=10;
	   break;
	   case 'a':
	      eyeX -=10;
	   break;
	   case 'd':
	      eyeX +=10;
	   break;
	   case 'z':
	      eyeZ -=10;
	   break;
	   case 'c':
	      eyeZ +=10;
	   break;
	   case 'n':
	      centerZ -=10;
	   break;
	   case 'm':
	      centerZ +=10;
	   break;
	}
	cout<<"x:"<<eyeX<<" y:"<<eyeY<<" z:"<<eyeZ<<"\n";
	glutPostRedisplay();
	
}
