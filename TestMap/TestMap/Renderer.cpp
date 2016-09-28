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

void Renderer::DisplayFirstFrame(int **tiles)
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint tex_2d = SOIL_load_OGL_texture("test.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );

	if (tex_2d == 0) { printf("SOIL loading error: %s\n"), SOIL_last_result(); }
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);
	std::cout << "Entering cycle\n";
	//Iterating through all the cells, column by column, row by row.
	for (int i = 0; i < 8; i++ ) {
		for (int j = 0; j < 8; j++) {
			//std::cout << "j = " << j << "i = " << i << "\n";
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

	//glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_TRIANGLES);

	//First triange
	glTexCoord2f(qv.upperLeftX, qv.upperLeftY);
	glVertex2f(qv.upperLeftX, qv.upperLeftY); //v0 - top left

	glTexCoord2f(qv.upperRightX, qv.upperRightY);
	glVertex2f(qv.upperRightX, qv.upperRightY); //v1 - top right

	glTexCoord2f(qv.lowerLeftX, qv.lowerLeftY);
	glVertex2f(qv.lowerLeftX, qv.lowerLeftY); //v2 - bottom left

	//Second triangle
	glTexCoord2f(qv.upperRightX, qv.upperRightY);
	glVertex2f(qv.upperRightX, qv.upperRightY); //v1 - top right

	glTexCoord2f(qv.lowerLeftX, qv.lowerLeftY);
	glVertex2f(qv.lowerLeftX, qv.lowerLeftY); //v2 - bottom left

	glTexCoord2f(qv.lowerRightX, qv.lowerLeftY);
	glVertex2f(qv.lowerRightX, qv.lowerRightY); //v3 - bottom right

	glEnd();
	
	/*glBegin(GL_QUADS);
	glVertex2d(qv.upperLeftX, qv.upperLeftY);
	glVertex2d(qv.upperRightX, qv.upperRightY);
	glVertex2d(qv.lowerRightX, qv.lowerRightY);
	glVertex2d(qv.lowerLeftX, qv.lowerLeftY);
	glEnd();*/
}

//This function calculates the quad verticles 
QuadVerticles Renderer::CalculateVertexes(int x, int y)
{
	QuadVerticles qv;
	float sizeMaxX = 640.0;
	float sizeMaxY = 480.0;
	float stepX = sizeMaxX / 8; //tile size on the display
	float stepY = sizeMaxY / 8; //tile size on the display

	
	qv.upperLeftX = stepX * x + 3.2f; //upper left x verticle
	qv.upperLeftY = stepY * y + 2.4f; //upper left y verticle
	qv.upperRightX = stepX * (x + 1) - 3.2f; //upper right x verticle
	qv.upperRightY = stepY * y + 2.4f; //upper right y verticle
	qv.lowerRightX = stepX * (x + 1.0f) - 3.2f; //lower right x verticle
	qv.lowerRightY = stepY * (y + 1.0f) - 2.4f; //lower right y verticle
	qv.lowerLeftX = stepX * x + 3.2f; // lower left x verticle
	qv.lowerLeftY = stepY * (y + 1.0f) - 2.4f; //lower y verticle

	return qv;
}

Renderer::Renderer(Map map)
{
	this->map = map;
	DisplayFirstFrame(map.getIconIds());
}

void PrepareForDisplay(void)
{
	GLenum err = glewInit();
	if (GLEW_OK != err) { fprintf(stderr, "Error: %s\n", glewGetErrorString(err)); }
	else { fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION)); }
	Map map = Map();
	Renderer renderer = Renderer(map);
}
