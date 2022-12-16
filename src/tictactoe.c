#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 3
#define COL 3

// boolean of either pvp or pvc
int menuInput;

// Swapping between player 1 and 2
int playerTurn = 1;

// Long String Matrix
int board[ROW][COL];
bool gameOver = false;
bool computer = false;

// Max Turns == 9
int maxTurns = 0;

// Declare Methods
void displayMenu();
void printBoard();
void winMessage();

void getPlayerTurn();
void computerInput();
void setGameState();
int drawCheck();
int isValid();
int isGameOver();

int main()
{

    int player; // 0 is false, 1 is true
    int game = 1; // Play Again
                  // get input on menu
    displayMenu();

    if (menuInput == 2)
        computer = true;
    else if (gameType == 3) {
        while (!gameOver) {
            computerTurn(1);
            checkWin(1);
            checkTie();
            if (!gameOver) {
                computerTurn(2);
                checkWin(2);
                checkTie();
            }
        }
    }

    while (game == 1) {

        // print out the first game state via method in a while loop while getting input
        setGameState(0, 0, 0);
        printBoard();

        while (isGameOver() == 0) {

            if (player == 1) {
                getPlayerTurn(playerTurn);
                setGameState(x, y, playerTurn);
                if (playerTurn == 1)
                    playerTurn = 2;
                else
                    playerTurn = 1;
            } else {
                getPlayerTurn(1);
                setGameState(x, y, 1);

                if (drawCheck() == 0) {
                    computerInput(); // sets x and y randomly
                    setGameState(x, y, 2);
                }
            }
            printBoard();
        }

        printf("\nPlay Again?\n1: Yes\n2: No\n");
        scanf("%d", &game);

        if (game == 2)
            exit(0);
    }
    return 0;
}

int drawCheck()
{
    if (maxTurns >= 9) {
        printf("Draw!\n");
        return 1;
    }
    return 0;
}

// Bug: didn't get the right input
// method for displaying menu
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

int isGameOver()
{

    // check vertical
    for (int i = 0; i < 3; i++) {
        if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player) {
            gameOver = true;
        }
    }
	
    // check horizontal
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) {
            gameOver = true;
        }
    }


    // check diagonal win (top left to bottom right)
    if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) {
        gameOver = true;
    }

    // check diagonal win (bottom left to top right)
    if (grid[2][0] == player && grid[1][1] == player && grid[0][2] == player) {
        gameOver = true;
    }

    if (gameOver) {
        if (vsComputer && player == 2) {
            printf("Game over! Result: Computer wins!\n");
            displayBoard();
        } else {
            printf("Game over! Result: Player %d wins!\n", player);
            displayBoard();
        }
    }
    return gameOver;
}

void winMessage(int player)
{
    if (player == 1) {
        printf("Player 1 Wins!\n");
    } else {
        printf("Player 2 Wins!\n");
    }
}

// Bug: giving the wrong coordinates and removed swap player turns in this method because it was messing up with the
// order get coords and swap
void getPlayerTurn(int pT)
{
    if (pT == 1) {
        printf("Player 1: make your move\n");
        scanf("%d %d", &x, &y);
        if (isValid(x, y) == 1) {
            x -= 1;
            y -= 1;
            maxTurns++;
        } else
            getPlayerTurn(1);
    } else {
        printf("Player 2: make your move\n");
        scanf("%d %d", &x, &y);
        if (isValid(x, y) == 1) {
            x -= 1;
            y -= 1;
            maxTurns++;
        } else
            getPlayerTurn(2);
    }
}

// Bug:wasn't resetting the board so I added an else to reset the board
void setGameState(int x, int y, int player)
{
    if (player == 1) {
        board[x][y] = 1;
    } else if (player == 2) {
        board[x][y] = 2;
    } else {
        // Resetting
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                board[i][j] = 0;
            }
        }
    }
}

// Bug: did not print out the correct table/ coordinate issue
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

// Bug: Didn't account for the computer's turn which caused checkDraw() to not work
void computerInput()
{
    time_t t;
    srand((unsigned)time(&t));
    x = rand() % 3;
    y = rand() % 3;

    while (board[x][y] != 0) {
        x = rand() % 3;
        y = rand() % 3;
    }
    maxTurns++;
    printf("Computer: makes their move\n%d %d\n", x + 1, y + 1);
}

// Change: Decided to substract 1 from the coords to fix the issue with misalignment
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
