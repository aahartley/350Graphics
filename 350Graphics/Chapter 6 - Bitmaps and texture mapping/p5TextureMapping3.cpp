//#include <math.h>
//#include <GL/glut.h>
#include <iostream>		// for malloc
#include "../myObjects2023.cpp"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 5, far = 20;
const float REGION_DIM = 4;
//const GLfloat DtoR = 0.017453;
GLfloat fov = 45.0, aspect = 1;
GLfloat theta = 30, phi = 60, rho = 10;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat alpha = 0, beta  = 0, gama = 0;
GLfloat dAlpha = 5, dBeta = 5, dGama = 5;
GLfloat a = 1, b = 1, c = 1;
GLfloat dA = 0.1, dB = 0.1, dC = 0.1;
GLfloat direction = 1.0;


GLfloat cubeVertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },
{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },{ -1.0,-1.0,1.0 },
{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } };

GLfloat colors[8][4] = { { 0, 0, 0, 1 },{ 1, 0, 0, 1 },{ 1, 1, 0, 1 },{ 0, 1, 0, 1 },{ 0, 0, 1, 1 },
{ 1, 0, 1, 1 },{ 1, 1, 1, 1 },{ 0, 1, 1, 1 } };

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void keys(unsigned char k, int x, int y);
void mouse(int, int, int, int);
void idle(void);
void polygonTex(int a, int b, int c, int d);
void colorPolygonTex(int a, int b, int c, int d);
void cubeTex();
void colorCubeTex();
GLubyte *checkerBoard(int n, int m);
GLubyte *strips(int n, int m);


void display(void)
{
	int n = 8;
	int m = 8;
	GLubyte *image;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	image = strips(n, m);
	//image = checkerBoard(n, m);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, n, m, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);

	//glDisable(GL_TEXTURE_2D);
	axes(2*REGION_DIM);
	//glEnable(GL_TEXTURE_2D);

	glRotatef(alpha, 1, 0, 0);
	glRotatef(beta, 0, 1, 0);
	glRotatef(gama, 0, 0, 1);
	glScalef(a, a, a);

	
	colorCubeTex();
	//cubeTex();
	//polygonTex(0, 1, 2, 3);
	//colorPolygonTex(0, 1, 2, 3);
	//glutSolidTeapot(b);
	

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void polygonTex(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glColor4f(1, 1, 1, alpha);
	glVertex3fv(cubeVertices[a]);

	glTexCoord2f(0.0, 1.0);
	glColor4f(1, 1, 1, alpha);
	glVertex3fv(cubeVertices[b]);

	glTexCoord2f(1.0, 1.0);
	glColor4f(1, 1, 1, alpha);
	glVertex3fv(cubeVertices[c]);

	glTexCoord2f(1.0, 0.0);
	glColor4f(1, 1, 1, alpha);
	glVertex3fv(cubeVertices[d]);
	glEnd();
}

void colorPolygonTex(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glColor4fv(colors[a]);
	glVertex3fv(cubeVertices[a]);

	glTexCoord2f(0.0, 1.0);
	glColor4fv(colors[b]);
	glVertex3fv(cubeVertices[b]);

	glTexCoord2f(1.0, 1.0);
	glColor4fv(colors[c]);
	glVertex3fv(cubeVertices[c]);

	glTexCoord2f(1.0, 0.0);
	glColor4fv(colors[d]);
	glVertex3fv(cubeVertices[d]);
	glEnd();
}

void cubeTex()
{
	polygonTex(0, 3, 2, 1);
	polygonTex(2, 3, 7, 6);
	polygonTex(0, 4, 7, 3);
	polygonTex(1, 2, 6, 5);
	polygonTex(4, 5, 6, 7);
	polygonTex(0, 1, 5, 4);
}

void colorCubeTex()
{
	colorPolygonTex(0, 3, 2, 1);
	colorPolygonTex(2, 3, 7, 6);
	colorPolygonTex(0, 4, 7, 3);
	colorPolygonTex(1, 2, 6, 5);
	colorPolygonTex(4, 5, 6, 7);
	colorPolygonTex(0, 1, 5, 4);
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

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
	glFrustum(left, right, bottom, top, near, far);	// perspective projection with frustum. use it as same time in reshape
	//gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w*1.0 / (h*1.0);

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
	glFrustum(left, right, bottom, top, near, far);	// perspective projection with frustum. use it as same time in init
	//gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void idle()
{
	alpha += 0.01;
	beta += 0.01;
	gama += 0.01;

	if (alpha >= 360)
		alpha -= 360;

	if (beta >= 360)
		beta -= 360;

	if (gama >= 360)
		gama -= 360;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		alpha += dAlpha * direction;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		beta += dBeta * direction;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gama += dGama * direction;
	}
}

void keys(unsigned char k, int x, int y)
{
	if (k == 'p' || k == 'P')
		direction = 1.0;
	else if (k == 'n' || k == 'N')
		direction = -1.0;
	else if (k == 'a' || k == 'A')
		a += dA * direction;
	else if (k == 'b' || k == 'B')
		b += dB * direction;
	else if (k == 'c' || k == 'C')
		c += dC * direction;
	else if (k == 'i' || k == 'I')
		glutIdleFunc(idle);
	else if (k == 'q' || k == 'Q')
		glutIdleFunc(NULL);
	else if (k == '+')
		rho -= dRho;
	else if (k == '-')
		rho += dRho;
	else if (k == 'r' || k == 'R')
	{
		near = 5;
		far = 20;
		theta = 30;
		phi = 60;
		rho = 10;
		alpha = 0;
		beta = 0;
		gama = 0;
		a = 1;
		b = 1;
		c = 1;
		direction = 1.0;
		glutIdleFunc(NULL);
	}
}

void specialKeys(int k, int x, int y)
{
	if (k == GLUT_KEY_LEFT)
		theta -= dTheta;
	else if (k == GLUT_KEY_RIGHT)
		theta += dTheta;
	else if (k == GLUT_KEY_UP)
	{
		if (phi > dPhi)
			phi -= dPhi;
		else if (phi == dPhi)
			phi = 0.01;		// to keep the direction vector of the camera
	}
	else if (k == GLUT_KEY_DOWN)
	{
		if (phi <= 180 - dPhi)
			phi += dPhi;
	}
}

GLubyte *checkerBoard(int n, int m)
{
	GLubyte *image;
	int nm, i, j;
	int greyLevel;

	nm = n * m;
	image = (GLubyte *)malloc(3 * sizeof(GLubyte)*nm);

	for (i = 0;i<n;i++)
	{
		for (j = 0; j<m; j++)
		{
			if ((i + j) % 2 == 0)
				greyLevel = 0;
			else
				greyLevel = 255;

			image[i * 3 * m + 3 * j] = greyLevel;
			image[i * 3 * m + 3 * j + 1] = greyLevel;
			image[i * 3 * m + 3 * j + 2] = greyLevel;
		}
	}

	return image;
}

GLubyte *strips(int n, int m)
{
	GLubyte *image;
	int nm, i;
	int greyLevel;

	nm = n * m;
	image = (GLubyte *)malloc(3 * sizeof(GLubyte)*nm);

	for (i = 0;i<nm;i++)
	{
		if (i % 2 == 0)
			greyLevel = 0;
		else
			greyLevel = 255;

		image[3 * i] = greyLevel;
		image[3 * i + 1] = greyLevel;
		image[3 * i + 2] = greyLevel;
	}

	return image;
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("3D programming");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);
	glutIdleFunc(NULL);

	glutMainLoop();
	return 1; 
}