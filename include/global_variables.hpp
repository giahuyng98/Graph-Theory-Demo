#pragma once
#include "list_vertices.hpp"
#include "button.hpp"

ListVertices listv;							// List vertices
int xCursor = xCURSOR;						// For printText()
int yCursor = yCURSOR;						// For printText()
int delayRunTime = 500;						// 500ms delay default
bool isSaved = 1;							// Check if Graph is saved or not
int trace[MAX_VERTEX]; 						// visited & save path...
float adjaGraph[MAX_VERTEX][MAX_VERTEX];	// Adjacency Matrix
HWND hwnd;									// Manage win32 api functions

// List button for select menu item 
Button menuButton[] =	{ {15, 30, 115, 70, BUTTON_COLOR,  	"DFS"},
						  {120, 30, 220, 70, BUTTON_COLOR,	"BFS"},
						  {225, 30, 325, 70, BUTTON_COLOR,	"X->Y"},
						  {15, 75, 115, 115, BUTTON_COLOR,	"DINH TRU"},
						  {120, 75, 220, 115, BUTTON_COLOR,	"DINH THAT"},
						  {225, 75, 325, 115, BUTTON_COLOR,	"CANH CAU"},
						  {15, 120, 115, 160, BUTTON_COLOR,	"HAMILTON"},
						  {120, 120, 220, 160, BUTTON_COLOR,"EULER"},
						  {225, 120, 325, 160, BUTTON_COLOR,"TOPO SORT"},
						  {15, 165, 115, 205, BUTTON_COLOR,	"TO MAU"},
						  {120, 165, 220, 205, BUTTON_COLOR,"TPLT"},
						  {15, 245, 115, 285, BUTTON_COLOR,	"Mo File"},
						  {120, 245, 220, 285, BUTTON_COLOR,"Luu File"},
						  {225, 245, 325, 285, BUTTON_COLOR,"Thoat"},
						  {357, 22, 417, 92, BUTTON_COLOR,	"Them Dinh"},
						  {357, 92, 417, 162, BUTTON_COLOR,	"Them/Xoa Cung"},
						  {357, 162, 417, 232, BUTTON_COLOR,"Doi Ten Dinh"},
						  {357, 232, 417, 302, BUTTON_COLOR,"Xoa Dinh"},
						  {357, 302, 417, 372, BUTTON_COLOR,"Di Chuyen"},
						  {357, 372, 417, 442, BUTTON_COLOR,"Xoa Do Thi"},
						  {357, 442, 417, 498, BUTTON_COLOR,"Giup Do"}};
