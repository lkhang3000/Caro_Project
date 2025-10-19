#pragma once
#ifndef Model_2ends_h
#define Model_2ends_h
#include <iostream>
using namespace std;

void ResetData();
bool IsFullBoard();
bool IsBlockedTwoEnds(int x, int y, int dx, int dy, int player);
int TestBoard_BlockedTwoEnds();
bool CheckWin_BlockedTwoEnds();
int CheckBoard(int pX, int pY);
#endif