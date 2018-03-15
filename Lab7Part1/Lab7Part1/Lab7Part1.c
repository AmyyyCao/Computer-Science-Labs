//  Copyright © 2018 Song You. All rights reserved.

#include <stdio.h>
#include <stdbool.h>



/*------------------------------ 0.0 PROTOTYPES------------------------------*/

void initializeBoard(int n);
void printBoard(char board[][26], int n);

bool positionInBounds(int n, int row, int col);

void takeTurn(char board[][26], int n);
void changeColour(char board[][26], int n, int i, int j, int colour);
bool changeTileColour(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol);

int main(int argc, const char * argv[]);



/*------------------------------ 1.0 FUNCTIONS ------------------------------*/

char board[][26] = {};


/*------------------------------ 1.1 Initialize Board ------------------------------*/

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
    
    if (!legal) {
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
    }
    return legal;
}


//done I think
void playerMove(char board[][26], int playerColour, int n) {
    char row, col;
    
    printf("Enter move for colour %c (RowCol): ", playerColour);
    scanf("%c%c", &row, &col);
    
    row = (int)row - 97;
    col = (int)col - 97;
    
    changeColour(board, n, row, col, playerColour);
}


void computerMove(char board[][26], int computerColour, int n) {
    int row, col;
    
    bestMove(); //calls function that returns row and column
    
    printf("Computer places %c at %c%c.", computerColour, row, col);

    changeColour(board, n, row, col, computerColour);
    printBoard(board, n);
}




void bestMove () {

    int newScore;
    char pseudoBoard = board;
    availableMoves(); returns all of the moves
    
    for (first move to last move) {
        takeTurn(pseudoBoard, move);
        countScore(pseudoBoard, move);
 
        newScore = countScore;
        bestMove(newScore);
    }
    return bestMove;
}

 
 


//DONE
//considers the weights of each tile
int countScore(char pseudoBoard, char color, int n) {
    int score = 0;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (pseudoBoard[i][j] == color) {

                //if the corners are the player's color
                if ((i == 0 && j == 0) || (i == (n-1) && j == 0) || (i == 0 && j == (n-1)) || (i == (n-1) && j == (n-1))) {
                    score += 5;
                }
                
                //if the tiles touching the corners are the player's color
                else if ((i <= 1 && j <= 1) || (i >= (n-2) && j <= 1) || (i <= 1 && j >= (n-2)) || (i >= (n-2) && j >= (n-2))) {
                    score -= -5;
                }

                else if ((i <= 2 && j <= 2) || (i >= (n-3) && j <= 2) || (i <= 2 && j >= (n-3)) || (i >= (n-3) && j >= (n-3))) {
                    score += 2;
                }

                else {
                    score++;
                }
            }
        }
    }
    
 return score;
}


//DONE
//but need to change bestRow and bestCol into pointers
int bestMove(int newScore, int newRow, int newCol, int n) {
    int bestScore = 0;
    int bestRow = n, bestCol = n;

    if (newScore > bestScore) {
        bestRow = newRow;
        bestCol = newCol;
    }

    else if (newScore == bestScore) {
        if (newRow < bestRow) {
            bestRow = newRow;
            bestCol = newCol;
        }
        else if (bestRow > newRow) {
            if (newCol < bestCol) {
                bestRow = newRow;
                bestCol = newCol;
            }
        }
    }
    return bestScore;
}



/*------------------------------ 2.0 MAIN FUNCTION ------------------------------*/

int main(int argc, const char * argv[]) {
    int boardSize;
    char computerColour, playerColour;
    bool playerTurn;
    
    printf("Enter the board dimension: ");
    scanf("%d", &boardSize);
    
    printf("Computer plays (B/W) : ");
    scanf("%c", &computerColour);
    
    initializeBoard(boardSize);
    printBoard(board, boardSize);
    
    //logic for assigning computer/player turn and tile colours
    if (computerColour == 'W') {
        playerTurn = true;
        playerColour = 'B';
    }
    
    else {
        playerTurn = false;
        playerColour = 'W';
    }
    
    //continue to play moves while the moves are legal
    do {
        
        if (playerTurn == true) {
            playerMove(board, playerColour, boardSize);
            playerTurn = false; //next time, it will be the computer's turn
        }
        
        else {
            computerMove(board, computerColour, boardSize);
            playerTurn = true; //next time, it will be the player's turn
        }
    }
    while (/*not illegal && board is empty*/);
    
    winner(); //function to count number of B & W pieces on the board.
    
    return 0;
}

