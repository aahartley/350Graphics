#include <iostream>	
#include <vector>
#include "myObjects2023.cpp"

#define DtoR 0.017453

GLsizei ww = 700, wh = 700;
GLfloat increment = 0.01;


const float REGION_DIM = 100;
//const GLfloat DtoR = 0.017453;
GLfloat fov = 45.0, aspect = 1;
GLfloat theta = 30, phi = 60, rho = 10;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat alpha = 0, beta = 0, gama = 0;
GLfloat dAlpha = 5, dBeta = 5, dGama = 5;
GLfloat a = 1.0, b = 1.0, c = 1.0;
GLfloat dA = 0.1, dB = 0.1, dC = 0.1;
GLfloat direction = 1.0;

GLfloat left, right, bottom, top, _near = 0.01, _far = 200;

float xangle = 0, yangle = 1, zangle = -1;

float x = 0, y = 2, z = 0.0f;
float sens = 0.01f;
float xPos = 0, yPos = 0;

float r1 = 0.5;
float r2 = 0.7;
float r3 = 0.9;
GLfloat lightPos[] = { 1, 4, 10, 1 };

struct Triangle {
	float* p1;
	float* p2;
	float* p3;
	float* normal;
};

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

materialStruct* currentMaterials;
lightingStruct* currentLighting;

materialStruct redPlasticMaterials = {
	{0.3, 0.0, 0.0, 1.0},
	{0.6, 0.0, 0.0, 1.0},
	{0.8, 0.6, 0.6, 1.0},
	32.0
};
lightingStruct coloredLighting = {
	{0.2, 0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0, 1.0},
	{0.0, 0.0, 1.0, 1.0}
};

lightingStruct whiteLighting = {
	{0.0, 0.0, 0.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0}
};
void materials(materialStruct* m)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m->shininess);
}

void lighting(lightingStruct* li)
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, li->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, li->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, li->specular);
}
void normal(float p0[], float p1[], float p2[], float n[])
{
	float a[3], b[3];
	float d;

	for (int i = 0; i < 3; i++)
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

	for (int i = 0; i < 3; i++)
		n[i] = n[i] / d;
}
float* normal(float p0[], float p1[], float p2[])
{
	float* n = new float[3];
	float a[3], b[3];
	float d;

	for (int i = 0; i < 3; i++)
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

	for (int i = 0; i < 3; i++)
		n[i] = n[i] / d;
	return n;
}
std::vector<std::vector<float*>> planes;
std::vector<float*> verts;
std::vector<Triangle> triangles;
void genplane(float* offset, bool build, int vertsPerRow) {
	verts.push_back(offset);
	if (build) {
		int base = verts.size() - 1;
		int index0 = base;
		int index1 = base - 1;
		int index2 = base - vertsPerRow;
		int index3 = base - vertsPerRow - 1;

		Triangle tmp;
		tmp.p1 = verts[index0];
		tmp.p2 = verts[index2];
		tmp.p3 = verts[index1];
		tmp.normal = normal(tmp.p1,tmp.p2,tmp.p3);
		triangles.push_back(tmp);

		Triangle tmp2;
		tmp2.p1 = verts[index2];
		tmp2.p2 = verts[index3];
		tmp2.p3 = verts[index1];
		tmp2.normal = normal(tmp2.p1, tmp2.p2, tmp2.p3); //3,1,2
		triangles.push_back(tmp2);
	}
}
void plane(float* offset) {
	std::vector<float*> plane;
	float length = 3;
	float* p1 = new float[3];
	float* p2 = new float[3];
	float* p3 = new float[3];
	float* p4 = new float[3];  //delete later

	p1[0] = 0 + offset[0];
	p1[1] = 0 + offset[1];
	p1[2] = 0 + offset[2];
	plane.push_back(p1);

	p2[0] = 0 + offset[0];
	p2[1] = 0 + offset[1];
	p2[2] = length + offset[2];
	plane.push_back(p2);

	p3[0] = length + offset[0];
	p3[1] = 0 + offset[1];
	p3[2] = length + offset[2];
	plane.push_back(p3);

	p4[0] = length + offset[0];
	p4[1] = 0 + offset[1];
	p4[2] = 0 + offset[2];
	plane.push_back(p4);
	planes.push_back(plane);
	//int planeIndex = baseIndex / 4;



}
void display()
{
	//glClearColor(1.0, 1.0, 1.0, 1.0);	// background color; default black; (R, G, B, Opacity)

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	materials(currentMaterials);
	lighting(currentLighting);
	gluLookAt(rho * sin(theta * DtoR) * sin(phi * DtoR), rho * cos(phi * DtoR), rho * cos(theta * DtoR) * sin(phi * DtoR), 0, 0, 0, 0, 1, 0);
	//std::cout << x+xangle  << ' ' << y-yangle << ' ' << z+zangle << '\n';
	//gluLookAt(x, y, z, x + xangle, y - yangle, z + zangle, 0, 1, 0);
	//gluLookAt(8, 8, 12, 0, 0, 0, 0, 1, 0); // for perspective view
	axes(7.5);
	//for (int i = 0; i < planes.size(); i++) {
	//	int baseIndex = 0;// ((i + 1) * 4) - 4;
	//	glNormal3f(0, 1, 0);
	//	glBegin(GL_TRIANGLES);
	//	glVertex3fv(planes[i][baseIndex]);
	//	glVertex3fv(planes[i][baseIndex + 3]);
	//	glVertex3fv(planes[i][baseIndex + 2]);

	//	glVertex3fv(planes[i][baseIndex]);
	//	glVertex3fv(planes[i][baseIndex + 2]);
	//	glVertex3fv(planes[i][baseIndex + 1]);

	//	glEnd();
	//}
	for (int i = 0; i < triangles.size(); i++) {
		//glNormal3f(0,1,0);
		glNormal3fv(triangles[i].normal);
		//glBegin(GL_TRIANGLES);
		glVertex3fv(triangles[i].p1);
		glVertex3fv(triangles[i].p2);
		glVertex3fv(triangles[i].p3);
		//glEnd();

	}
	float angle = 2 * 3.14159 / 100;//3.6 d
	angle = 3.14159 / 4;
	float h = 1.5, r = 1, H = 0.6, R = 1.5, n = 8;
	float p1[3], p2[3], p3[3], p4[3], norm[3];
	////----------------------- draw top --------------------------
	//glNormal3f(0, 0, 1);
	//glBegin(GL_POLYGON);
	//for (int i = 0; i < n; i++)
	//{
	//	p1[0] = r * cos(i * angle);
	//	p1[1] = r * sin(i * angle);
	//	p1[2] = h;

	//	glVertex3fv(p1);
	//}
	//glEnd();
	////------------------ draw side triangles ------------------
	//for (int i = 0; i < n; i++)
	//{
	//	p1[0] = R * cos(i * angle);
	//	p1[1] = R * sin(i * angle);
	//	p1[2] = H;

	//	if (i == n - 1)
	//	{
	//		p2[0] = R;
	//		p2[1] = 0;
	//	}
	//	else
	//	{
	//		p2[0] = R * cos((i + 1) * angle);
	//		p2[1] = R * sin((i + 1) * angle);
	//	}
	//	p2[2] = H;

	//	p3[0] = 0; p3[1] = 0; p3[2] = -1.0 * h;

	//	normal(p3, p2, p1, norm);
	//	glNormal3fv(norm);

	//	glBegin(GL_TRIANGLES);
	//	glVertex3fv(p1);
	//	glVertex3fv(p2);
	//	glVertex3fv(p3);
	//	glEnd();
	//}

	//---------------------------------------------------------
	//--------------------- draw side polygons --------------------
	//for (int i = 0; i < n; i++)
	//{
	//	p1[0] = r * cos(i * angle);
	//	p1[1] = r * sin(i * angle);
	//	p1[2] = h;

	//	if (i == n - 1)
	//	{
	//		p2[0] = r;
	//		p2[1] = 0;
	//	}
	//	else
	//	{
	//		p2[0] = r * cos((i + 1) * angle);
	//		p2[1] = r * sin((i + 1) * angle);
	//	}
	//	p2[2] = h;

	//	p3[0] = R * cos(i * angle);
	//	p3[1] = R * sin(i * angle);
	//	p3[2] = H;

	//	if (i == n - 1)
	//	{
	//		p4[0] = R;
	//		p4[1] = 0;
	//	}
	//	else
	//	{
	//		p4[0] = R * cos((i + 1) * angle);
	//		p4[1] = R * sin((i + 1) * angle);
	//	}
	//	p4[2] = H;
	//	normal(p1, p3, p2, norm);

	//	glNormal3fv(norm);
	//	glBegin(GL_POLYGON);
	//	glVertex3fv(p1);
	//	glVertex3fv(p2);
	//	glVertex3fv(p4);
	//	glVertex3fv(p3);
	//	glEnd();
	//}
	//-----------------------------------------------------------
	//draw squirtle shell bttb
	float radiusFront = 1;
	float zStart = 0;
	float zEnd = 1;
	float radiusBack = 2;
	for (int i = 0; i < n/2+1; i++) {
		p1[0] = radiusFront * cos(i * angle);
		p1[1] = radiusFront * sin(i * angle);
		if (i == 0 || i==(n/2) )
			p1[2] = zStart - 0.25;
		else p1[2] = zStart;

		if ((i == (n - 1)))
		{
			p2[0] = radiusFront;
			p2[1] = 0;
			p2[2] = -0.25;
		}
		else if (i == (n / 2) - 1) {
			p2[0] = radiusFront;
			p2[1] = 0;
			p2[2] = -0.25;
		}
		else
		{
			p2[0] = radiusFront * cos((i + 1) * angle);
			p2[1] = radiusFront * sin((i + 1) * angle);
			p2[2] = zStart;
		}
		//if (i == n / 2+1)std::cout << p2[2];
		p4[0] = radiusBack * cos(i * angle);
		p4[1] = radiusBack * sin(i * angle);
		p4[2] = zEnd;

		if (i == n - 1)
		{
			p3[0] = radiusBack;
			p3[1] = 0;
		}
		else
		{
			p3[0] = radiusBack * cos((i + 1) * angle);
			p3[1] = radiusBack * sin((i + 1) * angle);
		}
		p3[2] = zEnd;

		normal(p1, p2, p3, norm);

		glNormal3fv(norm);
		glBegin(GL_POLYGON);
		glVertex3fv(p1);
		glColor3f(1, 0, 0);
		glVertex3fv(p2);
		glColor3f(1, 1, 1);

		glVertex3fv(p3);
		glVertex3fv(p4);
		glEnd();
	}
	//-----------------------------------------------------------
	//-----------------------------------------------------------
	//draw shell top
	glNormal3f(0, 0, -1);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= n/2; i++)
	{
		p1[0] = r * cos(i * angle);
		p1[1] = r * sin(i * angle);
		if (p1[1] > 0.2)
			p1[2] = 0;
		else p1[2] = -.25; 
		

		glVertex3fv(p1);
	}
	glEnd();
	glNormal3f(0, 0, -1);
	glBegin(GL_POLYGON);
	for (int i = n/2; i <= n; i++)
	{
		p1[0] = r * cos(i * angle);
		p1[1] = r * sin(i * angle);
		if (p1[1] >-0.2)
			p1[2] = -.25;
		else p1[2] = 0;


		glVertex3fv(p1);
	}
	glEnd();
	//-----------------------------------------------------------

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
	//glFrustum(left, right, bottom, top, _near, _far);	// perspective projection with frustum. use it as same time in init
	gluPerspective(fov, aspect, _near, _far);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void init(void)
{
	float ratio = ww * 1.0 / (wh * 1.0);

	glClearColor(0, 0, 0, 1.0);	// background color; default black; (R, G, B, Opacity)
	//glColor3f(1, 1, 1);	// drawing color; default white
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	currentMaterials = &redPlasticMaterials;
	materials(currentMaterials);

	currentLighting = &whiteLighting;
	lighting(currentLighting);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

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
	//for (int i = 0; i < 10; i++) {
	//	float z = 3 * i;
	//	for (int j = 0; j < 10; j++) {
	//		float x = 3 * j;
	//		float* offset = new float[3];
	//		offset[0] = x;
	//		offset[1] = std::rand() % 2;
	//		offset[2] = z;
	//		plane(offset);
	//		delete[] offset;
	//	}
	//}
	for (int i = 0; i <= 10; i++) {
		float z = 3 * i;
		for (int j = 0; j <= 10; j++) {
			float x = 3 * j;
			float* offset = new float[3];
			offset[0] = x;
			offset[1] = std::rand() % 2;
			offset[2] = z;
			bool build = i > 0 && j > 0;
			genplane(offset, build, 10 + 1);
		}
	}

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
void mouseMove(int x, int y) {
	
	float xx, yy;
	xx = x;
	yy = y;
	if (xx >= ww - 2)xx = 3;
	else if (xx <= 2) xx = ww-3;
	if (xx != x || yy != y)glutWarpPointer(xx, yy);
	xPos = (xx - ww / 2) * sens;
	yPos = (yy - wh / 2) * sens;

	xangle = std::sin(xPos);
	yangle = std::sin(yPos);
	zangle = -std::cos(xPos);
	//std::cout << xangle << ' ' << zangle << '\n';

	if (std::abs(yPos)>=1.57){
		int sign = yPos > 0 ? 1 : -1;
		yangle = 1 * sign;
	}
}
void keys(unsigned char k, int xx, int yy)
{
	float speed = 0.5f;

	if (k == 'p' || k == 'P')
		direction = 1.0;
	else if (k == 'n' || k == 'N')
		direction = -1.0;
	else if (k == 'a' || k == 'A') {
		x += zangle * speed;
		z -= xangle * speed;
	}
	else if (k == 'd' || k == 'D') {
		x -= zangle * speed;
		z += xangle * speed;
	}
	else if (k == 'w' || k == 'W') {
		x +=xangle * speed;
		z += zangle * speed;
		//std::cout << x << ' ' << z << '\n';

	}
	else if (k == 's' || k == 'S') {
		x -= xangle * speed;
		z -= zangle * speed;
		//std::cout << x << ' ' << z << '\n';

	}
		//a += dA * direction;
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
		x = 0;
		y = 2;
		z = 0;
		xangle = 0;
		yangle = 1;
		zangle = -1;
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
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Austin Hartley");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMove);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);
	//glutIdleFunc(idle);
	init();
	glutMainLoop();

	return 1;
}

