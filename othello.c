// othello.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "othello.h"
#include <string.h>
#include <limits.h>

#define BLACK 1
#define WHITE 2
#define EMPTY 0

// Direction vectors
int directions[8][2] = {
    {-1, 0},  // Vertical up
    {1, 0},   // Vertical down
    {0, -1},  // Horizontal left
    {0, 1},   // Horizontal right
    {-1, 1},  // Diagonal upper right
    {-1, -1}, // Diagonal upper left
    {1, 1},   // Diagonal lower right
    {1, -1}   // Diagonal lower left
};

// Generate random numbers between 0 and n-1
int getRandomNumber(int n)
{
    static int firstCall = 0;

    if (firstCall == 0)
    {
        srand(time(NULL));
        firstCall = 1;
    }
    return (rand() % n);
}

// Initialize the board by placing the first 4 pieces
void initializeBoard(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            board[i][j] = 0;
        }
    }
    board[(N / 2) - 1][(N / 2) - 1] = BLACK;
    board[N / 2][N / 2] = BLACK;
    board[N / 2][(N / 2) - 1] = WHITE;
    board[(N / 2) - 1][N / 2] = WHITE;
}

// Display the board passed as argument
void displayBoard(int board[N][N])
{
    printf("\n");
    for (int row = 0; row < N; row++)
    {
        printf("%d.  ", row);
        for (int col = 0; col < N; col++)
        {
            printf("%d  ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n    ");
    for (int i = 0; i < N; i++)
    {
        printf("%d. ", i);
    }
    printf("\n");
}

// Returns True if a move is played on the board, False otherwise
int isCellValid(int row, int col)
{
    return ((row >= 0 && row < N) && (col >= 0 && col < N));
}

// Returns True if the played move is on an empty spot
int isEmptySpot(int board[N][N], int row, int col)
{
    return board[row][col] == 0;
}

int isDirectionValid(int board[N][N], int row, int col, int player, int dx, int dy)
{
    int opposingPlayer = nextPlayer(player);
    int i = row + dx;
    int j = col + dy;
    
    if (!isCellValid(i, j) || board[i][j] != opposingPlayer)
    {
        return 0;
    }

    while (isCellValid(i, j) && board[i][j] == opposingPlayer)
    {
        i += dx;
        j += dy;
    }

    return (isCellValid(i, j) && board[i][j] == player);
}

// Check if the move (i, j) is valid for the "vertical up" direction
int isVerticalUpValid(int board[N][N], int row, int col, int player)
{
    return isDirectionValid(board, row, col, player, directions[0][0], directions[0][1]);
}

// Check if the move (i, j) is valid for the "vertical down" direction
int isVerticalDownValid(int board[N][N], int row, int col, int player)
{
    return isDirectionValid(board, row, col, player, directions[1][0], directions[1][1]);
}

// Check if the move (i, j) is valid for the "horizontal left" direction
int isHorizontalLeftValid(int board[N][N], int row, int col, int player)
{
    return isDirectionValid(board, row, col, player, directions[2][0], directions[2][1]);
}

int isHorizontalRightValid(int board[N][N], int row, int col, int player)
{
    return isDirectionValid(board, row, col, player, directions[3][0], directions[3][1]);
}

int isDiagonalUpperRightValid(int board[N][N], int row, int col, int player)
{
    return isDirectionValid(board, row, col, player, directions[4][0], directions[4][1]);
}

int isDiagonalUpperLeftValid(int board[N][N], int row, int col, int player)
{
    return isDirectionValid(board, row, col, player, directions[5][0], directions[5][1]);
}

int isDiagonalLowerRightValid(int board[N][N], int row, int col, int player)
{
    return isDirectionValid(board, row, col, player, directions[6][0], directions[6][1]);
}

int isDiagonalLowerLeftValid(int board[N][N], int row, int col, int player)
{
    return isDirectionValid(board, row, col, player, directions[7][0], directions[7][1]);
}

// Check if a particular move is valid
int isMoveValid(int board[N][N], int row, int col, int player)
{
    if (!isCellValid(row, col) || !isEmptySpot(board, row, col))
    {
        return 0;
    }
    return isVerticalDownValid(board, row, col, player)
        || isVerticalUpValid(board, row, col, player)
        || isHorizontalRightValid(board, row, col, player)
        || isHorizontalLeftValid(board, row, col, player)
        || isDiagonalLowerRightValid(board, row, col, player)
        || isDiagonalLowerLeftValid(board, row, col, player)
        || isDiagonalUpperRightValid(board, row, col, player)
        || isDiagonalUpperLeftValid(board, row, col, player);
}

// Given a board configuration, checks if the current player can make a move
int canPlayerMove(int board[N][N], int player)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (isMoveValid(board, i, j, player))
            {
                return 1;
            }
        }
    }
    return 0;
}

// Determines the next player
int nextPlayer(int player)
{
    return (player % 2) + 1;
}

// Checks if the game is over
int isGameOver(int board[N][N])
{
    return !canPlayerMove(board, BLACK) && !canPlayerMove(board, WHITE);
}

// Determines the winner given the endgame board configuration and returns a string
char* determineWinner(int board[N][N])
{
    int blackCount = 0;
    int whiteCount = 0;
    static char result[50];  // static so its address remains valid after function exit

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == BLACK)
            {
                blackCount++;
            }
            else if (board[i][j] == WHITE)
            {
                whiteCount++;
            }
        }
    }

    if (blackCount > whiteCount)
    {
        snprintf(result, sizeof(result), "Player 1 (Black) wins! (%d vs %d)", blackCount, whiteCount);
    }
    else if (blackCount < whiteCount)
    {
        snprintf(result, sizeof(result), "Player 2 (White) wins! (%d vs %d)", whiteCount, blackCount);
    }
    else
    {
        snprintf(result, sizeof(result), "It's a tie! (Black: %d, White: %d)", blackCount, whiteCount);
    }
    return result;
}

// Given a board, calculates the score of both players
void calculateScore(int board[N][N])
{
    int blackCount = 0;
    int whiteCount = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == BLACK)
            {
                blackCount++;
            }
            else if (board[i][j] == WHITE)
            {
                whiteCount++;
            }
        }
    }
    printf("\nPlayer 1 (Black): %d points\nPlayer 2 (White): %d points\n", blackCount, whiteCount);
}

void makeMove(int board[N][N], int row, int col, int player) {
    int opponent = (player == BLACK) ? WHITE : BLACK;
    board[row][col] = player;

    for (int d = 0; d < 8; d++) {
        int newRow = row + directions[d][0];
        int newCol = col + directions[d][1];

        // This flag checks whether there are consecutive opponent pieces in the current direction
        int shouldFlip = 0;

        // This list stores the positions of the pieces we may have to flip
        int flipList[N*N][2];
        int flipCount = 0;

        while (isCellValid(newRow, newCol) && board[newRow][newCol] == opponent) {
            flipList[flipCount][0] = newRow;
            flipList[flipCount][1] = newCol;
            flipCount++;
            newRow += directions[d][0];
            newCol += directions[d][1];
        }

        // If we end up on a cell with our own piece and have encountered opponent's pieces before it
        if (isCellValid(newRow, newCol) && board[newRow][newCol] == player && flipCount > 0) {
            shouldFlip = 1;
        }

        // Flip the pieces if needed
        if (shouldFlip) {
            for (int i = 0; i < flipCount; i++) {
                board[flipList[i][0]][flipList[i][1]] = player;
            }
        }
    }
}

void getRandomMove(int board[N][N], int player, int *row, int *col) {
    int validMoves[N*N][2];
    int numValidMoves = 0;

    // Collect all valid moves
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (isMoveValid(board, i, j, player)) {
                validMoves[numValidMoves][0] = i;
                validMoves[numValidMoves][1] = j;
                numValidMoves++;
            }
        }
    }

    // Pick a random valid move
    int chosenMove = rand() % numValidMoves;
    *row = validMoves[chosenMove][0];
    *col = validMoves[chosenMove][1];
}

void getGreedyMove(int board[N][N], int player, int *row, int *col) {
    int maxScore = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (isMoveValid(board, i, j, player)) {
                int tempBoard[N][N];
                memcpy(tempBoard, board, N * N * sizeof(int));

                makeMove(tempBoard, i, j, player);
                int score = 0;

                for (int x = 0; x < N; x++) {
                    for (int y = 0; y < N; y++) {
                        if (tempBoard[x][y] == player) {
                            score++;
                        }
                    }
                }

                if (score > maxScore) {
                    maxScore = score;
                    *row = i;
                    *col = j;
                }
            }
        }
    }
}

int evaluateBoard(int board[N][N], int player) {
    int playerScore = 0;
    int opponentScore = 0;
    int opponent = (player == BLACK) ? WHITE : BLACK;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == player) playerScore++;
            else if (board[i][j] == opponent) opponentScore++;
        }
    }
    return playerScore - opponentScore;
}

int minimax(int board[N][N], int depth, int isMaximizing, int alpha, int beta, int player, int *bestRow, int *bestCol) {
    if (depth == 0 || isGameOver(board)) {
        return evaluateBoard(board, player);
    }

    int opponent = (player == BLACK) ? WHITE : BLACK;
    int maxEval = INT_MIN;
    int minEval = INT_MAX;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (isMoveValid(board, i, j, (isMaximizing ? player : opponent))) {
                int tempBoard[N][N];
                memcpy(tempBoard, board, N * N * sizeof(int));
                makeMove(tempBoard, i, j, (isMaximizing ? player : opponent));
                int currentEval = minimax(tempBoard, depth - 1, !isMaximizing, alpha, beta, player, NULL, NULL);

                if (isMaximizing) {
                    if (currentEval > maxEval) {
                        maxEval = currentEval;
                        if (bestRow) *bestRow = i;
                        if (bestCol) *bestCol = j;
                    }
                    alpha = (alpha > currentEval) ? alpha : currentEval;
                } else {
                    if (currentEval < minEval) {
                        minEval = currentEval;
                        if (bestRow) *bestRow = i;
                        if (bestCol) *bestCol = j;
                    }
                    beta = (beta < currentEval) ? beta : currentEval;
                }

                if (alpha >= beta) break;  // Alpha-beta pruning
            }
        }
    }

    return isMaximizing ? maxEval : minEval;
}

void getAlphaBetaMove(int board[N][N], int player, int *row, int *col) {
    int depth = 4;  // Change this as needed. Higher values make the AI think further ahead but take longer.
    minimax(board, depth, 1, INT_MIN, INT_MAX, player, row, col);
}
