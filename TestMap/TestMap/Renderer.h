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

#define WINDOW_WIDTH 640.0
#define WINDOW_HEIGHT 480.0

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

class TextureLoader {
	GLuint tex_2d;
	unsigned char * img;
	int tex_width, tex_height;
	void SetTextureParams();
public:
	void CreateTextureFromImage(const char * path);
};

class Renderer {
private:
	int tileId, tileToDraw;
	Map * map;
	TextureLoader * tl;
	void DisplayFirstFrame(Map * map);
	void DrawTile(int tileId, QuadVerticles qv);
	QuadVerticles CalculateVertexes(int x, int y);

public:
	Renderer(Map * map);
};
#endif