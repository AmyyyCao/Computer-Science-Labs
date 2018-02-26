//  Copyright © 2018 Song You. All rights reserved.

#include <stdio.h>
#include <stdbool.h>


char board[][26] = {};

void initializeBoard(int n) {
    
    for (int i = 0; i <= 26; i++) {
        for (int j = 0; j <= 26; j++) {
            board[i][j] = 'U';
        }
    }
    
    //prepares the initial setup
    board[(n/2)-1][(n/2)-1] = 'W';
    board[n/2][n/2] = 'W';
    board[(n/2)-1][n/2] = 'B';
    board[n/2][(n/2)-1] = 'B';
}


//"board" is the 2D array representing the current board state, n is the board dimensions
//this only PRINTS the board
void printBoard(char board[][26], int n) {
    
    char letter = 'a';
    printf("  ");
    
    for (int i = 0; i < n; i++) {
        printf("%c", letter);
        letter += 1;
    }

    letter = 'a';
    for (int i = 0; i < n; i++) {
        printf("\n");
        printf("%c ", letter);
        letter += 1;
        for (int j = 0; j < n; j++) {
            printf("%c", board[i][j]);
        }
    }
    printf("\n");
}


//checks whether (row, col) is a legal position for a tile of colour.
//deltaRow and deltaCol take on values of -1, 0, and 1. They cannot both be 0.
//The helper function will be called 8 times to search the lines in the 8 possible directions.
bool checkLegalInDirection(char board[][26], int n, char row, char col,
                           char colour, int deltaRow, int deltaCol);

//printf("Available moves for %c:\n", colour);

//    while (row <= n && col <= n) {
//        if () {
//            printf("%c%c", board[i][i]);
//        }
//        row += deltaRow;
//        col += deltaCol;
//    }
//}



//prepares initial board configuration based on user input
void boardConfig(int n) {
    char colour=0, row, col;
    
    scanf(" %c%c%c", &colour, &row, &col);
    
    while (colour != '!') { //exits while loop if !!! command is an input
        row = (int)row-97; //char conversion to ascii value
        col = (int)col-97;
        board[row][col] = colour;
        scanf(" %c%c%c", &colour, &row, &col);
    }
    printBoard(board, n);
    
    checkLegalInDirection(board, n, row, col,
                          colour, 1, -1);
    checkLegalInDirection(board, n, row, col,
                          colour, 1, 0);
    checkLegalInDirection(board, n, row, col,
                          colour, 1, 1);
    checkLegalInDirection(board, n, row, col,
                          colour, 0, -1);
    checkLegalInDirection(board, n, row, col,
                          colour, 0, 1);
    checkLegalInDirection(board, n, row, col,
                          colour, -1, -1);
    checkLegalInDirection(board, n, row, col,
                          colour, -1, 0);
    checkLegalInDirection(board, n, row, col,
                          colour, -1, 1);
}


//checks whether the specified (row, col) lies within the board dimensions.
bool positionInBounds(int n, char row, char col);


//makes a move, changing 'unoccupied' to a color
void takeTurn(int n) {
    char colour=0, row, col;

    scanf(" %c%c%c", &colour, &row, &col);
    
    while (colour == 'B' || colour == 'W') {
        row = (int)row-97; //char conversion to ascii value
        col = (int)col-97;
        
        positionInBounds(n, row, col);

        board[row][col] = colour;
    }
    printBoard(board, n);
}



//main function
int main(int argc, const char * argv[]) {
    int boardSize;
    
    printf("Enter the board dimension: ");
    scanf("%d", &boardSize);
    
    initializeBoard(boardSize);
    printBoard(board, boardSize);
    
    printf("Enter board configuration:\n");
    boardConfig(boardSize);
    
    printf("Enter a move:\n");
    
    takeTurn(boardSize);
    
    return 0;
}
