#include "Renderer.h"

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
}

void Renderer::DisplayFirstFrame(int **tiles)
{
	//Iterating through all the cells, column by column, row by row.
	for (int i = 0; i++; i < 64) {
		for (int j = 0; j++; j < 64) {
			tileId = tiles[j][i];
			QuadVerticles quadVert = CalculateVertexes(j, i);
			DrawTile(tileId, quadVert);
		}
	}
}

//This function simply draws the tile
void Renderer::DrawTile(int tileId, QuadVerticles qv)
{
	glBegin(GL_QUADS);
	glColor3d(0.0, 1.0, 0.0);
	glVertex2d(qv.upperLeftX, qv.upperLeftY);
	glVertex2d(qv.upperRightX, qv.upperRightY);
	glVertex2d(qv.lowerRightX, qv.lowerRightY);
	glVertex2d(qv.lowerLeftX, qv.lowerLeftY);
	glEnd;
}

//This function calculates the quad verticles 
QuadVerticles Renderer::CalculateVertexes(int x, int y)
{
	QuadVerticles qv;
	double sizeMaxX = 1.0;
	double sizeMaxY = 1.0;
	double stepX = sizeMaxX / x; //tile size on the display
	double stepY = sizeMaxY / y; //tile size on the display

	
	qv.upperLeftX = stepX * x; //upper left x verticle
	qv.upperLeftY = stepY * y; //upper left y verticle
	qv.upperRightX = stepX * (x + 1); //upper right x verticle
	qv.upperRightY = stepY * y; //upper right y verticle
	qv.lowerRightX = stepX * (x + 1); //lower right x verticle
	qv.lowerRightY = stepY * (y + 1); //lower right y verticle
	qv.lowerLeftX = stepX * x; // lower left x verticle
	qv.lowerLeftY = stepY * (y + 1); //lower y verticle

	return qv;
}

Renderer::Renderer()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Test Map");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutDisplayFunc(this->DisplayFirstFrame());
	glutMainLoop();
}
