#include "Renderer.h"

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Test Map");
	glutPositionWindow(1, 1);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 640.0, 480.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(PrepareForDisplay);

	glutMainLoop();

}

void Renderer::DisplayFirstFrame(Map * map)
{
	GLuint tex_2d = 0;
	unsigned char * img = NULL;
	int width = 91, height = 94;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &tex_2d);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_2d);

	img = SOIL_load_image("test2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	std::cout << "Entering cycle\n";
	//Iterating through all the cells, column by column, row by row.
	int **tiles = map->getIconIds();
	for (int i = 0; i < 8; i++ ) {
		for (int j = 0; j < 8; j++) {
			//std::cout << "j = " << j << "i = " << i << "\n";
			tileId = 0;//tiles[j][i];
			QuadVerticles quadVert = CalculateVertexes(j, i);
			DrawTile(tileId, quadVert, tex_2d);
		}
	}
	glEnd();
	glutSwapBuffers();
}

//This function simply draws the tile
void Renderer::DrawTile(int tileId, QuadVerticles qv, GLuint texture)
{

	//glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_TRIANGLES);

	//First triange
	glTexCoord2f(0.0, 0.0);
	glVertex2f(qv.upperLeftX, qv.upperLeftY); //v0 - top left

	glTexCoord2f(1.0, 0.0);
	glVertex2f(qv.upperRightX, qv.upperRightY); //v1 - top right

	glTexCoord2f(0.0, 1.0);
	glVertex2f(qv.lowerLeftX, qv.lowerLeftY); //v2 - bottom left

	//Second triangle
	glTexCoord2f(1.0, 0.0);
	glVertex2f(qv.upperRightX, qv.upperRightY); //v1 - top right

	glTexCoord2f(0.0, 1.0);
	glVertex2f(qv.lowerLeftX, qv.lowerLeftY); //v2 - bottom left

	glTexCoord2f(1.0, 1.0);
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
QuadVerticles Renderer::CalculateVertexes(int i, int j)
{
	QuadVerticles qv;
	float sizeMaxX = 640.0;
	float sizeMaxY = 480.0;
	float stepX = sizeMaxX / this->map->getSizeX(); //tile size on the display
	float stepY = sizeMaxY / this->map->getSizeY(); //tile size on the display

	float borderX = 3.2f; 
	float borderY = 2.4f; 
	qv.upperLeftX = stepX * i; //upper left x verticle
	qv.upperLeftY = stepY * j; //upper left y verticle
	qv.upperRightX = stepX * (i + 1); //upper right x verticle
	qv.upperRightY = stepY * j ; //upper right y verticle
	qv.lowerRightX = stepX * (i + 1); //lower right x verticle
	qv.lowerRightY = stepY * (j + 1); //lower right y verticle
	qv.lowerLeftX = stepX * i; // lower left x verticle
	qv.lowerLeftY = stepY * (j + 1); //lower y verticle

	return qv;
}

Renderer::Renderer(Map * map)
{
	this->map = map;
	DisplayFirstFrame(map);
}

void PrepareForDisplay(void)
{
	int tiles[3][5] = {
		{ 1, 0, 2, 1, 0 },
		{ 2, 1, 1, 0, 1 },
		{ 0, 2, 1, 1, 2 }
	};
	int **someArray = NULL; 
	Map * map = new Map(3, 5, someArray); //Need to get pointer-to-pointer instead of a 2d array!
	GLenum err = glewInit();
	if (GLEW_OK != err) { fprintf(stderr, "Error: %s\n", glewGetErrorString(err)); }
	else { fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION)); }
	Renderer renderer = Renderer(map);
}
