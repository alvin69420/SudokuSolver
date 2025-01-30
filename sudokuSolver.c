#include <stdio.h>

#define N 9

void findAvailableNumbers(int row, int column, int sudokuBoard[N][N], int availableNumbers[N]);

void resetAvailableNumbers (int availableNumbers[N])//TODO

int main() {
    
    int availableNumbers[N] = {1};
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
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (sudokuBoard[i][j] != 0) {
                findAvailableNumbers(i, j, sudokuBoard, availableNumbers);
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        availableNumbers[i] = 1;
    }
    
    findAvailableNumbers(7,7, sudokuBoard, availableNumbers);
    
    for (int i = 0; i < N; i++) {
        printf("%d", availableNumbers[i]);
    }
    
    return 0;
}

int* findAvailableNumbers(int row, int column, int sudokuBoard[N][N], int availableNumbers[N]) {
    
    int currentSquare = 0;
    
    for(int i = 0; i < N; i++) {
        if(sudokuBoard[row][i] != 0) {
            availableNumbers[sudokuBoard[row][i] - 1] = 0;
        }
        if(sudokuBoard[i][column] != 0) {
            availableNumbers[sudokuBoard[i][column] - 1] = 0;
        }
    }
    
    currentSquare = (row / 3) * 3 + (column / 3);
    
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
