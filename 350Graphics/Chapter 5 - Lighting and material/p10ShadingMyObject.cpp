#include <iostream>   // for the definition of NULL
#include <math.h>
#include <GL/glut.h>

#define DtoR 0.017453

GLfloat ww = 500, wh = 500;
GLfloat dx = 1, dy = 1, dz = 1;
GLfloat lightPos[] = {2, 4, 6, 1};
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

void normal(float p0[], float p1[], float p2[], float n[]);
void drawObject(float h, float r, float H, float R, int n);

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

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	currentMaterials = &redPlasticMaterials;
	materials(currentMaterials);

	currentLighting = &whiteLighting;
	lighting(currentLighting);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -10, 10);
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

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	materials(currentMaterials);
	lighting(currentLighting);

	glRotatef(-90, 1, 0, 0);
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);

	//---------------------------------------------------------------------

	//------------------ with shading --------------------
	drawObject(1.5, 1, 0.6, 1.5, 600);
	//----------------------------------------------------

	////------------------ without shading -----------------
	//glDisable(GL_LIGHTING);
	//glColor3f(0, 1, 1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//drawObject(1, 1, 0.8, 1.3, 6);
	////----------------------------------------------------
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-2.0*w/h, 2.0*w/h, -2.0, 2.0, -10, 10);
	else
		glOrtho(-2, 2, -2.0*h/w, 2.0*h/w, -10, 10);
	glMatrixMode(GL_MODELVIEW);

	ww = w;
	wh = h;

	glViewport(0, 0, w, h);
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("shading objects");

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
	return 1;
}

void normal(float p0[], float p1[], float p2[], float n[])
{
	float a[3], b[3];
	float d;

	for (int i = 0; i<3; i++)
	{
		a[i] = p1[i] - p0[i];
		b[i] = p2[i] - p0[i];
	}

	n[0] = a[1] * b[2] - a[2] * b[1];
	n[1] = a[2] * b[0] - a[0] * b[2];
	n[2] = a[0] * b[1] - a[1] * b[0];

	d = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);

	if (d == 0)
		d = 1;

	for (int i = 0; i<3; i++)
		n[i] = n[i] / d;
}

void drawObject(float h, float r, float H, float R, int n)
{
	float angle = 2.0 * 3.14159 / n;
	float p1[3], p2[3], p3[3], p4[3], norm[3];

	//--------------------- draw side polygons --------------------
	for (int i = 0; i<n; i++)
	{
		p1[0] = r * cos(i * angle);
		p1[1] = r * sin(i * angle);
		p1[2] = h;

		if (i == n - 1)
		{
			p2[0] = r;
			p2[1] = 0;
		}
		else
		{
			p2[0] = r * cos((i + 1) * angle);
			p2[1] = r * sin((i + 1) * angle);
		}
		p2[2] = h;

		p3[0] = R * cos(i * angle);
		p3[1] = R * sin(i * angle);
		p3[2] = H;

		if (i == n - 1)
		{
			p4[0] = R;
			p4[1] = 0;
		}
		else
		{
			p4[0] = R * cos((i + 1) * angle);
			p4[1] = R * sin((i + 1) * angle);
		}
		p4[2] = H;

		normal(p1, p3, p2, norm);

		glNormal3fv(norm);
		glBegin(GL_POLYGON);
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p4);
		glVertex3fv(p3);
		glEnd();
	}
	//-----------------------------------------------------------
	
	//----------------------- draw top --------------------------
	glNormal3f(0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i<n; i++)
	{
		p1[0] = r * cos(i * angle);
		p1[1] = r * sin(i * angle);
		p1[2] = h;

		glVertex3fv(p1);
	}
	glEnd();
	//---------------------------------------------------------

	//------------------ draw side triangles ------------------
	for (int i = 0; i<n; i++)
	{
		p1[0] = R * cos(i * angle);
		p1[1] = R * sin(i * angle);
		p1[2] = H;

		if (i == n - 1)
		{
			p2[0] = R;
			p2[1] = 0;
		}
		else
		{
			p2[0] = R * cos((i + 1) * angle);
			p2[1] = R * sin((i + 1) * angle);
		}
		p2[2] = H;

		p3[0] = 0; p3[1] = 0; p3[2] = -1.0 * h;

		normal(p3, p2, p1, norm);
		glNormal3fv(norm);

		glBegin(GL_TRIANGLES);
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);
		glEnd();
	}
	//-------------------------------------------------------
}