#include <iostream>	// need it for NULL
#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, _near = 5, _far = 20;
const float REGION_DIM = 4;
//const GLfloat DtoR = 0.017453;
GLfloat fov = 45.0, aspect = 1;
GLfloat alpha = 0, beta = 0, gama = 0;
GLfloat direction = 1.0;
GLfloat lightPos[] = { 2, 4, 6, 1 };

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void mouse(int, int, int, int);

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
	{ 0.33, 0.22, 0.03, 1.0 },
	{ 0.78, 0.57, 0.11, 1.0 },
	{ 0.99, 0.91, 0.81, 1.0 },
	27.8
};

lightingStruct whiteLighting = {
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 }
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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	gluLookAt(3, 2, 6, 0, 0, 0, 0, 1, 0);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	glRotatef(alpha, 1, 0, 0);
	glRotatef(beta, 0, 1, 0);
	glRotatef(gama, 0, 0, 1);

	glutSolidTeapot(2);
//	glutSolidDodecahedron();
//	glutSolidIcosahedron();
//	glutSolidSphere(2, 100, 200);
	//glutSolidTorus(0.5, 2, 100, 200);

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);
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
	glFrustum(left, right, bottom, top, _near, _far);	// perspective projection with frustum. use it as same time in reshape
//	gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w*1.0 / (h*1.0);
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
	glFrustum(left, right, bottom, top, _near, _far);	// perspective projection with frustum. use it as same time in init
	//gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		alpha += 5;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		beta += 5;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gama += 5;
	}
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("Lighting and material");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(idle);
	glutMouseFunc(mouse);

	glutMainLoop();
}