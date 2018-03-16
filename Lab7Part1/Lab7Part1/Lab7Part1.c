//  Copyright © 2018 Song You. All rights reserved.

#include <stdio.h>
#include <stdbool.h>



/*------------------------------ 0.0 PROTOTYPES------------------------------*/

void initializeBoard(char board[][26], int n);
void printBoard(char board[][26], int n);

bool positionInBounds(int n, int row, int col);

bool changeColour(char board[][26], int n, int i, int j, int colour);
bool changeTileColour(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol);

int main(int argc, const char * argv[]);

bool playerMove(char board[][26], int playerColour, int n);
void bestMove(char board[][26], char computerColour, int n, int *i, int *j);
int countScore(char pseudoBoard[][26], char color, int n);
int bestScore(int newScore, int newRow, int newCol, int n);

bool availableMoves(char board[][26], int n, int i, int j, int colour);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol);

/*------------------------------ 1.0 SETUP ------------------------------*/


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



/*------------------------------ 2.0 MOVES ------------------------------*/

/*------------------------------ 2.1 Player Move ------------------------------*/
//done I think
bool playerMove(char board[][26], int playerColour, int n) {
    int row = 0, col = 0;
    char r, c;
    bool legal = false;
    
    //checks to see if the player has any moves available to them
    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (availableMoves(board, n, i, j, playerColour)) {
                legal = true;
            }
        }
    };
    
    if (!legal) {
        printf("%c player has no valid move.", playerColour);
    }
    
    else {
        printf("Enter move for colour %c (RowCol): ", playerColour);
        scanf("%c%c", &r, &c);
        
        row = (int)r - 97;
        col = (int)c - 97;
        
        board[row][col] = playerColour; //tile is placed
        
        if (!changeColour(board, n, row, col, playerColour)) {
            board[row][col] = 'U';
            legal = false;
        }
    }
    
    return legal;
}


/*------------------------------ 2.2 Computer Move ------------------------------*/

void computerMove(char board[][26], int computerColour, int n) {
    int row = 0, col = 0;
    
    char pseudoBoard[26][26] = {};
    int newScore = 0, maxScore = 0, bestRow = 0, bestCol = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (availableMoves(board, n, i, j, computerColour)) {
                
                newScore = countScore(pseudoBoard, computerColour, n);
                
                if (newScore > maxScore) {
                    maxScore = newScore;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }
    
    printf("Computer places %c at %c%c.", computerColour, row, col);
    
    board[row][col] = computerColour;
    changeColour(board, n, row, col, computerColour);
    
}



/*------------------------------ 2.4 Computer Move Total Score ------------------------------*/
//tallies up the score for each possible move
//considers the weights of each tile
int countScore(char pseudoBoard[][26], char color, int n) {
    int score = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (pseudoBoard[i][j] == color) {
                
                //if the player's color captures a corner
                //REALLY GOOD. 5+ REWARD
                if ((i == 0 && j == 0) || (i == (n-1) && j == 0) || (i == 0 && j == (n-1)) || (i == (n-1) && j == (n-1))) {
                    score += 5;
                }
                
                //if the player's color lands on a tile touching the corners
                //UGH TERRIBLE. -5 PENALTY
                else if ((i <= 1 && j <= 1) || (i >= (n-2) && j <= 1) || (i <= 1 && j >= (n-2)) || (i >= (n-2) && j >= (n-2))) {
                    score -= -5;
                }
                
                //if the player's color captures an edge
                //GOOD. 3+ REWARD
                else if (i == 0 || j == 0 || i == (n-1) || j == (n-1)) {
                    score += 3;
                }
                
                //if the player's color is two tiles away from a corner
                //SURE. +2 REWARD
                else if ((i <= 2 && j <= 2) || (i >= (n-3) && j <= 2) || (i <= 2 && j >= (n-3)) || (i >= (n-3) && j >= (n-3))) {
                    score += 2;
                }
                
                //all other cases
                else {
                    score++;
                }
            }
        }
    }
    
    return score;
}









/*------------------------------ 1.5 Check Available Moves ------------------------------*/
/* Cycles through all 8 directions of the checkLegalInDirection function */

bool availableMoves(char board[][26], int n, int i, int j, int colour) {
    bool legal = true;
    
    if (checkLegalInDirection(board, n, i, j, colour, 1, -1))
        legal = true;
    else if (checkLegalInDirection(board, n, i, j, colour, 1, 0))
        legal = true;
    else if (checkLegalInDirection(board, n, i, j, colour, 1, 1))
        legal = true;
    else if (checkLegalInDirection(board, n, i, j, colour, 0, -1))
        legal = true;
    else if (checkLegalInDirection(board, n, i, j, colour, 0, 1))
        legal = true;
    else if (checkLegalInDirection(board, n, i, j, colour, -1, -1))
        legal = true;
    else if (checkLegalInDirection(board, n, i, j, colour, -1, 0))
        legal = true;
    else if (checkLegalInDirection(board, n, i, j, colour, -1, 1))
        legal = true;
    
    else {
        legal = false;
    }
    
    return legal;
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
























/*------------------------------ 3.0 GAME MECHANICS ------------------------------*/

/*------------------------------ 3.1 Change Colour ------------------------------*/
/* Calls the changeTileColour function 8 times */

bool changeColour(char board[][26], int n, int i, int j, int colour) {
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
    
    return legal;
}


/*------------------------------ 3.2 Flip Tiles ------------------------------*/
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


/*------------------------------ 3.3 Declare the Winner ------------------------------*/
//Who is the winner?
char winner(char board[][26], int n, char playerColour, char computerColour) {
    int player = 0;
    int computer = 0;
    char winner;
    
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n ; j++) {
            if (board[i][j] == playerColour) {
                player++;
            }
            
            else if (board[i][j] == computerColour) {
                computer++;
            }
        }
    }
    
    if (player > computer) {
        winner = playerColour;
    }
    
    else if (computer > player) {
        winner = computerColour;
    }
    
    else {
        winner = 'U';
    }
    
    return winner;
}



/*------------------------------ 4.0 MAIN FUNCTION ------------------------------*/

int main(int argc, const char * argv[]) {
    char computerColour, playerColour, winningColour;
    char board[][26] = {};
    int boardSize;
    bool playerTurn;
    
    printf("Enter the board dimension: ");
    scanf("%d", &boardSize);
    
    printf("Computer plays (B/W) : ");
    scanf(" %c", &computerColour);
    
    initializeBoard(board, boardSize);
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
            if(!playerMove(board, playerColour, boardSize)) {
                printf("Invalid move.\n");
                break;
            }
            playerTurn = false; //next time, it will be the computer's turn
        }
        
        else {
            computerMove(board, computerColour, boardSize);
            playerTurn = true; //next time, it will be the player's turn
        }
        
        printBoard(board, boardSize);
    }
    while (playerMove(board, playerColour, boardSize));
    
    winningColour = winner(board, boardSize, playerColour, computerColour); //function to count number of B & W pieces on the board.
    
    printf("%c player wins.\n", winningColour);
    
    return 0;
}

