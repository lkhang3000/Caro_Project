#pragma once
#ifndef Model_Standard_h
#define Model_Standard_h
#include <iostream>

using namespace std;

void ResetData();
bool IsFullBoard();
bool IsBlockedTwoEnds(int x, int y, int dx, int dy, int player);
bool CheckWin_BlockedTwoEnds();
int CheckBoard(int pX, int pY);
int TestBoard_Standard();

#endif