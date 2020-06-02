#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1000.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 30.0f, 70.0f, 70.0f, 0.0f };
//i * 10.0f +400.0, 0.0f, (j * 10.0f)+OffsetCube
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/// Menu Variables
int _MenuScreen = 1, _InstructionScreen = 0, _MainScreen = 0, _AboutScreen = 0;
int menuScreen, instructionScreen, aboutScreen, subWindow1, subWindow2, subWindow3, mainWindow;
int WindowPreview = 1, MenuPreview = 0, InstructionPreview, WindowToggle = 1;

/// Camera Variables
float lx = 0.0f, lz = -1.0f, ly = 0.0f, d = 1.75f;
float x = 30.0f, z = 70.0f, y = 1.75f, yt = 1.75f;

float angle = 0.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

/// Window Variables
int h, w;

/// TextVariables
char s[50];

/// SplitBorder Size
int border = 3;

void pressKey(int key, int xx, int yy);
void processNormalKeys(unsigned char key, int x, int y);
void releaseKey(int key, int x, int y);
void MainSplit();
void MainFull();
void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);

void setProjection(int w1, int h1)
{
	float ratio;
	ratio = 1.0f * w1 / h1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w1, h1);
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

/// ReOrganize Windows
void changeSize(int w1, int h1)
{
	if (h1 == 0)
		h1 = 1;
	w = w1;
	h = h1;

	if (_MenuScreen == 1)
	{
		glutSetWindow(menuScreen);
		glutPositionWindow(border, border);
		glutReshapeWindow(w, h);
		setProjection(w, h);
	}
	else if (_InstructionScreen == 1)
	{
		glutSetWindow(instructionScreen);
		glutPositionWindow(border, border);
		glutReshapeWindow(w, h);
		setProjection(w, h);
	}
	else if (_AboutScreen == 1)
	{
		glutSetWindow(aboutScreen);
		glutPositionWindow(border, border);
		glutReshapeWindow(w, h);
		setProjection(w, h);
	}
	else
	{
		if (WindowPreview)
		{
			glutSetWindow(subWindow1);
			glutPositionWindow(border, border);
			glutReshapeWindow(w, h);
			setProjection(w, h);
		}
		else
		{
			glutSetWindow(subWindow1);
			glutPositionWindow(border, border);
			glutReshapeWindow(w - 2 * border, h / 2 - border * 3 / 2);
			setProjection(w - 2 * border, h / 2 - border * 3 / 2);

			glutSetWindow(subWindow2);
			glutPositionWindow(border, (h + border) / 2);
			glutReshapeWindow(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
			setProjection(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);

			glutSetWindow(subWindow3);
			glutPositionWindow((w + border) / 2, (h + border) / 2);
			glutReshapeWindow(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
			setProjection(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
		}
	}
}

void drawPyramid1(float TriangleSize, float TrianglePoint, float Upward)
{

    glTranslatef(0,Upward,0);
    glColor3f(1.0f, 0.9f, 0.3f);
    glBegin(GL_TRIANGLES);
		  glVertex3f( 0.0f, TrianglePoint, 0.0f);
		  glVertex3f(-TriangleSize, -TriangleSize, TriangleSize);
		  glVertex3f(TriangleSize, -TriangleSize, TriangleSize);

		  glVertex3f(0.0f, TrianglePoint, 0.0f);
		  glVertex3f(TriangleSize, -TriangleSize, TriangleSize);
		  glVertex3f(TriangleSize, -TriangleSize, -TriangleSize);

		  glVertex3f(0.0f, TrianglePoint, 0.0f);
		  glVertex3f(TriangleSize, -TriangleSize, -TriangleSize);
		  glVertex3f(-TriangleSize, -TriangleSize, -TriangleSize);

		  glVertex3f( 0.0f, TrianglePoint, 0.0f);
		  glVertex3f(-TriangleSize,-TriangleSize,-TriangleSize);
		  glVertex3f(-TriangleSize,-TriangleSize, TriangleSize);
	glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);

    TrianglePoint += 0.01;
    TriangleSize +=0.01;
     /// Side1
	glBegin(GL_LINE_STRIP);
          glVertex3f( 0.0f, TrianglePoint, 0.0f);
          glVertex3f(-TriangleSize, -TriangleSize, TriangleSize);
    glEnd();

	glBegin(GL_LINE_STRIP);
          glVertex3f( 0.0f, TrianglePoint, 0.0f);
          glVertex3f(TriangleSize, -TriangleSize, TriangleSize);
    glEnd();

    glBegin(GL_LINE_STRIP);
          glVertex3f(-TriangleSize, -TriangleSize, TriangleSize);
          glVertex3f(TriangleSize, -TriangleSize, TriangleSize);
    glEnd();

    /// Side2
    glBegin(GL_LINE_STRIP);
          glVertex3f( 0.0f, TrianglePoint, 0.0f);
          glVertex3f(TriangleSize, -TriangleSize, TriangleSize);
    glEnd();
    glBegin(GL_LINE_STRIP);
          glVertex3f( 0.0f, TrianglePoint, 0.0f);
          glVertex3f(TriangleSize, -TriangleSize, -TriangleSize);
    glEnd();
    glBegin(GL_LINE_STRIP);
          glVertex3f(TriangleSize, -TriangleSize, TriangleSize);
          glVertex3f(TriangleSize, -TriangleSize, -TriangleSize);
    glEnd();

    ///Side3
    glBegin(GL_LINE_STRIP);
          glVertex3f( 0.0f, TrianglePoint, 0.0f);
          glVertex3f(TriangleSize, -TriangleSize, -TriangleSize);
    glEnd();
    glBegin(GL_LINE_STRIP);
          glVertex3f( 0.0f, TrianglePoint, 0.0f);
          glVertex3f(-TriangleSize, -TriangleSize, -TriangleSize);
    glEnd();
    glBegin(GL_LINE_STRIP);
          glVertex3f(TriangleSize, -TriangleSize, -TriangleSize);
          glVertex3f(-TriangleSize, -TriangleSize, -TriangleSize);
    glEnd();

    ///Side4

    glBegin(GL_LINE_STRIP);
          glVertex3f( 0.0f, TrianglePoint, 0.0f);
          glVertex3f(-TriangleSize,-TriangleSize,-TriangleSize);
    glEnd();
    glBegin(GL_LINE_STRIP);
          glVertex3f( 0.0f, TrianglePoint, 0.0f);
          glVertex3f(-TriangleSize,-TriangleSize,TriangleSize);
    glEnd();
    glBegin(GL_LINE_STRIP);
          glVertex3f(-TriangleSize,-TriangleSize,-TriangleSize);
          glVertex3f(-TriangleSize, -TriangleSize, TriangleSize);
    glEnd();

}

void drawCube()
{
	glTranslatef(0.0f, 2.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireCube(3.0f);
	glColor3f(1.0f, 0.9f, 0.3f);
	glutSolidCube(2.999f);
}

void renderBitmapString(float x, float y, float z, void* font, char* string)
{
	char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void restorePerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove)
{
	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void RenderWorld()
{
    float WorldSize = 1000.0;

    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    ///SkyColor
	glClearColor(0.2, 0.7, 0.9, 0.5);
	/// World Surface
	//glColor3f(0.9f, 0.7f, 0.3f);
	glColor3f(1.0f, 0.8f, 0.3f);
	glBegin(GL_QUADS);
        glVertex3f(-WorldSize, 0.0f, -WorldSize);
        glVertex3f(-WorldSize, 0.0f, WorldSize);
        glVertex3f(WorldSize, 0.0f, WorldSize);
        glVertex3f(WorldSize, 0.0f, -WorldSize);
	glEnd();

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -50.0f);
		drawPyramid1(20,10,20);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(60.0f, 0.0f, -90.0f);
		drawPyramid1(30,14,30);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(120.0f, 0.0f, -130.0f);
		drawPyramid1(20,10,20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		drawPyramid1(10,4,10);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(30.0f, 0.0f, 0.0f);
		drawPyramid1(10,4,10);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(60.0f, 0.0f, 0.0f);
		drawPyramid1(10,4,10);
	glPopMatrix();

    float OffsetCube = -400.0;
	for (int i = -10; i < 10; i++)
		for (int j = -10; j < 10; j++)
		{
			glPushMatrix();
			glTranslatef(i * 10.0f +400.0, 0.0f, (j * 10.0f)+OffsetCube);
			drawCube();
			glPopMatrix();
		}
}

// Display func for sub window 1
void renderScenesw1()
{


	glutSetWindow(subWindow1);
    glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x, d, z, x + lx, yt, z + lz, 0.0f, 1.0f, 0.0f);
	RenderWorld();
	sprintf(s, "X:%4.2f,Y:%4.2f,Z:%4.2f", x, d, z);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(100, 100, 0, GLUT_BITMAP_HELVETICA_12, s);
	glPopMatrix();
	restorePerspectiveProjection();
	glutSwapBuffers();
}
// Display func for sub window 2
void renderScenesw2()
{
	glutSetWindow(subWindow2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x, d + 15, z, x, yt - 1, z, lx, 0, lz);
	// Draw red cone at the location of the main camera
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(x, d, z);
	glRotatef(180 - (angle + deltaAngle) * 180.0 / 3.14, 0.0, 1.0, 0.0);
	glutSolidCone(0.2, 0.8f, 4, 4);
	glPopMatrix();
	RenderWorld();
	glutSwapBuffers();
}

void renderScenesw3()
{

	glutSetWindow(subWindow3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x - lz * 10, d, z + lx * 10, x, yt, z, 0.0f, 1.0f, 0.0f);
	// Draw red cone at the location of the main camera
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(x, d, z);
	glRotatef(180 - (angle + deltaAngle) * 180.0 / 3.14, 0.0, 1.0, 0.0);
	glutSolidCone(0.2, 0.8f, 4, 4);
	glPopMatrix();
	RenderWorld();
	glutSwapBuffers();
}

void RenderMenu()
{
	float CenterHeight = (h / 2) - 220, CenterWidth = (w / 2);
	glutSetWindow(menuScreen);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 15, 130, 0, 25.0f, 70.0f, 0.0f, 1.0f, 0.0f);
	RenderWorld();
	sprintf(s, "______________________________");
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 150.0, CenterHeight, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();
	sprintf(s, "MAIN MENU");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 50.0, CenterHeight + 40.0, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();
	sprintf(s, "______________________________");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 150.0, CenterHeight + 60, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();
	sprintf(s, "1. START SIMULATION");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 150.0, CenterHeight + 150, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();
	sprintf(s, "2. INSTRUCTIONS");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 150.0, CenterHeight + 180, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();
	sprintf(s, "3. ABOUT");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 150.0, CenterHeight + 210, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();
	sprintf(s, "4. EXIT");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 150.0, CenterHeight + 240, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	restorePerspectiveProjection();
	glutSwapBuffers();
}

void RenderInstructions()
{
	float CenterHeight = (h / 2) - 300, CenterWidth = (w / 2);
	glutSetWindow(instructionScreen);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 15, 120, 0, 25.0f, 85.0f, 0.0f, 1.0f, 0.0f);
	RenderWorld();
	sprintf(s, "______________________________________");
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "INSTRUCTIONS");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 60.0, CenterHeight + 40.0, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "______________________________________");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 60, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "MOVE FORWARD                     [ARROW UP]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 150, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "MOVE BACKWARD           [ARROW DOWN]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 180, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "MOVE UP                                                  [W]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 210, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "MOVE DOWN                                            [S]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 240, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "TURN RIGHT                                              [D]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 270, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "TURN LEFT                                                 [A]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 300, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "LOOK UP                                    [SHIFT + W]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 330, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "LOOK DOWN                              [SHIFT + S]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 360, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "---------------------------------");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 410, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "SPLIT VIEW                                               [T]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 430, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "RESET POSITION                                     [R]");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 460, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "---------------------------------");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 180.0, CenterHeight + 490, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "PRESS [ESC] TO GO TO MAIN MENU");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.184314f, 0.309804f, 0.309804f);
	renderBitmapString(CenterWidth - 160.0, CenterHeight + 520, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	restorePerspectiveProjection();
	glutSwapBuffers();
}

void RenderAbout()
{
	float CenterHeight = (h / 2) - 220, CenterWidth = (w / 2);
	glutSetWindow(aboutScreen);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 15, 130, 0, 25.0f, 75.0f, 0.0f, 1.0f, 0.0f);
	RenderWorld();

	sprintf(s, "______________________________");
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 150.0, CenterHeight, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "ABOUT");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 30.0, CenterHeight + 40.0, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "______________________________");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 150.0, CenterHeight + 60, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "PYRAMIDS OF GIZA SIMULATION");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 150.0, CenterHeight + 120, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();
	sprintf(s, "V 1.0");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth + 120.0, CenterHeight + 131, 0, GLUT_BITMAP_HELVETICA_12, s);
	glPopMatrix();

	sprintf(s, "PRASHANTH KUMAR   1BY17CS119");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 155.0, CenterHeight + 180, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "RICHA PAREKH             1BY17CS137");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	renderBitmapString(CenterWidth - 155.0, CenterHeight + 210, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	sprintf(s, "PRESS [ESC] TO GO TO MAIN MENU");
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.184314f, 0.309804f, 0.309804f);
	renderBitmapString(CenterWidth - 160.0, CenterHeight + 330, 0, GLUT_BITMAP_HELVETICA_18, s);
	glPopMatrix();

	restorePerspectiveProjection();
	glutSwapBuffers();

}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
}


void MainSplit()
{
	subWindow1 = glutCreateSubWindow(mainWindow, border, border, w - 2 * border, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw1);
	init();

	subWindow2 = glutCreateSubWindow(mainWindow, border, (h + border) / 2, w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw2);
	init();

	subWindow3 = glutCreateSubWindow(mainWindow, (w + border) / 3, (h + border) / 3, w / 3 - border * 6 / 2, h / 3 - border * 6 / 2);
	glutDisplayFunc(renderScenesw3);
	init();
	changeSize(w, h);
}

void MainFull()
{
	subWindow1 = glutCreateSubWindow(mainWindow, border, border, w, h);
	glutDisplayFunc(renderScenesw1);
	init();
	changeSize(w, h);
}

void DisplayMenu()
{

	menuScreen = glutCreateSubWindow(mainWindow, border, border, w - 2 * border, h / 2 - border * 3 / 2);
	glutDisplayFunc(RenderMenu);
	init();
	changeSize(w, h);

}

void DisplayInstruction()
{
	instructionScreen = glutCreateSubWindow(mainWindow, border, (h + border) / 2, w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	glutDisplayFunc(RenderInstructions);
	init();
	changeSize(w, h);
}


void DisplayAbout()
{
	aboutScreen = glutCreateSubWindow(mainWindow, border, (h + border) / 2, w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	glutDisplayFunc(RenderAbout);
	init();
	changeSize(w, h);
}


void renderSceneAll()
{
	// check for keyboard movement
	if (deltaMove)
		computePos(deltaMove);

	if (_MenuScreen == 1)
	{

		RenderMenu();
	}

	else if (_InstructionScreen == 1)
	{
		RenderInstructions();
	}
	else if (_AboutScreen == 1)
	{
		RenderAbout();
	}
	else
	{
		if (WindowPreview)
		{
			renderScenesw1();
		}
		else
		{
			renderScenesw1();
			renderScenesw2();
			renderScenesw3();
		}
	}
}


void pressKey(int key, int xx, int yy)
{
	if (_MainScreen == 1)
	{
		switch (key)
		{
		case GLUT_KEY_UP: deltaMove = 0.5f;
			break;

		case GLUT_KEY_DOWN: deltaMove = -0.5f;
			break;
		}
	}
}

void releaseKey(int key, int x, int y)
{
	if (_MainScreen == 1)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			deltaMove = 0;
			break;
		}
	}
}

void renderScene()
{
	glutFullScreen();


	glutSetWindow(mainWindow);
	glClear(GL_COLOR_BUFFER_BIT);


	glutSwapBuffers();
}

void mouseMove(int x, int y)
{

	if (_MainScreen == 1)
	{
		if (xOrigin >= 0)
		{
			// update deltaAngle
			deltaAngle = (x - xOrigin) * 0.001f;
			// update camera's direction
			lx = sin(angle + deltaAngle);
			lz = -cos(angle + deltaAngle);
		}
	}
}

void mouseButton(int button, int state, int x, int y)
{

	if (_MainScreen == 1)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			// when the button is released
			if (state == GLUT_UP)
			{
				angle += deltaAngle;
				deltaAngle = 0.0f;
				xOrigin = -1;
			}
			else
			{// state = GLUT_DOWN
				xOrigin = x;
			}
		}
	}
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (_MenuScreen == 1)
	{
		switch (key)
		{
		case '1':
			_MenuScreen = 0;
			_InstructionScreen = 0;
			_AboutScreen = 0;
			_MainScreen = 1;
			glutDestroyWindow(menuScreen);
			MainFull();

			break;
		case '2':
			_MenuScreen = 0;
			_InstructionScreen = 1;
			_AboutScreen = 0;
			_MainScreen = 0;
			glutDestroyWindow(menuScreen);
			DisplayInstruction();
			break;
		case '3':
			_MenuScreen = 0;
			_InstructionScreen = 0;
			_AboutScreen = 1;
			_MainScreen = 0;
			glutDestroyWindow(menuScreen);
			DisplayAbout();
			break;
		case '4':
			exit(0);
			break;
		}
	}

	else if (_InstructionScreen == 1)
	{
		switch (key)
		{
		case 27:
			_MenuScreen = 1;
			_InstructionScreen = 0;
			_AboutScreen = 0;
			_MainScreen = 0;
			glutDestroyWindow(instructionScreen);
			DisplayMenu();
			break;
		}
	}
	else if (_AboutScreen == 1)
	{
		switch (key)
		{
		case 27:
			_MenuScreen = 1;
			_InstructionScreen = 0;
			_AboutScreen = 0;
			_MainScreen = 0;
			glutDestroyWindow(aboutScreen);
			DisplayMenu();
			break;
		}
	}
	else
	{
		switch (key)
		{
		case 'a':
			angle -= 0.05f;
			lx = sin(angle);
			lz = -cos(angle);
			break;

		case 'd':
			angle += 0.05f;
			lx = sin(angle);
			lz = -cos(angle);
			break;

		case 'w':
			d += 0.5;
			yt += 0.5;
			break;

		case 's':
			if (yt > 1.75)
			{
				yt -= 0.5;
				d -= 0.5;
			}
			break;

		case 'S':
			yt -= 0.1;
			break;

		case 'W':
			yt += 0.1;
			break;

		case 'r':
			lx = 0.0f, lz = -1.0f, ly = 0.0f, d = 1.75f;
			x = -10.0f, z = 100.0f, y = 1.75f, yt = 1.75f;
			break;

		case 't':
			if (WindowToggle)
			{
				WindowPreview = 0;
				WindowToggle = 0;
				glutDestroyWindow(subWindow1);
				MainSplit();
				break;
			}
			else
			{
				WindowPreview = 1;
				WindowToggle = 1;
				glutDestroyWindow(subWindow1);
				glutDestroyWindow(subWindow3);
				glutDestroyWindow(subWindow2);
				MainFull();
				break;
			}
		case 27:
			_MenuScreen = 1;
			_InstructionScreen = 0;
			_AboutScreen = 0;
			_MainScreen = 0;
			if (WindowPreview)
			{
				glutDestroyWindow(subWindow1);
				DisplayMenu();
				break;
			}
			else
			{
				WindowPreview = 1;
				WindowToggle = 1;
				glutDestroyWindow(subWindow1);
				glutDestroyWindow(subWindow3);
				glutDestroyWindow(subWindow2);
				DisplayMenu();
				break;
			}
			break;
		}
	}
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	mainWindow = glutCreateWindow("Pyramid Simulation");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderSceneAll);

	menuScreen = glutCreateSubWindow(mainWindow, border, border, w - 2 * border, h / 2 - border * 3 / 2);
	glutDisplayFunc(RenderMenu);
	init();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	glutMainLoop();
	return 1;
}
