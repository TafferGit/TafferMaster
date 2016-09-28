#include "Renderer.h"
Element::Element() 
{
	this->id = 0;
}

Element::Element(int i) 
{
		this->id = i;
}

int Element::getIconId() 
{
	return this->id;
}

Map::Map() 
{
	this->sizeX = 8;//default
	this->sizeY = 8;//default
	for (int i = 0; i<sizeX;i++) {
		for (int j = 0;j<sizeY;j++) {
			this->map[i][j] = Element(0);
		}
	}
}
Map::Map(int x, int y) 
{
	this->sizeX = x;
	this->sizeY = y;
	for (int i = 0; i<sizeX;i++) {
		for (int j = 0;j<sizeY;j++) {
			this->map[i][j] = Element(0);
		}
	}
}
Map::Map(int x, int y, int **args) 
{
	this->sizeX = x;
	this->sizeY = y;
	for (int i = 0; i<sizeX;i++) {
		for (int j = 0;j<sizeY;j++) {
			this->map[i][j] = Element(args[i][j]);
		}
	}
}

int Map::getSizeX()
{
	return this->sizeX;
}

int Map::getSizeY()
{
	return this->sizeY;
}

int** Map::getIconIds() 
{
	int** array2D = 0;
	array2D = new int*[sizeX];
	for (int i = 0; i < sizeX; i++) {
		array2D[i] = new int[sizeY];
		for (int j = 0; j < sizeY; j++) {
			array2D[i][j] = this->map[i][j].getIconId();
		}
	}
	return array2D;
}