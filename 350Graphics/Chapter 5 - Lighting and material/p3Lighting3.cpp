#include <iostream>   // for the definition of NULL
#include <GL/glut.h>

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


//GLfloat dx = 1, dy = 1, dz = 1;
//GLfloat lightPos[] = {2, 4, 6, 1};
GLfloat theta[3] = {0, 0, 0};
GLint axis = 0;


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
	{0.3, 0.0, 0.0, 1.0},
	{0.6, 0.0, 0.0, 1.0},
	{0.8, 0.6, 0.6, 1.0},
	32.0
};

materialStruct whiteShineyMaterials = {
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	100.0
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

void idle()
{
	theta[axis] += 0.01;
	if (theta[axis] > 360.0)
		theta[axis] -= 360.0;
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
		glutIdleFunc(idle);
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

void display()
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

	//glShadeModel(GL_FLAT);  // default is GL_SMOOTH

	//glDisable(GL_LIGHTING);
	//glColor3f(1, 0, 0);

	//-------------------- objects ---------------------------
	glutSolidCube(2);
	//glutWireCube(2);
	//glutSolidTeapot(2);
	//glutWireTeapot(2);
	//glutSolidIcosahedron();
	//glutSolidDodecahedron();
	//glutSolidOctahedron();
	//glutSolidTetrahedron();
	//glutSolidSphere(1, 100, 100);
	//glutSolidCone(1, 2, 50, 50);
	//glutSolidTorus(0.15, 1, 150, 150);
	//--------------------------------------------------------
	

	glutSwapBuffers();
}


int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("shading objects");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0; 
}

