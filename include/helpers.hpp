#pragma once

#include <windows.h>
#include <cstring>
#include <sstream>
#include "graphics.h"
#define _USE_MATH_DEFINES
#include <cmath>
inline bool isInWorkingZone(int x, int y)
{	
	return (x > wbLEFT && x < wRIGHT && y > wTOP && y < wBOTTOM);
}
inline bool isInLimitZone(int x, int y)
{	
	return (x > wbLEFT + RADIUS_VALUE && x < wRIGHT - RADIUS_VALUE 
		&& y > wTOP + RADIUS_VALUE && y < wBOTTOM - RADIUS_VALUE);
}
inline float toFloat(char const *s)
{
	return atof(s);
}
inline int toInt(char const *s)
{
	return atoi(s);
}

template <typename T> 
void convertToChar(T num, char str[])
{
	std::ostringstream ss;
	ss << num;
	strcpy(str, ss.str().c_str());
}
//inline void convertToChar(int num, char *str)
//{
//	sprintf(str, "%d", num);
//}
bool inputFloat(char k)
{
	return ((k >= '0' && k <= '9' ) || k == '.' || k == '-');
}
bool inputAscii(char k)
{
	k = toupper(k);
	return (k >= 'A' && k <= 'Z') || (k >= '0' && k <= '9');
}
bool isUnsignedInt(char const *s)
{
	int len = strlen(s);
	for (int i = 0; i < len; ++i)
		if (s[i] < '0' || s[i] > '9') return 0;
	return 1;
}
void increaseStr(char *str)
{
	if (isUnsignedInt(str))
		convertToChar(toInt(str) + 1, str);
	else ++str[strlen(str) - 1];
}
bool isFloat(const char *s)
{
    char *ep = NULL;
    strtof(s, &ep);
    if (!ep  ||  *ep)
        return 0;
    return 1;
}

template <typename Type>
void setArrayTo(Type *arr, int num, Type value)
{
	for (int i = 0; i < num; ++i) arr[i] = value;
}

// This following function work on stack memory only
template <typename Type, size_t rows>
void setMatrixTo(Type (&arr)[rows][rows], Type value)
{
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < rows; ++j)
			arr[i][j] = value;
}

char const *max(char const *str1, char const *str2)
{
	if (strlen(str1) > strlen(str2)) return str1;
	if (strlen(str2) > strlen(str1)) return str2;
	return (strcmp(str1, str2) > 0) ? str1 : str2;
}

template<typename Type>
inline const Type& max(const Type& a, const Type& b)
{
	if (a > b)
		return a;
  	return b;
}

template<typename Type>
inline const Type& min(const Type& a, const Type& b)
{
	if (a < b)
		return a;
  	return b;
}

void printWeight(int x, int y, float w)
{
	setcolor(BLACK);
	setbkcolor(wZONE_COLOR);
	setusercharsize(11, 20, 11, 20);
	settextstyle(BOLD_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	char str[10];
	convertToChar(w, str);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextxy(x, y, str);
}
void drawTrianle(int x1, int y1, int x2, int y2, int color)
{
	setlinestyle(SOLID_LINE, 0, 2);
	setfillstyle(SOLID_FILL, color);
	int a[8];
	a[0] = x1 + y2 - y1;
	a[1] = y1 + x1 - x2;
	a[2] = x1 - y2 + y1;
	a[3] = y1 - x1 + x2;
	a[4] = x2; a[5] = y2;
	a[6] = a[0]; a[7] = a[1];
	setcolor(color);
	fillpoly(4, a);
}
void drawArrow(int x1, int y1, int x2, int y2, int color, float w)
{
	float corner = atan(float(abs(y1 - y2)) / abs(x1 - x2));
	float Rsin = RADIUS_VALUE * sin(corner);
	float Rcos = RADIUS_VALUE * cos(corner);
	int x11 = x1 + Rcos;
	int y11 = y1 + Rsin;
	int x22 = x2 - Rcos;
	int y22 = y2 - Rsin;
	if (x1 > x2)
	{
		x11 = x1 - Rcos;
		x22 = x2 + Rcos;
	}
	if (y1 > y2)
	{
		y11 = y1 - Rsin;
		y22 = y2 + Rsin;
	}
	setlinestyle(SOLID_LINE, 1, 2);
	setcolor(color);
	line(x11, y11, x22, y22);
	drawTrianle(2 * x22 - (x2 + x22) / 2, 2 * y22 -(y22 + y2) / 2, x22, y22, color);
	printWeight((x1 + x2) / 2, (y1 + y2) / 2, w);
}
void drawCurvedLine2(int x1, int y1, int x2, int y2, int color, float w)
{
	float xO = (x1 + x2) / 2 + (y1 - y2) / M_SQRT2; // or +
	float yO = (y1 + y2) / 2 + (x2 - x1) / M_SQRT2; // or +
	float r = sqrt(pow(xO - x1, 2) + pow(yO - y1, 2));
	float d = sqrt(pow(x1 - xO, 2) + pow(y1 - yO, 2));
	float a = (pow(r, 2) - pow(RADIUS_VALUE, 2) + pow(d ,2)) / (2 * d);
	float h = sqrt(r * r - a * a);								//					 
	float tmpx1 = xO + a * (x1 - xO) / d;						//					   xT		  
	float tmpx2 = xO + a * (x2 - xO) / d;						//        *  * x3             x4*  *
	float tmpy1 = yO + a * (y1 - yO) / d;						//     *        *            *        *
	float tmpy2 = yO + a * (y2 - yO) / d;						//    *    x1    *          *     x2   *
	int x3 = tmpx1 - h* (y1 - yO) / d;   // -h					//    *          *          *          *
	int x4 = tmpx2 + h* (y2 - yO) / d;   // +h					//     *        *            *        *
	int y3 = tmpy1 + h * (x1 - xO) / d;  // 					//        *  *                  *  *
	int y4 = tmpy2 - h * (x2 - xO) / d;  // 					//				 	   xO          
	float stangle, endangle;									//					 
	float angle1 = float(x1 - xO) / r;
	float angle2 = 1 - float(pow(RADIUS_VALUE, 2)) / (2 * pow(r, 2));
	if (angle1 < -1 || angle1 > 1) angle1 = int(angle1);
	if (angle2 < -1 || angle2 > 1) angle2 = int(angle2);
	angle1 = acos(angle1) * 180 / M_PI;
	angle2 = acos(angle2) * 180 / M_PI;
	if (y1 >= yO) angle1 = 360 - angle1;
	stangle = angle1 + angle2;
	angle1 = acos(1 - pow(sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2)), 2) / (2 * pow(r, 2)));
	angle1 = angle1 * 180 / M_PI;
	stangle = stangle - angle1 - 2 * angle2;
	endangle = stangle + angle1;
	float theta = atan2((y1 + y2) / 2 - yO, (x1 + x2) / 2 - xO);
	float xT = xO + r * cos(theta);
	float yT = yO + r * sin(theta);
	setcolor(color);
	setlinestyle(SOLID_LINE, 1, 2);
	arc(xO, yO, stangle, endangle, r);
	drawTrianle(2 * x4 - (x2 + x4) / 2, 2 * y4 - (y2 + y4) / 2, x4, y4, color); // FINALY
	printWeight(xT, yT, w);
}
void drawCurvedLine(int x1, int y1, int x2, int y2, int color, float w)
{
	float xO = (x1 + x2) / 2 + (y1 - y2) / -M_SQRT2; // or +
	float yO = (y1 + y2) / 2 + (x2 - x1) / -M_SQRT2; // or +
	float r = sqrt(pow(xO - x1, 2) + pow(yO - y1, 2));
	float d = sqrt(pow(x1 - xO, 2) + pow(y1 - yO, 2));
	float a = (pow(r, 2) - pow(RADIUS_VALUE, 2) + pow(d ,2)) / (2 * d);
	float h = sqrt(r * r - a * a);								//					 
	float tmpx1 = xO + a * (x1 - xO) / d;						//					   xT		  
	float tmpx2 = xO + a * (x2 - xO) / d;						//        *  * x3             x4*  *
	float tmpy1 = yO + a * (y1 - yO) / d;						//     *        *            *        *
	float tmpy2 = yO + a * (y2 - yO) / d;						//    *    x1    *          *     x2   *
	int x3 = tmpx1 + h* (y1 - yO) / d;   // -h					//    *          *          *          *
	int x4 = tmpx2 - h* (y2 - yO) / d;   // +h					//     *        *            *        *
	int y3 = tmpy1 - h * (x1 - xO) / d;  // 					//        *  *                  *  *
	int y4 = tmpy2 + h * (x2 - xO) / d;  // 					//				 	   xO          
	float stangle, endangle;									//					 
	float angle1 = float(x1 - xO) / r;
	float angle2 = 1 - float(pow(RADIUS_VALUE, 2)) / (2 * pow(r, 2));
	if (angle1 < -1 || angle1 > 1) angle1 = int(angle1);
	if (angle2 < -1 || angle2 > 1) angle2 = int(angle2);
	angle1 = acos(angle1) * 180 / M_PI;
	angle2 = acos(angle2) * 180 / M_PI;
	if (y1 >= yO) angle1 = 360 - angle1;
	stangle = angle1 + angle2;
	angle1 = acos(1 - pow(sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2)), 2) / (2 * pow(r, 2)));
	angle1 = angle1 * 180 / M_PI;
	endangle = stangle + angle1; 
	float theta = atan2((y1 + y2) / 2 - yO, (x1 + x2) / 2 - xO);
	float xT = xO + r * cos(theta);
	float yT = yO + r * sin(theta);
	if (xT <= wbLEFT || xT >= wRIGHT || yT <= wTOP || yT >= wBOTTOM)
		return drawCurvedLine2(x1, y1, x2, y2, color, w);
	setcolor(color);
	setlinestyle(SOLID_LINE, 1, 2);
	arc(xO, yO, stangle, endangle, r);
	drawTrianle(2 * x4 - (x2 + x4) / 2, 2 * y4 - (y2 + y4) / 2, x4, y4, color); // FINALY
	printWeight(xT, yT, w);
}

