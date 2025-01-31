#include <stdio.h>

#define N 9

void findAvailableNumbers(int row, int column, int sudokuBoard[N][N], int availableNumbers[N]);
void resetAvailableNumbers (int availableNumbers[N]);
int tryAvailableNumbers(int row, int column, int sudokuBoard[N][N], int availableNumbers[N]);
void displayBoardState(int sudokuBoard[N][N]);

int main() {
    
    int availableNumbers[N];
    int sudokuBoard[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    tryAvailableNumbers(0, 0, sudokuBoard, availableNumbers);

    displayBoardState(sudokuBoard);
    
    return 0;
}

void findAvailableNumbers(int row, int column, int sudokuBoard[N][N], int availableNumbers[N]) {
    
    for(int i = 0; i < N; i++) {
        if(sudokuBoard[row][i] != 0) {
            availableNumbers[sudokuBoard[row][i] - 1] = 0;
        }
        if(sudokuBoard[i][column] != 0) {
            availableNumbers[sudokuBoard[i][column] - 1] = 0;
        }
    }
    
    int currentSquare = (row / 3) * 3 + (column / 3);
    int rowOffset = (currentSquare / 3) * 3;
    int columnOffset = (currentSquare % 3) * 3;

    for (int row = 0; row < 3; row++) {
        for(int column = 0; column < 3; column++) {
            if (sudokuBoard[row + rowOffset][column + columnOffset] != 0) {
                availableNumbers[sudokuBoard[row + rowOffset][column + columnOffset] - 1] = 0;
            }
        }
    }
}    

void resetAvailableNumbers (int availableNumbers[N]) {
    for (int i = 0; i < N; i++) {
        availableNumbers[i] = 1;
    }
}

int tryAvailableNumbers(int row, int column, int sudokuBoard[N][N], int availableNumbers[N]) {

    int nextRow;
    int nextColumn;

    if (row == N) return 1;

    if (column == 8) {
        nextRow = row + 1;
        nextColumn = 0;
    } else {
        nextRow = row;
        nextColumn = column + 1;
    }

    if (sudokuBoard[row][column] != 0) {
        return tryAvailableNumbers(nextRow, nextColumn, sudokuBoard, availableNumbers);
    }

    for (int i = 0; i < N; i++) {
        resetAvailableNumbers(availableNumbers);
        findAvailableNumbers(row, column, sudokuBoard, availableNumbers);
        if (availableNumbers[i] != 0) {
            sudokuBoard[row][column] = i+1;
            if (tryAvailableNumbers(nextRow, nextColumn, sudokuBoard, availableNumbers)) {
                return 1;
            }
        }
    }
    sudokuBoard[row][column] = 0;
    
    for(int i = 0; i < N; i++) {
        printf("%d", availableNumbers[i]);
    }

    displayBoardState(sudokuBoard);
    return 0;
}

void displayBoardState(int board[N][N]) {
    int lastColumnIndex = N - 1;

    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < lastColumnIndex; j++) {
            if (((j + 1) % 3) != 0) printf("%c ", (board[i][j] == 0 ? ' ' : board[i][j] + '0'));
            else printf("%c || ", (board[i][j] == 0 ? ' ' : board[i][j] + '0'));
        }
        if (((i + 1) % 3) != 0 || i == N - 1) printf("%c\n", board[i][lastColumnIndex] == 0 ? ' ' : board[i][lastColumnIndex] + '0');
        else printf("%c\n=======================\n", board[i][lastColumnIndex] == 0 ? ' ' : board[i][lastColumnIndex] + '0');
    }
    printf("\n");
}
