#pragma once
#include "graphics.h"
#include "colors.hpp"
#include "constants.hpp"
#include "helpers.hpp"

struct Button
{
	const int left, top, right, bottom;
	int color;
	const char name[15];
	
	void showInit(int );
	void showNormalButton();
	void showHightLightButton();
	void showChoseButton();
	void showButtonHint();
	void showName() const;
	bool isButtonClick(int x, int y);
};

inline bool Button::isButtonClick(int x, int y)
{
	return (y > top && y < bottom && x > left && x < right);
}
void Button::showInit(int borderColor)
{
	setcolor(borderColor);
	setlinestyle(SOLID_LINE, 1, 2);
	setfillstyle(SOLID_FILL, color);
	bar(left, top, right, bottom);
	rectangle(left, top, right, bottom);
}
inline void Button::showNormalButton()
{
	color = BUTTON_COLOR;
	showInit(BUTTON_BORDER);
}
inline void Button::showHightLightButton()
{
	color = BUTTON_COLOR_HIGHTLIGHT;
	showInit(BUTTON_BORDER_HIGHTLIGHT);
}
inline void Button::showChoseButton()
{
	color = BUTTON_COLOR_CHOSE;
	showInit(BUTTON_BORDER_CHOSE);
}
void Button::showButtonHint()
{
	setusercharsize(1, 2, 1, 2);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	setcolor(BLACK);
	setbkcolor(BUTTON_HINT);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	outtextxy(right, bottom, name);
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	rectangle(right - 1, bottom, right + textwidth(name), bottom + textheight(name));
}
void Button::showName() const
{
	moveto((left + right) / 2, (top + bottom) / 2 + 6);
	settextjustify(CENTER_TEXT, CENTER_TEXT);	
	setusercharsize(1, 3, 1, 2); //gothic
	settextstyle(GOTHIC_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	setcolor(BLACK);
	setbkcolor(color);
	outtext(name);
}
void showButtonIcon(Button const *menu, int i)
{
	setcolor(BLACK);
	switch (i)
	{
	case ADD_VERTEX_MENU://357, 22, 417, 92,
		setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
		circle(387, 57, 25);
		setfillstyle(SOLID_FILL, BLACK);
		bar(375, 55, 399, 58);
		bar(386, 45, 389, 69);
		break;
	case ADD_EDGE_MENU://357, 92, 417, 162
		setlinestyle(SOLID_LINE, 1, 2);
		line(367, 147, 407, 107);
		drawTrianle(401, 113, 408, 106, BLACK);
		break;
	case RENAME_VERTEX_MENU://357, 162, 417, 232
		setlinestyle(SOLID_LINE, 1, 2);
		line(397, 180, 409, 192);
		line(374, 203, 386, 215);
		line(374, 203, 397, 180);
		line(386, 215, 409, 192);
		line(374, 203, 368, 220);
		line(386, 215, 368, 220);
		break;
	case DELETEVE_MENU://357, 232, 417, 302
		setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
		circle(387, 267, 25);
		setlinestyle(SOLID_LINE, 1, THICK_WIDTH);
		line(379, 259, 394, 274);
		line(379, 274, 394, 259);
		break;
	case MOVEVE_MENU://357, 302, 417, 372
		setfillstyle(SOLID_FILL, BLACK);
		bar(372, 336, 401, 338);
		bar(387, 323, 389, 352);
		drawTrianle(374, 336, 368, 336, BLACK);
		drawTrianle(387, 323, 387, 317, BLACK);
		drawTrianle(401, 336, 407, 336, BLACK);
		drawTrianle(387, 352, 387, 358, BLACK);
		break;
	case CLEAN_GRAPH_MENU://357, 372, 417, 442
		setlinestyle(SOLID_LINE, 1, 2);
		rectangle(369, 392, 405, 432);
		rectangle(373, 382, 401, 392);
		setlinestyle(SOLID_LINE, 1, 3);
		line(377, 403, 377, 427);
		line(387, 403, 387, 427);
		line(397, 403, 397, 427);
		line(365, 392, 409, 392);
		break;
	case HELP_MENU:
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setusercharsize(1, 1, 1, 1);
		settextstyle(GOTHIC_FONT, HORIZ_DIR, USER_CHAR_SIZE);
		setbkcolor(menu[HELP_MENU].color);
		outtextxy(387, 482, "?");
		break;
	default:
		menu[i].showName();
		break;
	}
}
