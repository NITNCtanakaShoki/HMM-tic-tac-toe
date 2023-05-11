#include <stdio.h>
#include <string.h>

char* NONE = " ";
char* MARU = "○";
char* BATU = "×";

void printBoard(char* board[9]);
char* judge(char* board[9]);
int cpuPutPosition(char* board[9]);
char* toggleTurn(const char* turn);
int isFull(char* board[9]);

int main(int argc, char** argv) {
    int isCPU = argc == 2;
    int isCPUTurn = isCPU && strcmp(argv[1], "-k") == 0;
    char* board[9] = {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
    char* turn = MARU;
    printBoard(board);
    while (!isFull(board) && judge(board) == NONE) {

        if (isCPU && isCPUTurn) {
            int position = cpuPutPosition(board);
            board[position] = turn;
            turn = toggleTurn(turn);
            printf("CPUが%dに置きました。\n", position + 1);
            printBoard(board);
            isCPUTurn = 0;
            continue;
        }

        int position;
        printf("%sの番です。どこに置きますか？\n", turn);
        scanf("%d", &position);
        position -= 1;
        if (board[position] != NONE) {
            printf("そこには置けません。\n");
            continue;
        }
        board[position] = turn;
        turn = toggleTurn(turn);
        isCPUTurn = isCPU;
        printBoard(board);
    }
    char* result = judge(board);
    if (result == NONE) {
        printf("引き分けです。\n");
    } else {
        printf("%sの勝ちです！\n", result);
    }
    return 0;
}

int isFull(char* board[9]) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == NONE) {
            return 0;
        }
    }
    return 1;
}

char* toggleTurn(const char* turn) {
    return turn == MARU ? BATU : MARU;
}

void printBoard(char* board[9]) {
    printf(" %s | %s | %s \n", board[0], board[1], board[2]);
    printf("-----------\n");
    printf(" %s | %s | %s \n", board[3], board[4], board[5]);
    printf("-----------\n");
    printf(" %s | %s | %s \n", board[6], board[7], board[8]);
}

char* judge(char* board[9]) {
    for (int i = 0; i < 3; i++) {
        if (board[i * 3] != NONE && board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
            return board[i * 3];
        }
        if (board[i] != NONE && board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            return board[i];
        }
    }
    if (board[0] != NONE && board[0] == board[4] && board[4] == board[8]) {
        return board[0];
    }
    if (board[2] != NONE && board[2] == board[4] && board[4] == board[6]) {
        return board[2];
    }
    return NONE;
}

int cpuPutPosition(char* board[9]) {
    if (board[4] == NONE) {
        return 4;
    }

    // Check for winning move
    for (int i = 0; i < 9; i++) {
        if (board[i] == NONE) {
            char* tempBoard[9];
            memcpy(tempBoard, board, sizeof(char*) * 9);
            tempBoard[i] = BATU;

            if (judge(tempBoard) == BATU) {
                return i;
            }
        }
    }

    // Check for blocking move
    for (int i = 0; i < 9; i++) {
        if (board[i] == NONE) {
            char* tempBoard[9];
            memcpy(tempBoard, board, sizeof(char*) * 9);
            tempBoard[i] = MARU;

            if (judge(tempBoard) == MARU) {
                return i;
            }
        }
    }

    // Play in corners if available
    if (board[0] == NONE && board[8] == NONE) {
        if (board[2] == NONE) {
            return 2;
        }
        if (board[6] == NONE) {
            return 6;
        }
    }
    if (board[2] == NONE && board[6] == NONE) {
        if (board[0] == NONE) {
            return 0;
        }
        if (board[8] == NONE) {
            return 8;
        }
    }
    int corners[4] = {0, 2, 6, 8};
    for (int i = 0; i < 4; i++) {
        if (board[corners[i]] == NONE) {
            return corners[i];
        }
    }

    // Play in center edges if available
    int edges[4] = {1, 3, 5, 7};
    for (int i = 0; i < 4; i++) {
        if (board[edges[i]] == NONE) {
            return edges[i];
        }
    }

    // This line should never be reached, but added to avoid a warning.
    return 0;
}