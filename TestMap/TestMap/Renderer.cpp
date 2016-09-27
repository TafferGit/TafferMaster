#include "Renderer.h"


int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Test Map");
	glutPositionWindow(1, 1);
	glClearColor(1.0, 0.0, 0.0, 1.0);

	//glMatrixMode(GL_PROJECTION);
	//glOrtho(0.0, 640, 0.0, 480, -100.0, 100.0);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glutDisplayFunc(PrepareForDisplay);

	gluOrtho2D(0.0, 1.0, 1.0, 0.0);

	glutMainLoop();

}

void Renderer::DisplayFirstFrame(int **tiles)
{
	glClear(GL_COLOR_BUFFER_BIT);
	std::cout << "Entering cycle\n";
	//Iterating through all the cells, column by column, row by row.
	for (int i = 0; i < 8; i++ ) {
		for (int j = 0; j < 8; j++) {
			std::cout << "j = " << j << "i = " << i << "\n";
			tileId = tiles[j][i];
			QuadVerticles quadVert = CalculateVertexes(j, i);
			DrawTile(tileId, quadVert);
		}
	}
	glEnd();
	/*std::cout << "Clearing color buffer bit";
	glClear(GL_COLOR_BUFFER_BIT);
	
	glRectf(0.0, 0.0, 0.5, 0.5);*/
	glutSwapBuffers();
}

//This function simply draws the tile
void Renderer::DrawTile(int tileId, QuadVerticles qv)
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2d(qv.upperLeftX, qv.upperLeftY);
	glVertex2d(qv.upperRightX, qv.upperRightY);
	glVertex2d(qv.lowerRightX, qv.lowerRightY);
	glVertex2d(qv.lowerLeftX, qv.lowerLeftY);
	glEnd();
}

//This function calculates the quad verticles 
QuadVerticles Renderer::CalculateVertexes(int x, int y)
{
	QuadVerticles qv;
	double sizeMaxX = 1.0;
	double sizeMaxY = 1.0;
	double stepX = sizeMaxX / 8; //tile size on the display
	double stepY = sizeMaxY / 8; //tile size on the display

	
	qv.upperLeftX = stepX * x + 0.005; //upper left x verticle
	qv.upperLeftY = stepY * y + 0.005; //upper left y verticle
	qv.upperRightX = stepX * (x + 1) - 0.005; //upper right x verticle
	qv.upperRightY = stepY * y + 0.005; //upper right y verticle
	qv.lowerRightX = stepX * (x + 1) - 0.005; //lower right x verticle
	qv.lowerRightY = stepY * (y + 1) - 0.005; //lower right y verticle
	qv.lowerLeftX = stepX * x + 0.005; // lower left x verticle
	qv.lowerLeftY = stepY * (y + 1) - 0.005; //lower y verticle

	return qv;
}

Renderer::Renderer(Map map)
{
	this->map = map;
	DisplayFirstFrame(map.getIconIds());
}

void PrepareForDisplay(void)
{
	Map map = Map();
	Renderer renderer = Renderer(map);
}
