// Model.cpp
#include "Model_2ends.h"
#include "Globals.h"

// Reset bàn cờ
void ResetData()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            _A[i][j].x = 4 * j + LEFT + 2;
            _A[i][j].y = 2 * i + TOP + 1;
            _A[i][j].c = 0;
        }
    }
    _TURN = true;   // true: lượt X đi, false: lượt O đi
    _COMMAND = -1;
    _X = _A[0][0].x;
    _Y = _A[0][0].y;
}

// Kiểm tra bàn cờ đầy (dùng chung cho 3 luật luôn)
bool IsFullBoard()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (_A[i][j].c == 0)
                return false;
    return true;
}

// Kiểm tra một hướng có bị chặn 2 đầu
bool IsBlockedTwoEnds(int x, int y, int dx, int dy, int player)
{
    int count = 1;
    int i = x + dx, j = y + dy;

    // Đếm xuôi
    while (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && _A[i][j].c == player)
    {
        count++;
        i += dx;
        j += dy;
    }
    bool blocked1 = (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && _A[i][j].c == -player);

    // Đếm ngược
    i = x - dx;
    j = y - dy;
    while (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && _A[i][j].c == player)
    {
        count++;
        i -= dx;
        j -= dy;
    }
    bool blocked2 = (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && _A[i][j].c == -player);

    return (count >= 5 && !(blocked1 && blocked2));
}

// Kiểm tra thắng cho quân của lượt hiện tại
bool CheckWin_BlockedTwoEnds()
{
    int player = _TURN ? -1 : 1; // -1: lượt X đi, 1: lượt O đi theo CheckBoard
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (_A[i][j].c == player)
            {
                if (IsBlockedTwoEnds(i, j, 1, 0, player)) return true;  // dọc
                if (IsBlockedTwoEnds(i, j, 0, 1, player)) return true;  // ngang
                if (IsBlockedTwoEnds(i, j, 1, 1, player)) return true;  // chéo xuống
                if (IsBlockedTwoEnds(i, j, 1, -1, player)) return true; // chéo lên
            }
        }
    }
    return false;
}

// Kiểm tra bàn cờ tổng hợp (hòa, thắng, chưa ai thắng)
int TestBoard_BlockedTwoEnds()
{
    if (IsFullBoard())
        return 0; // Hòa

    if (CheckWin_BlockedTwoEnds())
        return _TURN ? -1 : 1; // _TURN=true: X vừa đi thắng (-1), _TURN=false: O thắng (1)

    return 2; // Chưa ai thắng
}

//Ham danh dau vao ma tran
int CheckBoard(int pX, int pY)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0)
            {
                if (_TURN == true)
                {
                    _A[i][j].c = -1; // lượt X
                }
                else
                {
                    _A[i][j].c = 1;  // lượt O
                }
                return _A[i][j].c;
            }
        }
    }
    return 0;
}
