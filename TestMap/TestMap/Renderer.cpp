#include "Renderer.h"

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Test Map");
	glutPositionWindow(1, 1);
	glClearColor(1.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 640.0, 480.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(PrepareForDisplay);

	glutMainLoop();

}

void Renderer::DisplayFirstFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	std::cout << "Entering cycle\n";
	//Iterating through all the cells, column by column, row by row.
	for (int i = 0; i < this->map.getSizeX(); i++ ) {
		for (int j = 0; j < this->map.getSizeY(); j++) {
			std::cout << "j = " << j << "i = " << i << "\n";
			tileId = tiles[j][i];
			QuadVerticles quadVert = CalculateVertexes(j, i);
			DrawTile(tileId, quadVert);
		}
	}
	glEnd();
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
QuadVerticles Renderer::CalculateVertexes(int i, int j)
{
	QuadVerticles qv;
	double sizeMaxX = 640.0;
	double sizeMaxY = 480.0;
	double stepX = sizeMaxX / this->map.getSizeX(); //tile size on the display
	double stepY = sizeMaxY / this->map.getSizeY(); //tile size on the display

	double borderX = 3.2; 
	double borderY = 2.4; 
	qv.upperLeftX = stepX * i + borderX; //upper left x verticle
	qv.upperLeftY = stepY * j + borderY; //upper left y verticle
	qv.upperRightX = stepX * (i + 1) - borderX; //upper right x verticle
	qv.upperRightY = stepY * j + borderY; //upper right y verticle
	qv.lowerRightX = stepX * (i + 1) - borderX; //lower right x verticle
	qv.lowerRightY = stepY * (j + 1) - borderY; //lower right y verticle
	qv.lowerLeftX = stepX * i + borderX; // lower left x verticle
	qv.lowerLeftY = stepY * (j + 1) - borderY; //lower y verticle

	return qv;
}

Renderer::Renderer(Map map)
{
	this->map = map;
	this->DisplayFirstFrame();
}

void PrepareForDisplay(void)
{
	int tiles[3][5] = {
		{ 1, 0, 2, 1, 0 },
		{ 2, 1, 1, 0, 1 },
		{ 0, 2, 1, 1, 2 }
	};
	Map map = Map(3, 5, tiles);
	Renderer renderer = Renderer(map);
}
