int TestBoard() {
    // Kiểm tra bàn cờ đầy (hòa)
    bool full = true;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                full = false;
                break;
            }
        }
        if (!full) break;
    }
    if (full) return 0; 

    // Kiểm tra thắng
    auto checkWin = [&](int r, int c, int player) {
        if (player == 0) return false;
        const int dr[4] = {0, 1, 1, -1}; // hướng ngang, dọc, chéo xuống, chéo lên
        const int dc[4] = {1, 0, 1, 1};
        for (int k = 0; k < 4; k++) {
            int count = 1;
            // Đi xuôi
            int rr = r + dr[k], cc = c + dc[k];
            while (rr >= 0 && rr < SIZE && cc >= 0 && cc < SIZE && board[rr][cc] == player) {
                count++; rr += dr[k]; cc += dc[k];
            }
            // Đi ngược
            rr = r - dr[k]; cc = c - dc[k];
            while (rr >= 0 && rr < SIZE && cc >= 0 && cc < SIZE && board[rr][cc] == player) {
                count++; rr -= dr[k]; cc -= dc[k];
            }
            if (count >= 5) return true; // Luật tự do: >=5 là thắng
        }
        return false;
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int p = board[i][j];
            if (p != 0 && checkWin(i, j, p)) {
                return (_TURN == true ? -1 : 1);
            }
        }
    }

    // Không ai thắng, chưa hòa
    return 2;
}
