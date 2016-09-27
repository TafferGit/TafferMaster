#pragma once
#include <cstdlib>
#include "GL\freeglut.h"

struct QuadVerticles {
	double upperLeftX;
	double upperLeftY; 
	double upperRightX;
	double upperRightY;
	double lowerRightX;
	double lowerRightY;
	double lowerLeftX;
	double lowerLeftY;
};

class Renderer {
private:
	int tileId, tileToDraw;
	void DisplayFirstFrame(int **tiles);
	void DrawTile(int tileId, QuadVerticles qv);
	QuadVerticles CalculateVertexes(int x, int y);
public:
	Renderer();
};