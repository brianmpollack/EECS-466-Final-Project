#pragma once
#include "common.h"
#include "Helicopter.h"
//#include "ferris_wheel.h"

/* ---GLOBALS--- */
int window_width, window_height;    // Window dimensions
float CameraRadius = 10;
float CameraTheta = PI / 2;
float CameraPhi = PI / 2;
int MouseX = 0;
int MouseY = 0;
bool MouseLeft = false;
bool MouseRight = false;
Helicopter helicopter = Helicopter();
//FerrisWheel ferris_wheel = FerrisWheel(1.0); //TODO: Change radius
/* ---GLOBALS--- */

void ReshapeFunc(int x, int y)
{
	glViewport(0, 0, x, y);
	window_width = x;
	window_height = y;
}

void MouseFunc(int button, int state, int x, int y)
{
	MouseX = x;
	MouseY = y;

	if (button == GLUT_LEFT_BUTTON)
		MouseLeft = !(bool)state;
	if (button == GLUT_RIGHT_BUTTON)
		MouseRight = !(bool)state;
}


void MotionFunc(int x, int y)
{
	if (MouseLeft)
	{
		CameraTheta += 0.01*PI*(MouseX - x);
		CameraPhi += 0.01*PI*(MouseY - y);
		//CameraPhi = min(CameraPhi, 2 * PI / 3);
		//CameraPhi = max(CameraPhi, PI / 3);
	}
	if (MouseRight)
	{
		CameraRadius += 0.2*(MouseY - y);
		if (CameraRadius <= 0)
			CameraRadius = 0.2;
	}

	MouseX = x;
	MouseY = y;

	glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		helicopter.increaseRatio();
		break;
	case '-':
		helicopter.decreaseRatio();
		break;
	case 'Q':
	case 'q':
		exit(1);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//load projection and viewing transforms
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(60, (GLdouble)window_width / window_height, 0.01, 10000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Set camera position, orientation, target
	gluLookAt(CameraRadius*cos(CameraTheta)*sin(CameraPhi),
		CameraRadius*sin(CameraTheta)*sin(CameraPhi),
		CameraRadius*cos(CameraPhi),
		0, 0, 0,
		0, 0, 1);
	//glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_BACK, GL_FILL);

	//ferris_wheel.draw();
	helicopter.draw();

	glutSwapBuffers();
}

void Animations()
{
	helicopter.doAnimation();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("POLLACK EECS-466 FINAL PROJECT");


	glutDisplayFunc(display);
	glutReshapeFunc(ReshapeFunc);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MotionFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutIdleFunc(Animations);

	glutMainLoop();

    return 0;
}

