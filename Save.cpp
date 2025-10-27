#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "Globals.h"
#include "View.h"
using namespace std;

// Lưu game
void SaveGame(const string& filename, GameRule rule, int result)
{
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Khong the mo file de luu!" << endl;
        return;
    }

    // Ghi thời gian
    time_t now = time(0);
    tm* ltm = localtime(&now);
    fout << "Thoi gian luu: "
         << put_time(ltm, "%H:%M:%S %d/%m/%Y") << "\n";

    // Ghi luật chơi, lượt hiện tại, trạng thái thắng thua
    fout << (int)rule << "\n";     // 0: Freestyle, 1: Standard, 2: Blocked Two Ends
    fout << _TURN << "\n";         // true/false -> lượt đi (X/O)
    fout << result << "\n";        // -1: X thắng, 1: O thắng, 0: hòa, 2: đang chơi

    // Ghi bàn cờ
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (_A[i][j].c == -1) fout << 'X';
            else if (_A[i][j].c == 1) fout << 'O';
            else fout << '.';
        }
        fout << "\n";
    }

    fout.close();
    cout << "Da luu game vao " << filename << " luc "
         << put_time(ltm, "%H:%M:%S %d/%m/%Y") << endl;
}
