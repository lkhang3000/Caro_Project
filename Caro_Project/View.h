#pragma once
#ifndef View_h
#define View_h
#include <Windows.h>
#include <iostream>
#include <conio.h>

#define BOARD_SIZE 12 
const int BOARD_LEFT = 2;
const int BOARD_TOP = 1;

using namespace std;

void FixConsoleWindow();
void GotoXY(int x, int y);
void DrawBoard(int pSize);
int ProcessFinish(int pWhoWin);
int AskContinue();

int mainScreen(int& x, int& y);
void PrintXY(int x, int y, const string& message);
void Cursor(bool is_up, int POSX, int POSY);
#endif



