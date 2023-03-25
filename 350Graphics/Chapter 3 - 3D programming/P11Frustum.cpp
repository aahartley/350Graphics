#include "../myObjects2023.cpp"

GLsizei ww = 512, wh = 512;
GLfloat left = -2.0;
GLfloat right = 2.0;
GLfloat bottom = -2.0;
GLfloat top = 2.0;
GLfloat near = 5.0;
GLfloat far = 15.0;
GLfloat rho = 10.0;
GLfloat phi = 90.0;
GLfloat theta = 0.0;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat direction = 1.0;


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), rho*cos(theta*DtoR)*sin(phi*DtoR), 0, 0, 0, 0, 1, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//cylinder(2, 2);
	glutWireCube(2);
	
	glutSwapBuffers();
	glutPostRedisplay();
}


void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w >= h)
		glFrustum(left*w/h, right*w/h, bottom, top, near, far);
	else
		glFrustum(left, right, bottom*h/w, top*h/w, near, far);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);

	ww = w;
	wh = w;
}

void init()
{
	glClearColor(0, 0, 0, 1);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		theta += dTheta * direction;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		rho += dRho * direction;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		phi += dPhi * direction;
	}
}

void keys(unsigned char k, int x, int y)
{
	if (k == 'p' || k == 'P')
		direction = 1.0;
	else if (k == 'n' || k == 'N')
		direction = -1.0;
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
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);

	glutMainLoop();
}