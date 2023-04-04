#include <iostream>   // for the definition of NULL
//#include <math.h>
#include <stdlib.h>
//#include <GL/glut.h>
#include "../myObjects2023.cpp"


//===================== variables and initializations ======================
//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 5, far = 20;
const float REGION_DIM = 4;
//const GLfloat DtoR = 0.017453;
GLfloat fov = 45.0, aspect = 1;
GLfloat alpha = 0, beta = 0, gama = 0;
GLfloat direction = 1.0;
GLfloat lightPos[] = { 2, 4, 6, 1 };
GLfloat theta[3] = {0, 0, 0};
GLint axis;
//GLfloat DtoR = 0.017453;



int window1, window2;

typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

typedef struct lightingStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct;

materialStruct *currentMaterials;
lightingStruct *currentLighting;

materialStruct brassMaterials = {
	{0.33, 0.22, 0.03, 1.0},
	{0.78, 0.57, 0.11, 1.0},
	{0.99, 0.91, 0.81, 1.0},
	27.8
};

materialStruct redPlasticMaterials = {
	{0.3, 0.0, 0.0, .1},
	{0.6, 0.0, 0.0, .1},
	{0.8, 0.6, 0.6, .1},
	32.0
};

materialStruct whiteShineyMaterials = {
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	100.0
};

materialStruct myMaterials = {
	{1.0, 1.0, 1.0, 0.1},
	{1.0, 1.0, 1.0, 0.1},
	{1.0, 1.0, 1.0, 0.1},
	10.0
};

lightingStruct whiteLighting = {
	{0.0, 0.0, 0.0, 1.0},
	{1.0, 1.0, 1.0, 1.0}, 
	{1.0, 1.0, 1.0, 1.0}
};

lightingStruct coloredLighting = {
	{0.2, 0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0, 1.0},
	{0.0, 0.0, 1.0, 1.0}
};
//======================================================================

//======================= function prototypes ==========================
void materials(materialStruct *);
void lighting(lightingStruct *);
void commonIdle();
void key(unsigned char, int, int);
void init();
void mouse(int, int, int, int);
void myDisplay1();
void myDisplay2();
void designCubeWithNormal(GLfloat);
void drawCubeWithNormal(GLfloat);
void drawSphereWithNormalFlat(GLfloat);
void drawSphereWithNormalSmooth(GLfloat);
//======================================================================

int main()	// show two windows
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);

	glutInitWindowPosition(0, 0);
	window1 = glutCreateWindow("window one");
	glutDisplayFunc(myDisplay1);

	glutKeyboardFunc(key);
	glutMouseFunc(mouse);

	glutIdleFunc(commonIdle);
	init();

	glutInitWindowPosition(ww + 24, 0);
	window2 = glutCreateWindow("window two");
	glutDisplayFunc(myDisplay2);

	glutKeyboardFunc(key);
	glutMouseFunc(mouse);

	glutIdleFunc(commonIdle);
	init();
	glutMainLoop();
	return 0; 
}

//======================== functions ==========================
void materials(materialStruct *m)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m->shininess);
}

void lighting(lightingStruct *li)
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, li->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, li->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, li->specular);
}

void commonIdle()
{
	theta[axis] += .05;
	if (theta[axis] > 360.0)
		theta[axis] -= 360.0;

	glutSetWindow(window1);
	glutPostRedisplay(); 

	glutSetWindow(window2);
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case '1':
		glutIdleFunc(NULL);
		break;
	case '2':
		glutIdleFunc(commonIdle);   // for two windows
		break;
	case '3':
		currentMaterials = &redPlasticMaterials;
		break;
	case '4':
		currentMaterials = &whiteShineyMaterials;
		break;
	case '5':
		currentMaterials = &brassMaterials;
		break;
	case '6':
		currentLighting = &whiteLighting;
		break;
	case '7':
		currentLighting = &coloredLighting;
		break;
	case '8':
		currentMaterials = &myMaterials;
		break;
	case 'q':
		exit(0);
		break;
	}
}

void init(void)
{
	float ratio = ww * 1.0 / (wh*1.0);
	aspect = ratio;

	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glEnable(GL_LIGHTING);		// enable lighting
	glEnable(GL_LIGHT0);		// the first point light source

								//-------- set up the current material -------------------
	currentMaterials = &brassMaterials;
	materials(currentMaterials);

	//------------- set up the current lighting -------------------------
	currentLighting = &whiteLighting;
	lighting(currentLighting);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}

	//----------- just use one of the following -------------------
	//	glOrtho(left, right, bottom, top, near, far);	// orthogonal projection
	glFrustum(left, right, bottom, top, near, far);	// perspective projection with frustum. use it as same time in reshape
													//	gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w * 1.0 / (h*1.0);
	aspect = ratio;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}

	// ------------------------ just use one of the following -----------------------
	//glOrtho(left, right, bottom, top, near, far);	// orthogonal projection
	glFrustum(left, right, bottom, top, near, far);	// perspective projection with frustum. use it as same time in init
													//gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

								//------ reset the window size
	ww = w;
	wh = h;
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
}

void myDisplay1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 2, 6, 0, 0, 0, 0, 1, 0);

	materials(currentMaterials);
	lighting(currentLighting);

	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);

	drawCubeWithNormal(2);
	//drawSphereWithNormalFlat(2);
	//drawSphereWithNormalSmooth(2);
	//sphere(2, 72, 36);
	

	glutSwapBuffers();
}

void myDisplay2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 2, 6, 0, 0, 0, 0, 1, 0);

	materials(currentMaterials);
	lighting(currentLighting);

	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);

	//glShadeModel(GL_FLAT);

	glutSolidCube(2);
	//glutSolidSphere(2, 72, 36);

	glutSwapBuffers();
}


//=====================================================================

