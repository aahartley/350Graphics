#include <iostream>   // for the definition of NULL
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

//===================== variables and initializations ======================
GLfloat ww = 500, wh = 500;
GLfloat dx = 1, dy = 1, dz = 1;
GLfloat lightPos[] = { 2, 4, 6, 1 };
GLfloat theta[3] = { 0, 0, 0 };
GLint axis;
GLfloat DtoR = 0.017453;


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

materialStruct redPlasticMaterials = {
	{ 0.3, 0.0, 0.0, .1 },
	{ 0.6, 0.0, 0.0, .1 },
	{ 0.8, 0.6, 0.6, .1 },
	32.0
};

materialStruct whiteShineyMaterials = {
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	100.0
};

materialStruct myMaterials = {
	{ 1.0, 1.0, 1.0, 0.1 },
	{ 1.0, 1.0, 1.0, 0.1 },
	{ 1.0, 1.0, 1.0, 0.1 },
	10.0
};

lightingStruct whiteLighting = {
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 }
};

lightingStruct coloredLighting = {
	{ 0.2, 0.0, 0.0, 1.0 },
	{ 0.0, 1.0, 0.0, 1.0 },
	{ 0.0, 0.0, 1.0, 1.0 }
};
//======================================================================

//======================= function prototypes ==========================
void materials(materialStruct *);
void lighting(lightingStruct *);
void idle();
void key(unsigned char, int, int);
void init();
void mouse(int, int, int, int);
void display();
void drawSphereWithNormalFlat(GLfloat);
void drawSphereWithNormalSmooth(GLfloat);
//======================================================================

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	materials(currentMaterials);
	lighting(currentLighting);

	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);

	////------------- disable lighting and use color ------------
	//glDisable(GL_LIGHTING);
	//glColor3f(1, 0, 0);
	////---------------------------------------------------------

	//glutSolidSphere(3, 80, 40);
	drawSphereWithNormalFlat(3);
	//drawSphereWithNormalSmooth(3);

	glutSwapBuffers();
}

void main()	
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);

	glutInitWindowPosition(0, 0);
	glutCreateWindow("shading");
	glutDisplayFunc(display);

	glutKeyboardFunc(key);
	glutMouseFunc(mouse);

	glutIdleFunc(idle);
	init();

	glutMainLoop();
}

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
	theta[axis] += .05;
	if (theta[axis] > 360.0)
		theta[axis] -= 360.0;

	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch (k)
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
	case '8':
		currentMaterials = &myMaterials;
		break;
	case 'q':
		exit(0);
		break;
	}
}

void init()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	currentMaterials = &redPlasticMaterials;
	materials(currentMaterials);

	currentLighting = &whiteLighting;
	lighting(currentLighting);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -20, 20);
	glMatrixMode(GL_MODELVIEW);
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

void drawSphereWithNormalFlat(GLfloat radius)
{
	GLint longitude = 5, latitude = 5;
	GLint phi, theta;
	GLfloat p1[3], p2[3], p3[3], p4[3];

	for (phi = -90; phi <= 90 - latitude; phi += latitude)
	{
		for (theta = -180; theta <= 180; theta += longitude)
		{
			p1[0] = radius * cos(theta*DtoR) * cos(phi*DtoR);
			p1[1] = radius * sin(theta*DtoR) * cos(phi*DtoR);
			p1[2] = radius * sin(phi*DtoR);

			p2[0] = radius * cos((theta + longitude)*DtoR) * cos(phi*DtoR);
			p2[1] = radius * sin((theta + longitude)*DtoR) * cos(phi*DtoR);
			p2[2] = radius * sin(phi*DtoR);

			p3[0] = radius * cos((theta + longitude)*DtoR) * cos((phi + latitude)*DtoR);
			p3[1] = radius * sin((theta + longitude)*DtoR) * cos((phi + latitude)*DtoR);
			p3[2] = radius * sin((phi + latitude)*DtoR);

			p4[0] = radius * cos(theta*DtoR) * cos((phi + latitude)*DtoR);
			p4[1] = radius * sin(theta*DtoR) * cos((phi + latitude)*DtoR);
			p4[2] = radius * sin((phi + latitude)*DtoR);

			glNormal3f(p1[0] / radius, p1[1] / radius, p1[2] / radius);// normal is set up for a polygon	
			glBegin(GL_POLYGON);
			glVertex3fv(p1);
			glVertex3fv(p2);
			glVertex3fv(p3);
			glVertex3fv(p4);
			glEnd();
		}
	}
}

void drawSphereWithNormalSmooth(GLfloat radius)
{
	GLint longitude = 5, latitude = 5;
	GLint phi, theta;
	GLfloat p1[3], p2[3], p3[3], p4[3];

	for (phi = -90; phi <= 90 - latitude; phi += latitude)
	{
		for (theta = -180; theta <= 180; theta += longitude)
		{
			p1[0] = radius * cos(theta*DtoR) * cos(phi*DtoR);
			p1[1] = radius * sin(theta*DtoR) * cos(phi*DtoR);
			p1[2] = radius * sin(phi*DtoR);

			p2[0] = radius * cos((theta + longitude)*DtoR) * cos(phi*DtoR);
			p2[1] = radius * sin((theta + longitude)*DtoR) * cos(phi*DtoR);
			p2[2] = radius * sin(phi*DtoR);

			p3[0] = radius * cos((theta + longitude)*DtoR) * cos((phi + latitude)*DtoR);
			p3[1] = radius * sin((theta + longitude)*DtoR) * cos((phi + latitude)*DtoR);
			p3[2] = radius * sin((phi + latitude)*DtoR);

			p4[0] = radius * cos(theta*DtoR) * cos((phi + latitude)*DtoR);
			p4[1] = radius * sin(theta*DtoR) * cos((phi + latitude)*DtoR);
			p4[2] = radius * sin((phi + latitude)*DtoR);

			glBegin(GL_POLYGON);
			glNormal3f(p1[0] / radius, p1[1] / radius, p1[2] / radius); // could be set up for every vertex
			glVertex3fv(p1);
			glNormal3f(p2[0] / radius, p2[1] / radius, p2[2] / radius);
			glVertex3fv(p2);
			glNormal3f(p3[0] / radius, p3[1] / radius, p3[2] / radius);
			glVertex3fv(p3);
			glNormal3f(p4[0] / radius, p4[1] / radius, p4[2] / radius);
			glVertex3fv(p4);
			glEnd();
		}
	}
}
//=====================================================================

