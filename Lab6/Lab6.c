//  Copyright © 2018 Song You. All rights reserved.

#include <stdio.h>
#include <stdbool.h>



/*------------------------------ 0.0 PROTOTYPES------------------------------*/

void initializeBoard(char board[][26], int n);
void printBoard(char board[][26], int n);
void boardConfig(char board[][26], int n);

bool positionInBounds(int n, int row, int col);

void availableMoves(char board[][26], int n, int colour);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol);


void takeTurn(char board[][26], int n);
void changeColour(char board[][26], int n, int i, int j, int colour);
bool changeTileColour(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol);

int main(int argc, const char * argv[]);



/*------------------------------ 1.0 FUNCTIONS ------------------------------*/

/*------------------------------ 1.1 Initialize Board ------------------------------*/

void initializeBoard(char board[][26], int n) {
    
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


/*------------------------------ 1.2 Print Board ------------------------------*/
/* "board" is the 2D array representing the current board state,
 n is the board dimensions this only PRINTS the board */

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


/*------------------------------ 1.3 Board Configuration ------------------------------*/
/* prepares initial board configuration based on user input */

void boardConfig(char board[][26], int n) {
    char colour=0, row, col;
    
    scanf(" %c%c%c", &colour, &row, &col);
    
    while (colour != '!') { //exits while loop if !!! command is an input
        row = (int)row-97; //char conversion to ascii value
        col = (int)col-97;
        board[row][col] = colour;
        scanf(" %c%c%c", &colour, &row, &col);
    }
    printBoard(board, n);
}


/*------------------------------ 1.4 Position In Bounds ------------------------------*/
/* checks whether the specified (row, col) lies within the board dimensions. */

bool positionInBounds(int n, int row, int col) {
    if ((row >= 0)||(col >= 0)||(row < n)||(col < n)) {
        return true;
    }
    else {
        return false;
    }
    
}


/*------------------------------ 1.5 Check Available Moves ------------------------------*/
/* Cycles through all 8 directions of the checkLegalInDirection function */

void availableMoves(char board[][26], int n, int colour) {
    
    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            
            checkLegalInDirection(board, n, i, j, colour, 1, -1);
            checkLegalInDirection(board, n, i, j, colour, 1, 0);
            checkLegalInDirection(board, n, i, j, colour, 1, 1);
            checkLegalInDirection(board, n, i, j, colour, 0, -1);
            checkLegalInDirection(board, n, i, j, colour, 0, 1);
            checkLegalInDirection(board, n, i, j, colour, -1, -1);
            checkLegalInDirection(board, n, i, j, colour, -1, 0);
            checkLegalInDirection(board, n, i, j, colour, -1, 1);
            
        }
    }
}


/*------------------------------ 1.6 Check Legal Directions ------------------------------*/
/* checks whether (row, col) is a legal position for a tile of colour.
The helper function will be called 8 times to search the lines in the 8 possible directions. */

bool checkLegalInDirection(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol) {

    int initialRow = row, initialCol = col;
    char oppositeColour;
    bool legal;

    //assigns the oppositeColour
    if (turnColour == 'W') {
        oppositeColour = 'B';
    }

    else {
        oppositeColour = 'W';
    }

    
    //checks if the space you’re on is unoccupied
    //if not true, should go to the next value of the loop **(implement this)
    if (board[row][col] == 'U') {

        row += deltaRow;
        col += deltaCol;

        if ((board[row][col] == turnColour)||(board[row][col] == 'U')||!positionInBounds(n, row, col)) {
            legal = 0;
        }

        //potential for the move to be valid. So, check if there is a turnColour tile in that direction.
        else {
            do { //do instead of while so that you can check for turnColour before exiting the loop
                
                row += deltaRow;
                col += deltaCol;

                if (board[row][col] == turnColour) {
                    legal = 1;
                }

                else {   //if the detector encounters 'U'
                    //assigns legal to 0 here, BUT if the tile is oppositeColour, the loop will run again with the potential to be REASSIGNED to legal = 1 if it is the turnColour.
                    legal = 0;
                }
            }
            while (board[row][col] == oppositeColour);
            
            if (legal) { //may need to move this to a separate function if the boolean needs to be used.
                printf("%c%c\n", 'a'+initialRow, 'a'+initialCol);
            }

        }
    }

    else {
        legal = 0;
    }
    
    return legal;

}


/*------------------------------ 1.7 Take Turn ------------------------------*/
/* makes a move, changing 'unoccupied' to a color */

void takeTurn(char board[][26], int n) {
    char colour=0, row, col;
    
    scanf(" %c%c%c", &colour, &row, &col);
    
    if (colour == 'B' || colour == 'W') {
        row = (int)row-97; //char conversion to ascii value to get position of tile placement
        col = (int)col-97;
        
        board[row][col] = colour; //tile is placed
        
        changeColour(board, n, row, col, colour);
    }
    
    printBoard(board, n);
}


/*------------------------------ 1.8 Change Colour ------------------------------*/
/* Calls the changeTileColour function 8 times */

void changeColour(char board[][26], int n, int i, int j, int colour) {
    bool legal;
    
    if (changeTileColour(board, n, i, j, colour, 1, -1))
        legal = 1;
    else if (changeTileColour(board, n, i, j, colour, 1, 0))
        legal = 1;
    else if (changeTileColour(board, n, i, j, colour, 1, 1))
        legal = 1;
    else if (changeTileColour(board, n, i, j, colour, 0, -1))
        legal = 1;
    else if (changeTileColour(board, n, i, j, colour, 0, 1))
        legal = 1;
    else if (changeTileColour(board, n, i, j, colour, -1, -1))
        legal = 1;
    else if (changeTileColour(board, n, i, j, colour, -1, 0))
        legal = 1;
    else if (changeTileColour(board, n, i, j, colour, -1, 1))
        legal = 1;

    else {
        legal = 0;
    }
    
    if (legal) {
        printf("Valid move.\n");
    }
    
    else {
        board[i][j] = 'U';
        printf("Invalid move.\n");
    }
    
}


/*------------------------------ 1.9 Change Individual Tile Colours ------------------------------*/
/* Changes opposite coloured tiles to the turn colour */

bool changeTileColour(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol) {
    
    char oppositeColour;
    bool legal;
    
    //assigns the oppositeColour
    if (turnColour == 'W') {
        oppositeColour = 'B';
    }
    
    else {
        oppositeColour = 'W';
    }
    
    row += deltaRow;
    col += deltaCol;
    
    if ((board[row][col] == turnColour)||(board[row][col] == 'U')||!positionInBounds(n, row, col)) {
        legal = 0;
    }
    
    //potential for the move to be valid. So, check if there is a turnColour tile in that direction.
    else {
        
        do { //do instead of while so that you can check for turnColour before exiting the loop
            
            row += deltaRow;
            col += deltaCol;
            
            if (board[row][col] == turnColour) {
                legal = 1;
                //loops back here and actually changes the tiles
                
                deltaRow *= -1;
                deltaCol *= -1;
                
                do {
                    board[row][col] = turnColour;
                    
                    row += deltaRow;
                    col += deltaCol;
                }
                while (board[row][col] == oppositeColour);
                
            }
            
            else {   //if the detector encounters 'U'
                //assigns legal to 0 here, BUT if the tile is oppositeColour, the loop will run again with the potential to be REASSIGNED to legal = 1 if it is the turnColour.
                legal = 0;
            }
        }
        while (board[row][col] == oppositeColour);
        
//        if (legal) { //may need to move this to a separate function if the boolean needs to be used.
//            printf("Valid move.\n");
//        }
        
    }
    
    return legal;
}



/*------------------------------ 2.0 MAIN FUNCTION ------------------------------*/

int main(int argc, const char * argv[]) {
    int boardSize;
    char board[26][26];
    
    printf("Enter the board dimension: ");
    scanf("%d", &boardSize);
    
    initializeBoard(board, boardSize);
    printBoard(board, boardSize);
    
    printf("Enter board configuration:\n");
    boardConfig(board, boardSize);
    
    printf("Available moves for W:\n");
    availableMoves(board, boardSize, 'W');
    
    printf("Available moves for B:\n");
    availableMoves(board, boardSize, 'B');
    
    printf("Enter a move:\n");
    takeTurn(board, boardSize);
    
    return 0;
}
