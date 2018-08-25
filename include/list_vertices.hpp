#pragma once
#include "graphics.h"
#include "colors.hpp"
#include "constants.hpp"
#include "vertex.hpp"
#include "helpers.hpp"

class ListVertices
{
public:
	int num;
	Vertex *v[MAX_VERTEX];
	char currentName[MAX_NAME_LENGTH];
	
	ListVertices();
	~ListVertices();
	
	void addVertex(int, int);
	void addVertex(char const *, int, int);
	void deleteVertex(int );
	void updateCurrentName(const char*);
	int find(int , int ) const;
	bool isExist(char const *) const;
	void showAll() const;
	void showAll(int );
	void resetColor();
	void clear();
};

ListVertices::ListVertices()
{
	num = 0;
	strcpy(currentName, VERTEX_NAME_BEGIN);
}
void ListVertices::addVertex(int x, int y)
{
	v[num] = new Vertex;
	v[num]->create(x, y, currentName);
	v[num]->show();
	increaseStr(currentName);
	++num;
}
void ListVertices::addVertex(char const *name, int x, int y)
{
	v[num] = new Vertex;
	v[num]->create(x, y, name);
	strcpy(currentName, max(currentName, name));
	increaseStr(currentName);
	++num;
}
void ListVertices::deleteVertex(int pos)
{
	delete v[pos];
	--num;
	for (int i = pos; i < num; ++i)
		v[i] = v[i + 1];
}
int ListVertices::find(int x, int y) const
{
	for (int i = 0; i < num; ++i)
		if (v[i]->isVertexClick(x, y)) return i;
	return -1;
}
void ListVertices::showAll() const
{
	for (int i = 0; i < num; ++i)
		v[i]->show();
}
void ListVertices::showAll(int color)
{
	for (int i = 0; i < num; ++i)
		v[i]->show(color);
}
void ListVertices::resetColor()
{
	for (int i = 0; i < num; ++i)
		v[i]->setColor(VERTEX_COLOR);
}
bool ListVertices::isExist(char const *name) const
{
	for (int i = 0; i < num; ++i)
		if (strcmp(v[i]->name, name) == 0) return 1;
	return 0;
}
void ListVertices::clear()
{
	while (--num >= 0)
		delete v[num];
	num = 0;
	strcpy(currentName, VERTEX_NAME_BEGIN);
}
void ListVertices::updateCurrentName(const char *str)
{
	if (strcmp(currentName, max(currentName, str)) != 0)
	{
		strcpy(currentName, str);
		increaseStr(currentName);
	}
}
ListVertices::~ListVertices()
{
	while (--num >= 0)
		delete v[num];
}
