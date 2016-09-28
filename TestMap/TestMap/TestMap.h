#pragma once
#ifndef TESTMAP_H_INCLUDED
#define TESTMAP_H_INCLUDED


class Element {
private:
	int id = 0;
public:
	Element();
	Element(int i);
	int getIconId();
};

class Map {
private:
	int sizeX = 8;
	int sizeY = 8;
	Element map[sizeX][sizeY];
public:
	Map();
	Map(int x, int y);
	Map(int x, int y, int** args);
	int getSizeX();
	int getSizeY();
	int** getIconIds();
};
#endif // !TESTMAP_H_INCLUDED