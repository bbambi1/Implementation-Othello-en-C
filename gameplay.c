#include <stdio.h>
#include "othello.h"
#include <stdlib.h>

void printBoard(int board[N][N]) 
{
    printf("  0 1 2 3 4 5 6 7\n");  // Column numbers
    for (int i = 0; i < N; i++) 
    {
        printf("%d ", i);  // Row number
        for (int j = 0; j < N; j++) 
        {
            if (board[i][j] == EMPTY) printf(". ");
            else if (board[i][j] == BLACK) printf("O "); // Using O for Player 1
            else printf("X "); // Using X for Player 2
        }
        printf("\n");
    }
}

void getPlayerMove(int *row, int *col) 
{
    printf("Enter your move (row col): ");
    scanf("%d %d", row, col);
}

void getAIMove(int board[N][N], int player, int *row, int *col, StrategyFunc strategy) 
{
    strategy(board, player, row, col);
}

int selectStrategy() 
{
    int choice;
    printf("Select AI Strategy:\n1. Random\n2. Greedy\n3. Alpha-Beta\nChoice: ");
    scanf("%d", &choice);
    return choice;
}

void gameLoop(int mode, int ai1StrategyChoice, int ai2StrategyChoice)
{
    int board[N][N];
    initializeBoard(board);

    int currentPlayer = BLACK;
    while (!isGameOver(board))
    {
        printBoard(board);
        int row, col;

        if ((mode == PLAYER_VS_PLAYER) || 
            (mode == PLAYER_VS_AI && currentPlayer == BLACK)) 
        {
            getPlayerMove(&row, &col);
        }
        else
        {
            // AI's move
            StrategyFunc strategy = NULL;

            int strategyChoice = (currentPlayer == BLACK) ? ai1StrategyChoice : ai2StrategyChoice;

            switch(strategyChoice)
            {
                case 1:
                    strategy = getRandomMove;
                    break;
                case 2:
                    strategy = getGreedyMove;
                    break;
                case 3:
                    strategy = getAlphaBetaMove; // Assuming you named it this way
                    break;
                default:
                    printf("Invalid AI strategy choice!\n");
                    exit(1); // or handle this more gracefully if you prefer
            }
            getAIMove(board, currentPlayer, &row, &col, strategy);
        }

        // Make the move if valid
        if (isMoveValid(board, row, col, currentPlayer))
        {
            makeMove(board, row, col, currentPlayer);
            currentPlayer = nextPlayer(currentPlayer);
        }
        else 
        {
            printf("Invalid move! Try again.\n");
        }
    }

    printf("Game Over!\n");
    printBoard(board);
    printf("%s\n", determineWinner(board));
}

int main() 
{
    int choice, ai1StrategyChoice = 0, ai2StrategyChoice = 0;
    printf("Select Game Mode:\n1. Player vs Player\n2. Player vs AI\n3. AI vs AI\nChoice: ");
    scanf("%d", &choice);

    if (choice == PLAYER_VS_AI) {
        ai1StrategyChoice = selectStrategy();
    } else if (choice == AI_VS_AI) {
        printf("AI 1:\n");
        ai1StrategyChoice = selectStrategy();
        printf("AI 2:\n");
        ai2StrategyChoice = selectStrategy();
    }
    
    gameLoop(choice, ai1StrategyChoice, ai2StrategyChoice);
    return 0;
}
