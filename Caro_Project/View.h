#pragma once
#ifndef View_h
#define View_h
#include <Windows.h>
#include <iostream>
#include <conio.h>

#define BOARD_SIZE 12 
#define LEFT 
#define TOP

using namespace std;

void FixConsoleWindow();
void GotoXY(int x, int y);
void DrawBoard(int pSize);
int ProcessFinish(int pWhoWin);
int AskContinue();
#endif



