//#include <GL/glut.h>
//#include <math.h>
#include "../myObjects2023.cpp"

GLsizei ww = 500, wh = 500;
GLfloat theta[2] = {0, 0};
GLfloat shift[2] = {0, 0};
GLfloat scale = 1;
GLfloat increment[2] = {0, 0};
GLfloat halfWidth = 4;
GLfloat halfHeight = 4;
int axis = 0;


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(shift[0], shift[1], 0);

	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);

	glScalef(scale, scale, scale);

	glColor3f(1, 1, 0);
	glutSolidCube(1);
	glColor3f(1, 0, 0);
	glutWireCube(1);

	glutSwapBuffers();
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(0, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -20, 20);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glOrtho(-halfWidth*w/h, halfWidth*w/h, -halfHeight, halfHeight, -20, 20);
	else
		glOrtho(-halfWidth, halfWidth, -halfHeight*h/w, halfHeight*h/w, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = h;
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		increment[0] = (float)(x - ww / 2) / (ww / 2)*0.05;
		increment[1] = (float)((wh - y) - wh / 2) / (wh / 2)*0.05;
	}

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (ww <= wh)
		{
			shift[0] = (float)(x - ww / 2) / (float)(ww / 2) * halfWidth;
			shift[1] = (float)((wh - y) - wh / 2) / (float)(wh / 2) * (float)wh / (float)ww * halfHeight;
		}
		else
		{
			shift[0] = (float)(x - ww / 2) / (float)(ww / 2) * (float)ww / float(wh) * halfWidth;
			shift[1] = (float)((wh - y) - wh / 2) / (float)(wh / 2) * halfHeight;
		}
	}

	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		if (x > ww / 2)
			scale *= 2;
		else 
			scale *= 0.5;
	}
}

void idle()
{
	theta[0] += increment[0];
	theta[1] += increment[1];

	for (int i=0; i<2; i++)
	{
		if (theta[i] > 360.0)
			theta[i] -= 360.0;

		if (theta[i] < -360.0)
			theta[i] += 360.0;
	}

	glutPostRedisplay();
}



void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("cube");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
}

