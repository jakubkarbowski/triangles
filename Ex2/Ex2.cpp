// Ex2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <GL/gl.h>
#include <GL/glut.h>

int t = 0;
int dir = 1;
float translateVariable = 0;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void triangle(double ramie, double x, double colorR, double colorG, double colorB )
{	
	/*for (int i = 0; i < 3; i++) {*/
		//Niebieski
		
		glTranslatef(x, 0.0, 0.0);
		glTranslatef(ramie/3, ramie/3, 0.0);
		glRotatef((0 - t) % 360, 0, 0, 1);
		glTranslatef(-(ramie / 3), -(ramie / 3), 0.0);
		glBegin(GL_TRIANGLES);
		glColor3f(colorR, colorG, colorB);
		glVertex2f(ramie, 0);
		glColor3f(colorR, colorG, colorB);
		glVertex2f(0, ramie);
		glColor3f(colorR, colorG, colorB);
		glVertex2f(0, 0);
		glEnd();
		//}

	
}

void display(void)
{
	const float tablicaKolorow[4][3] = { {0, 0, 1}, {0, 1, 0}, {1, 0, 0}, {1, 0.5, 0.0} };
	int lKolo = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef((0+t)%360, 0, 0, 1);
	for (int k = 0; k < 4; k++) {
		glPushMatrix();
		double ramie = 15;
		int iloscTrojkatow = 4;
		int iloscWRzedzie = iloscTrojkatow;
		for (int i = 0; i < iloscTrojkatow; i++) {
			glPushMatrix();
			for (int j = 0; j < iloscWRzedzie; j++) {
				glPushMatrix();
				glTranslatef(translateVariable, translateVariable, 0.0);
				triangle(ramie, j*ramie, tablicaKolorow[(lKolo + i + j) % 4][0], tablicaKolorow[(lKolo + i + j) % 4][1], tablicaKolorow[(lKolo + i + j) % 4][2]);
				glPopMatrix();
			}
			glPopMatrix();
			iloscWRzedzie--;
			glTranslatef(0, ramie, 0);
		}
		glPopMatrix();
		glRotatef(90, 0, 0, 1);
		lKolo++;
	}
	glPopMatrix();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(-150.0, 150.0, -150.0, 150.0*(GLfloat)h / (GLfloat)w);
	else
		gluOrtho2D(-150.0, 150.0*(GLfloat)w / (GLfloat)h, -150.0, 150.0);
	glMatrixMode(GL_MODELVIEW);
}
void timer(int) {
	if (translateVariable >= 10 || translateVariable<0) {
		dir = -dir;
	}
	translateVariable += dir*0.1;
	t += 1;
	glutTimerFunc(20, timer, 1);
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(20, timer, 1);
	glutMainLoop();
	return 0;
}

