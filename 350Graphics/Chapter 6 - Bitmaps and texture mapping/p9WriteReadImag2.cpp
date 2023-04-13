#include <GL/glut.h>
#include <math.h>

GLsizei ww = 400, wh = 400;
GLfloat theta[3] = {0, 0, 0};
GLint axis = 2;

GLubyte image[200][200][3];


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 10, 0, 0, 0, 0, 1, 0);
	

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	glColor3f(0, 0, 1);
	glutSolidCube(1);
	glColor3f(1, 0, 0);
	glutWireCube(1.01);
	

	// read from the frame buffer and store in image
	glReadPixels(ww/2-100, wh/2-100, 200, 200, GL_RGB, GL_UNSIGNED_BYTE, image); 

	glRasterPos3f(-2, -2, 0); 
	glDrawPixels(200, 200, GL_RGB, GL_UNSIGNED_BYTE, image);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
			2.0 * (GLfloat)h / (GLfloat)w, 8.0, 15.0);
	else
		glFrustum(-2.0 * (GLfloat)w / (GLfloat)h,
			2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, 8.0, 15.0);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = h;
}

void init()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glColor4f(1, 1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -2.0, 2.0, 8.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
}

void idle()
{
	theta[axis] += 0.05;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void key(unsigned char k, int x, int y)
{
	if (k == 'i') glutIdleFunc(idle);
	if (k == 'q') glutIdleFunc(NULL);
}

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("objects");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(NULL);
	glutMouseFunc(mouse);
	glutKeyboardFunc(key);
	
	glutMainLoop();
}