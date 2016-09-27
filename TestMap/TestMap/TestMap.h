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
	Element map[8][8];
public:
	Map();
	int** getIconIds();
};
#endif // !TESTMAP_H_INCLUDED