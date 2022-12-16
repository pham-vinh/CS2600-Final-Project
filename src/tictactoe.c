#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 3
#define COL 3

int menuInput;

// Long String Matrix
int board[ROW][COL];
bool gameOver = false;
bool computer = false;

// Max Turns == 9
int maxTurns = 0;

// Declare Methods
void displayMenu();
void printBoard();

void getPlayerTurn(int pT);
void computerInput(int player);
void drawCheck();
int isValid(int x, int y);
bool isGameOver(int player);
void reset();
void delay(int number_of_seconds);

int main()
{

    displayMenu();

    if (menuInput == 2)
        computer = true;
    else if (menuInput == 3) {

        while (!gameOver) {
            computerInput(1);
            isGameOver(1);
            drawCheck();

            if (!gameOver) {
                delay(2);
                computerInput(2);
                isGameOver(2);
                drawCheck();
            }

            delay(2);
        }
    }

    while (!gameOver) {
        getPlayerTurn(1);
        isGameOver(1);
        drawCheck();
        if (computer && !gameOver) {
            computerInput(2);
            isGameOver(2);
            drawCheck();
        } else if (!gameOver) {
            getPlayerTurn(2);
            isGameOver(2);
            drawCheck();
        }
    }

    return 0;
}

void gameRestart()
{
    int input = 0;
    printf("\nPlay Again?\n1: Yes\n2: No\n");
    scanf("%d", &input);

    if (input == 1)
        reset();
    else if (input == 2)
        exit(0);
    else
        gameRestart();
}

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;

    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

void drawCheck()
{
    if (maxTurns >= 9) {
        printf("Draw!\n");
        gameOver = true;
    }
}

void displayMenu()
{
    printf("\n======================\n");
    printf("WELCOME TO TIC TAC TOE!\n");
    printf("1 --- person vs. person\n");
    printf("2 --- person vs. computer\n");
    printf("3 --- computer vs. computer\n");

    printf("Enter your choice\n");
    printf("=======================\n");
    scanf("%d", &menuInput);
    printf("\nYou have entered choice %d\n", menuInput);

    if (menuInput > 3) {
        printf("\nInvalid Choice Please Choose Again\n");
        displayMenu();
    }
}

bool isGameOver(int player)
{

    // check vertical
    for (int i = 0; i < COL; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            gameOver = true;
        }
    }

    // check horizontal
    for (int i = 0; i < ROW; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            gameOver = true;
        }
    }

    // check diagonal win (top left to bottom right)
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        gameOver = true;
    }

    // check diagonal win (bottom left to top right)
    if (board[2][0] == player && board[1][1] == player && board[0][2] == player) {
        gameOver = true;
    }

    if (gameOver) {
        if (computer && player == 2) {
            printf("Game over! Result: Computer wins!\n");
            printBoard();
        } else {
            printf("Player %d Wins!\n", player);
            printBoard();
        }
    }
    return gameOver;
}

void getPlayerTurn(int pT)
{
    printBoard();

    int row = 0;
    int col = 0;

    printf("Player %d: make your move\n", pT);
    scanf("%d %d", &row, &col);
    if (isValid(row, col) == 1) {
        row -= 1;
        col -= 1;
        board[row][col] = pT;
        maxTurns++;
    } else
        getPlayerTurn(pT);
}

void printBoard()
{
    for (int i = 0; i < 3; i++) {
        printf("+-----------+\n");
        for (int j = 0; j < 3; j++) {
            printf(" | ");

            if (board[i][j] == 1)
                printf("X");
            else if (board[i][j] == 2)
                printf("O");
            else
                printf(" ");
        }
        printf(" |\n");
    }
    printf("+-----------+\n");
}

void reset()
{
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            board[i][j] = 0;
        }
    }
}

void computerInput(int player)
{
    printBoard();
    bool isValid = false;

    while (!isValid) {
        int row = (rand() % (3)) + 1;
        int column = (rand() % (3)) + 1;

        if (board[row - 1][column - 1] == 0) {
            board[row - 1][column - 1] = player;
            printf("Computer: makes their move\n%d %d\n", row, column);
            isValid = true;
        }
    }
    maxTurns++;
}

int isValid(int x, int y)
{
    if ((x < 4 && x > 0) && (y < 4 && y > 0)) {
        int tempX = x - 1;
        int tempY = y - 1;
        if (board[tempX][tempY] == 0)
            printf("\nGood!\n");
        else {
            printf("\nInvalid Input Please try again.\n");
            return 0;
        }
        return 1;
    } else
        return 0;
}
