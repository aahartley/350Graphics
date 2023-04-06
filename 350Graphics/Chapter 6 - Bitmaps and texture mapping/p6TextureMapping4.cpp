#include <iostream>	// need it for NULL
#include <math.h>
#include <GL\glut.h>

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 5, far = 20;
const float REGION_DIM = 4;
//const GLfloat DtoR = 0.017453;
GLfloat fov = 45.0, aspect = 1;
GLfloat alpha = 0, beta = 0, gama = 0;
GLfloat direction = 1.0;

GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 },
{ 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 }, { -1.0, -1.0, 1.0 },
{ 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };
GLfloat colors[][4] = { { 0.0, 0.0, 0.0, 0.5 }, { 1.0, 0.0, 0.0, 0.5 },
{ 1.0, 1.0, 0.0, 0.5 }, { 0.0, 1.0, 0.0, 0.5 }, { 0.0, 0.0, 1.0, 0.5 },
{ 1.0, 0.0, 1.0, 0.5 }, { 1.0, 1.0, 1.0, 0.5 }, { 0.0, 1.0, 1.0, 0.5 } };

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void idle(void);
void mouse(int, int, int, int);
void polygonTex(int a, int b, int c, int d);
void colorCubeTex();



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4, 2, 6, 0, 0, 0, 0, 1, 0);

	glRotatef(alpha, 0, 1, 0);
	glRotatef(beta, 0, 1, 0);
	glRotatef(gama, 0, 0, 1);

	colorCubeTex();

	glutSwapBuffers();	
	glutPostRedisplay();	// work with GLUT_DOUBLE
}

void polygonTex(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor4fv(colors[a]);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(vertices[a]);

	glColor4fv(colors[b]);
	glTexCoord2f(0.0, 1);
	glVertex3fv(vertices[b]);

	glColor4fv(colors[c]);
	glTexCoord2f(1, 1);
	glVertex3fv(vertices[c]);

	glColor4fv(colors[d]);
	glTexCoord2f(1, 0);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorCubeTex()
{
	polygonTex(0, 3, 2, 1);
	polygonTex(2, 3, 7, 6);
	polygonTex(0, 4, 7, 3);
	polygonTex(1, 2, 6, 5);
	polygonTex(4, 5, 6, 7);
	polygonTex(0, 1, 5, 4);
}

void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	aspect = ratio;

	glClearColor(0.5, 0.5, 0.5, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

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
//	glFrustum(left, right, bottom, top, near, far);	// perspective projection with frustum. use it as same time in reshape
	gluPerspective(fov, aspect, near, far);

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
	//	glOrtho(left, right, bottom, top, near, far);	// orthogonal projection
	//glFrustum(left, right, bottom, top, near, far);	// perspective projection with frustum. use it as same time in init
	gluPerspective(fov, aspect, near, far);

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
	glutIdleFunc(NULL);

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

void keys(unsigned char k, int x, int y)
{
	if (k == 'i' || k == 'I')
		glutIdleFunc(idle);
	if (k == 'q' || k == 'Q')
		glutIdleFunc(NULL);
}

void main()
{
	GLubyte image[64][64][3];
	int i, j, r, c;
	for (i = 0; i<64; i++)
	{
		for (j = 0; j<64; j++)
		{
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;	// bit-wise XOR
			image[i][j][0] = (GLubyte)c;
			image[i][j][1] = (GLubyte)c;
			image[i][j][2] = (GLubyte)c;
		}
	}
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE work with glutPostRedisplay
	glutInitWindowSize(ww, wh);	// default size 300 by 300
	glutInitWindowPosition(100, 100); // defualt at (0, 0)
	glutCreateWindow("texture mapping");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(NULL);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);

	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glutMainLoop();
}