#include "..\myObjects2022.cpp"

//------ global variables and constants------------
GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near = 5, far = 20;
const float REGION_DIM = 4;
GLfloat fov = 45.0, aspect = 1;
GLfloat theta = 0, phi = 90, rho = 10;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat a = 1, b = 1, c = 1;
GLfloat dA = 0.1, dB = 0.1, dC = 0.1;
GLfloat direction = 1.0;

//----- prototypes ----------
void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void keys(unsigned char k, int x, int y);
void mouse(int, int, int, int);
void idle(void);


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho*cos(theta*DtoR)*sin(phi*DtoR), rho*sin(theta*DtoR)*sin(phi*DtoR), rho*cos(phi*DtoR), 0, 0, 0, 0, 0, 1);

	//----- draw in FILL mode -----------------
	glColor3f(1, 1, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	sphere(a, 40, 20);
	
	//------- draw in LINE mode -----------
	glColor3f(1, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	sphere(a*1.01, 40, 20);
	
	glutSwapBuffers();
	glutPostRedisplay();	// work with GLUT_DOUBLE
}


void init(void)
{
	float ratio = ww*1.0 / (wh*1.0);

	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color; default black; (R, G, B, Opacity)
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

	glutPostRedisplay();
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
	else if (k == 'a' || k == 'A')
		a += dA * direction;
	else if (k == 'b' || k == 'B')
		b += dB * direction;
	else if (k == 'c' || k == 'C')
		c += dC * direction;
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
	//glutIdleFunc(idle);

	glutMainLoop();
	return 1; 
}