#pragma once
#include <cstring>
#include <cmath>
#include "graphics.h" // Borland Graphic (Winbgi) Version 15.01.01
#include "colors.hpp"
#include "constants.hpp"

struct Vertex
{
	int x, y;
	int color;
	char name[MAX_NAME_LENGTH];
	
	Vertex();
	void create(int , int , char const*);
	void setColor(int );
	void setCoordinate(int , int );
	void showName(int ) const;
	void clearName();
	void show() const; //Show with current this->color
	void show(int ); //Show with custom color
	void showActive(bool);
	bool isVertexClick(int , int ) const;
};

Vertex::Vertex()
{
	name[0] = '\0';
	color = VERTEX_COLOR;
}
void Vertex::create(int x, int y, char const *name)
{
	this->x = x; this->y = y;
	strcpy(this->name, name);
}
void Vertex::show() const
{
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	setcolor(VERTEX_BORDER);
	circle(x, y, RADIUS_VALUE);
	setfillstyle(SOLID_FILL, color);
	floodfill(x, y, 0);
	showName(BLACK);
}
void Vertex::show(int c)
{
	clearName();
	setColor(c);
	show();
}
void Vertex::showActive(bool isOn)
{
	isOn ? setcolor(VERTEX_ACTIVE_COLOR) : setcolor(wZONE_COLOR);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	circle(x, y, RADIUS_VALUE);
}
void Vertex::showName(int textColor) const
{
	setcolor(textColor);
	setbkcolor(color);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	if (strlen(name) < 3)
	{
		setusercharsize(3, 5, 3, 5);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	}
	else
		settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	outtextxy(x, y + 8, name);
}
inline void Vertex::clearName()
{
	showName(color);
}
inline void Vertex::setColor(int c)
{
	this->color = c;
}
inline void Vertex::setCoordinate(int x, int y)
{
	this->x = x;
	this->y = y;
}
inline bool Vertex::isVertexClick(int x, int y) const
{
	return (pow(this->x - x, 2) + pow(this->y - y, 2) <= RADIUS_VALUE * RADIUS_VALUE);
} // simple circle theorem

