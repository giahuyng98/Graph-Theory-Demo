// ---------------------------------------------------------------------------
//                          Include Directives
// ---------------------------------------------------------------------------
#include <fstream>						// For open & save file
#include <iostream>						// Debug std::cin std::cout
#include "include/queue.hpp"			// int queue using linked list
#include "include/stack.hpp"			// int stack also using linked list
#include "include/colors.hpp"			// Define all colors need
#include "include/button.hpp"			// Button structures
#include "include/vertex.hpp"			// Vertex structures
#include "include/list_vertices.hpp"	// Manage all vertices
#include "include/helpers.hpp" 			// Basic functions & draw edges
#include "include/constants.hpp" 		// All constants go here
#include "include/global_variables.hpp"	// All Global variables
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// 							Draw all stuff here
// ---------------------------------------------------------------------------
void drawWindow();
void drawWorkingZone();
void drawLimitZone();
void drawMenuZone();
void drawTextZone();
void drawMatrixZone();
void showSpeed();
void showAllButtons();
void refreshScreen();
void refreshGraph(int);
void initScreen();
void initializer();
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
//                          All algogrimth for menu
// ---------------------------------------------------------------------------
void DFS();
void BFS();
void pathXY();
void cutVertex();
void knotVertex();
void bridgeEdge();
void hamilton();
void euler();
void topoSort();
void pert();
void colorGraph();
void SCC();
// ---------------------------------------------------------------------------
//                          		File
// ---------------------------------------------------------------------------
void open();
void save();
void quit();
void help();

// ---------------------------------------------------------------------------
//                          Graph editing functions
// ---------------------------------------------------------------------------
void addVertex();
void addEdges();
void renameVertex();
void deleteVertex();
void moveVertex();
void cleanGraph();

// ---------------------------------------------------------------------------
//                          Algogrimth helper
// ---------------------------------------------------------------------------
void removeVertex(int);
void removeRow(int);
void removeCol(int);
void removeLast();

void dfsTraveler(int);
void bfsTraveler(int);

void tarjanVisit(int, int *, int *, stack &, int &, int &, bool);
void tarjanResult(stack &, int, int);
int tarjanAlgo(bool, int remove = -1);

void recursiveHamilton(int, int *, bool &);
void resultHamilton(int *);
void continueHamilton(bool &);

bool isExistUndirectedEdge(int, int);
bool isExistDirectedEdge(int , int);
bool dfsToCheckConnected(bool (*)(int, int), int, int stop = -1);
void dfsToCheckKnot(int, int, bool *);

void calcDegree(int *, int *);
void sortDecendingDegree(int *);
bool isStronglyConnected();
bool isWeaklyConnected();
int eulerChecker();

void copyToMutilGraph(bool [][MAX_VERTEX]);
bool isNegativeWeight(); // Check for negative weight Dijkstra
bool isNegativeCycle(double *); // Check for negative cycle fordbellman
void dijkstra(int, int);
bool fordbellman(int, int);
bool numbering(int *, int *); //topo

// ---------------------------------------------------------------------------
//                          Graph helper functions
// ---------------------------------------------------------------------------
void drawEdge(int, int, int);
void drawAllEdges();
int chooseVertex(int, int skipReset = -1);
bool chooseStartVertex(int &, const char*, const char*);
bool chooseTwoVertices(int &, int &);
char getKey();
void adjustSpeed(char);
bool isEmptyGraph();
void showResultStack(stack &);
void showResultPathXY(double [], int, int);

// ---------------------------------------------------------------------------
//                          Keyboard editor functions
// ---------------------------------------------------------------------------
bool getInputChar(char *, int, bool (*)(char));
bool getInputWeight(float &);

// ---------------------------------------------------------------------------
//                          Texts: print, delete, set style
// ---------------------------------------------------------------------------
void setTextPrintStyle(int);
void printText(float);
void printText(const char*);
void deleteText(const char*);
template <typename Type>
void printTextWl(Type); // print text -> endl
template <typename Type>
void printTextWlb(Type); // endl -> print text

// ---------------------------------------------------------------------------
//                          		Menu
// ---------------------------------------------------------------------------
int findButton(int, int);
void switchMenuItem(int);
void menu();
void backToMenu();
// ---------------------------------------------------------------------------

int main()
{
    initializer();
	menu();
	closegraph();
	return EXIT_SUCCESS;
}
void drawWorkingZone()
{
	setfillstyle(SOLID_FILL, wZONE_COLOR);
	bar(wbLEFT, wTOP, wRIGHT, wBOTTOM);
	setcolor(LINE_COLOR);
	setlinestyle(SOLID_LINE, 1, 2);
	rectangle(wLEFT, wTOP, wRIGHT, wBOTTOM);
}
void drawLimitZone()
{
	setcolor(LIMIT_COLOR);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	rectangle(wbLEFT + 2, wTOP + 2, wRIGHT - 2, wBOTTOM - 2);
}
void drawMenuZone()
{
	setbkcolor(BACKGROUND_COLOR);
	setusercharsize(1, 2, 1, 2);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(BLACK);
	outtextxy(5, mTOP - 20, "Menu");
	outtextxy(5, fTOP - 20, "File");
	outtextxy(5, aTOP - 20, "Adjacency matrix");
	setlinestyle(SOLID_LINE, 1, 2);
	setcolor(LINE_COLOR);
	rectangle(mLEFT, mTOP, mRIGHT, mBOTTOM);
	rectangle(fLEFT, fTOP, fRIGHT, fBOTTOM);
}
void drawTextZone()
{
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(tLEFT, tTOP, tRIGHT, tBOTTOM);
	setcolor(LINE_COLOR);
	setlinestyle(SOLID_LINE, 1, 2);
	rectangle(tLEFT, tTOP, tRIGHT, tBOTTOM);
	xCursor = xCURSOR; // Move cursor x to beginning
	yCursor = yCURSOR;
}
void drawMatrixZone()
{
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(aLEFT, aTOP, aRIGHT, aBOTTOM);
	setcolor(LINE_COLOR);
	setlinestyle(SOLID_LINE, 1, 2);
	rectangle(aLEFT, aTOP, aRIGHT, aBOTTOM);
	const int &n = listv.num + 1;
	if (n == 1) return;
	const float width = float(aRIGHT - aLEFT) / n;
	const float hight = float(aBOTTOM - aTOP) / n;
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	setcolor(BLACK);
	setbkcolor(BACKGROUND_COLOR);
	settextjustify(LEFT_TEXT, CENTER_TEXT);
	if (n > aVERTEX_MAX_2)
	{
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
		outtextxy((aRIGHT + aLEFT) / 2, (aBOTTOM + aTOP) / 2, "KHONG THE HIEN THI.");
		return;
	}
	if (n > aVERTEX_MAX_1) settextstyle(SMALL_FONT, HORIZ_DIR, 4);
	else
	{
		setusercharsize(1, 2, 1, 2);
		settextstyle(BOLD_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	}
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	char str[10];
	for (int i = 1; i < n; ++i)
	{
		line(aLEFT, aTOP + i * hight, aRIGHT, aTOP + i * hight);
		line(aLEFT + i * width, aTOP, aLEFT + i * width, aBOTTOM);
		outtextxy(ADJUST_TEXT_X, i * hight + ADJUST_TEXT_Y, listv.v[i - 1]->name);
		outtextxy(ADJUST_TEXT_X + i * width, ADJUST_TEXT_Y, listv.v[i - 1]->name);
		for (int j = 1; j < n; ++j)
			if (adjaGraph[i - 1][j - 1] != NO_EDGE_VALUE)
			{
				convertToChar(adjaGraph[i - 1][j - 1], str);
				outtextxy(ADJUST_TEXT_X + j * width, i * hight + ADJUST_TEXT_Y, str);
			}
	}
}
void showSpeed()
{
	char status[15];
	char speed[3];
	convertToChar((MAX_SPEED - delayRunTime) / 100, speed);
	strcpy(status, "Speed: ");
	strcat(status, speed);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(sLEFT, sTOP, sRIGHT, sBOTTOM);
	setbkcolor(BACKGROUND_COLOR);
	setusercharsize(1, 2, 1, 2);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	outtextxy(sLEFT, sTOP, status);
}
void drawWindow()
{
	setcolor(DOT_COLOR);
	setbkcolor(BACKGROUND_COLOR);
	setfillstyle(CLOSE_DOT_FILL, wZONE_COLOR);
	bar(0, 0, WINDOW_WIDTH, WINDOW_HIGHT);
}
void showAllButtons()
{
	for (int i = 0; i < NUM_OF_MENU; ++i)
	{
		menuButton[i].showNormalButton();
		showButtonIcon(menuButton, i);
	}
}
void initScreen()
{
	drawWindow();
	drawWorkingZone();
	drawTextZone();
	drawMenuZone();
	drawMatrixZone();
	showAllButtons();
	showSpeed();
}
void initializer()
{
	initwindow(WINDOW_WIDTH + 5, WINDOW_HIGHT + 10); //Remove +5, +10
	setwindowtitle("Graph Theory Demo 2.0");
	hwnd = GetActiveWindow();
	::SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE)&~WS_MAXIMIZEBOX);//&~WS_SIZEBOX
    initScreen();
    setMatrixTo(adjaGraph, NO_EDGE_VALUE);
}
void DFS()
{
	if (isEmptyGraph()) return;
	int start;
	if (chooseStartVertex(start, "Chon dinh bat dau: ", "DFS: "))
	{
		setArrayTo(trace, listv.num, 0);
		trace[start] = 1;
		dfsTraveler(start);
		return backToMenu();
	}
}
void BFS()
{
	if (isEmptyGraph()) return;
	int start;
	if (chooseStartVertex(start, "Chon dinh bat dau: ", "BFS: "))
	{
		setArrayTo(trace, listv.num, 0);
		trace[start] = 1;
		bfsTraveler(start);
		return backToMenu();
	}
}
void pathXY()
{
	if (isEmptyGraph()) return;
	int start, stop;
	if (chooseTwoVertices(start, stop))
	{
		setTextPrintStyle(TEXT_COLOR);
		if (!isNegativeWeight())
		{
			printTextWl("Khoi chay thuat toan Dijkstra:");
			dijkstra(start, stop);
		}
		else
		{
			// if graph doesn't contain negative cycle
			// run algorimth shortestPathFasterAlgo(start, stop)
			// instead of fordbellman
			printTextWl("Khoi chay thuat toan FordBellman: ");
			if (!fordbellman(start, stop))
				printTextWlb("Do thi ton tai chu trinh am.");
		} 
	}
	return backToMenu();
}
void cutVertex()
{
	if (isEmptyGraph()) return;
	int SCC = tarjanAlgo(0);
	int count(0);
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac dinh tru tim duoc:");
	for (int i = 0; i < listv.num; ++i)
	{
		int SCCAfterRemove = tarjanAlgo(0, i); //tarjan algorithm without show result & delete vertex i
		if (SCCAfterRemove > SCC) // is a cut vertex
		{
			listv.v[i]->show(VERTEX_DELETE_COLOR);
			setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
			printText(listv.v[i]->name);
			printText(", ");
			++count;
		}
	}
	deleteText(", ");
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);
	return backToMenu();
}
void knotVertex()
{
	if (isEmptyGraph()) return;
	int start, stop, count(0);
	if (chooseTwoVertices(start, stop))
	{
		setTextPrintStyle(TEXT_COLOR);
		if (adjaGraph[start][stop] != NO_EDGE_VALUE ||
			!dfsToCheckConnected(isExistDirectedEdge, start, stop))
			printText("Khong co dinh that (co duong di truc tiep hoac khong ton tai duong di).");
		else
		{
			bool mark[listv.num];
			setArrayTo(mark, listv.num, true); // marked all as knot vertex
			setArrayTo(trace, listv.num, 0); // reset visited
			dfsToCheckKnot(start, stop, mark); // calculate mark as result
			mark[start] = mark[stop] = false; // start & stop are not knot themself
			printTextWl("Cac dinh that tim duoc: ");
			for (int i = 0; i < listv.num; ++i)
				if (mark[i]) // is knot vertex between start & stop
				{
					++count;
					listv.v[i]->show(VERTEX_DELETE_COLOR);
					setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
					printText(listv.v[i]->name);
					printText(", ");
				}
			deleteText(", ");
			setTextPrintStyle(TEXT_COLOR);
			printTextWlb("Tong cong: ");
			printText(count);
		}
	}
	return backToMenu();
}
void bridgeEdge()
{
	if (isEmptyGraph()) return;
	int SCC = tarjanAlgo(0); // first find current SCC
	int count(0);
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac canh cau tim duoc:");
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE)
			{
				float backup = adjaGraph[i][j]; // backup edge
				adjaGraph[i][j] = NO_EDGE_VALUE; // Delete edge
				int SCCAfterRemoveEdge = tarjanAlgo(0); // recalculate SCC
				adjaGraph[i][j] = backup; // restore
				if (SCCAfterRemoveEdge > SCC) // is strong bridge
				{
					++count;
					drawEdge(i, j, EDGE_HIGHTLIGHT_COLOR);
					setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
					printText("(");
					printText(listv.v[i]->name);
					printText(",");
					printText(listv.v[j]->name);
					printText(");");
				}
			}
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);
	return backToMenu();
}
void hamilton()
{
	if (isEmptyGraph()) return;
	int path[listv.num];
	setArrayTo(trace, listv.num, 0);
	bool continueRun = 1;
	for (int i = 0; i < listv.num; ++i)
		if (continueRun && dfsToCheckConnected(isExistDirectedEdge, i)) // from i can visit all others
		{
			setArrayTo(trace, listv.num, 0);
			path[0] = i;
			trace[i] = 1;
			recursiveHamilton(1, path, continueRun);
		}
	setTextPrintStyle(TEXT_COLOR);
	printText("Tim kiem ket thuc.");
	return backToMenu();
}
void euler()
{
		
 /*
*Code below still has bug, you can implement by 
*reading this https://math.stackexchange.com/questions/1871065/euler-path-for-directed-graph
* Happy coding.
*/
	MessageBox(hwnd, "Code bi bug khong nen chay", "Thong bao", MB_APPLMODAL | MB_ICONWARNING);
//	if (isEmptyGraph()) return;
//	int start = eulerChecker();
//	setTextPrintStyle(TEXT_COLOR);
//	if (start == NOT_EXIST_EULER)
//	{
//		printTextWl("Do thi khong phai la Euler/Nua Euler.");
//		return backToMenu();
//	}
//	if (start == EXIST_EULER) // exist euler cycle
//	{
//		if (!chooseStartVertex(start, "Chon dinh bat dau: ", "Chu trinh euler: ")) return;
//	}
//	else printText("Duong di euler: "); // exist haft euler start already calc in eulerChecker
//	stack s, result;
//	bool gr[MAX_VERTEX][MAX_VERTEX];
//	copyToMutilGraph(gr);
//	s.push(start);
//	int u, v;
//	while (!s.isEmpty())
//	{
//		u = s.get();
//		for (v = 0; v < listv.num; ++v)
//			if (gr[u][v])
//			{
//				s.push(v);
//				gr[u][v] = 0;
//				break;
//			}
//		if (v == listv.num)
//			result.push(s.pop());
//	}
//	showResultStack(result);
//	return backToMenu();
}
void topoSort()
{
	if (isEmptyGraph()) return;
	int const &NUM = listv.num;
	int degIn[NUM];
	int order[NUM];
	for (int i = 0; i < NUM; ++i)
	{
		degIn[i] = 0;
		for (int j = 0; j < NUM; ++j)
			if (adjaGraph[j][i] != NO_EDGE_VALUE) ++degIn[i];
	}
	setTextPrintStyle(TEXT_COLOR);
	if (numbering(degIn, order))
	{
		printTextWl("Thu tu sap xep topo: ");
		for (int i = 0; i < NUM; ++i)
		{
			if (getKey() == KEY_ESC) break;
			listv.v[order[i]]->show(VERTEX_VISTED_COLOR);
			setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
			printText(listv.v[order[i]]->name);
			printText("->");
			delay(delayRunTime);
		}
		deleteText("->");
	} 
	else
		printText("Do thi ton tai chu trinh.");
	return backToMenu();
}
void colorGraph()
{
	if (isEmptyGraph()) return;
	const int &NUM = listv.num;
	int order[NUM];
	sortDecendingDegree(order); // sort vertex decending by degree (out + in)
	setArrayTo(trace, NUM, -1); // trace is now color, -1 mean it's not colored
	int count(0), currentColor(1);
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac mau to: ");
	while (count < NUM) // while exist not colored vertex
	{
		int i;
		for (i = 0; i < NUM; ++i)
			if (trace[i] == -1) break; // find the first vertex that has not been colored
		trace[i] = currentColor; // color that vertex
		printText(currentColor); printText(":(");
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[order[i]]->name);
		listv.v[order[i]]->show(VERTEX_MORE_COLOR[currentColor]); // also show
		++count;
		for (int j = i + 1; j < NUM; ++j) // for each vertex ...
		{
			bool canColoring = (trace[j] == -1); // ... has not been colored then ...
			for (int k = 0; k < NUM && canColoring; ++k) // ... check orther vertex has same color && is neighbor
				if (trace[k] == currentColor && isExistUndirectedEdge(order[j], order[k]))
					canColoring = 0; // if so then ignore
			if (canColoring) //else color it with currentColor
			{
				trace[j] = currentColor;
				listv.v[order[j]]->show(VERTEX_MORE_COLOR[currentColor]); // also show
				setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
				printText(","); printText(listv.v[order[j]]->name);
				++count;
			}
		}
		setTextPrintStyle(TEXT_COLOR);
		printText(") ");
		++currentColor;
	}
	printTextWlb("Tong cong: ");
	printText(--currentColor);
	return backToMenu();
}
void SCC()
{
	if (isEmptyGraph()) return;
	//listv.showAll(VERTEX_COLOR_0);
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Cac thanh phan lien thong manh:");
	int count = tarjanAlgo(1); // Use tarjan algorithm to calculate SCC & show result
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tong cong: ");
	printText(count);
	return backToMenu();
}
inline void removeRow(int row)
{
	for (int i = row; i < listv.num - 1; ++i)
		for (int j = 0; j < listv.num; ++j)
			adjaGraph[i][j] = adjaGraph[i + 1][j];
}
inline void removeCol(int col)
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = col; j < listv.num - 1; ++j)
			adjaGraph[i][j] = adjaGraph[i][j + 1];
}
inline void removeLast()
{
	const int &LAST = listv.num - 1;
	for (int i = 0; i < listv.num; ++i) //Remove last row & last column
	{
		adjaGraph[LAST][i] = NO_EDGE_VALUE;
		adjaGraph[i][LAST] = NO_EDGE_VALUE;
	}
}
void removeVertex(int v)
{
	removeCol(v);
	removeRow(v);
	removeLast();
}
void bfsTraveler(int u)
{
	queue q;
	q.push(u);
	while (!q.isEmpty())
	{
		u = q.pop();
		listv.v[u]->show(VERTEX_VISTED_COLOR);
		listv.v[u]->showActive(1);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[u]->name);
		printText("->");
		delay(delayRunTime);
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && adjaGraph[u][i] != NO_EDGE_VALUE)
			{
				trace[i] = 1;
				q.push(i);
				drawEdge(u, i, EDGE_VISTED_COLOR);
				listv.v[i]->show(VERTEX_QUEUE_COLOR);
				if (getKey() == KEY_ESC) return;
				delay(delayRunTime);
			}
		listv.v[u]->showActive(0);
		listv.v[u]->show(VERTEX_VISTED_COLOR);
	}
	deleteText("->");
}
void dfsTraveler(int u)
{
	stack s;
	s.push(u);
	while (!s.isEmpty())
	{
		u = s.pop();
		listv.v[u]->show(VERTEX_VISTED_COLOR);
		listv.v[u]->showActive(1);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[u]->name);
		printText("->");
		delay(delayRunTime);
		//for (int i = listv.num - 1; i >= 0 ; --i) //like recursive order
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && adjaGraph[u][i] != NO_EDGE_VALUE)
			{
				trace[i] = 1;
				s.push(i);
				drawEdge(u, i, EDGE_VISTED_COLOR);
				listv.v[i]->show(VERTEX_QUEUE_COLOR);
				if (getKey() == KEY_ESC) return;
				delay(delayRunTime);
			}
		listv.v[u]->showActive(0);
		listv.v[u]->show(VERTEX_VISTED_COLOR);
	}
	deleteText("->");
}
void calcDegree(int *degIn, int *degOut)
{
	for (int i = 0; i < listv.num; ++i)
	{
		degOut[i] = degIn[i] = 0;
		for (int j = 0; j < listv.num; ++j)
		{
			if (adjaGraph[i][j] != NO_EDGE_VALUE) ++degOut[i];
			if (adjaGraph[j][i] != NO_EDGE_VALUE) ++degIn[i];
		}
	}
}
void sortDecendingDegree(int *order)
{
	const int &NUM = listv.num;
	int degIn[NUM];
	int degOut[NUM];
	calcDegree(degIn, degOut);
	setArrayTo(trace, NUM, 1);
	for (int i = 0; i < NUM; ++i)
	{
		int maxDegree = -1;
		int maxPos;
		for (int j = 0; j < NUM; ++j)
		{
			if (trace[j] && degOut[j] + degIn[j] > maxDegree)
			{
				maxDegree = degOut[j] + degIn[j];
				maxPos = j;
			}
		}
		order[i] = maxPos;
		trace[maxPos] = 0;
	}
}
int tarjanAlgo(bool showResult, int remove)
{
	const int &NUM = listv.num;
	int disc[NUM];
	int low[NUM];
	setArrayTo(disc, NUM, 0);
	setArrayTo(trace, NUM, 1);
	int count(0), components(0);
	stack s;
	if (remove != -1)
	{
		disc[remove] = 1; // ignore remove
		trace[remove] = 0; // ignore remove
	}
	for (int i = 0; i < NUM; ++i)
		if (disc[i] == 0) tarjanVisit(i, disc, low, s, count, components, showResult);
	return components;
}
void tarjanVisit(int u, int *disc, int *low, stack &s, int &count, int &components, bool callTarjanResult)
{
	low[u] = disc[u] = ++count;
	s.push(u);
	int v;
	for (v = 0; v < listv.num; ++v)
		if (trace[v] != 0 && adjaGraph[u][v] != NO_EDGE_VALUE)
			if (disc[v] != 0)
				low[u] = min(low[u], disc[v]);
			else
			{
				tarjanVisit(v, disc, low, s, count, components, callTarjanResult);
				low[u] = min(low[u], low[v]);
			}
	if (disc[u] == low[u])
	{
		++components;
		if (callTarjanResult)
			tarjanResult(s, u, components);
		else
			do
			{
				v = s.pop();
				trace[v] = 0;
			} while (v != u);
	}
}
void tarjanResult(stack &s, int stop, int components)
{
	setTextPrintStyle(TEXT_COLOR);
	printText(components);
	printText(":(");
	int v;
	do
	{
		v = s.pop();
		trace[v] = 0;
		listv.v[v]->show(VERTEX_MORE_COLOR[components]);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText(listv.v[v]->name);
		printText(",");
		
	} while (v != stop);
	deleteText(",");
	printText(") ");
}
void continueHamilton(bool &continueRun)
{
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Tiep tuc tim kiem Y/N ? : ");
	fflush(stdin);
	while (1)
	{
		if (kbhit())
		{
			if (toupper(getch()) == 'N')
			{
				continueRun = 0;
				printTextWl("");
				return;
			}
			break;
		}
		delay(DELAY_VALUE);
	}
	drawTextZone();
	drawAllEdges();
	listv.showAll(VERTEX_COLOR);
}
void recursiveHamilton(int u, int *path, bool &continueRun)
{
	for (int v = 0; v < listv.num; ++v)
		if (trace[v] != 1 && adjaGraph[path[u - 1]][v] != NO_EDGE_VALUE)
		{
			path[u] = v;
			if (u < listv.num - 1)
			{
				trace[v] = 1;
				if (continueRun) recursiveHamilton(u + 1, path, continueRun);
				trace[v] = 0;
			}
			else 
			{
				resultHamilton(path);
				continueHamilton(continueRun);
			}
		}
}
void resultHamilton(int *path)
{
	int begin = path[0];
	int end = path[listv.num - 1];
	bool isExistCycle = (adjaGraph[end][begin] != NO_EDGE_VALUE);
	setTextPrintStyle(TEXT_COLOR);
	(isExistCycle) ? printText("Chu trinh hamilton: ") : printText("Duong di hamilton: ");
	printText(listv.v[begin]->name);
	listv.v[begin]->show(VERTEX_CHOSE_COLOR);
	for (int i = 1; i < listv.num; ++i)
	{
		end = path[i];
		drawEdge(begin, end, EDGE_VISTED_COLOR);
		listv.v[end]->show(VERTEX_VISTED_COLOR);
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText("->");
		printText(listv.v[end]->name);
		begin = end;
		if (getKey() == KEY_ESC) return;
		delay(delayRunTime);
	}
	if (isExistCycle)
	{
		begin = path[0];
		printText("->");
		printText(listv.v[begin]->name);
		drawEdge(end, begin, EDGE_VISTED_COLOR);
	}
}
inline bool isExistUndirectedEdge(int v1, int v2)
{
	return (adjaGraph[v1][v2] != NO_EDGE_VALUE || adjaGraph[v2][v1] != NO_EDGE_VALUE);
}
inline bool isExistDirectedEdge(int v1, int v2)
{
	return (adjaGraph[v1][v2] != NO_EDGE_VALUE);
}
bool dfsToCheckConnected(bool (*checkEdge)(int , int ), int start, int stop)
{
	setArrayTo(trace, listv.num, 0);
	stack s;
	s.push(start);
	trace[start] = 1;
	int numOfCheckedVertex(0);
	while (!s.isEmpty())
	{
		start = s.pop();
		if (start == stop) return 1;
		++numOfCheckedVertex;
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && checkEdge(start, i))
			{
				trace[i] = 1;
				s.push(i);
			}
	}
	return (numOfCheckedVertex == listv.num);
}
void dfsToCheckKnot(int start, int stop, bool *mark)
{
	trace[start] = 1;
	if (start == stop) // found path start->stop
		for (int i = 0; i < listv.num; ++i) // update mark
			mark[i] = trace[i] && mark[i];
	else
	{
		for (int i = 0; i < listv.num; ++i)
			if (trace[i] == 0 && adjaGraph[start][i] != NO_EDGE_VALUE)
				dfsToCheckKnot(i, stop, mark);
	}
	trace[start] = 0;
}
inline bool isStronglyConnected()
{
	return (tarjanAlgo(0) == 1); // Strong Connected Components = 1
}
inline bool isWeaklyConnected()
{
	return dfsToCheckConnected(isExistUndirectedEdge, 0);
}
int eulerChecker()
{
	int returnValue = NOT_EXIST_EULER;
	int degIn[listv.num];
	int degOut[listv.num];
	calcDegree(degIn, degOut);
	int u(0), v(0), count(0);
	for (int i = 0; i < listv.num; ++i)
		if (degIn[i] != degOut[i])
			(++count == 1) ? u = i : v = i;
	if (isStronglyConnected() && count == 0)
		returnValue = EXIST_EULER;
	else
		if (isWeaklyConnected() && count == 2)
		{
			const int s1 = abs(degOut[u] - degIn[u]);
			const int s2 = abs(degIn[v] - degOut[v]);
			if (s1 == 1 && s2 == 1)
				(degOut[u] < degOut[v]) ? returnValue = v : returnValue = u; // return start's vertex haft euler 
		}
	return returnValue;
}
void copyToMutilGraph(bool gr[][MAX_VERTEX]) // use for euler
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			gr[i][j] = (adjaGraph[i][j] != NO_EDGE_VALUE);
}
bool isNegativeWeight()
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE && adjaGraph[i][j] < 0)
				return 1;
	return 0;
}
void dijkstra(int start, int stop)
{
	const int &NUM = listv.num;
	bool free[NUM];
	double dist[NUM];
	setArrayTo(free, NUM, true);
	setArrayTo(trace, NUM, start);
	setArrayTo(dist, NUM, MAX_EDGE_VALUE);
	dist[start] = 0;
	float d; int u;
	while (1)
	{
		d = MAX_EDGE_VALUE;
		u = -1;
		for (int i = 0; i < NUM; ++i)
			if (free[i] && dist[i] < d)
			{
				d = dist[i];
				u = i;
			}
		if (u == -1 || u == stop) break;
		free[u] = 0;
		for (int i = 0; i < NUM; ++i)
		{
			float weight = adjaGraph[u][i];
			if (free[i] && weight != NO_EDGE_VALUE && dist[i] > d + weight)
			{
				dist[i] = d + weight;
				trace[i] = u;
			}
		}
	}
	showResultPathXY(dist, start, stop);
}
bool isNegativeCycle(double *dist)
{
	const int &NUM = listv.num;
	for (int i = 0; i < NUM; ++i)
		for (int j = 0; j < NUM; ++j)
			if (adjaGraph[j][i] != NO_EDGE_VALUE && dist[j] != MAX_EDGE_VALUE 
				&& dist[i] > dist[j] + adjaGraph[j][i])
				return true;
	return false;
}
bool fordbellman(int start, int stop)
{
	const int &NUM = listv.num;
	double dist[NUM];
	setArrayTo(trace, NUM, start);
	for (int i = 0; i < NUM; ++i)
		dist[i] = (adjaGraph[start][i] == NO_EDGE_VALUE) ? MAX_EDGE_VALUE : adjaGraph[start][i];
	dist[start] = 0;
	for (int k = 1; k < NUM - 1; ++k)
	{
		bool stop = 1;
		for (int i = 0; i < NUM; ++i)
		{
			if (i == start) continue;
			for (int j = 0; j < NUM; ++j)
			{
				if (i == j) continue;
				double weight = adjaGraph[j][i];
				if (weight != NO_EDGE_VALUE && dist[i] > dist[j] + weight && dist[j] != NO_EDGE_VALUE)
				{
					dist[i] = dist[j] + weight;
					trace[i] = j;
					stop = 0;
				}
			}
		}
		if (stop) break; // if not update any dist ==> stop
	}
	if (isNegativeCycle(dist)) return false;
	showResultPathXY(dist, start, stop);
	return true;
}
bool numbering(int *degIn, int *order) //Kahns algorithm for Topological Sorting
{
	int const &NUM = listv.num;
	queue q;
	for (int i = 0; i < NUM; ++i)
		if (degIn[i] == 0) q.push(i);
	int u, count(0);
	while (!q.isEmpty())
	{
		u = q.pop();
		order[count++] = u;
		for (int i = 0; i < NUM; ++i)
			if (adjaGraph[u][i] != NO_EDGE_VALUE)
				if (--degIn[i] == 0) q.push(i);
	}
	return (count == NUM);
}
void open()
{

	if (listv.num > 0 && MessageBox(hwnd,"Dang ton tai do thi\
	\nBan co muon xoa va mo do thi moi khong?","Thong bao",
	MB_APPLMODAL | MB_ICONWARNING | MB_YESNO) == IDNO) return;
	OPENFILENAME file;
	char fileName[MAX_PATH] = "\0";
//	_getcwd(fileName, MAX_PATH);
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.lpstrFile = fileName;
	file.nMaxFile = sizeof(fileName);
	file.lpstrFilter = (FILE_FILTER);
	file.nFilterIndex = 1;
	file.hwndOwner = hwnd;
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_READONLY;
	bool error = 0;
	if (GetOpenFileName(&file) == 1)
	{
		while (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
		std::ifstream openFile(fileName);
		int num;
		if ((openFile >> num) && openFile.good())
		{
			listv.clear();
			setMatrixTo(adjaGraph, NO_EDGE_VALUE); //Clear maxtix
			char tmpName[MAX_NAME_LENGTH];
			int x, y; float weight; 
			for (int i = 0; i < num && !error; ++i)
				if (!(openFile >> tmpName >> x >> y)) error = 1;
				else listv.addVertex(tmpName, x, y);
			if (!error)
				while (!openFile.eof())
				{
					if (!(openFile >> x >> y >> weight)) break;
					else adjaGraph[x][y] = weight;
				}
			isSaved = 1;
		}
		else error = 1;
		openFile.close();
	}
	if (error) 
	{
		listv.clear();
		setMatrixTo(adjaGraph, NO_EDGE_VALUE); //Clear maxtix
		MessageBox(hwnd, "LOI DOC FILE!!!", "Loi",  MB_APPLMODAL | MB_ICONERROR);
	}
}
void save()
{
	OPENFILENAME file;
	char fileName[MAX_PATH] = "\0";
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.lpstrFile = fileName;
	file.nMaxFile = sizeof(fileName);
	file.lpstrFilter = (FILE_FILTER);
	file.nFilterIndex = 1;
	file.hwndOwner = hwnd;
	file.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;
	if (GetSaveFileName(&file) == 1)
	{
		if (!strstr(fileName, ".graph")) 
			strcat(fileName, ".graph"); // Add file name extension if it isn't exsit, but be aware !!! 
		std::ofstream saveFile(fileName);
		const int num = listv.num;
		saveFile << num << '\n';
		for (int i = 0; i < num; ++i)
			saveFile << listv.v[i]->name << ' ' << listv.v[i]->x << ' ' << listv.v[i]->y << '\n';
		saveFile << '\n'; // Endl between Vertexs and ListEdge
		for (int i = 0; i < num; ++i)
			for (int j = 0; j < num; ++j)
				if (adjaGraph[i][j] != NO_EDGE_VALUE)
					saveFile << i << ' ' << j << ' ' << adjaGraph[i][j] << '\n';
		saveFile.close();
		isSaved = 1;
	}
}
void quit()
{
	if (!isSaved && listv.num > 0)
	{
		int id = MessageBox(hwnd, "Ban co muon luu do thi lai khong?", "Save file",
								  MB_APPLMODAL | MB_ICONEXCLAMATION | MB_YESNOCANCEL);
		if (id == IDCANCEL) return;
		if (id == IDYES) return save();
	}
	closegraph();
	exit(EXIT_SUCCESS);
}

void drawEdge(int begin, int end, int color)
{
	const int &x1 = listv.v[begin]->x;
	const int &y1 = listv.v[begin]->y;
	const int &x2 = listv.v[end]->x;
	const int &y2 = listv.v[end]->y;
	if (adjaGraph[end][begin] == NO_EDGE_VALUE || begin < end)
		drawArrow(x1, y1, x2, y2, color, adjaGraph[begin][end]);
	else
		drawCurvedLine(x1, y1, x2, y2, color, adjaGraph[begin][end]);
}
void drawAllEdges()
{
	for (int i = 0; i < listv.num; ++i)
		for (int j = 0; j < listv.num; ++j)
			if (adjaGraph[i][j] != NO_EDGE_VALUE)
				drawEdge(i, j, EDGE_COLOR);
}
int chooseVertex(int highLightColor, int skipReset)
{
	drawLimitZone();
	int x, y;
	int newPos(-1), oldPos(-1);
	while (1)
	{
		if (getKey() == KEY_ESC) break;
		newPos = listv.find(mousex(), mousey());
		if (newPos != oldPos)
		{
			if (newPos != -1 && newPos != skipReset) 
				listv.v[newPos]->show(highLightColor);
			if (oldPos != -1 && oldPos != skipReset)
				listv.v[oldPos]->show(VERTEX_COLOR);
			oldPos = newPos;
		}
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (!isInWorkingZone(x, y)) break;
			if (newPos != -1)
			{
				listv.v[newPos]->show(highLightColor);
				return newPos;
			}
		}
		delay(DELAY_VALUE);
	}
	return -1;
}
bool chooseStartVertex(int &start, const char *text1, const char *text2)
{
	setTextPrintStyle(TEXT_COLOR);
	printText(text1);
	start = chooseVertex(VERTEX_CHOOSING_COLOR);
	if (start == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printText(listv.v[start]->name);
	printTextWlb(text2);
	return 1;
	
}
bool chooseTwoVertices(int &start, int &stop)
{
	setTextPrintStyle(TEXT_COLOR);
	printText("Chon dinh xuat phat: ");
	start = chooseVertex(VERTEX_CHOOSING_COLOR);
	if (start == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl(listv.v[start]->name);
	listv.v[start]->show(VERTEX_CHOSE_COLOR);
	setTextPrintStyle(TEXT_COLOR);
	printText("Chon dinh ket thuc: ");
	stop = chooseVertex(VERTEX_CHOOSING_COLOR, start);
	if (stop == -1) return 0;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl(listv.v[stop]->name);
	listv.v[stop]->show(VERTEX_CHOSE_COLOR);
	if (start == stop)
	{
		listv.v[stop]->show(VERTEX_COLOR);
		return 0;
	}
	return 1;
}
bool isEmptyGraph()
{
	if (listv.num == 0)
	{
		MessageBox(hwnd, "Do thi rong", "Loi", MB_APPLMODAL | MB_ICONERROR);
		return 1;
	}
	return 0;
}
void adjustSpeed(char key)
{
	if (key == KEY_LEFT)
		delayRunTime = (delayRunTime < MAX_SPEED) ? delayRunTime + 100 : MAX_SPEED;
	else if (key == KEY_RIGHT)
		delayRunTime = (delayRunTime > 100) ? delayRunTime - 100 : 0;
	showSpeed();
}
char getKey()
{
	if (kbhit())
	{
		char c = getch();
		switch (c)
		{
			case KEY_ESC:
				return KEY_ESC;
			case ARROW_KEY:
				c = getch();
				adjustSpeed(c);
				return c;
			case KEY_Q:
				return KEY_Q;
			case KEY_LQ:
				return KEY_Q;
			default:
				return KEY_NULL;
		}
	}
	return KEY_NULL;
}
void showResultStack(stack &s)
{
	int v, u = s.pop();
	setTextPrintStyle(TEXT_COLOR);
	printText(listv.v[u]->name);
	listv.v[u]->show(VERTEX_CHOSE_COLOR);
	while (!s.isEmpty())
	{
		v = s.pop();
		setTextPrintStyle(TEXT_HIGHTLIGHT_COLOR);
		printText("->");
		printText(listv.v[v]->name);
		drawEdge(u, v, EDGE_VISTED_COLOR);
		listv.v[v]->show(VERTEX_VISTED_COLOR);
		u = v;
		if (getKey() == KEY_ESC) return;
		delay(delayRunTime);
	}
}
void showResultPathXY(double dist[], int start, int stop)
{
	setTextPrintStyle(TEXT_COLOR);
	if (dist[stop] == MAX_EDGE_VALUE)
		printText("Khong ton tai duong di.");
	else
	{
		printText("Tong trong so: ");
		printTextWl(dist[stop]);
		printText("Duong di ngan nhat: ");
		stack s;
		while (stop != start)
		{
			s.push(stop);
			stop = trace[stop];
		}
		s.push(start);
		return showResultStack(s);
	}
}
void setTextPrintStyle(int color)
{
//	setusercharsize(9, 10, 9, 10);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
	setbkcolor(BACKGROUND_COLOR);
	setcolor(color);
	settextjustify(LEFT_TEXT, TOP_TEXT);
}
bool getInputWeight(float &res)
{
	char str[10];
	getInputChar(str, 10, inputFloat);
	if (!isFloat(str)) return 0;
	res = roundf(toFloat(str) * 100) / 100;
	if (res > MAX_WEIGHT || res < MIN_WEIGHT)
	{
		char msg[70]; char w[10];
		strcpy(msg, "Trong so khong cho phep.\nTrong so >= ");
		convertToChar(MIN_WEIGHT, w);
		strcat(msg, w);
		strcat(msg, " & Trong so <= ");
		convertToChar(MAX_WEIGHT, w);
		strcat(msg, w);
		MessageBox(hwnd, msg, "Loi", MB_APPLMODAL | MB_ICONERROR);
		return 0;
	}
	return 1;
}
bool getInputChar(char *str, int max, bool (*checkKey)(char key))
{
	setTextPrintStyle(BLUE);
	int i = 0; str[0] = '\0';
	char key[2] = {'\0', '\0'};
	while (i < max)
	{
		if (kbhit())
		{
			key[0] = getch();
			if (key[0] == KEY_ESC || key[0] == KEY_ENTER) break;
			if (key[0] == KEY_BACKSPACE && i > 0) {--i; key[0] = str[i]; deleteText(key); str[i] = '\0';}
			else if (checkKey(key[0])) {strcat(str, key); ++i; printText(key);}
		}
		if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
		delay(DELAY_VALUE);
	}
	return (i > 0);
}
void deleteText(const char* str)
{
	if (xCursor <= xCURSOR) return;
	const int currentColor = getcolor();
	setTextPrintStyle(BACKGROUND_COLOR);
	const int tw = textwidth(str);
	xCursor -= tw;
	printText(str);
	xCursor -= tw;
	setTextPrintStyle(currentColor);
}
void printText(const char *str)
{
	int const tw = textwidth(str);
	if (xCursor + tw >= tRIGHT)
	{
		xCursor = xCURSOR;
		yCursor += TEXTHIGHT;
	}
	if (yCursor > tBOTTOM - TEXTHIGHT)
	{
		drawTextZone();
		xCursor = xCURSOR;
		yCursor = yCURSOR;
		setTextPrintStyle(TEXT_COLOR);
	}
	outtextxy(xCursor, yCursor, str);
	xCursor += tw;
}
void printText(float value)
{
	char str[MAX_INPUT];
	convertToChar(value, str);
	printText(str);
}
template <typename Type>
void printTextWl(Type s)
{
	printText(s);
	xCursor = xCURSOR;
	yCursor += TEXTHIGHT;
}
template <typename Type>
void printTextWlb(Type s)
{
	xCursor = xCURSOR;
	yCursor += TEXTHIGHT;
	printText(s);
}
void addVertex()
{
	drawLimitZone();
	if (listv.num == MAX_VERTEX)
	{
		char msg[45], num[3];
		strcpy(msg, "Qua so luong dinh cho phep MAX_VERTEX = ");
		convertToChar(MAX_VERTEX, num);
		strcat(msg, num);
		MessageBox(hwnd, msg, "Loi", MB_APPLMODAL | MB_ICONERROR);
	}
	int x, y;
	setTextPrintStyle(TEXT_COLOR);
	printText("Click chuot de them dinh.");
	while (listv.num < MAX_VERTEX)
	{
		if (getKey() == KEY_ESC) break;
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (listv.find(x, y) != -1)
			{
				MessageBox(hwnd, "Trung dinh da co\nVui long chon lai.", "Loi",
							MB_APPLMODAL | MB_ICONERROR);
				continue;
			}
			if (isInLimitZone(x, y))
			{
				listv.addVertex(x, y);
				drawMatrixZone();
				isSaved = 0;
			}
			else break;
		}
		delay(DELAY_VALUE);
	}
}
void addEdges()
{
	if (isEmptyGraph()) return;
	int begin, end, oldEnd = -1;
	float weight;
	setTextPrintStyle(TEXT_COLOR);
	printText("Noi hai dinh de them/xoa cung.");
	while (1)
	{
		begin = chooseVertex(VERTEX_CHOOSING_COLOR);
		if (begin == -1) break;
		int x = listv.v[begin]->x;
		int y = listv.v[begin]->y;
		if (ismouseclick(WM_LBUTTONUP)) clearmouseclick(WM_LBUTTONUP);
		while (!ismouseclick(WM_LBUTTONUP))
		{
			setactivepage(1 - getactivepage());
			initScreen();
			drawLimitZone();
			drawAllEdges();
			listv.showAll();
			listv.v[begin]->show(VERTEX_CHOSE_COLOR);
			menuButton[ADD_EDGE_MENU].showChoseButton();
			showButtonIcon(menuButton, ADD_EDGE_MENU);
			end = listv.find(mousex(), mousey());
			drawArrow(x, y, mousex(), mousey(), EDGE_HIGHTLIGHT_COLOR, 0);
			setvisualpage(getactivepage());
			if (oldEnd != -1 && oldEnd != end && oldEnd != begin)
				listv.v[oldEnd]->show(VERTEX_COLOR);
			if (end != begin && end != -1 && end != oldEnd)
				listv.v[end]->show(VERTEX_CHOOSING_COLOR);
			oldEnd = end;
			if (!isInWorkingZone(mousex(), mousey())) break;
			delay(DELAY_VALUE);
		}
		if (end == -1 || end == begin)
		{
			refreshGraph(ADD_EDGE_MENU);
			listv.v[begin]->show(VERTEX_COLOR);
			continue;
		}
		listv.v[end]->show(VERTEX_CHOSE_COLOR);
		setvisualpage(getactivepage());
		adjaGraph[begin][end] = DEFAULT_WEIGHT;
		refreshGraph(ADD_EDGE_MENU);
		drawEdge(begin, end, EDGE_HIGHTLIGHT_COLOR);
		setTextPrintStyle(TEXT_COLOR);
		printText("Nhap trong so (xoa cung nhap '-') cung ");
		printText(listv.v[begin]->name);
		printText("->");
		printText(listv.v[end]->name);
		printText(": ");
		if (getInputWeight(weight)) adjaGraph[begin][end] = weight;
		else adjaGraph[begin][end] = NO_EDGE_VALUE;
		isSaved = 0;
		refreshGraph(ADD_EDGE_MENU);
		listv.v[begin]->show(VERTEX_COLOR);
		listv.v[end]->show(VERTEX_COLOR);
	}
}
void renameVertex()
{
	if (isEmptyGraph()) return;
	int choose;
	while (1)
	{
		if (chooseStartVertex(choose, "Chon dinh can doi ten: ", "Nhap ten moi cho dinh "))
		{
			printText(listv.v[choose]->name);
			printText(": ");
			listv.v[choose]->show(VERTEX_CHOSE_COLOR);
			char name[MAX_NAME_LENGTH];
			if (getInputChar(name, MAX_NAME_LENGTH - 1, inputAscii) && !listv.isExist(name))
			{
				listv.updateCurrentName(name);
				listv.v[choose]->clearName();
				strcpy(listv.v[choose]->name, name);
				drawMatrixZone();
				isSaved = 0;
			}
			else MessageBox(hwnd, "Trung ten hoac nhap sai", "Loi", MB_APPLMODAL | MB_ICONERROR);
			listv.v[choose]->show(VERTEX_COLOR);
			printTextWl("");
		} else break;
	}
}
void deleteVertex()
{
	if (isEmptyGraph()) return;
	while (listv.num > 0)
	{
		setTextPrintStyle(TEXT_COLOR);
		printText("Chon dinh can xoa: ");
		int choose = chooseVertex(VERTEX_DELETE_COLOR);
		if (choose == -1) break;
		setTextPrintStyle(VERTEX_DELETE_COLOR);
		printText(listv.v[choose]->name);
		removeVertex(choose);
		listv.deleteVertex(choose); // --num is in here
		refreshGraph(DELETEVE_MENU);
		isSaved = 0;
		if (listv.num == 0)
			listv.clear();
	}
}
void moveVertex()
{
	if (isEmptyGraph()) return;
	int x, y;
	setTextPrintStyle(TEXT_COLOR);
	printTextWl("Dung thao tac keo/tha dinh de di chuyen tung dinh");
	printText("hoac Ctr + keo/tha de di chuyen toan bo do thi.");
	while (1)
	{
		int choose = chooseVertex(VERTEX_CHOOSING_COLOR);
		if  (choose == -1) break;
		if (ismouseclick(WM_LBUTTONUP)) clearmouseclick(WM_LBUTTONUP);
		isSaved = 0;
		listv.v[choose]->show(VERTEX_CHOSE_COLOR);
		while (!ismouseclick(WM_LBUTTONUP))
		{
			if (ismouseclick(WM_MOUSEMOVE))
			{
				getmouseclick(WM_MOUSEMOVE, x, y);
				if (!isInLimitZone(x, y)) continue;
				if (GetKeyState(VK_CONTROL) < 0) // Crt + move all vertices
				{
					int dx = x - listv.v[choose]->x;
					int dy = y - listv.v[choose]->y;
					for (int i = 0; i < listv.num; ++i)
					{
						listv.v[i]->x += dx;
						listv.v[i]->y += dy;
						if (!isInLimitZone(listv.v[i]->x, listv.v[i]->y))
						{
							for (int j = i; j >= 0; --j)
							{
								listv.v[j]->x -= dx;
								listv.v[j]->y -= dy;
							}
							break;
						}
					}
				} else listv.v[choose]->setCoordinate(x, y); // Move single vertex
				setactivepage(1 - getactivepage());
				initScreen();
				drawLimitZone();
				drawAllEdges();
				listv.showAll();
				menuButton[MOVEVE_MENU].showChoseButton();
				showButtonIcon(menuButton, MOVEVE_MENU);
				setvisualpage(getactivepage());
			}
			delay(DELAY_VALUE);
		}
		listv.v[choose]->show(VERTEX_COLOR);
		setvisualpage(getactivepage());
	}
}
void cleanGraph()
{
	if (isEmptyGraph()) return;
	if (MessageBox(hwnd, "Ban co chac khong?", "Xoa do thi",
		MB_APPLMODAL| MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		listv.clear();
		setMatrixTo(adjaGraph, NO_EDGE_VALUE);
		refreshGraph(CLEAN_GRAPH_MENU);
		isSaved = 1;
	}
}
void help()
{
	MessageBox(hwnd, "Chuong trinh demo Do thi co huong co trong so.\n"
					"Su dung:\n"
					"Phim <ESC> : Huy chuc nang.\n"
					"Phim <Q>/<q> : Thoat chuong trinh.\n"
					"Phim <LEFT>/<RIGHT> : Chinh toc do giam/tang.\n"
					"\nTac gia:\n"
					"Nguyen Gia Huy (giahuyng98@gmail.com) PTITHCM\n",
				 	"Help", MB_APPLMODAL | MB_ICONINFORMATION);
}
int findButton(int x, int y)
{
	for (int i = 0; i < NUM_OF_MENU; ++i)
		if (menuButton[i].isButtonClick(x, y))
			return i;
	return -1;
}
void backToMenu()
{
	setTextPrintStyle(TEXT_COLOR);
	printTextWlb("Nhan phim bat ky hoac click chuot de tiep tuc.");
	if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
	fflush(stdin);
	while (1)
	{
		if (kbhit()) break;
		if (ismouseclick(WM_LBUTTONDOWN)) break;
		delay(DELAY_VALUE);
	}
	if (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
	fflush(stdin);
}
void switchMenuItem(int chose)
{
	switch (chose)
	{
		case DFS_MENU:				return DFS();
		case BFS_MENU: 				return BFS();
		case PATHXY_MENU: 			return pathXY();
		case CUT_VERTEX_MENU:	 	return cutVertex();
		case KNOT_VERTEX_MENU: 		return knotVertex();
		case BRIDGE_EDGE_MENU: 		return bridgeEdge();
		case HAMILTON_MENU: 		return hamilton();
		case EULER_MENU: 			return euler();
		case TOPO_SORT_MENU: 		return topoSort();
		case COLOR_GRAPH_MENU: 		return colorGraph();
		case SCC_MENU:				return SCC();
		case OPEN_MENU: 			return open();
		case SAVE_MENU:				return save();
		case QUIT_MENU: 			return quit();
		case ADD_VERTEX_MENU:	 	return addVertex();
		case ADD_EDGE_MENU: 		return addEdges();
		case RENAME_VERTEX_MENU: 	return renameVertex();
		case DELETEVE_MENU: 		return deleteVertex();
		case MOVEVE_MENU: 			return moveVertex();
		case CLEAN_GRAPH_MENU: 		return cleanGraph();
		case HELP_MENU: 			return help();
		default: return;
	}
}
void refreshScreen()
{
	setactivepage(1 - getactivepage());
	initScreen();
	drawAllEdges();
	listv.showAll(VERTEX_COLOR);
	setvisualpage(getactivepage());
}
void refreshGraph(int mPos)
{
	setactivepage(1 - getactivepage());
	drawWorkingZone();
	drawMatrixZone();
	drawTextZone();
	showAllButtons();
	drawAllEdges();
	listv.showAll();
	menuButton[mPos].showChoseButton();
	showButtonIcon(menuButton, mPos);
	setvisualpage(getactivepage());
}
inline void showChoseButton(int pos)
{
	if (pos >= ADD_VERTEX_MENU) refreshScreen();
	menuButton[pos].showChoseButton();
	showButtonIcon(menuButton, pos);
}
inline void showHightLightButton(int pos)
{
	menuButton[pos].showHightLightButton();
	if (pos >= ADD_VERTEX_MENU) menuButton[pos].showButtonHint();
	showButtonIcon(menuButton, pos);
}
inline void showNormalButton(int pos)
{
	if (pos >= ADD_VERTEX_MENU) refreshScreen();
	menuButton[pos].showNormalButton();
	showButtonIcon(menuButton, pos);
}
inline void update(int &oldPos, int &newPos, int x, int y)
{
	newPos = findButton(x, y);
	if (newPos != oldPos)
	{
		if (oldPos != -1) showNormalButton(oldPos);
		if (newPos != -1) showHightLightButton(newPos);
		oldPos = newPos;
	}
}
void menu()
{
	int x, y;
	int newPos(-1), oldPos(-1);
	while (1)
	{
		if (getKey() == KEY_Q) quit();
		if (ismouseclick(WM_MOUSEMOVE))
		{
			getmouseclick(WM_MOUSEMOVE, x, y);
			update(oldPos, newPos, x, y);
		}
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			clearmouseclick(WM_LBUTTONDOWN);
			if (newPos != -1)
			{
				showChoseButton(newPos);
				switchMenuItem(newPos);
			}
			oldPos = -1;
			refreshScreen();
			update(oldPos, newPos, mousex(), mousey());
		}
		delay(DELAY_VALUE);
	}
}
