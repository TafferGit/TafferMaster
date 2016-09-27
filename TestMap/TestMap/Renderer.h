#pragma once
#ifndef RENDERED_H_INCLUDED
#define RENDERED_H_INCLUDED
#include <cstdlib>
#include <iostream>
#include "GL\freeglut.h"
#include "TestMap.h"
void PrepareForDisplay(void);
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
	Map map;
public:
	Renderer(Map map);
};
#endif