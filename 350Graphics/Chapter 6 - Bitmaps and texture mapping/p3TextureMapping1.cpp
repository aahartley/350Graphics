#include <iostream>
#include <GL/glut.h>

GLfloat theta[] = {0.0,0.0,0.0};
GLint axis = 2;
int n1, m1;
int n2, m2;
int n3, m3;
int n4, m4;
int n5, m5;
int n6, m6;

GLubyte *image1, *image2, *image3, *image4, *image5, *image6;

GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
    {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
    {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat colors[8][4]= {{0, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 0, 1}, {0, 1, 0, 1}, {0, 0, 1, 1},
{1, 0, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}};

//-------------------------------------------------------------
GLubyte *stripes(int n, int m);
GLubyte *checkerBoard(int n, int m);
void polygon(int a, int b, int c, int d, int n, int m, GLubyte *image);
void cube();
//-------------------------------------------------------------


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	cube();

	glutSwapBuffers();
}

void polygon(int a, int b, int c, int d, int n, int m, GLubyte *image)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBegin(GL_POLYGON);

    glTexCoord2f(0.0,0.0);
	glColor4fv(colors[a]);	
    glVertex3fv(vertices[a]);

    glTexCoord2f(0.0,1.0);
	glColor4fv(colors[b]);
    glVertex3fv(vertices[b]);

    glTexCoord2f(1.0,1.0);
	glColor4fv(colors[c]);
    glVertex3fv(vertices[c]);
 
    glTexCoord2f(1.0,0.0);
	glColor4fv(colors[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}

void cube()
{
	n1 = m1 = 4;
	image1 = stripes(n1, m1);

	n2 = m2 = 4;
	image2 = checkerBoard(n2, m2);

	n3 = m3 = 16;
	image3 = checkerBoard(n3, m3);

	n4 = m4 = 8;
	image4 = stripes(n4, m4);

	n5 = m5 = 8;
	image5 = checkerBoard(n5, m5);

	n6 = m6 = 16;
	image6 = checkerBoard(n6, m6);

    polygon(0,3,2,1, n1, m1, image1);
    polygon(2,3,7,6, n2, m2, image2);
    polygon(0,4,7,3, n3, m3, image3);
    polygon(1,2,6,5, n4, m4, image4);
    polygon(4,5,6,7, n5, m5, image5);
    polygon(0,1,5,4, n6, m6, image6);
}

GLubyte *checkerBoard(int n, int m)
{
	GLubyte *image;
	int nm, i, j;
	int greyLevel;

	nm = n * m;
	image = (GLubyte *)malloc(3 * sizeof(GLubyte)*nm);

	for (i = 0; i<n; i++)
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

GLubyte *stripes(int n, int m)
{
	GLubyte *image;
	int nm, i;
	int greyLevel;

	nm = n * m;
	image = (GLubyte *)malloc(3 * sizeof(GLubyte)*nm);

	for (i = 0; i<nm; i++)
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

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glColor4f(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -2.0, 2.0, 8.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
}

void spinCube()
{
    theta[axis] += 0.05;
    if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
    if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glFrustum(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, 8.0, 15.0);
    else
        glFrustum(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, 8.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char k, int x, int y)
{
	if (k == 'i') glutIdleFunc(spinCube);
	if (k == 'q') glutIdleFunc(NULL);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("texture map");

	init();

    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);
	glutReshapeFunc(myReshape);
    glutKeyboardFunc(key);

    glutMainLoop();
}
