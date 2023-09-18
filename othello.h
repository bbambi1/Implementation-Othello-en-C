#ifndef OTHELLO_H
#define OTHELLO_H

#define N 8
#define EMPTY 0
#define BLACK 1
#define WHITE 2

// Game Modes
#define PLAYER_VS_PLAYER 1
#define PLAYER_VS_AI 2
#define AI_VS_AI 3

// Function prototypes
int getRandomNumber(int n);
void initializeBoard(int board[N][N]);
void displayBoard(int board[N][N]);
int isCellValid(int row, int col);
int isEmptySpot(int board[N][N], int row, int col);
int isDirectionValid(int board[N][N], int row, int col, int player, int dx, int dy);
int isMoveValid(int board[N][N], int row, int col, int player);
int canPlayerMove(int board[N][N], int player);
int nextPlayer(int player);
int isGameOver(int board[N][N]);
char* determineWinner(int board[N][N]);
void calculateScore(int board[N][N]);
void makeMove(int board[N][N], int row, int col, int player);

void getRandomMove(int board[N][N], int player, int *row, int *col);
void getGreedyMove(int board[N][N], int player, int *row, int *col);

// New typedef for strategy function
typedef void (*StrategyFunc)(int board[N][N], int player, int *row, int *col);

void getAIMove(int board[N][N], int player, int *row, int *col, StrategyFunc strategy);
void gameLoop(int mode, int ai1StrategyChoice, int ai2StrategyChoice);

void printBoard(int board[N][N]);
void getPlayerMove(int *row, int *col);

#endif // OTHELLO_H
