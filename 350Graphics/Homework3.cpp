#include "myObjects2023.cpp"

#define DtoR 0.017453

GLsizei ww = 500, wh = 500;
GLfloat increment = 0.01;


const float REGION_DIM = 4;
//const GLfloat DtoR = 0.017453;
GLfloat fov = 45.0, aspect = 1;
GLfloat theta = 30, phi = 60, rho = 10;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat alpha = 0, beta = 0, gama = 0;
GLfloat dAlpha = 5, dBeta = 5, dGama = 5;
GLfloat a = 1.0, b = 1.0, c = 1.0;
GLfloat dA = 0.1, dB = 0.1, dC = 0.1;
GLfloat direction = 1.0;

GLfloat left, right, bottom, top, _near = 5, _far = 20;


float r1 = 0.5;
float r2 = 0.7;
float r3 = 0.9;


void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color; default black; (R, G, B, Opacity)

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho * sin(theta * DtoR) * sin(phi * DtoR), rho * cos(phi * DtoR), rho * cos(theta * DtoR) * sin(phi * DtoR), 0, 0, 0, 0, 1, 0);

	//gluLookAt(8, 8, 12, 0, 0, 0, 0, 1, 0); // for perspective view
	axes(7.5);

	//----------------------- xy ring ---------------------
   // glPushMatrix();
	glRotatef(alpha, 0, 1, 0);

	glColor3f(1, 0.0, 0.0);
	glutSolidTorus((r1/6)*a, (r1*2)*b, 30, 30);
	glColor3f(0.9, 0, 0);
	glutWireTorus(((r1/6)+0.01)*a, ((r1*2)+0.01)*b, 30, 30);
	//glPopMatrix();
	//-----------------------------------------------------
	glRotatef(beta, 1, 0, 0);

		//----------------------- xz ring ---------------------
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 1, 0);
	glutSolidTorus((r2 / 6)*a, (r2 * 2)*b, 30, 30);
	glColor3f(0, 0.9, 0);
	glutWireTorus(((r2 / 6) + 0.01)*a, ((r2 * 2) + 0.01)*b, 30, 30);
	glPopMatrix();
	//-----------------------------------------------------
		//----------------------- yz ring ---------------------
	glPushMatrix();
	glRotatef(gama, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glColor3f(0, 0.0, 1);
	glutSolidTorus((r3 / 6)*a, (r3 * 2)*b, 30, 30);
	glColor3f(0, 0, 0.9);
	glutWireTorus(((r3 / 6) + 0.01)*a, ((r3 * 2) + 0.01)*b, 30, 30);
    glPopMatrix();

	//-----------------------------------------------------

	glutSwapBuffers();
	glutPostRedisplay();
}

// ============================= perspective view ====================================
void reshape(GLsizei w, GLsizei h)
{
	float ratio = w * 1.0 / (h * 1.0);

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
	glFrustum(left, right, bottom, top, _near, _far);	// perspective projection with frustum. use it as same time in init
	//gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void init(void)
{
	float ratio = ww * 1.0 / (wh * 1.0);

	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(1, 1, 1);	// drawing color; default white

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
	glFrustum(left, right, bottom, top, _near, _far);	// perspective projection with frustum. use it as same time in reshape
	//gluPerspective(fov, aspect, near, far);

	glMatrixMode(GL_MODELVIEW);
}
// =================================================================================

void idle()
{

	alpha += 14.92 * increment;
	if (alpha > 360) alpha -= 360;
	glutPostRedisplay();

	beta += 14.92 * increment;
	if (beta > 360) beta -= 360;
	glutPostRedisplay();

	gama += 14.92 * increment;
	if (gama > 360) gama -= 360;
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
		_near = 5;
		_far = 20;
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



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Austin Hartley");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);
	//glutIdleFunc(idle);

	glutMainLoop();
	return 1;
}

