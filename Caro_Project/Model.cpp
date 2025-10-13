#include "Model.h"
#include "Globals.h"
//các hàm xử lí dữ liệu trò chơi

void ResetData() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			_A[i][j].x = 4 * j + LEFT + 2; 
			_A[i][j].y = 2 * i + TOP + 1; 
			_A[i][j].c = 0; 			
		}
	}
	_TURN = true; _COMMAND = -1;
	_X = _A[0][0].x; _Y = _A[0][0].y; 
}


//int TestBoard()
//{
//		if (<Ma trận đầy>) return 0; 
//		else {
//				if (<tồn tại điều kiện thắng theo luật caro>)
//					7
//					return (_TURN == true ? -1 : 1);
//				Else
//				return 2; 
//		}
//}

//Ham danh dau vao ma tran

int CheckBoard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true) {
					_A[i][j].c = -1;
				}
				else {
					_A[i][j].c = 1;
				}
				return _A[i][j].c;
				
			}
		}
	}
	return 0;
}



