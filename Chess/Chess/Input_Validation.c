#include <stdio.h>
#include "board.h"
#include "movement.h"
#include <windows.h>


void Get_Input()
{
    if (counter % 2 == 0)
    {
        colour_it("blue");
        printf("Player two move: ");
        colour_it("white");
    }
    else
    {
        colour_it("yellow");
        printf("Player one move: ");
        colour_it("white");
    }

    int flag = 0,i = -1;
    do
    {
        for (int j =0;j<=i;j++)
            input[j] = '\0';
        if (i!= -1)
        {
            colour_it("red");
            printf("Retry : ");
            colour_it("white");
        }
        i =-1;
        fflush(stdin);
        while (input [i] != '\n')
        {
            i++;
            scanf("%c", &input[i]);
        }
        if ((input[0] == 'S' || input[0] == 'L' || input[0] == 'U' || input[0] == 'R' || input[0] == 'Q') && input[1] == '\n')
        {
            flag = 1;
            i = -1;
            switch (input[0])
            {
            case 'S':
                save();
                break;
            case 'L':
                load_inside();
                break;
            case 'U':
                undo();
                break;
            case 'R':
                redo();
                break;
            case 'Q':
                flag1 = 1;
                flag = 0;
                break;
            }
            if (counter % 2 == 0 && input[0] != 'Q')
            {
                colour_it("blue");
                printf("Player two move: ");
                colour_it("white");
            }
            else if (input[0] != 'Q')
            {
                colour_it("yellow");
                printf("Player one move: ");
                colour_it("white");
            }
        }
        else if (input[0] < 'A' || input[0] > 'H' || input[2] < 'A' || input[2] > 'H' || input[1] < '1' || input[1] > '8' || input[3] < '1' || input[3] > '8')
        {
            colour_it("red");
            printf("Invalid Input\n");
            colour_it("white");
            flag = 1;
        }
        else if ((input[4] == 'r' || input[4] == 'n' || input[4] == 'b' || input[4] == 'q') && input[5] == '\n' && counter%2 == 1)
        {
            //Promotion
            int x1 = input[0] - 'A';
            int x2 = input[2] - 'A';
            int y1 = input[1] - '1';
            int y2 = input[3] - '1';
            flag = pawns_promotion(x1,y1,x2,y2);
            if (flag == 1)
                flag = 0;
            else
                flag = 1;
        }
        else if ((input[4] == 'R' || input[4] == 'N' || input[4] == 'B' || input[4] == 'Q') && input[5] == '\n' && counter%2 == 0)
        {
            /*promote*/
            int x1 = input[0] - 'A';
            int x2 = input[2] - 'A';
            int y1 = input[1] - '1';
            int y2 = input[3] - '1';
            flag = pawns_promotion(x1,y1,x2,y2);
            if (flag == 1)
                flag = 0;
            else
                flag = 1;
        }
        else if (input[4] != '\n')
        {
            colour_it("red");
            printf("Invalid Input\n");
            colour_it("white");
            flag = 1;
        }
        else
        {
            int x1 = input[0] - 'A';
            int x2 = input[2] - 'A';
            int y1 = input[1] - '1';
            int y2 = input[3] - '1';
            int x = x2 - x1;
            int y = y1 - y2;
            if (counter % 2 == 0)/*player2*/
            {
                /*check inside square*/
                if (chess[x1][7-y1] !=  'K' && chess[x1][7-y1] !=  'Q' && chess[x1][7-y1] !=  'R' && chess[x1][7-y1] !=  'P' && chess[x1][7-y1] !=  'B' && chess[x1][7-y1] !=  'N')
                {
                    colour_it("red");
                    printf("Invalid move: There is nothing in the square or its not your piece\n");
                    colour_it("white");
                    flag = 1;
                }
                /*check to the new square*/
                else if (chess[x2][7-y2] == 'K' || chess[x2][7-y2] == 'Q' || chess[x2][7-y2] == 'R' || chess[x2][7-y2] == 'P' || chess[x2][7-y2] == 'B' || chess[x2][7-y2] == 'N')
                {
                    colour_it("red");
                    printf("Invalid move: You want to put two of your pieces in the same square\n");
                    colour_it("white");
                    flag = 1;
                }
                else
                {
                    /*make if and check about check mate before moving*/
                    switch (chess[x1][7-y1])
                    {
                    case 'K':
                            flag = king(x,y);
                            break;
                    case 'Q':
                            flag = queen(x,y,y1,x1);
                            break;
                    case 'B':
                            flag = bishops(x,y,y1,x1);
                            break;
                    case 'N':
                            flag = knights(x,y);
                            break;
                    case 'R':
                            flag = rooks(x,y,y1,x1);
                            break;
                    case 'P':
                            flag = pawns(x,y,x2,y2);
                            break;
                    }
                    if (flag == 1)
                        flag = 0;
                    else
                    {
                        flag = 1;
                        colour_it("red");
                        printf("Invalid move\n");
                        colour_it("white");
                    }
                }
            }
            else /*player1*/
            {
                /*check inside square*/
                if (chess[x1][7-y1] !=  'k' && chess[x1][7-y1] !=  'q' && chess[x1][7-y1] !=  'r' && chess[x1][7-y1] !=  'p' && chess[x1][7-y1] !=  'b' && chess[x1][7-y1] !=  'n')
                {
                    colour_it("red");
                    printf("Invalid move: There is nothing in the square or its not your piece\n");
                    colour_it("white");
                    flag = 1;
                }
                /*check to the new square*/
                else if (chess[x2][7-y2] == 'k' || chess[x2][7-y2] == 'q' || chess[x2][7-y2] == 'r' || chess[x2][7-y2] == 'p' || chess[x2][7-y2] == 'b' || chess[x2][7-y2] == 'n')
                {
                    colour_it("red");
                    printf("Invalid move: You want to put two of your pieces in the same square\n");
                    colour_it("white");
                    flag = 1;
                }
                else
                {
                    /*make if and check about check mate before moving*/
                    switch (chess[x1][7-y1])
                    {
                    case 'k':
                            flag = king(x,y);
                            break;
                    case 'q':
                            flag = queen(x,y,y1,x1);
                            break;
                    case 'b':
                            flag = bishops(x,y,y1,x1);
                            break;
                    case 'n':
                            flag = knights(x,y);
                            break;
                    case 'r':
                            flag = rooks(x,y,y1,x1);
                            break;
                    case 'p':
                            flag = pawns(x,y,x2,y2);
                            break;
                    }
                    if (flag == 1)
                        flag = 0;
                    else
                    {
                        flag = 1;
                        colour_it("red");
                        printf("Invalid move\n");
                        colour_it("white");
                    }
                }
            }
        }
    }
    while (flag == 1);
}

int checkmate_input(char piece,int x1,int y1,int x2,int y2)
{
    int flag4 =0;
    check = 0;
    int x = x2-x1;
    int y = y1-y2;
    switch (piece)
    {
    case 'N':
    case 'n':
        flag4 = knights(x,y);
        break;
    case 'Q':
    case 'q':
        flag4 = queen_check(x,y,y1,x1);
        break;
    case 'R':
    case 'r':
        flag4 = rooks_check(x,y,y1,x1);
        break;
    case 'B':
    case 'b':
        flag4 = bishops_check(x,y,y1,x1);
        break;
    case 'P':
    case 'p':
        flag4 = pawns_check(x,y,x2,y2);
        break;
    }
    if (flag4 == 1)
        return 1;
    else
        return 0;
}

