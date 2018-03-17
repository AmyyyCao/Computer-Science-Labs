//  Copyright © 2018 Song You. All rights reserved.

#include <stdio.h>
#include <stdbool.h>



/*------------------------------ 0.0 PROTOTYPES------------------------------*/

void initializeBoard(char board[][26], int n);
void printBoard(char board[][26], int n);

bool positionInBounds(int n, int row, int col);

bool changeColour(char board[][26], int n, int i, int j, int colour);
bool changeTileColour(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol);

int main();

bool playerMove(char board[][26], char playerColour, int n, bool *allowed);
bool computerMove(char board[][26], char computerColour, int n);
void bestMove(char board[][26], char computerColour, int n, int *i, int *j);
int countScore(char board[][26], char color, int n, int row, int col);
int bestScore(int newScore, int newRow, int newCol, int n);

bool availableMoves(char board[][26], int n, int i, int j, int colour);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol);

/*------------------------------ 1.0 SETUP ------------------------------*/


/*------------------------------ 1.1 Initialize Board ------------------------------*/

void initializeBoard(char board[][26], int n) {
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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
    if ((row >= 0) && (col >= 0) && (row < n) && (col < n)) {
        return true;
    }
    else {
        return false;
    }
    
}





/*------------------------------ 2.0 MOVES ------------------------------*/

/*------------------------------ 2.1 Player Move ------------------------------*/
bool playerMove(char board[][26], char playerColour, int n, bool *allowed) {
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
    }
    
    if (legal) {
        printf("Enter move for colour %c (RowCol): ", playerColour);
        scanf(" %c%c", &r, &c);
        
        row = r - 'a';
        col = c - 'a';
        
        board[row][col] = playerColour; //tile is placed
        
        
        if (!changeColour(board, n, row, col, playerColour)) {
            board[row][col] = 'U';
            legal = false;
            *allowed = false;
            return legal;
        }
        else {
            printBoard(board, n);
        }
    }
    
    return legal;
}


/*------------------------------ 2.2 Computer Move ------------------------------*/

bool computerMove(char board[][26], char computerColour, int n) {
    int newScore = 0, maxScore = 0, bestRow = -1, bestCol = -1;
    bool legal = true;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (availableMoves(board, n, i, j, computerColour)) {
                
                legal = true;
                newScore = countScore(board, computerColour, n, i, j);
                
                if (newScore > maxScore) {
                    maxScore = newScore;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }
    
    if (bestRow == -1 && bestCol == -1) {
        legal = false;
    }
    
    else {
        printf("Computer places %c at %c%c.\n", computerColour, bestRow + 'a', bestCol + 'a');
        board[bestRow][bestCol] = computerColour;
        changeColour(board, n, bestRow, bestCol, computerColour);
        printBoard(board, n);
    }
    
    return legal;
}


/*------------------------------ 2.4 Computer Move Total Score ------------------------------*/
//tallies up the score for each possible move
//considers the weights of each tile
int countScore(char board[][26], char color, int n, int row, int col) {
    int score = 0;
    
    char pseudoBoard[26][26];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pseudoBoard[i][j] = board[i][j];
        }
    }
    
    changeColour(pseudoBoard, n, color, row, col);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (pseudoBoard[i][j] == color) {
                //if the player's color captures a corner
                //REALLY GOOD. +100 REWARD
                if ((i == 0 && j == 0) || (i == (n-1) && j == 0) || (i == 0 && j == (n-1)) || (i == (n-1) && j == (n-1))) {
                    score += 100;
                }
                
                //if the player's color lands on a tile touching the corners
                //UGH TERRIBLE. -20 PENALTY
                else if ((i <= 1 && j <= 1) || (i >= (n-2) && j <= 1) || (i <= 1 && j >= (n-2)) || (i >= (n-2) && j >= (n-2))) {
                    score -= -20;
                }
                
                //if the player's color captures an edge
                //GOOD. +3 REWARD
                else if (i == 0 || j == 0 || i == (n-1) || j == (n-1)) {
                    score += 20;
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
    bool legal = false;
    
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
    
    return legal;
}


/*------------------------------ 1.6 Check Legal Directions ------------------------------*/
/* checks whether (row, col) is a legal position for a tile of colour.
 The helper function will be called 8 times to search the lines in the 8 possible directions. */

bool checkLegalInDirection(char board[][26], int n, int row, int col, char turnColour, int deltaRow, int deltaCol) {
    
    char oppositeColour;
    bool legal = false;
    
    //assigns the oppositeColour
    if (turnColour == 'W') {
        oppositeColour = 'B';
    }
    
    else {
        oppositeColour = 'W';
    }
    
    
    //checks if the space you’re on is unoccupied
    //if not true, should go to the next value of the loop
    if (board[row][col] == 'U' && positionInBounds(n, row, col)) {
        
        row += deltaRow;
        col += deltaCol;
        
        if ((board[row][col] == turnColour)||(board[row][col] == 'U')||!positionInBounds(n, row, col)) {
            legal = false;
        }
        
        //potential for the move to be valid. So, check if there is a turnColour tile in that direction.
        else {
            do { //do instead of while so that you can check for turnColour before exiting the loop
                
                row += deltaRow;
                col += deltaCol;
                
                if (board[row][col] == turnColour) {
                    legal = true;
                }
                
                else {   //if the detector encounters 'U'
                    //assigns legal to 0 here, BUT if the tile is oppositeColour, the loop will run again with the potential to be REASSIGNED to legal = 1 if it is the turnColour.
                    legal = false;
                }
            }
            while (board[row][col] == oppositeColour);
            
        }
    }
    
    
    
    return legal;
    
}
















/*------------------------------ 3.0 GAME MECHANICS ------------------------------*/

/*------------------------------ 3.1 Change Colour ------------------------------*/
/* Calls the changeTileColour function 8 times */

bool changeColour(char board[][26], int n, int i, int j, int colour) {
    bool legal = false;
    
    if (changeTileColour(board, n, i, j, colour, 1, -1))
        legal = true;
    if (changeTileColour(board, n, i, j, colour, 1, 0))
        legal = true;
    if (changeTileColour(board, n, i, j, colour, 1, 1))
        legal = true;
    if (changeTileColour(board, n, i, j, colour, 0, -1))
        legal = true;
    if (changeTileColour(board, n, i, j, colour, 0, 1))
        legal = true;
    if (changeTileColour(board, n, i, j, colour, -1, -1))
        legal = true;
    if (changeTileColour(board, n, i, j, colour, -1, 0))
        legal = true;
    if (changeTileColour(board, n, i, j, colour, -1, 1))
        legal = true;
    
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
    
    //loops through the board, records how many player tiles and computer tiles there are.
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
    
    //co
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

int main() {
    char computerColour = 'X', playerColour, winningColour;
    char board[26][26];
    int boardSize;
    bool playerTurn, playerLegal = true, compLegal = true;
    bool allowed = true;
    
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
    while (playerLegal || compLegal) {
        
        
        
        if (playerTurn == true) {
            playerLegal = playerMove(board, playerColour, boardSize, &allowed);
            playerTurn = false; //next time, it will be the computer's turn
            
            //if there are available moves, but the player chooses an invalid move
            if (!allowed) {
                winningColour = computerColour;
                printf("Invalid move.\n");
                break;
            }
        }
        
        else {
            compLegal = computerMove(board, computerColour, boardSize);
            playerTurn = true; //next time, it will be the player's turn
        }
        
        
        //break function if there are no legal moves
        if (!playerLegal && !compLegal) {
            break;
        }
        
        else if (!playerTurn && !playerLegal) {
            printf("%c player has no valid move.\n", playerColour);
        }
        
        else if (playerTurn && !compLegal) {
            printf("%c player has no valid move.\n", computerColour);
        }
        
        
        bool yes = false;
        
        for (int i=0; i < boardSize; i++) {
            for (int j=0; j < boardSize; j++) {
                if (availableMoves(board, boardSize, i, j, playerColour)) {
                    yes = true;
                }
            }
        }
        
        for (int i=0; i < boardSize; i++) {
            for (int j=0; j < boardSize; j++) {
                if (availableMoves(board, boardSize, i, j, computerColour)) {
                    yes = true;
                }
            }
        }
        
        if (!yes) {
            break;
        }
        
        
    }
    
    
    winningColour = winner(board, boardSize, playerColour, computerColour); //function to count number of B & W pieces on the board.
    
    printf("%c player wins.\n", winningColour);
    
    return 0;
}


