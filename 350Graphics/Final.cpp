#include <iostream>	
#include <vector>
#include <time.h>
#include "myObjects2023.cpp"

#define DtoR 0.017453

GLsizei ww = 700, wh = 700;
GLfloat increment = 0.01;


const float REGION_DIM = 100;
//const GLfloat DtoR = 0.017453;
GLfloat fov = 45.0, aspect = 1;
GLfloat theta = 30, phi = 60, rho = 10;
float theta2 = 30;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat alpha = 0, beta = 0, gama = 0;
GLfloat dAlpha = 5, dBeta = 5, dGama = 5;
GLfloat a = 1.0, b = 1.0, c = 1.0;
GLfloat dA = 0.1, dB = 0.1, dC = 0.1;
GLfloat direction = 1.0;

int initialTime = time(NULL), finalTime, frameCount=0;

GLfloat left, right, bottom, top, _near = 0.01, _far = 200;

float xangle = 0, yangle = 1, zangle = -1;

float x = 0, y = 2, z = 0.0f;
float sens = 0.01f;
float xPos = 0, yPos = 0;

float r1 = 0.5;
float r2 = 0.7;
float r3 = 0.9;

float legtheta = 90;
GLfloat global_ambient[] = { 1, 0.0, 0.0, 1.0 };  // independent of any of the sources
GLfloat emission[] = { 1, 1, 1 };

GLfloat lightPos[] = { 0, 3, 5, 1};

struct Triangle {
	float* p1;
	float* p2;
	float* p3;
	float* normal;
};

struct Vector3f {
	float x, y, z;
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
materialStruct blueMaterials = {
	{0., 0.0, 0.6, 1.0},
	{0.0, 0.0, 0.4, 1.0},
	{0.0, 0.6, 0.1, 1.0},
	2.0
};

materialStruct brassMaterials = {
	{ 0.33, 0.22, 0.03, 1.0 },
	{ 0.78, 0.57, 0.11, 1.0 },
	{ 0.99, 0.91, 0.81, 1.0 },
	27.8
};
materialStruct whiteShineyMaterials = {
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	{1.0, 1.0, 1.0, 1.0},
	100.0
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

void drawHalfSphereWithNormalSmooth(GLfloat radius)
{
	GLint longitude = 5, latitude = 5;
	GLint phi, theta;
	GLfloat p1[3], p2[3], p3[3], p4[3];
	float invR = 1 / radius;
	glBegin(GL_QUADS);

	for (phi = -90; phi <= 0 - latitude; phi += latitude)
	{
		for (theta = -180; theta <= 180; theta += longitude)
		{
			p1[0] = radius * cos(theta * DtoR) * cos(phi * DtoR);
			p1[1] = radius * sin(theta * DtoR) * cos(phi * DtoR);
			p1[2] = radius * sin(phi * DtoR);

			p2[0] = radius * cos((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[1] = radius * sin((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[2] = radius * sin(phi * DtoR);

			p3[0] = radius * cos((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[1] = radius * sin((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[2] = radius * sin((phi + latitude) * DtoR);

			p4[0] = radius * cos(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[1] = radius * sin(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[2] = radius * sin((phi + latitude) * DtoR);

			glNormal3f(p1[0] * invR, p1[1] * invR, p1[2] * invR); // could be set up for every vertex
			glVertex3fv(p1);
			glNormal3f(p2[0] * invR, p2[1] * invR, p2[2] * invR);
			glVertex3fv(p2);
			glNormal3f(p3[0] * invR, p3[1] * invR, p3[2] * invR);
			glVertex3fv(p3);
			glNormal3f(p4[0] * invR, p4[1] * invR, p4[2] * invR);
			glVertex3fv(p4);
		}
	}
	glEnd();

}
void drawSphereWithNormalSmooth(GLfloat radius)
{
	GLint longitude = 5, latitude = 5;
	GLint phi, theta;
	GLfloat p1[3], p2[3], p3[3], p4[3];
	float invR = 1 / radius;

	glBegin(GL_QUADS);
	for (phi = -90; phi <= 90 - latitude; phi += latitude)
	{
		for (theta = -180; theta <= 180; theta += longitude)
		{
			p1[0] = radius * cos(theta * DtoR) * cos(phi * DtoR);
			p1[1] = radius * sin(theta * DtoR) * cos(phi * DtoR);
			p1[2] = radius * sin(phi * DtoR);

			p2[0] = radius * cos((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[1] = radius * sin((theta + longitude) * DtoR) * cos(phi * DtoR);
			p2[2] = radius * sin(phi * DtoR);

			p3[0] = radius * cos((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[1] = radius * sin((theta + longitude) * DtoR) * cos((phi + latitude) * DtoR);
			p3[2] = radius * sin((phi + latitude) * DtoR);

			p4[0] = radius * cos(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[1] = radius * sin(theta * DtoR) * cos((phi + latitude) * DtoR);
			p4[2] = radius * sin((phi + latitude) * DtoR);

			glNormal3f(p1[0] * invR, p1[1] * invR, p1[2] * invR); // could be set up for every vertex
			glVertex3fv(p1);
			glNormal3f(p2[0] * invR, p2[1] * invR, p2[2] * invR);
			glVertex3fv(p2);
			glNormal3f(p3[0] * invR, p3[1] * invR, p3[2] * invR);
			glVertex3fv(p3);
			glNormal3f(p4[0] * invR, p4[1] * invR, p4[2] * invR);
			glVertex3fv(p4);
		}

	}
	glEnd();

}
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
void shell() {
	float angle = 2 * 3.14159 / 100;//3.6 d
	angle = 3.14159 / 4;
	float h = 1.5, r = 1, H = 0.6, R = 1.5, n = 8;
	float p1[3], p2[3], p3[3], p4[3], norm[3];

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	currentMaterials = &redPlasticMaterials;
	materials(currentMaterials);
	glTranslatef(0, 0, -2.4);
	glRotatef(90,0, 0, 1);
	//draw squirtle shell bttb
	float radiusFront = 1;
	float zStart = 0;
	float zEnd = 1;
	float radiusBack = 2;
	float shellIncrement = .25;
	for (int i = 0; i < n; i++) {
		p1[0] = radiusFront * cos(i * angle);
		p1[1] = radiusFront * sin(i * angle);
		if (i == 0 || i == (n / 2))
			p1[2] = zStart - shellIncrement;
		else p1[2] = zStart;

		if ((i == (n - 1)))
		{
			p2[0] = radiusFront;
			p2[1] = 0;
			p2[2] = zStart - shellIncrement;
		}
		else if (i == (n / 2) - 1) {
			p2[0] = radiusFront * cos((i + 1) * angle);
			p2[1] = radiusFront * sin((i + 1) * angle);
			p2[2] = zStart - shellIncrement;
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
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p4);
		glEnd();
	}
	//-----------------------------------------------------------
	//-----------------------------------------------------------
	//draw shell top
	//glNormal3f(0, 0, -1);
	std::vector<Vector3f> topPoints;
	for (int i = 0; i <= n / 2; i++)
	{
		p1[0] = radiusFront * cos(i * angle);
		p1[1] = radiusFront * sin(i * angle);
		if (p1[1] > 0.2)
			p1[2] = 0;
		else p1[2] = zStart-shellIncrement;
		Vector3f tmp{ p1[0],p1[1],p1[2] };
		topPoints.push_back(tmp);

	}
	p1[0] = topPoints[0].x;
	p1[1] = topPoints[0].y;
	p1[2] = topPoints[0].z;

	p2[0] = topPoints[1].x;
	p2[1] = topPoints[1].y;
	p2[2] = topPoints[1].z;

	p3[0] = topPoints[2].x;
	p3[1] = topPoints[2].y;
	p3[2] = topPoints[2].z;

	normal(p3, p2, p1, norm);
	glNormal3fv(norm);
	glBegin(GL_POLYGON);
	for (int i = 0; i < topPoints.size(); i++) {
		p1[0] = topPoints[i].x;
		p1[1] = topPoints[i].y;
		p1[2] = topPoints[i].z;
		glVertex3fv(p1);
	}
	glEnd();



	for (int i = n / 2; i <= n; i++)
	{
		p1[0] = r * cos(i * angle);
		p1[1] = r * sin(i * angle);
		if (p1[1] > -0.2)
			p1[2] = -.25;
		else p1[2] = 0;
		Vector3f tmp{ p1[0],p1[1],p1[2] };
		topPoints.push_back(tmp);

	}
	p1[0] = topPoints[5].x;
	p1[1] = topPoints[5].y;
	p1[2] = topPoints[5].z;

	p2[0] = topPoints[6].x;
	p2[1] = topPoints[6].y;
	p2[2] = topPoints[6].z;

	p3[0] = topPoints[7].x;
	p3[1] = topPoints[7].y;
	p3[2] = topPoints[7].z;
	normal(p3, p2, p1, norm);
	glNormal3fv(norm);
	//std::cout << norm[0] << norm[1] << norm[2] << '\n';

	glBegin(GL_POLYGON);
	for (int i = 5; i < topPoints.size(); i++) {
		p1[0] = topPoints[i].x;
		p1[1] = topPoints[i].y;
		p1[2] = topPoints[i].z;
		glVertex3fv(p1);
	}
	glEnd();
	//-----------------------------------------------------------
	//draw shell base
	float shellStacks = 25;
	//glNormal3f(0, 0, -1);
	std::vector<Vector3f> basePoints;
	for (int j = 0; j < shellStacks; j++) {
		for (int i = 0; i <= n; i++)
		{
			p1[0] = (radiusBack + shellIncrement) * cos(i * angle);
			p1[1] = (radiusBack + shellIncrement) * sin(i * angle);
			p1[2] = zEnd+j*.01;
			Vector3f tmp{ p1[0],p1[1],p1[2] };
			basePoints.push_back(tmp);
		}
		p1[0] = basePoints[0].x;
		p1[1] = basePoints[0].y;
		p1[2] = basePoints[0].z;

		p2[0] = basePoints[1].x;
		p2[1] = basePoints[1].y;
		p2[2] = basePoints[1].z;

		p3[0] = basePoints[2].x;
		p3[1] = basePoints[2].y;
		p3[2] = basePoints[2].z;
		if (j == shellStacks - 1)normal(p1, p2, p3, norm);
		else normal(p3, p2, p1, norm);
		if (j!=0 && j < shellStacks-2)glNormal3f(1, 0, 0);
		else glNormal3fv(norm);
		currentMaterials = &whiteShineyMaterials;
		materials(currentMaterials);
		glBegin(GL_POLYGON);
		for (int i = 0; i < basePoints.size(); i++) {
			p1[0] = basePoints[i].x;
			p1[1] = basePoints[i].y;
			p1[2] = basePoints[i].z;
			glVertex3fv(p1);
		}
		glEnd();
		basePoints.clear();
	}
	
	glPopAttrib();
	glPopMatrix();
	currentMaterials = &blueMaterials;
	materials(currentMaterials);
}

void mainBody();
void lowerBody();
void leftLegCheek();
void rightLegCheek();
void head();
void noseArea();
void rightHand();
void leftHand();
void leftEar();
void rightEar();
void leftEyes();
void rightEyes();
void nose();
void tail();
void leftCheek();
void rightCheek();
void drawPikachu();

void head2();
void rightEye();
void leftEye();
void body();
void leftArm();
void rightArm();
void shell();
void leftLeg();
void rightLeg();
void leftFoot();
void drawSquirtle();

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
	/*glPushMatrix();
	glRotatef(theta2,1,0,0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();*/
	
	//std::cout << x+xangle  << ' ' << y-yangle << ' ' << z+zangle << '\n';
	//gluLookAt(x, y, z, x + xangle, y - yangle, z + zangle, 0, 1, 0);
	//gluLookAt(8, 8, 12, 0, 0, 0, 0, 1, 0); // for perspective view
	axes(7.5);
	//for (int i = 0; i < triangles.size(); i++) {
	//	glNormal3f(0,1,0);
	//	glNormal3fv(triangles[i].normal);
	//	glBegin(GL_TRIANGLES);
	//	glVertex3fv(triangles[i].p1);
	//	glVertex3fv(triangles[i].p2);
	//	glVertex3fv(triangles[i].p3);
	//	glEnd();

	//}
	//drawPikachu();
	//glTranslatef(0, 0, -4.2);
	//shell();
	drawSquirtle();

	glutSwapBuffers();
	//glutPostRedisplay();

	frameCount++;
	finalTime = time(NULL);
	if (finalTime - initialTime > 0) {
		std::cout << "FPS: " << frameCount / (finalTime - initialTime) << '\n';
		frameCount = 0;
		initialTime = finalTime;
	}
}


void init(void)
{
	float ratio = ww * 1.0 / (wh * 1.0);

	glClearColor(0, 0, 0, 1.0);	// background color; default black; (R, G, B, Opacity)
	//glColor3f(1, 1, 1);	// drawing color; default white
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_POLYGON_SMOOTH);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_COLOR_MATERIAL);
	currentMaterials = &blueMaterials;
	materials(currentMaterials);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

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

// =================================================================================

void idle()
{
	theta2 += 14.92 * increment;
	if (theta2 > 360) theta2 -= 360;

	//legtheta -= 14.92 * increment;
	//if (legtheta < 80) legtheta = 90;
	glutPostRedisplay();
	//alpha += 14.92 * increment;
	//if (alpha > 360) alpha -= 360;
	//glutPostRedisplay();

	//beta += 14.92 * increment;
	//if (beta > 360) beta -= 360;
	//glutPostRedisplay();

	//gama += 14.92 * increment;
	//if (gama > 360) gama -= 360;
	//glutPostRedisplay();


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
	//glutPassiveMotionFunc(mouseMove);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);
	glutIdleFunc(idle);
	init();
	glutMainLoop();

	return 1;
}
void drawPikachu() {
	mainBody();
	lowerBody();
	leftLegCheek();
	rightLegCheek();
	head();
	//noseArea();
	rightHand();
	leftHand();
	leftEar();
	rightEar();
	leftEyes();
	rightEyes();
	nose();
	tail();
	leftCheek();
	rightCheek();
};
void drawSquirtle() {
	head2();
	rightEye();
	leftEye();
	shell();
	body();
	leftArm();
	rightArm();
	leftLeg();
	rightLeg();
	leftFoot();
}

void head2() {

	glPushMatrix();
	//top half sphere
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
	glTranslatef(0, 2, 0);
	glRotatef(90, 0, 1,0);
	glRotatef(90, 1, 0, 0);
	glScalef(1.4, 1.3, 1.6);
	drawHalfSphereWithNormalSmooth(1);
	glPopAttrib();
	glPopMatrix();

	//bottm plane of top half sphere
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
	glTranslatef(0, 2, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(1.4, 1.3, .5);
	drawHalfSphereWithNormalSmooth(1);
	glPopAttrib();
	glPopMatrix();
	//small thing
	glPushMatrix();
	glTranslatef(0.2, 2.05, 1.335);
	glRotatef(-10, 0, 0, -1);
	glRotatef(-30, -1, 0, 0);
	glScalef(0.3, 0.4, 0.2);
	drawSphereWithNormalSmooth(0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, 2.05, 1.335);
	glRotatef(10, 0, 0, 1);
	glRotatef(30, 1, 0, 0);
	glScalef(0.3, 0.4, 0.2);
	drawSphereWithNormalSmooth(0.4);
	glPopMatrix();
	glPopMatrix();


	//bottom half of head
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
	glTranslatef(0, 2, -.11);
	glRotatef(90, 0, 1, 0);
	glRotatef(-10, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(1.29, 1.3, 1);
	drawHalfSphereWithNormalSmooth(1);
	glPopAttrib();
	glPopMatrix();

	// red mouth
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	currentMaterials = &redPlasticMaterials;
	materials(currentMaterials);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
	glTranslatef(0, 2,0.39);
	//glRotatef(90, 1, 0, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(1, 1.4, 1);
	drawHalfSphereWithNormalSmooth(0.8);
	glPopAttrib();
	glPopMatrix();
	currentMaterials = &blueMaterials;
	materials(currentMaterials);

	//bottom jaw for red mouth
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
	glTranslatef(0, 1.9, 0.14);
	glRotatef(90, 0, 1, 0);
	glRotatef(18, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glScalef(1, 1.26, 1);
	drawHalfSphereWithNormalSmooth(1);
	glPopAttrib();
	glPopMatrix();




	for (float i = 0.00; i < 0.35; i += 0.01) {


		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
		glTranslatef(0, 2.05+i, 0.3-i);
		glRotatef(90, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glScalef(1.4, 1.3, .5);
		drawHalfSphereWithNormalSmooth(0.9);
		glPopAttrib();
		glPopMatrix();
	}
}
void rightEye() {
	//right eye shape
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0.6, 2.7, 1);
	glRotatef(90, 0, 0, 1);
	glRotatef(30, 0, 1, 0);
	glRotatef(30, 1, 0, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.4, 0.1, 0.3);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
	//small thing
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
	glTranslatef(0.5, 2.86, 0.979);
	glRotatef(-10, 0, 0, -1);
	glRotatef(30, -1, 0, 0);
	glScalef(0.3, 0.4, 0.2);
	drawSphereWithNormalSmooth(0.4);
	glPopAttrib();
	glPopMatrix();
	glPopMatrix();
}
void leftEye() {
	//left eye shape
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-0.6, 2.7, 1);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-30, 0, 1, 0);
	glRotatef(30, 1, 0, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.4, 0.1, 0.3);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
	//small thing
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
	glTranslatef(-0.5, 2.86, 0.985);
	glRotatef(10, 0, 0, 1);
	glRotatef(-30, 1, 0, 0);
	glScalef(0.3, 0.4, 0.2);
	drawSphereWithNormalSmooth(0.4);
	glPopAttrib();
	glPopMatrix();
	glPopMatrix();
}
void body() {
	//bod
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
	currentMaterials = &brassMaterials;
	materials(currentMaterials);
	glTranslatef(0, -0.3, -0.2);
	//glRotatef(90, 0, 0, 1);
	//glRotatef(90, 1, 0, 0);
	glScalef(1.4, 1.4, 1);
	drawSphereWithNormalSmooth(1.4);
	glPopAttrib();
	glPopMatrix();
	currentMaterials = &blueMaterials;
	materials(currentMaterials);
}
void leftArm() {
	//hand left
	//glPushMatrix();
	//glTranslatef(-2, 0, 2);
	//glScalef(0.4, 1, 0.4);
	//drawCylinder(1, 1, 1, 1, 1);
	//glPopMatrix();
	for (float i = 0; i < 0.5; i += 0.05) {

		glPushMatrix();
		glTranslatef(-1.5 - i, 0.5, 0 + i);
		glScalef(1, 1, 1);
		drawSphereWithNormalSmooth(0.5);
		glPopMatrix();
	}
	glPushMatrix();
	glRotatef(25, 0, 1, 0);
	for (float i = 0.5; i < 1; i += 0.1) {
		glPushMatrix();
		glTranslatef(-1.6 - i, 0.5, -1+ i * 1.3);
		glScalef(1, 1, 1);
		drawSphereWithNormalSmooth(0.5);
		glPopMatrix();
	}
	glPopMatrix();

}
void rightArm() {
	//hand right
	//glPushMatrix();
	//glTranslatef(-2, 0, 2);
	//glScalef(0.4, 1, 0.4);
	//drawCylinder(1, 1, 1, 1, 1);
	//glPopMatrix();
	for (float i = 0; i < 0.5; i += 0.05) {

		glPushMatrix();
		glTranslatef(1.5 +i, 0.5, 0 + i);
		glScalef(1, 1, 1);
		drawSphereWithNormalSmooth(0.5);
		glPopMatrix();
	}
	glPushMatrix();
	glRotatef(-25, 0, 1, 0);
	for (float i = 0.5; i < 1; i += 0.1) {
		glPushMatrix();
		glTranslatef(1.6 +i, 0.5, -1 + i * 1.3);
		glScalef(1, 1, 1);
		drawSphereWithNormalSmooth(0.5);
		glPopMatrix();
	}
	glPopMatrix();

}
void leftLeg() {
	//leg left
	glPushMatrix();
	//glTranslatef(-2, 0, 2);
	//glScalef(0.4, 1, 0.4);
	//drawCylinder(1, 1, 1, 1, 1);
	//glPopMatrix();
	glTranslatef(0, -.8, 0);
	glRotatef(90, 1, 0, 1);
	for (float i = 0; i < 0.5; i += 0.1) {

		glPushMatrix();
		glTranslatef(-1.5 - i, 0.5, 0 + i);
		glScalef(1, 1, 1);
		drawSphereWithNormalSmooth(0.5);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(0.3, 0, 0.3);
	glRotatef(15, -1, 1, 0);
	for (float i = 0.5; i < 1; i += 0.1) {
		glPushMatrix();
		glTranslatef(-1.6 - i, 0.5, -1 + i * 1.3);
		glScalef(1, 1, 1);
		drawSphereWithNormalSmooth(0.5);
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();

}
void rightLeg() {
	//leg left
	glPushMatrix();
	//glTranslatef(-2, 0, 2);
	//glScalef(0.4, 1, 0.4);
	//drawCylinder(1, 1, 1, 1, 1);
	//glPopMatrix();
	glTranslatef(2, -.8, 0);
	glRotatef(legtheta, 1, 0, 1);
	for (float i = 0; i < 0.5; i += 0.1) {

		glPushMatrix();
		glTranslatef(-1.5 - i, 0.5, 0 + i);
		glScalef(1, 1, 1);
		drawSphereWithNormalSmooth(0.5);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(0.3, 0, 0.3);
	glRotatef(15, -1, 1, 0);
	for (float i =0.5; i < 1; i += 0.1) {
		glPushMatrix();
		glTranslatef(-1.6 - i, 0.5, -1 + i * 1.3);
		glScalef(1, 1, 1);
		drawSphereWithNormalSmooth(0.5);
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();

}
void leftFoot() {

}
void mainBody() {

	//main body
	glPushMatrix();
	glTranslatef(0, 0, -2.0);
	//glRotatef(0, 0, 0, -1);
	glScalef(1.1, 2, 0.95);
	drawCylinder(1, 1, 1, 1, 1);
	glPopMatrix();
}
void lowerBody() {
	//lower body
	glPushMatrix();
	glTranslatef(0, .25, -2.0);
	glScalef(1.1, 1.1, 1.0);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
}
void leftLegCheek() {
	//left leg cheek
	glPushMatrix();
	glTranslatef(-.45, -0.1, -2.0);
	glRotatef(2, 1, 0, 0);
	glScalef(0.8, 0.8, 1.0);
	drawSphereWithNormalSmooth(1);

	glPushMatrix();
	glTranslatef(0, -1.25, 0.0);
	glScalef(0.3, 0.5, 0.3);
	drawCylinder(1, 1, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.35, 0.2, 0.5);
	glTranslatef(0, -6, 0.75);
	glRotatef(90, 1, 0, 0);
	drawCylinder(1, 1, 0.95, 0.95, 1);
	drawSphereWithNormalSmooth(1);

	glTranslatef(0, 1.1, 0.0);
	glScalef(1, 0.3, 1);
	drawSphereWithNormalSmooth(0.95);
	glPopMatrix();

	glPopMatrix();
}
void rightLegCheek() {
	//right Leg cheek
	glPushMatrix();
	glTranslatef(.45, -0.1, -2.0);
	glRotatef(2, 1, 0, 0);
	glScalef(0.8, 0.8, 1.0);
	drawSphereWithNormalSmooth(1);

	glPushMatrix();
	glTranslatef(0, -1.25, 0.0);
	glScalef(0.3, 0.5, 0.3);
	drawCylinder(1, 1, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.35, 0.2, 0.5);
	glTranslatef(0, -6, 0.75);
	glRotatef(90, 1, 0, 0);
	drawCylinder(1, 1, 0.95, 0.95, 1);
	drawSphereWithNormalSmooth(1);

	glTranslatef(0, 1.1, 0.0);
	glScalef(1, 0.3, 1);
	drawSphereWithNormalSmooth(0.95);
	glPopMatrix();

	glPopMatrix();
}
void head() {

	//head
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);  // add a fixed color
	glTranslatef(0, 2, -2);
	glScalef(1.2, 1.1, 1.1);
	drawSphereWithNormalSmooth(1);
	glPopAttrib();
	glPopMatrix();
}
void noseArea() {
	//nose
	glPushMatrix();
	glTranslatef(0, 2, -1.2);
	glScalef(0.7, 0.5, 0.4);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
}
void rightHand() {
	//hand right
	glPushMatrix();
	glTranslatef(1.5, 2, -2.0);
	//glRotatef(20, 1, 0, 0);
	glRotatef(150, 0, 0, 1);
	glScalef(0.2, 1.0, 0.25);
	drawCylinder(1, 1, 1, 1, 1);

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glScalef(1, 0.5, 1);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.1, 0.3, 1.1);
	glTranslatef(0, -.4, 0);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
	glPopMatrix();
}
void leftHand() {

	//hand left
	glPushMatrix();
	glTranslatef(-2, 1.2, -2.0);
	//glRotatef(2, -1, 0, 0);
	glRotatef(-90, 0, 0, 1);
	glScalef(0.2, 1.0, 0.25);
	drawCylinder(1, 1, 1, 1, 1);

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glScalef(1, 0.5, 1);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.1, 0.3, 1.1);
	glTranslatef(0, -.4, 0);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
	glPopMatrix();
}
void leftEar() {



	//left ear
	glPushMatrix();
	glTranslatef(-0.6, 2.8, -2.0);
	glRotatef(2, 1, 1, 1);
	glScalef(0.25, 1, 0.1);
	drawCylinder(1, 1, 1, 1, 1);

	glPushMatrix();
	glTranslatef(0, 1, 0);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
	glPopMatrix();
}
void rightEar() {
	//right ear
	glPushMatrix();
	glTranslatef(0.6, 2.8, -2.0);
	glRotatef(2, 1, 1, 1);
	glScalef(0.25, 1, 0.1);
	drawCylinder(1, 1, 1, 1, 1);

	glPushMatrix();
	glTranslatef(0, 1, 0);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
	glPopMatrix();
}
void leftEyes() {


	//left eyes
	glPushMatrix();
	glTranslatef(-0.4, 2.5, -1.1);
	glRotatef(-30, 0, 0, -1);
	glRotatef(-30, 1, 0, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.3, 0.1, 0.3);
	drawSphereWithNormalSmooth(1);

	glPushMatrix();
	glRotatef(-40, -1, 0, 1);
	glTranslatef(0, -0.8, 0);
	glScalef(0.3, 0.4, 0.2);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
	glPopMatrix();
}
void rightEyes() {
	//right eyes
	glPushMatrix();
	glTranslatef(0.4, 2.5, -1.1);
	glRotatef(-30, 0, 0, 1);
	glRotatef(-30, 1, 0, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.3, 0.1, 0.3);
	drawSphereWithNormalSmooth(1);

	glPushMatrix();
	glRotatef(-40, -1, 0, 1);
	glTranslatef(-0.3, -0.8, 0);
	glScalef(0.3, 0.4, 0.2);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
	glPopMatrix();
}
void nose() {

	//nose
	glPushMatrix();
	glTranslatef(0, 2.2, -0.8);
	glRotatef(90, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	drawPyramid();
	glPopMatrix();

}
void tail() {
	//tails
	glPushMatrix();
	glTranslatef(0, -0.4, -2);
	glRotatef(50, 1, 0, 0);
	glScalef(0.1, 0.5, 1.5);

	glTranslatef(0, 0.5, -0.5);
	glScalef(1.2, 1.2, 1.2);
	glRotatef(-20, 1, 0, 0);
	cube(.25);

	glTranslatef(0, -0.3, -0.3);
	glScalef(1.2, 1.2, 1.5);
	cube(.25);


	glTranslatef(0, -0.3, -0.3);
	glScalef(1.2, 1.2, 1.5);
	cube(.25);

	glTranslatef(0, -0.3, -0.3);
	glScalef(1.2, 1.2, 1.5);
	cube(.25);
	glPopMatrix();
}
void leftCheek() {

	//left cheek
	glPushMatrix();
	glTranslatef(-0.7, 2.0, -1.1);
	glRotatef(-90, 0, 0, 1);
	glRotatef(50, 1, 0, 0);
	glRotatef(-100, 1, 0, 0);
	glScalef(0.2, 0.1, 0.2);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
}
void rightCheek() {


	//right cheek
	glPushMatrix();
	glTranslatef(0.7, 2.0, -1.1);
	glRotatef(-90, 0, 0, -1);
	glRotatef(50, 1, 0, 0);
	glRotatef(-100, 1, 0, 0);
	glScalef(0.2, 0.1, 0.2);
	drawSphereWithNormalSmooth(1);
	glPopMatrix();
}
