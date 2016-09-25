#include "Includes.h"
int window_unique_id;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	GLint slices = 5;
	GLint stacks = 3;
	glutSolidCone(3.0, 5.0, slices, stacks);
	glutSwapBuffers();
}

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(1, 1);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA);
	window_unique_id = glutCreateWindow("GLUT");
	glutDisplayFunc(display);
	glutMainLoop();
}