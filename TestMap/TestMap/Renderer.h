#pragma once
#ifndef RENDERED_H_INCLUDED
#define RENDERED_H_INCLUDED
#include <cstdlib>
#include <iostream>
#include <string>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "GL\SOIL.h"
#include "TestMap.h"

void PrepareForDisplay(void);
struct QuadVerticles {
	float upperLeftX;
	float upperLeftY;
	float upperRightX;
	float upperRightY;
	float lowerRightX;
	float lowerRightY;
	float lowerLeftX;
	float lowerLeftY;
};

class Renderer {
private:
	int tileId, tileToDraw;
	void DisplayFirstFrame(Map map);
	void DrawTile(int tileId, QuadVerticles qv);
	QuadVerticles CalculateVertexes(int x, int y);
	Map map;
public:
	Renderer(Map map);
};
#endif