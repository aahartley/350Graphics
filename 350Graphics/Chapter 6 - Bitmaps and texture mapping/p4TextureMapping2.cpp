#include <iostream>
#include <GL/glut.h>

#define alpha 1

GLfloat theta[] = {0.0,0.0,0.0};
GLint axis = 2;


GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
    {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
    {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat colors[8][4]= {{0, 0, 0, alpha}, {1, 0, 0, alpha}, {1, 1, 0, alpha}, {0, 1, 0, alpha}, {0, 0, 1, alpha},
{1, 0, 1, alpha}, {1, 1, 1, alpha}, {0, 1, 1, alpha}};

void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
		glTexCoord2f(0.0,0.0);
		glColor4f(1, 1, 1, alpha);
		glVertex3fv(vertices[a]);

		glTexCoord2f(0.0,1.0);
		glColor4f(1, 1, 1, alpha);
		glVertex3fv(vertices[b]);

		glTexCoord2f(1.0,1.0);
		glColor4f(1, 1, 1, alpha);
		glVertex3fv(vertices[c]);
 
		glTexCoord2f(1.0,0.0);
		glColor4f(1, 1, 1, alpha);
		glVertex3fv(vertices[d]);
    glEnd();
}

void colorPolygon(int a, int b, int c, int d)
{
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

void aCube()
{
    polygon(0,3,2,1);
    polygon(2,3,7,6);
    polygon(0,4,7,3);
    polygon(1,2,6,5);
    polygon(4,5,6,7);
    polygon(0,1,5,4);
}
void aColorCube()
{
    colorPolygon(0,3,2,1);
    colorPolygon(2,3,7,6);
    colorPolygon(0,4,7,3);
    colorPolygon(1,2,6,5);
    colorPolygon(4,5,6,7);
    colorPolygon(0,1,5,4);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

	//aColorCube();

	//glColor3f(1, 0, 0);
	aCube();

	//glutSolidTeapot(1);

    glutSwapBuffers();
}

void spinCube()
{
    theta[axis] += 0.02;
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
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char k, int x, int y)
{
    if(k == '1') glutIdleFunc(spinCube);
    if(k == '2') glutIdleFunc(NULL);
    if(k == 'q') exit(0);
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

int main(int argc, char **argv)
{
	int n, m;
	GLubyte *image;
//	image = readPPM(&n, &m);

	n = m = 8;
	//image = stripes(n, m);
	image = checkerBoard(n, m);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("texture mapping");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D,0,3,n,m,0,GL_RGB,GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glutKeyboardFunc(key);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glutMainLoop();
}
