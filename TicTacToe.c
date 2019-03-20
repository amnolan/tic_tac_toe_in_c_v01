#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int static currentWinner = 0;

void printTitleCard(){
    // get variables set to open title card file
    char cwd[1024];
    //chdir("/path/to/change/directory/to");
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    char *filePath = strcat(cwd, "/tic_tac_toe_title_card.txt");
    int c;
    FILE *file;
    file = fopen(filePath, "r");
    if (file) {
        while ((c = getc(file)) != EOF)
        {
            putchar(c);
            usleep(700);
        }
        fclose(file);
    }
}

void printBoardState(char board[3][3])
{
    printf("\n    | 1 | 2 | 3 |");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j ++)
        {
            if( ( j % 3 == 0 ) )
            {
                printf("\n| %d | %c |", i + 1, board[i][j]);
            }
            else if ( ( j % 2 ) == 0 || ( (j % 2 ) == 1))
            {
                printf(" %c |", board[i][j]);
            }
            else
            {
                printf("| %c |", board[i][j]);
            }
        }
    }
}

int solidLineMade(char a, char b, char c, char board [3][3])
{
    // check for three consecutive hits
    if(a == 'X' && b == 'X' && c == 'X' )
    {
        printf("\nPlayer 1 wins!\n");
        printBoardState(board);
        return 1;
    }
    else if(a == 'O' && b == 'O' && c == 'O')
    {
        printf("\nPlayer 2 wins!\n");
        printBoardState(board);
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkWinner(char board[3][3])
{
    char a = '_';
    char b = '_';
    char c = '_';
    int i = 0;
    int j = 0;
    int retVal;

    for(i = 0; i < 3; i++)
    {
        // vertical check
        a = board[i][0];
        b = board[i][1];
        c = board[i][2];

        retVal = solidLineMade( a, b, c , board);
        if(retVal)
        {
            return retVal;
        }
    }
    for(j = 0; j < 3; j++)
    {
        // horizontal check
        a = board[0][j];
        b = board[1][j];
        c = board[2][j];

        retVal = solidLineMade( a, b, c , board);
        if(retVal)
        {
            return retVal;
        }
    }
    // diagonal check
    a = board[0][0];
    b = board[1][1];
    c = board[2][2];
    retVal = solidLineMade( a, b, c , board);
    if(retVal)
    {
       return retVal;
    }
    a = board[0][2];
    b = board[1][1];
    c = board[2][0];
    retVal = solidLineMade( a, b, c , board);
    if(retVal)
    {
       return retVal;
    }
    return retVal;
}

int game()
{
    char board[3][3];
    int turnsCounter = 0;
    // init board
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j ++)
        {
            board[i][j] = '_';
        }
    }

    int keepIterating = 0;
    int playerNum = 1;
    int indexI = 0;
    int indexJ = 0;

    printf("\nCurrent board state: \n");
    while( !keepIterating )
    {
        printBoardState(board);
        printf("\n\nType -1 to quit\n");
        if(playerNum % 2 == 0)
        {
            printf("\nPlayer 2 Type your first index (1 through 3) for the row\n");
        }
        else
        {
            printf("\nPlayer 1 Type your first index (1 through 3) for the row\n");
        }
        scanf("%d", &indexI);
        indexI = indexI - 1;
        if(indexI < 0 || indexJ < 0){ break; }
        if(playerNum % 2 == 0)
        {
            printf("\nPlayer 2 Type your first index (1 through 3) for the column\n");
        }
        else
        {
            printf("\nPlayer 1 Type your first index (1 through 3) for the column\n");
        }
        scanf("%d", &indexJ);
        indexJ = indexJ - 1;
        int goodResult = 0;
        if(indexI < 0 || indexJ < 0){ break; }
        while( goodResult == 0)
        {
            if(playerNum % 2 != 0)
            {
                if(board[indexI][indexJ] == '_')
                {
                    board[indexI][indexJ] = 'X';
                    playerNum += 1;
                    goodResult = 1;
                    keepIterating = checkWinner( board );
                    if(keepIterating){currentWinner = 1;}

                }
                else
                {
                    printf("\nSpace already occupied! Enter row:\n");
                    scanf("%d", &indexI);
                    indexI = indexI - 1;
                    printf("\nEnter column number:\n");
                    scanf("%d", &indexJ);
                    indexJ = indexJ - 1;
                    if(indexI < 0 || indexJ < 0){ break; }
                }
            }
            else
            {
                if(board[indexI][indexJ] == '_')
                {
                    board[indexI][indexJ] = 'O';
                    playerNum += 1;
                    goodResult = 1;
                    keepIterating = checkWinner( board );
                    if(keepIterating){currentWinner = 2;}
                }
                else
                {
                    printf("\nSpace already occupied! Enter row:\n");
                    scanf("%d", &indexI);
                    indexI = indexI - 1;
                    printf("\nEnter column number:\n");
                    scanf("%d", &indexJ);
                    indexJ = indexJ - 1;
                    if(indexI < 0 || indexJ < 0){ break; }
                }
            }
            turnsCounter += 1;
            if(turnsCounter == 9)
            {
                printf("\nNobody wins, cat's game!\n");
                break;
            }
        }
    }
    printf("\n\n");
    return 0;
}

int main()
{
    int scorePlayer1 = 0;
    int scorePlayer2 = 0;
    int keepPlaying = 1;

    printTitleCard();
    while( keepPlaying )
    {
        game();
        if(currentWinner == 1){ scorePlayer1++; } else if (currentWinner % 2 == 0) { scorePlayer2++; }
        printf("\n");
        printf("\nScore P1: %d", scorePlayer1);
        printf("\nScore P2: %d", scorePlayer2);
        printf("\n\nPlay again? 1 for yes, 0 for no: ");
        scanf("%d", &keepPlaying);
    }
    printf("\n\nThanks for playing!\n\n");
}
