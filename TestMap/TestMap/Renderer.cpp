#include "Renderer.h"

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Test Map");
	glutPositionWindow(1, 1);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(PrepareForDisplay);

	glutMainLoop();

}

void Renderer::DisplayFirstFrame(Map * map)
{
	glEnable(GL_TEXTURE_2D);
	this->tl->CreateTextureFromImage("test2.png");
	//glActiveTexture(GL_TEXTURE0);

	std::cout << "Entering cycle\n";
	//Iterating through all the cells, column by column, row by row.

	int **tiles = map->getIconIds();
	for (int i = 0; i < 9; i++ ) {
		for (int j = 0; j < 9; j++) {
			tileId = 0; //tiles[j][i];
			QuadVerticles quadVert = CalculateVertexes(j, i);
			DrawTile(tileId, quadVert);
		}
	}
	glutSwapBuffers();
}

//This function simply draws the tile
void Renderer::DrawTile(int tileId, QuadVerticles qv)
{
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
}

//This function calculates the quad verticles 
QuadVerticles Renderer::CalculateVertexes(int i, int j)
{
	QuadVerticles qv;
	float sizeMaxX = WINDOW_WIDTH;
	float sizeMaxY = WINDOW_HEIGHT;
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
	this->tl = new TextureLoader;
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
	Map * map = new Map(9, 9, someArray); //Need to get pointer-to-pointer instead of a 2d array!
	GLenum err = glewInit();
	if (GLEW_OK != err) { fprintf(stderr, "Error: %s\n", glewGetErrorString(err)); }
	else { fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION)); }
	Renderer renderer = Renderer(map);
}

void TextureLoader::SetTextureParams()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void TextureLoader::CreateTextureFromImage(const char * path)
{
	this->tex_2d = 0;
	this->img = NULL;
	this->tex_width = 240;
	this->tex_height = 240;

	glGenTextures(1, &this->tex_2d);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	img = SOIL_load_image(path, &this->tex_width, &this->tex_height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->tex_width, this->tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	this->SetTextureParams();
}
