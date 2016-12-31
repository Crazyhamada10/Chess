#include <stdio.h>
#include <math.h>
#include "board.h"
#include <windows.h>

int knights (int x,int y)
{
    if (abs(x) == abs(y) + 1 && (x == 2 || x == -2))
        return 1;
    if (abs(y) == abs(x) + 1 && (y == 2 || y == -2))
        return 1;
    else
        return 0;
}

int bishops (int x,int y,int y1,int x1)
{
    if (abs(x) == abs (y))
    {
        int y2 = y1 - y;
        int x2 = x1 + x;
        int relation1 = x1 - (7-y1);
        int relation2 = x2 - (7-y2);
        if (y > 0 && x > 0/*y +ve (y1>y2)and x+ve (x2>x1) */)
        {
            for (int i = (8-y1); i < (7-y2);i++)
            {
                if (chess[i+relation1][i] != '.' && chess[i+relation1][i] != '-')
                {
                    colour_it("red");
                    printf("There is a piece on your way\n");
                    colour_it("white");
                    i = 7-y2;
                    return 0;
                }
            }
            return 1;
        }
        else if (y > 0 && x < 0/*y +ve (y1>y2)and x-ve (x1>x2) */)
        {
            int even = 0;
            for (int i = (8-y1); i < (7-y2);i++)
            {
                even +=2;
                if (chess[i+relation1-even][i] != '.' && chess[i+relation1-even][i] != '-')
                {
                    colour_it("red");
                    printf("There is a piece on your way\n");
                    colour_it("white");
                    i = 7-y2;
                    return 0;
                }
            }
            return 1;
        }
        else if (y < 0 && x > 0/*y -ve (y2>y1)and x+ve (x2>x1)*/)
        {
            int even = 0;
            for (int i = (8-y2); i < (7-y1);i++)
            {
                even +=2;
                if (chess[i+relation2-even][i] != '.' && chess[i+relation2-even][i] != '-')
                {
                    colour_it("red");
                    printf("There is a piece on your way\n");
                    colour_it("white");
                    i = 7-y1;
                    return 0;
                }
            }
            return 1;
        }
        else /*y -ve (y2>y1)and x -ve (x1>x2)*/
        {
            for (int i = (8-y2); i < (7-y1);i++)
            {
                if (chess[i+relation2][i] != '.' && chess[i+relation2][i] != '-')
                {
                    colour_it("red");
                    printf("There is a piece on your way\n");
                    colour_it("white");
                    i = 7-y1;
                    return 0;
                }
            }
            return 1;
        }
    }
    else
        return 0;
}

int rooks (int x, int y,int y1,int x1)
{
    if (x == 0 || y == 0)
    {
        if (x == 0)
        {
            int y2 = y1-y;
            if (y < 0)
            {
                for (int i = (8-y2); i < (7-y1); i++)
                {
                    if (chess[x1][i] != '.' && chess[x1][i] != '-')
                    {
                         colour_it("red");
                        printf("There is a piece on your way\n");
                        colour_it("white");
                        i = 7-y1;
                        return 0;
                    }
                }
                return 1;
            }
            else
            {
                for (int i = (8-y1); i < (7-y2); i++)
                {
                    if (chess[x1][i] != '.' && chess[x1][i] != '-')
                    {
                        colour_it("red");
                        printf("There is a piece on your way\n");
                        colour_it("white");
                        i = 7-y2;
                        return 0;
                    }
                }
                return 1;
            }
        }
        else
        {
            int x2 = x1 + x;
            if (x < 0)
            {
                for (int i = x2+1; i < x1; i++)
                {
                    if (chess[i][7-y1] != '.' && chess[i][7-y1] != '-')
                    {
                        colour_it("red");
                        printf("There is a piece on your way\n");
                        colour_it("white");
                        i = x1;
                        return 0;
                    }
                }
                return 1;
            }
            else
            {
                for (int i = x1+1; i < x2; i++)
                {
                    if (chess[i][7-y1] != '.' && chess[i][7-y1] != '-')
                    {
                         colour_it("red");
                        printf("There is a piece on your way\n");
                        colour_it("white");
                        i = x2;
                        return 0;
                    }
                }
                return 1;
            }
        }
    }
    else
        return 0;
}

int queen (int x, int y,int y1,int x1)
{
    if (x == 0 || y == 0)
    {
        if (x == 0)
        {
            int y2 = y1-y;
            if (y < 0)
            {
                for (int i = (8-y2); i < (7-y1); i++)
                {
                    if (chess[x1][i] != '.' && chess[x1][i] != '-')
                    {
                         colour_it("red");
                        printf("There is a piece on your way\n");
                        colour_it("white");
                        i = 7-y1;
                        return 0;
                    }
                }
                return 1;
            }
            else
            {
                for (int i = (8-y1); i < (7-y2); i++)
                {
                    if (chess[x1][i] != '.' && chess[x1][i] != '-')
                    {
                         colour_it("red");
                        printf("There is a piece on your way\n");
                        colour_it("white");
                        i = 7-y2;
                        return 0;
                    }
                }
                return 1;
            }
        }
        else
        {
            int x2 = x1 + x;
            if (x < 0)
            {
                for (int i = x2+1; i < x1; i++)
                {
                    if (chess[i][7-y1] != '.' && chess[i][7-y1] != '-')
                    {
                         colour_it("red");
                        printf("There is a piece on your way\n");
                        colour_it("white");
                        i = x1;
                        return 0;
                    }
                }
                return 1;
            }
            else
            {
                for (int i = x1+1; i < x2; i++)
                {
                    if (chess[i][7-y1] != '.' && chess[i][7-y1] != '-')
                    {
                         colour_it("red");
                        printf("There is a piece on your way\n");
                        colour_it("white");
                        i = x2;
                        return 0;
                    }
                }
                return 1;
            }
        }
    }
    else if (abs(x) == abs(y))
    {
        int y2 = y1 - y;
        int x2 = x1 + x;
        int relation1 = x1 - (7-y1);
        int relation2 = x2 - (7-y2);
        if (y > 0 && x > 0/*y +ve (y1>y2)and x+ve (x2>x1) */)
        {
            for (int i = (8-y1); i < (7-y2);i++)
            {
                if (chess[i+relation1][i] != '.' && chess[i+relation1][i] != '-')
                {
                     colour_it("red");
                    printf("There is a piece on your way\n");
                    colour_it("white");
                    i = 7-y2;
                    return 0;
                }
            }
            return 1;
        }
        else if (y > 0 && x < 0/*y +ve (y1>y2)and x-ve (x1>x2) */)
        {
            int even = 0;
            for (int i = (8-y1); i < (7-y2);i++)
            {
                even +=2;
                if (chess[i+relation1-even][i] != '.' && chess[i+relation1-even][i] != '-')
                {
                     colour_it("red");
                    printf("There is a piece on your way\n");
                    colour_it("white");
                    i = 7-y2;
                    return 0;
                }
            }
            return 1;
        }
        else if (y < 0 && x > 0/*y -ve (y2>y1)and x+ve (x2>x1)*/)
        {
            int even = 0;
            for (int i = (8-y2); i < (7-y1);i++)
            {
                even +=2;
                if (chess[i+relation2-even][i] != '.' && chess[i+relation2-even][i] != '-')
                {
                     colour_it("red");
                    printf("There is a piece on your way\n");
                    colour_it("white");
                    i = 7-y1;
                    return 0;
                }
            }
            return 1;
        }
        else /*y -ve (y2>y1)and x -ve (x1>x2)*/
        {
            for (int i = (8-y2); i < (7-y1);i++)
            {
                if (chess[i+relation2][i] != '.' && chess[i+relation2][i] != '-')
                {
                     colour_it("red");
                    printf("There is a piece on your way\n");
                    colour_it("white");
                    i = 7-y1;
                    return 0;
                }
            }
            return 1;
        }
    }
    else
        return 0;
}

int king (int x,int y)
{
    if ((abs(x) == 1 && y == 0) || (abs(x) == 1 && abs(y) == 1) || (x == 0 && abs(y) == 1))
        return 1;
    else
        return 0;
}

int pawns(int x,int y,int x2,int y2)
{
    if (counter % 2 == 1)
    {
        if (y == -2 && x == 0 && input[1] == '2' && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && (chess[x2][8-y2] == '.' || chess[x2][8-y2] == '-'))
            return 1;
        else if (y == -1 && x == 0 && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-'))
        {
            int y1 = input[1] - '1';
            if (y1 == 6 && y2 == 7)
            {
                 colour_it("red");
                printf("You don't enter promotion piece\n");
                colour_it("white");
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else if (y == -1 && abs(x) == 1 && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-')
        {
            int y1 = input[1] - '1';
            if (y1 == 6 && y2 == 7)
            {
                 colour_it("red");
                printf("You don't enter promotion piece\n");
                colour_it("white");
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
            return 0;
    }
    else
    {
        if (y == 2 && x == 0 && input[1] == '7' && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && (chess[x2][6-y2] == '.' || chess[x2][6-y2] == '-'))
            return 1;
        else if (y == 1 && x == 0 && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-'))
        {
            int y1 = input[1] - '1';
            if (y1 == 1 && y2 == 0)
            {
                colour_it("red");
                printf("You don't enter promotion piece\n");
                colour_it("white");
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else if (y == 1 && abs(x) == 1 && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-')
        {
            int y1 = input[1] - '1';
            if (y1 == 1 && y2 == 0)
            {
                 colour_it("red");
                printf("You don't enter promotion piece\n");
                colour_it("white");
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
            return 0;
    }
}

int pawns_promotion (int x1,int y1,int x2,int y2)
{
    if (counter % 2 == 1)
    {
        int x = x2-x1;
        int y = y1-y2;
        if (chess[x1][7-y1] == 'p' && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && x == 0 && y == -1 && y1 == 6 && y2 == 7)
            return 1;
        else if (chess[x1][7-y1] == 'p' && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-' && abs(x) == 1 && y == -1 && y1 == 6 && y2 == 7)
            return 1;
        else
            return 0;
    }
    else
    {
        int x = x2-x1;
        int y = y1-y2;
        if (chess[x1][7-y1] == 'P' && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && x == 0 && y == 1 && y1 == 1 && y2 == 0)
            return 1;
        else if (chess[x1][7-y1] == 'P' && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-' && abs(x) == 1 && y == 1 && y1 == 1 && y2 == 0)
            return 1;
        else
            return 0;
    }
}

int check_myself()
{
    if (counter%2 ==1)
    {
        int xking=0,yking=0;
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'k')
                {
                    xking=i;
                    yking=j;
                    j=8;
                    i=8;
                }
            }
        }
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'P' || chess[i][j] == 'N' || chess[i][j] == 'R' || chess[i][j] == 'Q' || chess[i][j] == 'B')
                {
                    counter++;
                    check = checkmate_input(chess[i][j],i,7-j,xking,7-yking);
                    counter--;
                    if (check == 1)
                    {
                        colour_it("red");
                        printf("Invalid move: You are still Check\n");
                        colour_it("white");
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
    else /*player 2*/
    {
        int xking=0,yking=0;
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'K')
                {
                    xking=i;
                    yking=j;
                    j=8;
                    i=8;
                }
            }
        }
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'p' || chess[i][j] == 'n' || chess[i][j] == 'r' || chess[i][j] == 'q' || chess[i][j] == 'b')
                {
                    counter++;
                    check = checkmate_input(chess[i][j],i,7-j,xking,7-yking);
                    counter--;
                    if (check == 1)
                    {
                        colour_it("red");
                        printf("Invalid move: You are still Check\n");
                        colour_it("white");
                        return 0;
                    }
                }
            }
        }
        return 1;
    }
}

int probability_of_movement()
{
    if (counter % 2 == 1)
    {
        int flag_check = 0;
        int exist = 0;
        int x2,y2;
        int x1,y1;
        for (int i = 0;i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (chess[i][j] == 'k' || chess[i][j] == 'p' || chess[i][j] == 'n' || chess[i][j] == 'b' || chess[i][j] == 'r' || chess[i][j] == 'q')
                {
                    x1 = i;
                    y1 = 7-j;
                    for (int q = 0;q<8;q++)
                    {
                        for (int w =0;w<8;w++)
                        {
                            flag_check =0;
                            exist = 0;
                            x2 = q;
                            y2 = 7-w;
                            int x = x2 - x1;
                            int y = y1 - y2;
                            if (chess[x2][7-y2] == 'k' || chess[x2][7-y2] == 'q' || chess[x2][7-y2] == 'r' || chess[x2][7-y2] == 'p' || chess[x2][7-y2] == 'b' || chess[x2][7-y2] == 'n')
                            {
                                flag_check = 0;
                            }
                            else
                            {
                                switch (chess[i][j])
                                {
                                case 'p':
                                    if (pawns_check(x,y,x2,y2) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'k':
                                    if ((abs(x) == 1 && y == 0) || (abs(x) == 1 && abs(y) == 1) || (x == 0 && abs(y) == 1))
                                    {
                                       exist = 1;
                                       flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'n':
                                    if ((abs(x) == abs(y) + 1 && (x == 2 || x == -2)) || (abs(y) == abs(x) + 1 && (y == 2 || y == -2)))
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'r':
                                    if (rooks_check (x,y,y1,x1) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'b':
                                    if (bishops_check (x,y,y1,x1) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'q':
                                    if (queen_check (x,y,y1,x1) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                }
                            }
                            if (flag_check == 0 && exist == 1)
                            {
                                w = 8;q = 8;i = 8;j = 8;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        return 1;
    }
    else
    {
        int flag_check = 0;
        int exist = 0;
        int x2,y2;
        int x1,y1;
        for (int i = 0;i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (chess[i][j] == 'K' || chess[i][j] == 'P' || chess[i][j] == 'N' || chess[i][j] == 'B' || chess[i][j] == 'R' || chess[i][j] == 'Q')
                {
                    x1 = i;
                    y1 = 7-j;
                    for (int q = 0;q<8;q++)
                    {
                        for (int w =0;w<8;w++)
                        {
                            flag_check =0;
                            exist = 0;
                            x2 = q;
                            y2 = 7-w;
                            int x = x2 - x1;
                            int y = y1 - y2;
                            if (chess[x2][7-y2] == 'K' || chess[x2][7-y2] == 'Q' || chess[x2][7-y2] == 'R' || chess[x2][7-y2] == 'P' || chess[x2][7-y2] == 'B' || chess[x2][7-y2] == 'N')
                            {
                                flag_check = 0;
                            }
                            else
                            {
                                switch (chess[i][j])
                                {
                                case 'P':
                                    if (pawns_check(x,y,x2,y2) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'K':
                                    if ((abs(x) == 1 && y == 0) || (abs(x) == 1 && abs(y) == 1) || (x == 0 && abs(y) == 1))
                                    {
                                       exist = 1;
                                       flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'N':
                                    if ((abs(x) == abs(y) + 1 && (x == 2 || x == -2)) || (abs(y) == abs(x) + 1 && (y == 2 || y == -2)))
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'R':
                                    if (rooks_check (x,y,y1,x1) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'B':
                                    if (bishops_check (x,y,y1,x1) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                case 'Q':
                                    if (queen_check (x,y,y1,x1) == 1)
                                    {
                                        exist = 1;
                                        flag_check = change_board_structure_for_checkmate (x1,y1,x2,y2);
                                    }
                                    break;
                                }
                            }
                            if (flag_check == 0 && exist == 1)
                            {
                                w = 8;q = 8;i = 8;j = 8;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        return 1;
    }
}

int change_board_structure_for_checkmate(int x1,int y1,int x2,int y2)
{
        char flash1 = chess[x1][7-y1], flash2 = chess[x2][7-y2];
        if((x1+y1)%2==0)
        {
            chess[x2][7-y2] = chess[x1][7-y1];
            chess[x1][7-y1]='-';
        }
        else
        {
            chess[x2][7-y2]=chess[x1][7-y1];
            chess[x1][7-y1]='.';
        }

        int flash = checkmate();
        chess[x2][7-y2] = flash2;
        chess[x1][7-y1] = flash1;
        return flash;
}

int checkmate ()
{
    if (counter%2 ==1)
    {
        int xking=0,yking=0;
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'k')
                {
                    xking=i;
                    yking=j;
                    j=8;
                    i=8;
                }
            }
        }
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'P' || chess[i][j] == 'N' || chess[i][j] == 'R' || chess[i][j] == 'Q' || chess[i][j] == 'B')
                {
                    counter++;
                    int check = checkmate_input(chess[i][j],i,7-j,xking,7-yking);
                    counter--;
                    if (check == 1)
                    {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
    else /*player 2*/
    {
        int xking=0,yking=0;
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'K')
                {
                    xking=i;
                    yking=j;
                    j=8;
                    i=8;
                }
            }
        }
        for (int i =0;i < 8;i++)
        {
            for (int j =0;j<8;j++)
            {
                if (chess[i][j] == 'p' || chess[i][j] == 'n' || chess[i][j] == 'r' || chess[i][j] == 'q' || chess[i][j] == 'b')
                {
                    counter++;
                    int check = checkmate_input(chess[i][j],i,7-j,xking,7-yking);
                    counter--;
                    if (check == 1)
                    {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
}

int pawns_check(int x,int y,int x2,int y2)
{
    if (counter % 2 == 1)
    {
        if (y == -2 && x == 0 && input[1] == '2' && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && (chess[x2][8-y2] == '.' || chess[x2][8-y2] == '-'))
            return 1;
        else if (y == -1 && x == 0 && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-'))
            return 1;
        else if (y == -1 && abs(x) == 1 && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-')
            return 1;
        else
            return 0;
    }
    else
    {
        if (y == 2 && x == 0 && input[1] == '7' && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-') && (chess[x2][6-y2] == '.' || chess[x2][6-y2] == '-'))
            return 1;
        else if (y == 1 && x == 0 && (chess[x2][7-y2] == '.' || chess[x2][7-y2] == '-'))
            return 1;
        else if (y == 1 && abs(x) == 1 && chess[x2][7-y2] != '.' && chess[x2][7-y2] != '-')
            return 1;
        else
            return 0;
    }
}

int rooks_check (int x, int y,int y1,int x1)
{
    if (x == 0 || y == 0)
    {
        if (x == 0)
        {
            int y2 = y1-y;
            if (y < 0)
            {
                for (int i = (8-y2); i < (7-y1); i++)
                {
                    if (chess[x1][i] != '.' && chess[x1][i] != '-')
                    {
                        i = 7-y1;
                        return 0;
                    }
                }
                return 1;
            }
            else
            {
                for (int i = (8-y1); i < (7-y2); i++)
                {
                    if (chess[x1][i] != '.' && chess[x1][i] != '-')
                    {
                        i = 7-y2;
                        return 0;
                    }
                }
                return 1;
            }
        }
        else
        {
            int x2 = x1 + x;
            if (x < 0)
            {
                for (int i = x2+1; i < x1; i++)
                {
                    if (chess[i][7-y1] != '.' && chess[i][7-y1] != '-')
                    {
                        i = x1;
                        return 0;
                    }
                }
                return 1;
            }
            else
            {
                for (int i = x1+1; i < x2; i++)
                {
                    if (chess[i][7-y1] != '.' && chess[i][7-y1] != '-')
                    {
                        i = x2;
                        return 0;
                    }
                }
                return 1;
            }
        }
    }
    else
        return 0;
}

int bishops_check (int x,int y,int y1,int x1)
{
    if (abs(x) == abs (y))
    {
        int y2 = y1 - y;
        int x2 = x1 + x;
        int relation1 = x1 - (7-y1);
        int relation2 = x2 - (7-y2);
        if (y > 0 && x > 0/*y +ve (y1>y2)and x+ve (x2>x1) */)
        {
            for (int i = (8-y1); i < (7-y2);i++)
            {
                if (chess[i+relation1][i] != '.' && chess[i+relation1][i] != '-')
                {
                    i = 7-y2;
                    return 0;
                }
            }
            return 1;
        }
        else if (y > 0 && x < 0/*y +ve (y1>y2)and x-ve (x1>x2) */)
        {
            int even = 0;
            for (int i = (8-y1); i < (7-y2);i++)
            {
                even +=2;
                if (chess[i+relation1-even][i] != '.' && chess[i+relation1-even][i] != '-')
                {
                    i = 7-y2;
                    return 0;
                }
            }
            return 1;
        }
        else if (y < 0 && x > 0/*y -ve (y2>y1)and x+ve (x2>x1)*/)
        {
            int even = 0;
            for (int i = (8-y2); i < (7-y1);i++)
            {
                even +=2;
                if (chess[i+relation2-even][i] != '.' && chess[i+relation2-even][i] != '-')
                {
                    i = 7-y1;
                    return 0;
                }
            }
            return 1;
        }
        else /*y -ve (y2>y1)and x -ve (x1>x2)*/
        {
            for (int i = (8-y2); i < (7-y1);i++)
            {
                if (chess[i+relation2][i] != '.' && chess[i+relation2][i] != '-')
                {
                    i = 7-y1;
                    return 0;
                }
            }
            return 1;
        }
    }
    else
        return 0;
}

int queen_check (int x,int y,int y1,int x1)
{
    if (x == 0 || y == 0)
    {
        if (x == 0)
        {
            int y2 = y1-y;
            if (y < 0)
            {
                for (int i = (8-y2); i < (7-y1); i++)
                {
                    if (chess[x1][i] != '.' && chess[x1][i] != '-')
                    {
                        i = 7-y1;
                        return 0;
                    }
                }
                return 1;
            }
            else
            {
                for (int i = (8-y1); i < (7-y2); i++)
                {
                    if (chess[x1][i] != '.' && chess[x1][i] != '-')
                    {
                        i = 7-y2;
                        return 0;
                    }
                }
                return 1;
            }
        }
        else
        {
            int x2 = x1 + x;
            if (x < 0)
            {
                for (int i = x2+1; i < x1; i++)
                {
                    if (chess[i][7-y1] != '.' && chess[i][7-y1] != '-')
                    {
                        i = x1;
                        return 0;
                    }
                }
                return 1;
            }
            else
            {
                for (int i = x1+1; i < x2; i++)
                {
                    if (chess[i][7-y1] != '.' && chess[i][7-y1] != '-')
                    {
                        i = x2;
                        return 0;
                    }
                }
                return 1;
            }
        }
    }
    else if (abs(x) == abs(y))
    {
        int y2 = y1 - y;
        int x2 = x1 + x;
        int relation1 = x1 - (7-y1);
        int relation2 = x2 - (7-y2);
        if (y > 0 && x > 0/*y +ve (y1>y2)and x+ve (x2>x1) */)
        {
            for (int i = (8-y1); i < (7-y2);i++)
            {
                if (chess[i+relation1][i] != '.' && chess[i+relation1][i] != '-')
                {
                    i = 7-y2;
                    return 0;
                }
            }
            return 1;
        }
        else if (y > 0 && x < 0/*y +ve (y1>y2)and x-ve (x1>x2) */)
        {
            int even = 0;
            for (int i = (8-y1); i < (7-y2);i++)
            {
                even +=2;
                if (chess[i+relation1-even][i] != '.' && chess[i+relation1-even][i] != '-')
                {
                    i = 7-y2;
                    return 0;
                }
            }
            return 1;
        }
        else if (y < 0 && x > 0/*y -ve (y2>y1)and x+ve (x2>x1)*/)
        {
            int even = 0;
            for (int i = (8-y2); i < (7-y1);i++)
            {
                even +=2;
                if (chess[i+relation2-even][i] != '.' && chess[i+relation2-even][i] != '-')
                {
                    i = 7-y1;
                    return 0;
                }
            }
            return 1;
        }
        else /*y -ve (y2>y1)and x -ve (x1>x2)*/
        {
            for (int i = (8-y2); i < (7-y1);i++)
            {
                if (chess[i+relation2][i] != '.' && chess[i+relation2][i] != '-')
                {
                    i = 7-y1;
                    return 0;
                }
            }
            return 1;
        }
    }
    else
        return 0;
}


